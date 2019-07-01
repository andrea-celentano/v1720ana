#ifndef _JEventSourceGenerator_BinaryData_
#define _JEventSourceGenerator_BinaryData_

// JANA headers
#include "JANA/JEventSourceGenerator.h"
using namespace jana;

class JEventSourceBinaryDataGenerator: public JEventSourceGenerator{
	public:
		JEventSourceBinaryDataGenerator(){}
		virtual ~JEventSourceBinaryDataGenerator(){}


		virtual const char* className(void){return static_className();}
		static const char* static_className(void){return "JEventSourceBinaryDataGenerator";}
		
		const char* Description(void);
		double CheckOpenable(string source);

		jana::JEventSource* MakeJEventSource(string source);
};

#endif // _JEventSourceGenerator_BinaryData_

