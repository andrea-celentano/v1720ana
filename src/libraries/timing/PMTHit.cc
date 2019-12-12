#include "PMTHit.h"
#include "TH1D.h"
#include "TCanvas.h"

PMTHit::PMTHit() :
		hWave(0) {
}

PMTHit::~PMTHit() {
	if (hWave != 0) {
		delete hWave;
		hWave = 0;
	}
}

TCanvas* PMTHit::Draw(int id) const {

	if (m_canvas==0) {
		if (id<0) {
			m_canvas=new TCanvas();
		}
		else {
			m_canvas=new TCanvas(Form("ch%i",m_channel),100,100,id);
		}
	}
	m_canvas->cd();

	if (hWave!=0) delete hWave;
	hWave=new TH1D(Form("h%i_%i",m_channel,m_id),Form("h%i_%i",m_channel,m_id),this->m_samples.size(),-0.5*m_dT+m_T0-m_preT,(this->m_samples.size()-0.5)*m_dT+m_T0-m_preT);
	this->toHisto(hWave);
	hWave->Draw("HIST");
	return m_canvas;
}

void PMTHit::toHisto(TH1D *h)const {
	if (h==0) {
		jerr<<"PMTHit::toHisto, h pointer is null. Do nothing"<<std::endl;
	}
	int N=this->m_samples.size();
	h->Reset();
	for (int ii=0;ii<N;ii++) {
		h->Fill(ii*m_dT+m_T0-m_preT,this->m_samples[ii]);
	}
	for (int ii=0;ii<=h->GetNbinsX();ii++) {
		h->SetBinError(ii,m_LSB);
	}
	return;
}
