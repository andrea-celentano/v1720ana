// $Id$
//
//    File: JEventProcessor_monitoring.h
// Created: Fri Oct  4 11:30:24 CEST 2019
// Creator: celentan (on Linux apcx4 3.10.0-957.el7.x86_64 x86_64)
//

#ifndef _JEventProcessor_monitoring_
#define _JEventProcessor_monitoring_

#include <JANA/JEventProcessor.h>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <sys/time.h>

class TH1D;
class TCanvas;
class TGraph;
class JEventProcessor_monitoring:public jana::JEventProcessor{
	public:
		JEventProcessor_monitoring();
		~JEventProcessor_monitoring();
		const char* className(void){return "JEventProcessor_monitoring";}

	private:
		jerror_t init(void);						///< Called once at program start.
		jerror_t brun(jana::JEventLoop *eventLoop, uint32_t runnumber);	///< Called everytime a new run number is detected.
		jerror_t evnt(jana::JEventLoop *eventLoop, uint64_t eventnumber);	///< Called every event.
		jerror_t erun(void);						///< Called everytime run number changes, provided brun has been called.
		jerror_t fini(void);						///< Called after last event of last event source has been processed.\


		//This is for the main histogram
		double Tmin,Tmax,dT;
		int log;

		double updateTime;


		TH1D* m_histoMonitor;
		TH1D* m_histoMonitor2;
		TCanvas* c_Monitor;
		TCanvas* c_Monitor2;

		struct timeval startTime,thisTime;



		int nevt;
		vector<std::pair<double,double>> integralTimes;
		vector<TGraph *> integralPlots;

		int counter;
};

#endif // _JEventProcessor_monitoring_

