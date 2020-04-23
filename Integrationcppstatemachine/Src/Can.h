/*
 * Can.h
 *
 *  Created on: 23 avr. 2020
 *      Author: PARIS
 */

#ifndef CAN_H_
#define CAN_H_

#include "ScpiClientServer.h"
#include <String>
#include <iostream>

#define REQ_RST 1
#define REQ_IDN 2
#define REQ_x 3
#define REQ_QST 4

class Can : public ScpiClientServer {
public:
	Can();
	virtual ~Can();
};

#endif /* CAN_H_ */
