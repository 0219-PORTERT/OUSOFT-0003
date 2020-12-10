/*
 * OUELEC0158.h
 *
 *  Created on: 23 nov. 2020
 *      Author: PARIS
 */

#ifndef OUELEC0158_H_
#define OUELEC0158_H_

#include <string>
#include <iostream>
#include "json.hpp"
#include "OUCART0018.h"
#include "OUCART0020.h"




class OUELEC_0158 {
public:
	OUELEC_0158();
	OUELEC_0158(uint8_t _adressrack);
	virtual ~OUELEC_0158();

	void setRackadress(uint8_t adr);
	uint8_t getRackadress(void);
	float readCurrent(uint8_t channel);
	uint8_t setPosition(uint8_t channel, uint16_t value);
	void loadJson();
	void init();

	OUCART0018 carteEIC1;
	OUCART0020 carteLEM1;

private:

	nlohmann::json jsonstruct;
	uint8_t adressrack;
	uint8_t tabCfa[5];
	uint8_t tabCfb[5];









};

#endif /* OUELEC0158_H_ */
