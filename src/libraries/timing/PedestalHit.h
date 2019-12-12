// $Id$
//
//    File: PedestalHit.h
// Created: Thu Nov 28 14:48:09 CET 2019
// Creator: celentan (on Linux apcx4 3.10.0-957.el7.x86_64 x86_64)
//

#ifndef _PedestalHit_
#define _PedestalHit_

#include <JANA/JObject.h>
#include <JANA/JFactory.h>

class PedestalHit: public jana::JObject {
public:
	JOBJECT_PUBLIC(PedestalHit)
	;

	// Add data members here. For example:
	// int id;
	// double E;

	// This method is used primarily for pretty printing
	// the second argument to AddString is printf style format
	void toStrings(vector<pair<string, string> > &items) const {
		AddString(items, "id", "%4d", id);
		AddString(items, "ch", "%4d", m_channel);
		AddString(items, "mean", "%f", mean);
		AddString(items, "rms", "%f", rms);
	}
	int m_channel;
	double mean, rms;
};

#endif // _PedestalHit_

