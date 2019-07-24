// $Id$
//
//    File: PMTHit_factory.h
// Created: Tue Jul  2 09:51:21 CEST 2019
// Creator: celentan (on Linux apcx4 3.10.0-957.el7.x86_64 x86_64)
//

#ifndef _PMTHit_factory_
#define _PMTHit_factory_

#include <JANA/JFactory.h>
#include "PMTHit.h"

class PMTHit_factory:public jana::JFactory<PMTHit>{
	public:
		PMTHit_factory();
		~PMTHit_factory(){};


	private:
		jerror_t init(void);						///< Called once at program start.
		jerror_t brun(jana::JEventLoop *eventLoop, uint32_t runnumber);	///< Called everytime a new run number is detected.
		jerror_t evnt(jana::JEventLoop *eventLoop, uint64_t eventnumber);	///< Called every event.
		jerror_t erun(void);						///< Called everytime run number changes, provided brun has been called.
		jerror_t fini(void);						///< Called after last event of last event source has been processed.


		double m_THR[8];
		int m_preHit; //number of samples to include before THR
		int m_postHit;//number of samples to include after THR

		int m_polarity; //0 is POSITIVE, 1 is NEGATIVE



};

#endif // _PMTHit_factory_

