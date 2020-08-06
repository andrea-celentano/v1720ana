// $Id$
//
//    File: JEventProcessor_monitoring.cc
// Created: Fri Oct  4 11:30:24 CEST 2019
// Creator: celentan (on Linux apcx4 3.10.0-957.el7.x86_64 x86_64)
//

#include "JEventProcessor_monitoring.h"
using namespace jana;

#include "timing/PMTHit.h"

#include "TH1D.h"
#include "TApplication.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "TF1.h"
#include <fstream>
#include <sstream>

TApplication gui("GUI",0,NULL);

#define MAX_INTEGRALS 9

// Routine used to create our JEventProcessor
#include <JANA/JApplication.h>
#include <JANA/JFactory.h>
extern "C" {
void InitPlugin(JApplication *app) {
	InitJANAPlugin(app);
	app->AddProcessor(new JEventProcessor_monitoring());

}
} // "C"

//------------------
// JEventProcessor_monitoring (Constructor)
//------------------
JEventProcessor_monitoring::JEventProcessor_monitoring() {

	Tmin = 0;
	Tmax = 16000;
	dT = 4;
	log = 0;
	updateTime = 5;
	
	gPARMS->GetParameter("SYSTEM:OUTPUT", optf);
	outType.assign(optf, 0, optf.find(","));
	outFile.assign(optf, optf.find(",") + 1, optf.size());
	outFile.assign(outFile,0,outFile.find(".root"));

	

	gPARMS->SetDefaultParameter("MONITOR::TMIN", Tmin);
	gPARMS->SetDefaultParameter("MONITOR::TMAX", Tmax);
	gPARMS->SetDefaultParameter("MONITOR::DT", dT);
	gPARMS->SetDefaultParameter("MONITOR::LOG", log);

	gPARMS->SetDefaultParameter("MONITOR::UPDATE_TIME", updateTime);

	m_histoMonitor = 0;
	m_histoMonitor2 = 0;
	c_Monitor = 0;
	c_Monitor2 = 0;
	c_Monitor3 = 0;

	jout<<"MONITOR PARMS: "<<Tmin<<" "<<Tmax<<" "<<dT<<" "<<log<<" "<<updateTime<<endl;
	jout<<"MONITOR FILES: "<<outFile<<endl;
	
	counter=0;
}

//------------------
// ~JEventProcessor_monitoring (Destructor)
//------------------
JEventProcessor_monitoring::~JEventProcessor_monitoring() {

}

//------------------
// init
//------------------
jerror_t JEventProcessor_monitoring::init(void) {
	// This is called once at program startup. If you are creating
	// and filling historgrams in this plugin, you should lock the
	// ROOT mutex like this:
	//
	// japp->RootWriteLock();
	//  ... fill historgrams or trees ...
	// japp->RootUnLock();
	//

	//open the config file
	ifstream fConfig(gPARMS->GetConfigFileName().c_str());

	string line, word;
	double intTmin, intTmax;

	bckTmin=-1;
	bckTmax=-1;
	
	while (getline(fConfig, line)) {
		stringstream iss(line);

		iss >> word;
		if (word == "INTEGRAL") {
			iss >> intTmin >> intTmax;
			cout << "INTEGRAL: " << intTmin << " " << intTmax << endl;
			integralTimes.push_back(make_pair(intTmin, intTmax));
			counterIndividual.push_back(0);
		}
		if (word == "BCK") {
			iss >> bckTmin >> bckTmax;
			cout << "BCK: " << bckTmin << " " << bckTmax << endl;
		}
	}

	cout << "THERE ARE: " << integralTimes.size() << " integrals " << endl;
	if (integralTimes.size()>= MAX_INTEGRALS){
		cerr<<"ERROR: TOO MANY! MAX IS: "<<MAX_INTEGRALS<<endl;
		exit(1);
	}


	for (int ii=0;ii<integralTimes.size();ii++){
		integralPlots.push_back(new TGraph());
		integralPlots[ii]->SetTitle(Form("%f_%f",integralTimes[ii].first,integralTimes[ii].second));

		integralPlots2.push_back(new TGraph());
		integralPlots2[ii]->SetTitle(Form("%f_%f",integralTimes[ii].first,integralTimes[ii].second));
	}

	japp->RootWriteLock();
	m_histoMonitor = new TH1D("m_histoMonitor", "m_histoMonitor", int((Tmax - Tmin) / dT), Tmin, Tmax);
	m_histoMonitor2 = new TH1D("m_histoMonitor2", "m_histoMonitor2", int((Tmax - Tmin) / dT), Tmin, Tmax);
	c_Monitor = new TCanvas("cMonitor", "cMonitor", 800, 800);
	c_Monitor2 = new TCanvas("cMonitor2", "PEAK HEIGHT", 800, 800);
	c_Monitor3 =  new TCanvas("cMonitor3", "SIGMA", 800, 800);

	if (integralPlots.size()==1){
	  c_Monitor2->Divide(1,1);
	  c_Monitor3->Divide(1,1);
	}
	else if (integralPlots.size()==2){
	  c_Monitor2->Divide(2,1);
	  c_Monitor3->Divide(2,1);
	} 
	else if (integralPlots.size()<=4){
	  c_Monitor2->Divide(2,2);
	  c_Monitor3->Divide(2,2);
	}
	else if (integralPlots.size()<=9){
	  c_Monitor2->Divide(3,3);
	  c_Monitor3->Divide(3,3);
	}
	japp->RootUnLock();

	nevt=0;
	return NOERROR;
}

