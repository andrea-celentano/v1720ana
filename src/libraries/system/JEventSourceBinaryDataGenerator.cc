// C++ headers
#include <string>
using namespace std;

// bdx headers
#include "JEventSourceBinaryDataGenerator.h"
#include <DAQ/JEventSourceBinaryDataDAQ.h>

#include <JANA/JParameterManager.h>
using namespace jana;

//---------------------------------
// Description
//---------------------------------
const char* JEventSourceBinaryDataGenerator::Description(void) {
	return "BinaryData";
}

//---------------------------------
// CheckOpenable
//---------------------------------
double JEventSourceBinaryDataGenerator::CheckOpenable(string source) {
	// This should return a value between 0 and 1 inclusive
	// with 1 indicating it definitely can read events from
	// the specified source and 0 meaning it definitely can't.
	// Typically, this will just check the file suffix.

	if (source.find(".dat") != std::string::npos) {
		std::cout << "JEventSourceBinaryDataGenerator: source name " << source << " contains \".dat\" substring. Open it" << endl;
		return 1.0;
	} else {
		std::cout << "JEventSourceBinaryDataGenerator failed on source " << source << endl;
		return 0.0;
	}
}

//---------------------------------
// MakeJEventSource
//---------------------------------
JEventSource* JEventSourceBinaryDataGenerator::MakeJEventSource(string source) {

	int m_verbose;

	m_verbose = 0;
	gPARMS->GetParameter("SYSTEM:VERBOSE", m_verbose);

	if (m_verbose > 2) jout << "JEventSourceBinaryDataGenerator::MakeJEventSource for DATA " << endl;
	return new JEventSourceBinaryDataDAQ(source.c_str());

}

