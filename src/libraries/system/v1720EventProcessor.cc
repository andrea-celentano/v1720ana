// C++ headers
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <string>
using namespace std;

// bdx headers
#include "v1720EventProcessor.h"
#include "string_utilities.h"
//DAQ
#include "DAQ/fa250Mode1Hit.h"
//timing
#include "timing/PMTHit.h"
#include "timing/TriggerHit.h"

#include "TTree.h"

#include "JOutput.h"
#include "JROOTOutput.h"

// Constructor
v1720EventProcessor::v1720EventProcessor() :
		m_output(0), deltaTime(0) {
	bout << "v1720EventProcessor creator start" << endl;
	optf = "";
	isFirstCallToBrun = 1;
	startTime = 9999999999;
	stopTime = -9999999999;

	bout.SetTag("v1720EventProcessor >>");
	berr.SetTag("v1720EventProcessorError >>");

	bout << "v1720EventProcessor creator end" << endl;
}

// Destructor
v1720EventProcessor::~v1720EventProcessor() {

}

// init
jerror_t v1720EventProcessor::init(void) {

	bout << "v1720EventProcessor::init" << endl;

	gPARMS->SetDefaultParameter("SYSTEM:OUTPUT", optf, "Set OUTPUT file type and name, using the form \"TYPE,FILENAME\". Type can be ROOT, EVIO, TXT. Example: -PSYSTEM:OUTPUT=\"ROOT,out.root\" ");
	bout << "Out string is: " << optf << endl;
	outType.assign(optf, 0, optf.find(","));
	outFile.assign(optf, optf.find(",") + 1, optf.size());

	std::transform(outType.begin(), outType.end(), outType.begin(), ::tolower);

	if (optf != "none") {
		bout << "Again, out string is: " << optf << endl;
		bout << "Out file type is: " << outType << endl;
		if (outType == "root") {
			m_output = new JROOTOutput();
		}
	} else if (outType == "evio") {
		berr << "evio not yet implemented" << endl;
	} else if (outType == "txt") {
		berr << "txt not yet implemented" << endl;
	} else {
		berr << "file type not recognized: " << outType << endl;
	}

	// lock all root operations
	japp->RootWriteLock();
	/*Event header and runInfo are always created - as memory resident TTrees (these are quite small)*/
	gDirectory->cd();
	//CREATE HERE THE TTREE


	m_tree = new TTree("tout", "tout");
	m_tree->Branch("time0", &time0);
	m_tree->Branch("ampl0", &ampl0);
	m_tree->Branch("time1",&time1);
	m_tree->Branch("Ttrg",&Ttrg);



	japp->RootUnLock();





	return NOERROR;
}

// brun
jerror_t v1720EventProcessor::brun(JEventLoop *eventLoop, uint32_t runnumber) {

	bout << "v1720EventProcessor::brun " << runnumber << "(isFirstCallToBrun: " << isFirstCallToBrun << " m_output: " << m_output << ")" << endl;

	// lock all root operations
	japp->RootWriteLock();
	if (isFirstCallToBrun) {
		if (m_output != 0) {
			bout << "got m_output, className is: " << m_output->className() << endl;
			if (strcmp(m_output->className(), "JROOTOutput") == 0) {
				JROOTOutput* m_ROOTOutput = (JROOTOutput*) m_output;
				m_ROOTOutput->OpenOutput(outFile);


				/*If an output exists, add the eventHeader and runInfo*/
				(m_ROOTOutput)->AddObject(m_tree);

			}
		}
	}


	// lock all root operations
	japp->RootUnLock();
	return NOERROR;
}

// evnt
jerror_t v1720EventProcessor::evnt(JEventLoop *loop, uint64_t eventnumber) {


	vector<const PMTHit*> hits;
	vector<const TriggerHit*> thits;


	loop->Get(hits);

	//loop->Get(thits);

	if (hits.size()==0){
		return NOERROR;
	}

//	if (thits.size()!=1){
//		jerr<<"Error on event: "<<eventnumber<<" number of trigger hits: "<<thits.size()<<endl;
//		return VALUE_OUT_OF_RANGE;
	//}

	ampl0.clear();
	time0.clear();
	time1.clear();
	for (int ii=0;ii<hits.size();ii++){
		if (hits[ii]->m_channel==0){
			ampl0.push_back(hits[ii]->m_A);
			time0.push_back(hits[ii]->m_T0);
		}
		if (hits[ii]->m_channel==1) time1.push_back(hits[ii]->m_T0);
	}
//	Ttrg=thits[0]->m_T0;

	japp->RootWriteLock();
	m_tree->Fill();
	japp->RootUnLock();


	return NOERROR;
}

// erun
jerror_t v1720EventProcessor::erun(void) {
	japp->RootWriteLock();
	deltaTime = stopTime - startTime;
	bout << "v1720EventProcessor::erun " << endl;
	bout << "Run start: " << startTime << " stop: " << stopTime << " diff: " << deltaTime << endl;
	//m_runInfo->Fill();


	japp->RootUnLock();
	return NOERROR;
}

// fini
jerror_t v1720EventProcessor::fini(void) {
	// If another EventProcessor is in the list ahead of this one, then
	// it will have finished before this is called. e.g. closed the
	// ROOT file!
	bout << "v1720EventProcessor fini called" << endl;
	fflush(stdout);
	japp->RootWriteLock();
	if (m_output) {
		m_output->CloseOutput(); /*This is ok, CloseOutput takes care of m_output already closed*/
	}
	japp->RootUnLock();
	bout << "v1720EventProcessor fini ends" << endl;
	fflush(stdout);
	return NOERROR;
}

