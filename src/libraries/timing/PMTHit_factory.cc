// $Id$
//
//    File: PMTHit_factory.cc
// Created: Tue Jul  2 09:51:21 CEST 2019
// Creator: celentan (on Linux apcx4 3.10.0-957.el7.x86_64 x86_64)
//

#include <iostream>
#include <iomanip>
using namespace std;

#include <DAQ/fa250Mode1Hit.h>
#include <DAQ/fa250Mode1CalibPedSubHit.h>
#include <vector>
#include "PMTHit_factory.h"
using namespace jana;

PMTHit_factory::PMTHit_factory() {

	for (int ii = 0; ii < 8; ii++) {
		m_THR[ii] = 10; //some dummy dflt value
	}

	m_polarity = 1;
	m_preHit = 10;
	m_postHit = 20;

	gPARMS->SetDefaultParameter("PMTHIT::THR0", m_THR[0]);
	gPARMS->SetDefaultParameter("PMTHIT::THR1", m_THR[1]);
	gPARMS->SetDefaultParameter("PMTHIT::THR2", m_THR[2]);
	gPARMS->SetDefaultParameter("PMTHIT::THR3", m_THR[3]);
	gPARMS->SetDefaultParameter("PMTHIT::THR4", m_THR[4]);
	gPARMS->SetDefaultParameter("PMTHIT::THR5", m_THR[5]);
	gPARMS->SetDefaultParameter("PMTHIT::THR6", m_THR[6]);
	gPARMS->SetDefaultParameter("PMTHIT::THR7", m_THR[7]);

	gPARMS->SetDefaultParameter("PMTHIT::PREHIT", m_preHit);
	gPARMS->SetDefaultParameter("PMTHIT::POSTHIT", m_postHit);
	gPARMS->SetDefaultParameter("PMTHIT::POLARITY", m_polarity);

}

//------------------
// init
//------------------
jerror_t PMTHit_factory::init(void) {
	return NOERROR;
}

//------------------
// brun
//------------------
jerror_t PMTHit_factory::brun(jana::JEventLoop *eventLoop, uint32_t runnumber) {
	return NOERROR;
}

//------------------
// evnt
//------------------
jerror_t PMTHit_factory::evnt(JEventLoop *loop, uint64_t eventnumber) {

	//Get the fa250Mode1Hits
	vector<const fa250Mode1CalibPedSubHit*> m_fa250Mode1Hits;
	const fa250Mode1CalibPedSubHit* m_fa250Mode1Hit;
	loop->Get(m_fa250Mode1Hits);
	int m_channel;
	PMTHit *mPMTHit;
	int ii, jj, kk;
	int count=0;
	double ampl=99999;
	//Loop over the fa250Mode1Hits
	for (ii = 0; ii < m_fa250Mode1Hits.size(); ii++) {
		m_fa250Mode1Hit = m_fa250Mode1Hits[ii];
		m_channel = m_fa250Mode1Hit->m_channel;
		count=0;
		//Loop over the samples and determine the Hits
		for (jj = 0; jj < m_fa250Mode1Hit->samples.size(); jj++) {
			if (((m_polarity == 0) && (m_fa250Mode1Hit->samples[jj] > m_THR[m_channel])) || ((m_polarity == 1) && (m_fa250Mode1Hit->samples[jj] < -m_THR[m_channel]))) {

				mPMTHit = new PMTHit();
				mPMTHit->m_LSB = m_fa250Mode1Hit->m_LSB;
				mPMTHit->m_preT = m_preHit*m_fa250Mode1Hit->m_dT;
				mPMTHit->m_channel = m_channel;
				mPMTHit->m_T0 = jj * m_fa250Mode1Hit->m_dT;
				mPMTHit->m_dT = m_fa250Mode1Hit->m_dT;
				mPMTHit->m_id = count++;
				/*Save the pre-samples*/
				for (kk = jj - m_preHit; kk < jj; kk++) {
					if (kk < 0) continue;
					mPMTHit->m_samples.push_back(-m_fa250Mode1Hit->samples[kk]);
				}

				/*Save all the samples before the new thr crossing*/
				kk = jj;
				while (1) {
					if (m_fa250Mode1Hit->samples[kk]<ampl) ampl=m_fa250Mode1Hit->samples[kk];
					mPMTHit->m_samples.push_back(-m_fa250Mode1Hit->samples[kk]);
					if (kk >= m_fa250Mode1Hit->samples.size()) break;
					kk++;
					if (((m_polarity == 0) && (m_fa250Mode1Hit->samples[kk] < m_THR[m_channel])) || ((m_polarity == 1) && (m_fa250Mode1Hit->samples[kk] > -m_THR[m_channel]))) break;
				}
				jj = kk + 1;
				/*Save the post-samples*/
				for (kk = jj; kk < jj+m_preHit; kk++) {
					if (kk >= m_fa250Mode1Hit->samples.size()) continue;
					mPMTHit->m_samples.push_back(-m_fa250Mode1Hit->samples[kk]);
				}
				jj = kk+1;
				mPMTHit->m_A=-ampl;
				_data.push_back(mPMTHit);
			}
		}
	}

// Code to generate factory data goes here. Add it like:
//
// PMTHit *myPMTHit = new PMTHit;
// myPMTHit->x = x;
// myPMTHit->y = y;
// ...
// _data.push_back(myPMTHit);
//
// Note that the objects you create here will be deleted later
// by the system and the _data vector will be cleared automatically.

	return NOERROR;
}

//------------------
// erun
//------------------
jerror_t PMTHit_factory::erun(void) {
	return NOERROR;
}

//------------------
// fini
//------------------
jerror_t PMTHit_factory::fini(void) {
	return NOERROR;
}

