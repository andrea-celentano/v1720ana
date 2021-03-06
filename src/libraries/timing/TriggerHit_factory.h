// $Id$
//
//    File: TriggerHit_factory.h
// Created: Thu Nov 28 13:26:18 CET 2019
// Creator: celentan (on Linux apcx4 3.10.0-957.el7.x86_64 x86_64)
//

#ifndef _TriggerHit_factory_
#define _TriggerHit_factory_

#include <JANA/JFactory.h>
#include "TriggerHit.h"

class TF1;

class TriggerHit_factory:public jana::JFactory<TriggerHit>{
	public:
		TriggerHit_factory(){
			m_CH=1;
			m_Tstart=400.;
			m_Tstop=700.;
		};
		~TriggerHit_factory(){};


	private:
		jerror_t init(void);						///< Called once at program start.
		jerror_t brun(jana::JEventLoop *eventLoop, uint32_t runnumber);	///< Called everytime a new run number is detected.
		jerror_t evnt(jana::JEventLoop *eventLoop, uint64_t eventnumber);	///< Called every event.
		jerror_t erun(void);						///< Called everytime run number changes, provided brun has been called.
		jerror_t fini(void);						///< Called after last event of last event source has been processed.

		int m_CH;
		double  m_Tstart,m_Tstop;

		TF1 *funFit;
};

#endif // _TriggerHit_factory_

