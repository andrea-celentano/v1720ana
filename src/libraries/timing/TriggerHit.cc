#include "TriggerHit.h"
#include "TH1D.h"
#include "TCanvas.h"

TriggerHit::TriggerHit() :
		hTMP(0) {
}

TriggerHit::~TriggerHit() {
	if (hTMP != 0) {
		delete hTMP;
		hTMP = 0;
	}
}

TCanvas* TriggerHit::Draw(int id) const {

	if (m_canvas == 0) {
		if (id < 0) {
			m_canvas = new TCanvas();
		} else {
			m_canvas = new TCanvas("cTrigger", 100, 100, id);
		}
	}
	m_canvas->cd();

	if (hTMP != 0) {
		hTMP->Draw();
	}
	return m_canvas;
}