//------------------
// brun
//------------------
jerror_t JEventProcessor_monitoring::brun(JEventLoop *eventLoop, uint32_t runnumber) {
	// This is called whenever the run number changes


	gettimeofday(&startTime, NULL);

	return NOERROR;
}

//------------------
// evnt
//------------------
jerror_t JEventProcessor_monitoring::evnt(JEventLoop *loop, uint64_t eventnumber) {
	// This is called for every event. Use of common resources like writing
	// to a file or filling a histogram should be mutex protected. Using
	// loop->Get(...) to get reconstructed objects (and thereby activating the
	// reconstruction algorithm) should be done outside of any mutex lock
	// since multiple threads may call this method at the same time.
	// Here's an example:
	//
	// vector<const MyDataClass*> mydataclasses;
	// loop->Get(mydataclasses);
	//
	// japp->RootWriteLock();
	//  ... fill historgrams or trees ...
	// japp->RootUnLock();

	vector<const PMTHit *> pmtHits;
	vector<const PMTHit *>::iterator pmtHits_it;
	const PMTHit* pmtHit;
	TF1 *f1;
	double intTmin,intTmax,val;
	loop->Get(pmtHits);

	if (pmtHits.size()==0) return NOERROR;

	nevt++;

	for (pmtHits_it = pmtHits.begin(); pmtHits_it != pmtHits.end(); pmtHits_it++) {
		pmtHit = *pmtHits_it;

		m_histoMonitor->Fill(pmtHit->m_T0);
		m_histoMonitor2->Fill(pmtHit->m_T0);

	}
	gettimeofday(&thisTime, NULL);


	double deltaTime =(thisTime.tv_sec-startTime.tv_sec);
	double peak,mean,sigma;

	double parPeak,parSigma,parMean,parBck;
	double bckVal=0;
	if (deltaTime >= updateTime) {
		startTime = thisTime;

		if (nevt==0) return NOERROR;

		//if bckTmin>0 and bckTmax>0 comput bck
		if ((bckTmin>0)&&(bckTmax>0)&&(bckTmax>bckTmin)){
		  bckVal=m_histoMonitor2->Integral(m_histoMonitor2->FindBin(bckTmin),m_histoMonitor2->FindBin(bckTmax));
		  bckVal/=(bckTmax-bckTmin);
		}
		for (int ii=0;ii<integralTimes.size();ii++){
		  intTmin=integralTimes[ii].first;
		  intTmax=integralTimes[ii].second;
		  val=m_histoMonitor2->Integral(m_histoMonitor2->FindBin(intTmin),m_histoMonitor2->FindBin(intTmax));

		  val=val-bckVal*(intTmax-intTmin);
		  if (ii<(integralTimes.size()-1)){
		    f1=new TF1("f1","gaus(0)+pol0(3)",intTmin,intTmax);

		    parMean=(intTmax+intTmin)/2.;

		    parBck=m_histoMonitor2->GetBinContent(m_histoMonitor2->FindBin(intTmin));
		    parBck+=m_histoMonitor2->GetBinContent(m_histoMonitor2->FindBin(intTmax));
		    parBck/=2;

		    parPeak=m_histoMonitor2->GetBinContent(m_histoMonitor2->FindBin(parMean));
		    parPeak-=parBck;

		    m_histoMonitor2->GetXaxis()->SetRangeUser(intTmin,intTmax);
		    parSigma=m_histoMonitor2->GetRMS();
		    m_histoMonitor2->GetXaxis()->UnZoom();
		   
		    
		    f1->SetParameters(parPeak,parMean,parSigma,parBck);
		    int result=m_histoMonitor2->Fit(f1,"RQN","",intTmin,intTmax);
		    
		    peak=f1->GetParameter(0);
		    mean=f1->GetParameter(1);
		    sigma=f1->GetParameter(2);
		    
		    delete f1;
		    
		
		    if ((result==0)&&(peak>0)&&(mean>intTmin)&&(mean<intTmax)&&(sigma>0)){
		      //integralPlots[ii]->SetPoint(counter,counter*updateTime,peak/nevt);
		      integralPlots2[ii]->SetPoint(counterIndividual[ii],counter*updateTime,sigma);
		      counterIndividual[ii]++;
		    }
		  }
		  integralPlots[ii]->SetPoint(counter,counter*updateTime,val/nevt); 
		}
		counter++;




		m_histoMonitor2->Reset();
		c_Monitor->cd();
		if (log) {
			c_Monitor->SetLogy();
		}
		m_histoMonitor2->Draw();
		m_histoMonitor->Draw();
		c_Monitor->Modified();
		c_Monitor->Update();

		for (int ii=0;ii<integralTimes.size();ii++){
			c_Monitor2->cd(ii+1);
			integralPlots[ii]->Draw();
		}
		c_Monitor2->Modified();
		c_Monitor2->Update();

	        //c_Monitor3->cd();
		for (int ii=0;ii<integralTimes.size()-1;ii++){
			c_Monitor3->cd(ii+1);
			integralPlots2[ii]->Draw();
		}
		c_Monitor3->Modified();
		c_Monitor3->Update();
		
	

		nevt=0;
	}

	
	return NOERROR;
}

