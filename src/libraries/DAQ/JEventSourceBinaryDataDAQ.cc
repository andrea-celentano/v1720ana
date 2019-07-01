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
		evtData=new uint32_t[evtSize-1];
		fread((void*)evtData,4,evtSize-1,infile);
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

		evtData++; //ignore BoardID
		evtData++; //ignore Pattern

		jout<<*evtData<<endl; //ch
		evtData++;

		evtData++; //EventCounter
		evtData++;//TriggerTimeTag


		fac_fa250Mode1Hit->CopyTo(data);

		return NOERROR;

	}

	return OBJECT_NOT_AVAILABLE;
}

