// $Id$
//
//    File: JEventProcessor_monitoring.cc
// Created: Fri Oct  4 11:30:24 CEST 2019
// Creator: celentan (on Linux apcx4 3.10.0-957.el7.x86_64 x86_64)
//

#include "JEventProcessor_monitoring.h"
using namespace jana;

#include "timing/PMTHit.h"

#include "TH1D.h"
#include "TApplication.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include <fstream>
#include <sstream>

TApplication gui("GUI",0,NULL);

#define MAX_INTEGRALS 9

// Routine used to create our JEventProcessor
#include <JANA/JApplication.h>
#include <JANA/JFactory.h>
extern "C" {
void InitPlugin(JApplication *app) {
	InitJANAPlugin(app);
	app->AddProcessor(new JEventProcessor_monitoring());

}
} // "C"

//------------------
// JEventProcessor_monitoring (Constructor)
//------------------
JEventProcessor_monitoring::JEventProcessor_monitoring() {

	Tmin = 0;
	Tmax = 20000;
	dT = 4;
	log = 0;
	updateTime = 10;
	startTime = 0;
	thisTime = 0;

	gPARMS->SetDefaultParameter("MONITOR::TMIN", Tmin);
	gPARMS->SetDefaultParameter("MONITOR::TMAX", Tmax);
	gPARMS->SetDefaultParameter("MONITOR::DT", dT);
	gPARMS->SetDefaultParameter("MONITOR::LOG", log);

	gPARMS->SetDefaultParameter("MONITOR::UPDATE_TIME", updateTime);

	m_histoMonitor = 0;
	m_histoMonitor2 = 0;
	c_Monitor = 0;
	c_Monitor2 = 0;

	counter=0;
}

//------------------
// ~JEventProcessor_monitoring (Destructor)
//------------------
JEventProcessor_monitoring::~JEventProcessor_monitoring() {

}

//------------------
// init
//------------------
jerror_t JEventProcessor_monitoring::init(void) {
	// This is called once at program startup. If you are creating
	// and filling historgrams in this plugin, you should lock the
	// ROOT mutex like this:
	//
	// japp->RootWriteLock();
	//  ... fill historgrams or trees ...
	// japp->RootUnLock();
	//

	//open the config file
	ifstream fConfig(gPARMS->GetConfigFileName().c_str());

	string line, word;
	double intTmin, intTmax;
	while (getline(fConfig, line)) {
		stringstream iss(line);

		iss >> word;
		if (word == "INTEGRAL") {
			iss >> intTmin >> intTmax;
			cout << "INTEGRAL: " << intTmin << " " << intTmax << endl;
			integralTimes.push_back(make_pair(intTmin, intTmax));
		}
	}

	cout << "THERE ARE: " << integralTimes.size() << " integrals " << endl;
	if (integralTimes.size()>= MAX_INTEGRALS){
		cerr<<"ERROR: TOO MANY! MAX IS: "<<MAX_INTEGRALS<<endl;
		exit(1);
	}


	for (int ii=0;ii<integralTimes.size();ii++){
		integralPlots.push_back(new TGraph());
	}

	japp->RootWriteLock();
	m_histoMonitor = new TH1D("m_histoMonitor", "m_histoMonitor", int((Tmax - Tmin) / dT), Tmin, Tmax);
	m_histoMonitor2 = new TH1D("m_histoMonitor2", "m_histoMonitor2", int((Tmax - Tmin) / dT), Tmin, Tmax);
	c_Monitor = new TCanvas("cMonitor", "cMonitor", 800, 800);
	c_Monitor2 = new TCanvas("cMonitor2", "cMonitor2", 800, 800);

	if (integralPlots.size()==1){
	  c_Monitor2->Divide(1,1);
	}
	else if (integralPlots.size()==2){
	  c_Monitor2->Divide(2,1);
	} 
	else if (integralPlots.size()<=4){
	  c_Monitor2->Divide(2,2);
	}
	else if (integralPlots.size()<=9){
	  c_Monitor2->Divide(3,3);
	}
	japp->RootUnLock();

	return NOERROR;
}

//------------------
// brun
//------------------
jerror_t JEventProcessor_monitoring::brun(JEventLoop *eventLoop, uint32_t runnumber) {
	// This is called whenever the run number changes

	startTime = clock();
	return NOERROR;
}

//------------------
// evnt
//------------------
jerror_t JEventProcessor_monitoring::evnt(JEventLoop *loop, uint64_t eventnumber) {
	// This is called for every event. Use of common resources like writing
	// to a file or filling a histogram should be mutex protected. Using
	// loop->Get(...) to get reconstructed objects (and thereby activating the
	// reconstruction algorithm) should be done outside of any mutex lock
	// since multiple threads may call this method at the same time.
	// Here's an example:
	//
	// vector<const MyDataClass*> mydataclasses;
	// loop->Get(mydataclasses);
	//
	// japp->RootWriteLock();
	//  ... fill historgrams or trees ...
	// japp->RootUnLock();

	vector<const PMTHit *> pmtHits;
	vector<const PMTHit *>::iterator pmtHits_it;
	const PMTHit* pmtHit;
	double intTmin,intTmax,val;
	loop->Get(pmtHits);

	for (pmtHits_it = pmtHits.begin(); pmtHits_it != pmtHits.end(); pmtHits_it++) {
		pmtHit = *pmtHits_it;
		japp->RootWriteLock();
		m_histoMonitor->Fill(pmtHit->m_T0);
		m_histoMonitor2->Fill(pmtHit->m_T0);
		japp->RootUnLock();
	}

	thisTime = clock();

	if (((thisTime - startTime) / CLOCKS_PER_SEC) > updateTime) {
		startTime = thisTime;

		for (int ii=0;ii<integralTimes.size();ii++){
			intTmin=integralTimes[ii].first;
			intTmax=integralTimes[ii].second;
			val=m_histoMonitor2->Integral(m_histoMonitor2->FindBin(intTmin),m_histoMonitor2->FindBin(intTmax));
			integralPlots[ii]->SetPoint(counter,counter*updateTime,val);
		}

		counter++;





		japp->RootWriteLock();
		c_Monitor->cd();
		if (log) {
			c_Monitor->SetLogy();
		}
		m_histoMonitor->Draw();
		c_Monitor->Modified();
		c_Monitor->Update();

		for (int ii=0;ii<integralTimes.size();ii++){
			c_Monitor2->cd(ii+1);
			integralPlots[ii]->Draw();
		}
		c_Monitor2->Modified();
		c_Monitor2->Update();
		m_histoMonitor2->Reset();
		japp->RootUnLock();
	}

	return NOERROR;
}

//------------------
// erun
//------------------
jerror_t JEventProcessor_monitoring::erun(void) {
	// This is called whenever the run number changes, before it is
	// changed to give you a chance to clean up before processing
	// events from the next run number.
	return NOERROR;
}

//------------------
// fini
//------------------
jerror_t JEventProcessor_monitoring::fini(void) {
	// Called before program exit after event processing is finished.
	return NOERROR;
}

