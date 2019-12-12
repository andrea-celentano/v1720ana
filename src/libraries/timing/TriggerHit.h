// $Id$
//
//    File: TriggerHit.h
// Created: Thu Nov 28 13:26:18 CET 2019
// Creator: celentan (on Linux apcx4 3.10.0-957.el7.x86_64 x86_64)
//

#ifndef _TriggerHit_
#define _TriggerHit_

#include <JANA/JObject.h>
#include <JANA/JFactory.h>
#include "system/v1720Object.h"

class TH1D;

class TriggerHit:public v1720Object{
	public:
		JOBJECT_PUBLIC(TriggerHit);
		
		TriggerHit();
		virtual ~TriggerHit();

		// Add data members here. For example:
		// int id;
		// double E;
		
		// This method is used primarily for pretty printing
		// the second argument to AddString is printf style format
		void toStrings(vector<pair<string,string> > &items)const{
			AddString(items, "id", "%4d", id);
			AddString(items, "T0", "%f", m_T0);
		}
		
		double m_T0;


		mutable TH1D *hTMP;
		virtual TCanvas* Draw(int id = 0) const;




};

#endif // _TriggerHit_

