// $Id$
//
//    File: JFactoryGenerator_timing.h
// Created: Tue Jan 12 11:28:22 CET 2016
// Creator: celentan (on Linux apcx4 2.6.32-504.30.3.el6.x86_64 x86_64)
//

#ifndef _JFactoryGenerator_timing_
#define _JFactoryGenerator_timing_

#include <JANA/jerror.h>
#include <JANA/JFactoryGenerator.h>
#include "PMTHit_factory.h"
#include "TriggerHit_factory.h"
#include "PedestalHit_factory.h"
#include "PMTTimeFit_factory.h"

class JFactoryGenerator_timing: public jana::JFactoryGenerator {
public:
	JFactoryGenerator_timing() {
	}
	virtual ~JFactoryGenerator_timing() {
	}
	virtual const char* className(void) {
		return static_className();
	}
	static const char* static_className(void) {
		return "JFactoryGenerator_timing";
	}

	jerror_t GenerateFactories(jana::JEventLoop *loop) {

		loop->AddFactory(new PMTHit_factory());
		loop->AddFactory(new TriggerHit_factory());
		loop->AddFactory(new PedestalHit_factory());
		loop->AddFactory(new PMTTimeFit_factory());
		return NOERROR;
	}

};

#endif // _JFactoryGenerator_timing_

