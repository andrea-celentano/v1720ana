// $Id$
//
//    File: PMTTimeFit.h
// Created: Thu Nov 28 15:15:30 CET 2019
// Creator: celentan (on Linux apcx4 3.10.0-957.el7.x86_64 x86_64)
//

#ifndef _PMTTimeFit_
#define _PMTTimeFit_

#include <JANA/JObject.h>
#include <JANA/JFactory.h>
#include "system/v1720Object.h"

class TSpectrum;
class TH1D;

class PMTTimeFit: public v1720Object {
public:
	JOBJECT_PUBLIC(PMTTimeFit);
	// Add data members here. For example:
	// int id;
	// double E;
	PMTTimeFit();
	virtual ~PMTTimeFit();
	// This method is used primarily for pretty printing
	// the second argument to AddString is printf style format
	void toStrings(vector<pair<string, string> > &items) const {
		AddString(items, "id", "%4d", id);
		AddString(items, "channel", "%4d", m_channel);
		AddString(items, "m_id", "%4d", m_id);
		AddString(items,"n_peaks","%d",n_peaks);
		if (m_T.size() >= 1) AddString(items, "time[0]", "%f", m_T[0]);
		if (m_T.size() >= 2) AddString(items, "time[1]", "%f", m_T[1]);
		if (m_T.size() >= 3) AddString(items, "time[2]", "%f", m_T[2]);
		if (m_T.size() >= 4) AddString(items, "time[3]", "%f", m_T[3]);
		if (m_T.size() >= 5) AddString(items, "time[4]", "%f", m_T[3]);

	}

	int m_channel;
	int n_peaks;
	int m_id;
	vector<double> m_T;
	void toHisto(TH1D *h) const;
	virtual TCanvas* Draw(int id = 0) const;
	mutable TH1D *hPMT;
	mutable TSpectrum *sPMT;

};

#endif // _PMTTimeFit_

