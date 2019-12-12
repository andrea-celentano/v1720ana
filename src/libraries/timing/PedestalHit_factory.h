// $Id$
//
//    File: PedestalHit_factory.h
// Created: Thu Nov 28 14:48:09 CET 2019
// Creator: celentan (on Linux apcx4 3.10.0-957.el7.x86_64 x86_64)
//

#ifndef _PedestalHit_factory_
#define _PedestalHit_factory_

#include <JANA/JFactory.h>
#include "PedestalHit.h"

class PedestalHit_factory:public jana::JFactory<PedestalHit>{
	public:
		PedestalHit_factory(){};
		~PedestalHit_factory(){};


	private:
		jerror_t init(void);						///< Called once at program start.
		jerror_t brun(jana::JEventLoop *eventLoop, uint32_t runnumber);	///< Called everytime a new run number is detected.
		jerror_t evnt(jana::JEventLoop *eventLoop, uint64_t eventnumber);	///< Called every event.
		jerror_t erun(void);						///< Called everytime run number changes, provided brun has been called.
		jerror_t fini(void);						///< Called after last event of last event source has been processed.

		int NPED;

};

#endif // _PedestalHit_factory_

