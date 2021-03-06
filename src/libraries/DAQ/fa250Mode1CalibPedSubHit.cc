#include "fa250Mode1CalibPedSubHit.h"
#include "TH1D.h"
#include "TCanvas.h"

fa250Mode1CalibPedSubHit::fa250Mode1CalibPedSubHit(){
	m_ped=0;
}

fa250Mode1CalibPedSubHit::~fa250Mode1CalibPedSubHit(){

}

TCanvas* fa250Mode1CalibPedSubHit::Draw(int id) const{


	if (m_canvas==0){
		if (id<0){
			m_canvas=new TCanvas();
		}
		else{
			m_canvas=new TCanvas(Form("ch%i",m_channel),100,100,id);
		}
	}
	m_canvas->cd();

	if (hWave!=0) delete hWave;
	hWave=new TH1D(Form("hh%i",m_channel),Form("h%i",m_channel),this->samples.size(),-0.5*m_dT,(this->samples.size()-0.5)*m_dT);
	this->toHisto(hWave);
	hWave->Draw("HIST");
	return m_canvas;
}


void fa250Mode1CalibPedSubHit::toHisto(TH1D *h)const{
	if (h==0){
		jerr<<"fa250Mode1CalibPedSubHit::toHisto, h pointer is null. Do nothing"<<std::endl;
	}
	int N=this->samples.size();
	h->Reset();
	for (int ii=0;ii<N;ii++){
		h->Fill(ii*m_dT,this->samples[ii]);
	}
	for (int ii=0;ii<=h->GetNbinsX();ii++){
		h->SetBinError(ii,this->m_LSB);
	}
	return;
}