//------------------
// erun
//------------------
jerror_t JEventProcessor_monitoring::erun(void) {
	// This is called whenever the run number changes, before it is
	// changed to give you a chance to clean up before processing
	// events from the next run number.
	return NOERROR;
}

//------------------
// fini
//------------------
jerror_t JEventProcessor_monitoring::fini(void) {
	// Called before program exit after event processing is finished.



  c_Monitor2->Print(Form("peak_%s.pdf",outFile.c_str()));
  c_Monitor3->Print(Form("sigma_%s.pdf",outFile.c_str()));
  c_Monitor2->Print(Form("peak_%s.root",outFile.c_str()));
  c_Monitor3->Print(Form("sigma_%s.root",outFile.c_str()));
  
  //Print the content of the amplitude vs time stripchart
  auto ii=0,jj=0,N=0;
  double xx,yy;
  for (auto plot : integralPlots){
    ofstream f(Form("%s_peak_vstime_%i.dat",outFile.c_str(),ii));
    f<<plot->GetTitle()<<endl;
    N=plot->GetN();
    f<<N<<endl;
    for (jj=0;jj<N;jj++){
      plot->GetPoint(jj,xx,yy);
      f<<xx<<" "<<yy<<endl;
    }
    f.close();
    ii++;
  }
  
  //Print the content of the sigma vs timee stripchart
  ii=0;jj=0;N=0;
  for (auto plot : integralPlots2){
    ofstream f(Form("%s_sigma_vstime_%i.dat",outFile.c_str(),ii));
    f<<plot->GetTitle()<<endl;
    N=plot->GetN();
    f<<N<<endl;
    for (jj=0;jj<N;jj++){
      plot->GetPoint(jj,xx,yy);
      f<<xx<<" "<<yy<<endl;
    }
    f.close();
    ii++;
  }
  //Print the content of the TOF spectrum
  ofstream f(Form("%s.dat",outFile.c_str()));
  double Time,Counts;
  f<<Tmin<<" "<<Tmax<<" "<<dT<<endl;
  for (int ibin=1;ibin<=m_histoMonitor->GetNbinsX();ibin++){
    Time=m_histoMonitor->GetBinCenter(ibin);
    Counts=m_histoMonitor->GetBinContent(ibin);
    f<<Time<<" "<<Counts<<endl;
  }
  f.close();

  return NOERROR;
}

