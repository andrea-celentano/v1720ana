// $Id$
//
//    File: PMTTimeFit_factory.cc
// Created: Thu Nov 28 15:15:30 CET 2019
// Creator: celentan (on Linux apcx4 3.10.0-957.el7.x86_64 x86_64)
//

#include <iostream>
#include <iomanip>
using namespace std;

#include "PMTTimeFit_factory.h"
#include "PMTHit.h"
#include "PMTTimeFit.h"
#include "TSpectrum.h"
#include "TH1D.h"
using namespace jana;

//------------------
// init
//------------------
jerror_t PMTTimeFit_factory::init(void) {
	return NOERROR;
}

//------------------
// brun
//------------------
jerror_t PMTTimeFit_factory::brun(jana::JEventLoop *eventLoop, uint32_t runnumber) {
	return NOERROR;
}

//------------------
// evnt
//------------------
jerror_t PMTTimeFit_factory::evnt(JEventLoop *loop, uint64_t eventnumber) {

	// Code to generate factory data goes here. Add it like:
	//
	// PMTTimeFit *myPMTTimeFit = new PMTTimeFit;
	// myPMTTimeFit->x = x;
	// myPMTTimeFit->y = y;
	// ...
	// _data.push_back(myPMTTimeFit);
	//
	// Note that the objects you create here will be deleted later
	// by the system and the _data vector will be cleared automatically.

	/*Get the PMT hits*/
	vector<const PMTHit*> m_PMTHits;
	loop->Get(m_PMTHits);

	PMTTimeFit *mPMTTimeFit;

	TH1D *hPMT;
	TSpectrum *sPMT;

	for (int ii = 0; ii < m_PMTHits.size(); ii++) {
		if (m_PMTHits[ii]->m_channel != m_CH) continue;

		mPMTTimeFit = new PMTTimeFit;
		mPMTTimeFit->m_channel = m_PMTHits[ii]->m_channel;
		mPMTTimeFit->m_id = m_PMTHits[ii]->m_id;

		mPMTTimeFit->hPMT = new TH1D(Form("h%i_%i", mPMTTimeFit->m_channel, mPMTTimeFit->m_id), Form("h%i_%i", mPMTTimeFit->m_channel, mPMTTimeFit->m_id), m_PMTHits[ii]->m_samples.size(), -0.5 * m_PMTHits[ii]->m_dT + m_PMTHits[ii]->m_T0 - m_PMTHits[ii]->m_preT,
				(m_PMTHits[ii]->m_samples.size() - 0.5) * m_PMTHits[ii]->m_dT + m_PMTHits[ii]->m_T0 - m_PMTHits[ii]->m_preT);
		hPMT = mPMTTimeFit->hPMT;

		for (int jj = 0; jj < m_PMTHits[ii]->m_samples.size(); jj++) {
			hPMT ->Fill(jj * m_PMTHits[ii]->m_dT + m_PMTHits[ii]->m_T0 - m_PMTHits[ii]->m_preT, m_PMTHits[ii]->m_samples[jj]);
		}
		for (int jj = 0; jj <= hPMT->GetNbinsX(); jj++) {
			hPMT ->SetBinError(jj, m_PMTHits[ii]->m_LSB);
		}
		hPMT->ShowPeaks();

		mPMTTimeFit->sPMT = new TSpectrum();
		sPMT=mPMTTimeFit->sPMT;
		mPMTTimeFit->n_peaks=sPMT->Search(hPMT,2,"",0.05);

		_data.push_back(mPMTTimeFit);

	}

	return NOERROR;
}

//------------------
// erun
//------------------
jerror_t PMTTimeFit_factory::erun(void) {
	return NOERROR;
}

//------------------
// fini
//------------------
jerror_t PMTTimeFit_factory::fini(void) {
	return NOERROR;
}

