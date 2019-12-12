// $Id$
//
//    File: TriggerHit_factory.cc
// Created: Thu Nov 28 13:26:18 CET 2019
// Creator: celentan (on Linux apcx4 3.10.0-957.el7.x86_64 x86_64)
//

#include <iostream>
#include <iomanip>
using namespace std;

#include "TriggerHit_factory.h"
#include <DAQ/fa250Mode1CalibPedSubHit.h>
#include "TGraph.h"
#include "TF1.h"
#include "TH1D.h"
using namespace jana;

//------------------
// init
//------------------
jerror_t TriggerHit_factory::init(void) {

	return NOERROR;
}

//------------------
// brun
//------------------
jerror_t TriggerHit_factory::brun(jana::JEventLoop *eventLoop, uint32_t runnumber) {

	gPARMS->SetDefaultParameter("TRIGGERHIT::CH", m_CH);
	gPARMS->SetDefaultParameter("TRIGGERHIT::TSTART", m_Tstart);
	gPARMS->SetDefaultParameter("TRIGGERHIT::TSTOP", m_Tstop);

	jout << "TriggerHit_factory::brun is called" << endl;
	funFit = new TF1("funFit", "[0]+[1]/(1+exp(-(x-[2])/[3]))", m_Tstart, m_Tstop);

	return NOERROR;
}

//------------------
// evnt
//------------------
jerror_t TriggerHit_factory::evnt(JEventLoop *loop, uint64_t eventnumber) {

	//Get the fa250Mode1Hits
	vector<const fa250Mode1CalibPedSubHit*> m_fa250Mode1Hits;
	const fa250Mode1CalibPedSubHit* m_fa250Mode1Hit;
	loop->Get(m_fa250Mode1Hits);

	// Code to generate factory data goes here. Add it like:
	//
	// TriggerHit *myTriggerHit = new TriggerHit;
	// myTriggerHit->x = x;
	// myTriggerHit->y = y;
	// ...
	// _data.push_back(myTriggerHit);
	//
	// Note that the objects you create here will be deleted later
	// by the system and the _data vector will be cleared automatically.
	TriggerHit *mTriggerHit = new TriggerHit;
	int m_channel;
	TH1D *hTMP = 0;
	double t;
	int ip = 0;
	//Loop over the fa250Mode1Hits
	for (int ii = 0; ii < m_fa250Mode1Hits.size(); ii++) {
		m_fa250Mode1Hit = m_fa250Mode1Hits[ii];
		m_channel = m_fa250Mode1Hit->m_channel;

		/*Check the trigger channel*/
		if (m_channel == m_CH) {

			mTriggerHit->hTMP = new TH1D("hTMP", "hTMP", m_fa250Mode1Hit->samples.size(), -0.5 * m_fa250Mode1Hit->m_dT, (m_fa250Mode1Hit->samples.size() - 0.5) * m_fa250Mode1Hit->m_dT);
			hTMP = mTriggerHit->hTMP;

			for (int jj = 0; jj < m_fa250Mode1Hit->samples.size(); jj++) {
				hTMP->Fill(jj * m_fa250Mode1Hit->m_dT, m_fa250Mode1Hit->samples[jj]);
			}
			for (int jj = 0; jj <= (mTriggerHit->hTMP->GetNbinsX()); jj++) {
				hTMP->SetBinError(jj, m_fa250Mode1Hit->m_LSB);
			}

			funFit->SetParameter(0, m_fa250Mode1Hit->samples[0]);
			funFit->SetParameter(1, m_fa250Mode1Hit->samples[m_fa250Mode1Hit->samples.size() - 1] - m_fa250Mode1Hit->samples[0]);
			funFit->SetParameter(2, (m_Tstart + m_Tstop) / 2);
			funFit->SetParameter(3, 4);

			hTMP->Fit(funFit,"RQ","",m_Tstart,m_Tstop);

			mTriggerHit->m_T0 = funFit->GetParameter(2);

		}
	}

	_data.push_back(mTriggerHit);

	return NOERROR;
}

//------------------
// erun
//------------------
jerror_t TriggerHit_factory::erun(void) {
	return NOERROR;
}

//------------------
// fini
//------------------
jerror_t TriggerHit_factory::fini(void) {
	return NOERROR;
}

