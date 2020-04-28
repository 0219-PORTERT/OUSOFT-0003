/*
 * SimCapTemp.h
 *
 *  Created on: 28 avr. 2020
 *      Author: PARIS
 */

#ifndef SIMCAPTEMP_H_
#define SIMCAPTEMP_H_

#include "ScpiClientServer.h"
#include <String>
#include <iostream>

#define TEMP1 1
#define TEMP2 2
#define TEMP3 3
#define TEMP4 4

#define REQ_RST 1
#define REQ_IDN 2
#define REQ_x 3
#define REQ_QST 4

class SimCapTemp : public ScpiClientServer {
public:
	SimCapTemp();
	SimCapTemp(std::string _name, uint8_t _capteur);
	virtual ~SimCapTemp();
private:
	std::string _name;
	uint8_t capteur;
	int tmpValue;
	short int ExecuteCmde (std::string& _cmde,std::string& _rep);
	int decodeInstruct(std::string& _cmde);
};

#endif /* SIMCAPTEMP_H_ */
