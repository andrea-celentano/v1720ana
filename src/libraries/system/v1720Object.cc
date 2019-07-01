/*
 * v1720Object.cc
 *
 *  Created on: Apr 3, 2016
 *      Author: celentan
 */

#include "v1720Object.h"

#include "TCanvas.h"

v1720Object::v1720Object():m_canvas(0){
}

v1720Object::~v1720Object() {
	if (m_canvas) delete m_canvas;
	m_canvas=0;
}


