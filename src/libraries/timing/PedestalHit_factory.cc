// $Id$
//
//    File: PedestalHit_factory.cc
// Created: Thu Nov 28 14:48:09 CET 2019
// Creator: celentan (on Linux apcx4 3.10.0-957.el7.x86_64 x86_64)
//

#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

#include "PedestalHit_factory.h"
#include "DAQ/fa250Mode1CalibPedSubHit.h"
using namespace jana;

//------------------
// init
//------------------
jerror_t PedestalHit_factory::init(void) {

	NPED=20;
	return NOERROR;
}

//------------------
// brun
//------------------
jerror_t PedestalHit_factory::brun(jana::JEventLoop *eventLoop, uint32_t runnumber) {
	return NOERROR;
}

//------------------
// evnt
//------------------
jerror_t PedestalHit_factory::evnt(JEventLoop *loop, uint64_t eventnumber) {

	// Code to generate factory data goes here. Add it like:
	//
	PedestalHit *mPedestalHit;
	double mean,rms;

	vector<const fa250Mode1CalibPedSubHit*> m_fa250Mode1Hits;
	const fa250Mode1CalibPedSubHit* m_fa250Mode1Hit;
	loop->Get(m_fa250Mode1Hits);

	for (int ii = 0; ii < m_fa250Mode1Hits.size(); ii++) {
		mPedestalHit=new PedestalHit;
		mPedestalHit->m_channel=m_fa250Mode1Hits[ii]->m_channel;
		mean=0;
		rms=0;
		for (int jj = 0; jj < NPED; jj++){
			mean+=m_fa250Mode1Hits[ii]->samples[jj];
			rms+=m_fa250Mode1Hits[ii]->samples[jj]*m_fa250Mode1Hits[ii]->samples[jj];
		}
		mean=mean/NPED;
		rms=rms/NPED;
		rms=sqrt(rms-mean*mean);
		mPedestalHit->mean=mean;
		mPedestalHit->rms=rms;
		cout<<mean<<" "<<rms<<endl;
		_data.push_back(mPedestalHit);
	}



	return NOERROR;
}

//------------------
// erun
//------------------
jerror_t PedestalHit_factory::erun(void) {
	return NOERROR;
}

//------------------
// fini
//------------------
jerror_t PedestalHit_factory::fini(void) {
	return NOERROR;
}

