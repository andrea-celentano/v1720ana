// $Id$
//
//    File: fa250Mode1Hit.h
// Created: Mon Dec 28 11:04:04 CET 2015
// Creator: celentan (on Linux apcx4 2.6.32-504.30.3.el6.x86_64 x86_64)
//

#ifndef _fa250Mode1Hit_
#define _fa250Mode1Hit_

#include <JANA/JObject.h>
#include <JANA/JFactory.h>

#include <system/v1720Object.h>


class TH1D;
class TCanvas;
class fa250Mode1Hit:public v1720Object{
	public:
		JOBJECT_PUBLIC(fa250Mode1Hit);
		
		
		fa250Mode1Hit();
		virtual ~fa250Mode1Hit();

		vector <double> samples;

		// This method is used primarily for pretty printing
		// the second argument to AddString is printf style format
		void toStrings(vector<pair<string,string> > &items)const{
			 AddString(items, "channel", "%4d",  m_channel);
			 AddString(items, "timestamp","%lld",(long long)timestamp);


			// AddString(items, "E", "%f", E);
		}
		void toHisto(TH1D *h) const;
		
		virtual TCanvas* Draw(int id=0) const;

		double m_dT; //sampling time
		int m_channel;
		long long unsigned int timestamp;

	protected:
		mutable TH1D *hWave;
};

#endif // _fa250Mode1Hit_

