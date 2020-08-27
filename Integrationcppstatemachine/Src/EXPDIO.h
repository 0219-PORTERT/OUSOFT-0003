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
#define REQ_QST 3

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

	short int ExecuteCmde (std::string& _cmde,std::string& _rep);
	int decodeInstruct(std::string& _cmde);
	uint16_t readPort();
};

#endif /* EXPDIO_H_ */
