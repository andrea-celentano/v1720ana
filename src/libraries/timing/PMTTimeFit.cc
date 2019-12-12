#include "PMTTimeFit.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TSpectrum.h"

PMTTimeFit::PMTTimeFit() :
		hPMT(0), sPMT(0) {
}

PMTTimeFit::~PMTTimeFit() {
	if (hPMT != 0) {
		delete hPMT;
		hPMT = 0;
	}
	if (sPMT != 0) {
		delete sPMT;
		sPMT = 0;
	}
}

TCanvas* PMTTimeFit::Draw(int id) const {

	if (m_canvas == 0) {
		if (id < 0) {
			m_canvas = new TCanvas();
		} else {
			m_canvas = new TCanvas(Form("ch%i", m_channel), 100, 100, id);
		}
	}
	m_canvas->cd();

	if (hPMT != 0) {
		hPMT->Draw("HIST");
	}
	if (sPMT != 0) {
		sPMT->Draw("SAME");
	}
	return m_canvas;
}

