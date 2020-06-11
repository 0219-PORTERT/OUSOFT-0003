/*
 * CommutPOS.h
 *
 *  Created on: 11 juin 2020
 *      Author: PARIS
 */

#ifndef COMMUTPOS_H_
#define COMMUTPOS_H_

#include "ScpiClientServer.h"
#include <String>
#include <iostream>

#define REQ_RST 1
#define REQ_IDN 2
#define REQ_QST 4
#define REQ_x 3

class CommutPOS : public ScpiClientServer {
public:
	CommutPOS();
	CommutPOS(std::string _name);
	virtual ~CommutPOS();

private:
	std::string _name;
	uint16_t relaystate;
	short int ExecuteCmde (std::string& _cmde,std::string& _rep);
	int decodeInstruct(std::string& _cmde);
	uint16_t getStateRelay();
	uint16_t Commut1Relay(uint16_t relay);
};

#endif /* COMMUTPOS_H_ */
