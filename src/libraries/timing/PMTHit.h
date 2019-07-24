// $Id$
//
//    File: PMTHit.h
// Created: Tue Jul  2 09:51:21 CEST 2019
// Creator: celentan (on Linux apcx4 3.10.0-957.el7.x86_64 x86_64)
//

#ifndef _PMTHit_
#define _PMTHit_

#include <JANA/JObject.h>
#include <JANA/JFactory.h>
#include <system/v1720Object.h>
class TH1D;

class PMTHit: public v1720Object {
public:
	JOBJECT_PUBLIC(PMTHit)
	;

	PMTHit();
	virtual ~PMTHit();
	// Add data members here. For example:
	// int id;
	// double E;

	// This method is used primarily for pretty printing
	// the second argument to AddString is printf style format
	void toStrings(vector<pair<string, string> > &items) const {
		AddString(items, "channel", "%4d", m_channel);
		AddString(items, "T0", "%f", m_T0);

	}

	int m_channel;
	int m_id; //counting each per channel
	vector<double> m_samples;
	double m_T0;
	double m_dT;


	void toHisto(TH1D *h) const;
	virtual TCanvas* Draw(int id = 0) const;

protected:
	mutable TH1D *hWave;
};

#endif // _PMTHit_

