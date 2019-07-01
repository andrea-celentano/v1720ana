/*
 * v1720Object.h
 *
 *  Created on: Apr 3, 2016
 *      Author: celentan
 */

#ifndef SRC_LIBRARIES_SYSTEM_V1720OBJECT_H_
#define SRC_LIBRARIES_SYSTEM_V1720OBJECT_H_

#include <JANA/JObject.h>
#include <JANA/JFactory.h>

#include "TObject.h"

using namespace jana;
using namespace std;

class TCanvas;

class v1720Object: public jana::JObject {
public:
	v1720Object();
	virtual ~v1720Object();
	virtual TCanvas* Draw(int id = 0) const {
		return m_canvas;
	} //!

protected:
	mutable TCanvas *m_canvas; //!

ClassDef(v1720Object,1);

};

#endif /* SRC_LIBRARIES_SYSTEM_V1720OBJECT_H_ */
