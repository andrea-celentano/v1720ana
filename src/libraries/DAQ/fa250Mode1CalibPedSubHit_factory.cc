// $Id$
//
//    File: fa250Mode1PedSubHit_factory.cc
// Created: Wed Feb  3 07:38:15 EST 2016
// Creator: davidl (on Darwin harriet.jlab.org 13.4.0 i386)
//

#include <iostream>
#include <iomanip>
using namespace std;

#include "fa250Mode1CalibPedSubHit_factory.h"
using namespace jana;


fa250Mode1CalibPedSubHit_factory::fa250Mode1CalibPedSubHit_factory(){
	m_pedSamples=10;
	m_LSB = 0.4884; //this is in any case the default
	m_dT = 4;

	gPARMS->SetDefaultParameter("FA250MODE1CALIBPEDSUB::PEDSAMPLES",m_pedSamples);

}

//------------------
// init
//------------------
jerror_t fa250Mode1CalibPedSubHit_factory::init(void) {


	return NOERROR;
}

//------------------
// brun
//------------------
jerror_t fa250Mode1CalibPedSubHit_factory::brun(jana::JEventLoop *eventLoop, int32_t runnumber) {


	return NOERROR;
}

//------------------
// evnt
//------------------
jerror_t fa250Mode1CalibPedSubHit_factory::evnt(JEventLoop *loop, uint64_t eventnumber) {

	vector<const fa250Mode1Hit*> hits;

	double m_ped;
	double sample = 0;


	//First get and process fa250Mode1Hit from JLab FADC
	loop->Get(hits);

	for (uint32_t i = 0; i < hits.size(); i++) {

		const fa250Mode1Hit *hit = hits[i];

		// Create new fa250Mode1PedSubHit
		fa250Mode1CalibPedSubHit *CalibPedSubHit = new fa250Mode1CalibPedSubHit;



		//Compute the pedestal
		m_ped=0;
		for (uint32_t j = 0; j < m_pedSamples; j++) {
			m_ped+=hit->samples[j];
		}
		m_ped/=m_pedSamples;


		for (uint32_t j = 0; j < hit->samples.size(); j++) {  //j=0
			sample = (double) hit->samples[j]; //get the sample
			sample = sample - m_ped; //subtract the pedestal (in FADC units)
			sample = sample * m_LSB; //convert to mV
			CalibPedSubHit->samples.push_back(sample);
		}

		CalibPedSubHit->m_channel = hit->m_channel;
		CalibPedSubHit->m_dT = m_dT;
		CalibPedSubHit->m_LSB = m_LSB;
		CalibPedSubHit->m_ped = m_ped * m_LSB;

		// Add original as associated object 
		CalibPedSubHit->AddAssociatedObject(hit);
		_data.push_back(CalibPedSubHit);
	}


	return NOERROR;
}

//------------------
// erun
//------------------
jerror_t fa250Mode1CalibPedSubHit_factory::erun(void) {



	return NOERROR;
}

//------------------
// fini
//------------------
jerror_t fa250Mode1CalibPedSubHit_factory::fini(void) {

	return NOERROR;
}

