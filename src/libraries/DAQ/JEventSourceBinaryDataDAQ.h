/*
 * JEventSourceBinaryDataDAQ.h
 *
 *  Created on: Jan 24, 2019
 *      Author: celentan
 */

#ifndef SRC_LIBRARIES_DAQ_JEVENTSOURCEBINARYDATADAQ_H_
#define SRC_LIBRARIES_DAQ_JEVENTSOURCEBINARYDATADAQ_H_

// JANA headers
#include <JANA/JEventSource.h>
#include <JANA/jerror.h>
#include <iostream>
#include <fstream>
using namespace jana;
//BinaryData headers


#define PHYSICS_EVENT_TYPE 1
#define EPICS_EVENT_TYPE 31



class JEventSourceBinaryDataDAQ: public JEventSource {
public:

	enum BinaryDataDAQSourceType {
		kNoSource, kFileSource
	};

	JEventSourceBinaryDataDAQ(const char* source_name);
	virtual ~JEventSourceBinaryDataDAQ();

	virtual const char* className(void) {
		return static_className();
	}
	static const char* static_className(void) {
		return "JEventSourceBinaryDataDAQ";
	}

	jerror_t GetEvent(JEvent &event);
	void FreeEvent(JEvent &event);
	jerror_t GetObjects(JEvent &event, JFactory_base *factory);




private:

	std::ifstream infile;
	int flagEnd;
	std::streampos infilePos;



};

#endif /* SRC_LIBRARIES_DAQ_JEVENTSOURCEBINARYDATADAQ_H_ */
