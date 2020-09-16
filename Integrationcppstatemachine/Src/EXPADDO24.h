/*
 * EXPADDO24.h
 *
 *  Created on: 7 sept. 2020
 *      Author: PARIS
 */

#ifndef EXPADDO24_H_
#define EXPADDO24_H_

#include "ScpiClientServer.h"
#include <String>
#include <iostream>

#define REQ_RST 1
#define REQ_IDN 2
#define REQ_QSTRD 3
#define REQ_WR 4
#define REQ_QSTDIR 5
#define REQ_SETDIR 6
#define REQ_TSTAB 7
#define REQ_TSTAC 8

#define SIDEA 0
#define SIDEB 1
#define SIDEC 3

class EXPADDO24 : public ScpiClientServer {
public:
	EXPADDO24();
	EXPADDO24(std::string _name, uint8_t _side);
	virtual ~EXPADDO24();
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

	std::string testAB(uint8_t bytetotest);
	std::string testAC(uint8_t bytetotest);

	uint16_t readPin();
	uint16_t writePin();
};

#endif /* EXPADDO24_H_ */
