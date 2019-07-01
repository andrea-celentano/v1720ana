#include "JEventSourceBinaryDataDAQ.h"

#include <iostream>
#include <time.h>
#include <unistd.h>
using namespace std;

// JANA headers
#include <JANA/JEvent.h>
#include <JANA/JParameterManager.h>
#include <JANA/JApplication.h>

//DAQ
#include <DAQ/fa250Mode1Hit.h>

int countOnes(uint32_t data);

// Constructor
JEventSourceBinaryDataDAQ::JEventSourceBinaryDataDAQ(const char* source_name) :
		JEventSource(source_name), infile(0) {

	jout << "JEventSourceBinaryDataDAQ creator: " << this << endl;

	jout << "Opening file: " << source_name << endl;

	//TODO: check if file exists

	if ((infile = fopen(source_name, "rb")) == NULL) {
		jout << "Error opening file";
		exit(1);
	}
	//currEventTimeSlice = 0;
	jout << "JEventSourceBinaryDataDAQ creator DONE: " << this << endl;

}

// Destructor
JEventSourceBinaryDataDAQ::~JEventSourceBinaryDataDAQ() {
	jout << " Closing input file " << source_name << " ." << endl;

}

// GetEvent
jerror_t JEventSourceBinaryDataDAQ::GetEvent(JEvent &event) {

	event.SetRef(NULL);
	uint32_t evtSize; //size of the event in number of bytes
	uint32_t *evtData;
	if (feof(infile)) {
		jout << "End of file" << endl;
		fclose(infile);
		return NO_MORE_EVENTS_IN_SOURCE;
	} else {
		//read the file
		fread((void*)(&evtSize),4,1,infile);
		evtSize=evtSize/4; //size of the event in number of 32-bit words
		evtData=new uint32_t[evtSize];
		uint32_t *evtDatap=evtData;
		*evtDatap=evtSize;
		evtDatap++;
		fread((void*)evtDatap,4,evtSize-1,infile);
		event.SetJEventSource(this);
		event.SetRef((void*)evtData);

		return NOERROR;
	}



}

// FreeEvent
void JEventSourceBinaryDataDAQ::FreeEvent(JEvent &event) {
	if (event.GetRef() != NULL) {
		delete event.GetRef();
	}
}

// GetObjects
jerror_t JEventSourceBinaryDataDAQ::GetObjects(JEvent & event, JFactory_base * factory) {
/// This gets called through the virtual method of the
/// JEventSource base class. It creates the objects of the type
/// which factory is based.

/// Example: DCsegment needs DCHit. If DCHit doesn't exist already, then
/// it will be read here.
// We must have a factory to hold the data
	if (!factory) throw RESOURCE_UNAVAILABLE;

// Get name of data class we're trying to extract
	string dataClassName = factory->GetDataClassName();
//As suggested by David, do a check on the factory type to decide what to do
	JFactory<fa250Mode1Hit> *fac_fa250Mode1Hit = dynamic_cast<JFactory<fa250Mode1Hit>*>(factory);

	//JFactory<eventData> *fac_eventData = dynamic_cast<JFactory<eventData>*>(factory);

	uint32_t *evtData=(uint32_t*)event.GetRef();

	if (fac_fa250Mode1Hit != NULL) {
		vector<fa250Mode1Hit*> data;
		fa250Mode1Hit *mfa250Mode1Hit;
		int Nch;
		int theCh;
		int chMask;
		uint32_t sample;
		uint Nsamples=(*evtData);


		evtData++; //samples
		evtData++; //ignore BoardID
		evtData++; //ignore Pattern

		chMask=*evtData; //chMask
		evtData++;

		evtData++; //EventCounter
		evtData++;//TriggerTimeTag

		Nch=countOnes(*evtData);
		Nsamples=(Nsamples)-6; //-6 due to event header. These are the 32-bit words with data. 1 word = 2 samples
		Nsamples=Nsamples*2; //the TOTAL number of samples
		Nsamples/=Nch;       //samples per channel


		for (int ich=0;ich<8;ich++){
			if ((chMask>>ich &0x1)==0) continue;
			mfa250Mode1Hit = new fa250Mode1Hit();
			mfa250Mode1Hit->m_channel=ich;
			for (int iSample=0;iSample<Nsamples/2;iSample++){
				sample=(*evtData);
				mfa250Mode1Hit->samples.push_back(sample&0xFFF);
				mfa250Mode1Hit->samples.push_back((sample>>16)&0xFFF);
			}
			data.push_back(mfa250Mode1Hit);
		}
		fac_fa250Mode1Hit->CopyTo(data);

		return NOERROR;

	}

	return OBJECT_NOT_AVAILABLE;
}

int countOnes(uint32_t data){
	int N=0;
	for (int ii=0;ii<8;ii++){
		if ((data>>ii)&0x1) N++;
	}
	return N;
}
