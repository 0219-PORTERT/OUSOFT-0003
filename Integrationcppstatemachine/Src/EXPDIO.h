/*
 * EXPDIO.h
 *
 *  Created on: 27 août 2020
 *      Author: PARIS
 */

#ifndef EXPDIO_H_
#define EXPDIO_H_

#include "ScpiClientServer.h"
#include <String>
#include <iostream>

#define REQ_RST 1
#define REQ_IDN 2
#define REQ_QSTRD 3
#define REQ_WR 4
#define REQ_QSTDIR 5
#define REQ_SETDIR 6

#define SIDEA 0
#define SIDEB 1

class EXPDIO : public ScpiClientServer  {
public:
	EXPDIO();
	EXPDIO(std::string _name, uint8_t _side);
	virtual ~EXPDIO();
private:
	std::string _name;
	uint8_t side;
	uint8_t direction;
	uint8_t writevalue;

	short int ExecuteCmde (std::string& _cmde,std::string& _rep);
	int decodeInstruct(std::string& _cmde);
	uint8_t readPort();
	uint8_t writePort();
	uint8_t setDir();

	uint16_t readPin();
	uint16_t writePin();
};

#endif /* EXPDIO_H_ */
