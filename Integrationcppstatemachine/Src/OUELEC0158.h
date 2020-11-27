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
	uint16_t readCurrent(uint8_t channel);

private:

	nlohmann::json jsonstruct;
	uint8_t adressrack;
	uint8_t tabCfa[5];
	uint8_t tabCfb[5];
	OUCART0018 carteEIC1;
	OUCART0020 carteLEM1;






	void loadJson();

};

#endif /* OUELEC0158_H_ */
