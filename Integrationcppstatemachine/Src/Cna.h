/*
 * Cna.h
 *
 *  Created on: 22 avr. 2020
 *      Author: PARIS
 */

#ifndef CNA_H_
#define CNA_H_

#include "ScpiClientServer.h"
#include <String>
#include <iostream>
#include "tm_stm32_adc.h"
#include "OUELEC0158.h"

#define REQ_RST 1
#define REQ_IDN 2
#define REQ_x 3
#define REQ_QST 4

class Cna : public ScpiClientServer{
public:
	Cna();
	Cna(std::string _name);
	Cna(std::string _name, OUELEC_0158 _rack,uint8_t _channel);

	virtual ~Cna();
private:
	int modValue;
	std::string _name;
	uint8_t channel;
	OUELEC_0158 rack;
	short int ExecuteCmde (std::string& _cmde,std::string& _rep);
	int decodeInstruct(std::string& _cmde);
	void setModulation();
};

#endif /* CNA_H_ */
