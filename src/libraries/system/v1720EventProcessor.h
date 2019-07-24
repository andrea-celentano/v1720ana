#ifndef _EventProcessor_
#define _EventProcessor_

// JANA headers
#include <JANA/JEventProcessor.h>
#include <JANA/JApplication.h>
#include <JANA/JEventLoop.h>
using namespace jana;

#include <vector>
#include <utility>
#include <map>
#include <algorithm>
using namespace std;
// EVIO headers
//#include "evioUtil.hxx"
//#include "evioFileChannel.hxx"
//using namespace evio;

//ROOT headers
#include "TFile.h"

class TranslationTable;
class JOutput;
class TTree;
class CataniaEventProto2;
class TEvent;

/*This class is the "main" event processor, that gets called in any case,
 * also if we use users plugins
 *
 * Here I want to handle the output in a proper way.
 */
class v1720EventProcessor: public JEventProcessor {
public:
	v1720EventProcessor();
	~v1720EventProcessor();
	const char* className(void) {
		return "v1720EventProcessor";
	} /*A.C. DO NOT TOUCH THIS!*/

	JOutput* getOutput() {
		return m_output;
	}


private:
	jerror_t init();                                 // Called once at program start.
	jerror_t brun(JEventLoop*, int32_t runnumber);       // Called everytime a new run number is detected.
	jerror_t evnt(JEventLoop*, uint64_t eventnumber);     // Called every event.
	jerror_t erun();                                 // Called everytime run number changes, provided brun has been called.
	jerror_t fini();                                 // Called after last event of last event source has been processed.



	string optf;     // Output file
	string outType, outFile;


	JOutput *m_output;
	TTree *m_tree;

	vector<double> time0,time1;


	/*Time*/
	Long64_t startTime, stopTime, deltaTime;




	int isFirstCallToBrun;

	JStreamLog bout;
	JStreamLog berr;
};

#endif

