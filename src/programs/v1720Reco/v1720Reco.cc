// bdx reconstruction software

// JANA headers
#include <JANA/JApplication.h>
using namespace jana;

// bdx headers



//factory generators
#include <system/JFactoryGenerator_system.h>
#include <system/JEventSourceBinaryDataGenerator.h>
#include <DAQ/JFactoryGenerator_DAQ.h>
#include <system/v1720EventProcessor.h>
#include <timing/JFactoryGenerator_timing.h>


#include "TH1D.h"
// C++ headers
#include <iostream>
using namespace std;




int main(int narg, char *argv[])
{
	/*A.C. If I de-comment following, RootSPy won't work!*/
	//TH1::AddDirectory(kFALSE);

	JApplication app(narg, argv);

	if(narg==1){
		app.Usage();
		return 0;
	}


	jout<<"JEventSource START"<<endl;
	app.AddEventSourceGenerator(new JEventSourceBinaryDataGenerator());
	jout<<"JEventSourceBinartDAtaGenerator DONE"<<endl;


	app.AddFactoryGenerator(new JFactoryGenerator_system());
	jout<<"JFactoryGenerator_system DONE"<<endl;
	app.AddFactoryGenerator(new JFactoryGenerator_DAQ());
	jout<<"JFactoryGenerator_DAQ DONE"<<endl;

	app.AddFactoryGenerator(new JFactoryGenerator_timing());
	jout<<"JFactoryGenerator_timing DONE"<<endl;

	app.AddProcessor(new v1720EventProcessor());
	jout<<"v1720EventProcessor DONE"<<endl;



	app.Run();

	return 1;
}


