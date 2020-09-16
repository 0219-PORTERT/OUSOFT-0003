/*
 * EXPSEC.h
 *
 *  Created on: 3 juin 2020
 *      Author: PARIS
 */

#ifndef EXPSEC_H_
#define EXPSEC_H_

#include "ScpiClientServer.h"
#include <String>
#include <iostream>

#define REQ_RST 1
#define REQ_IDN 2
#define REQ_QST 3
#define REQ_RTST 4
#define REQ_I2CEXT1TST 5
#define REQ_I2CEXT2TST 6

#define SIDEA 0
#define SIDEB 1

class EXPSEC : public ScpiClientServer {
public:
	EXPSEC();
	EXPSEC(std::string _name);
	virtual ~EXPSEC();

private :
	std::string _name;
	uint8_t staterelaysecu;
	short int ExecuteCmde (std::string& _cmde,std::string& _rep);
	int decodeInstruct(std::string& _cmde);
	int configseq();
	uint16_t readPort();
	std::string testI2CEXT1();
	std::string testI2CEXT2();
};

#endif /* EXPSEC_H_ */
