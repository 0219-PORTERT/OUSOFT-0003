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
#include "OUELEC0158.h"

#define REQ_RST 1
#define REQ_IDN 2
#define REQ_QSTRD 3
#define REQ_WR 4
#define REQ_QSTDIR 5
#define REQ_SETDIR 6
#define REQ_TST 7

#define REQ_SDR 8
#define REQ_RTR 9
#define REQ_MBA 10
#define REQ_THO 11
#define REQ_THM 12
#define REQ_THN 13
#define REQ_WDSDR 14
#define REQ_RTA 15

#define SIDEA 0
#define SIDEB 1

class EXPDIO : public ScpiClientServer  {
public:
	EXPDIO();
	EXPDIO(std::string _name, uint8_t _side);
	EXPDIO(std::string _name, uint8_t _side, OUELEC_0158 _rack);
	virtual ~EXPDIO();

	uint8_t getSDR(void);
	uint8_t getRTR(void);
	uint8_t getMBA(void);
	uint8_t getTHO(void);
	uint8_t getTHM(void);
	uint8_t getTHN(void);
	uint8_t getWDSDR(void);
	uint8_t getRTA(void);

	uint8_t readPort();
	uint8_t writePort();
private:
	std::string _name;
	uint8_t side;
	OUELEC_0158 rack;
	uint8_t direction;
	uint8_t writevalue;

	short int ExecuteCmde (std::string& _cmde,std::string& _rep);
	int decodeInstruct(std::string& _cmde);
	uint8_t setDir();

	std::string testAB(uint8_t bytetosend);

};

#endif /* EXPDIO_H_ */
