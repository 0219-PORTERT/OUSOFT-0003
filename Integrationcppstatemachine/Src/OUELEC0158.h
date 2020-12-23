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
	uint8_t setPosition(uint8_t channel, int value);
	uint8_t loadJson();
	void init();
	uint16_t readADC(uint8_t channel);

	OUCART0018 carteEIC1;
	OUCART0020 carteLEM1;

private:

	nlohmann::json jsonstruct;
	uint8_t adressrack;

	float tabCfa[5];
	float tabCfb[5];
	std::string partNb;
	std::string serialNb;
	std::string affaire;
	std::string calDate;
	std::string mcoDate;


	std::string getPartnb();
	std::string getSerialnb();
	std::string getAffaire();
	std::string getLastcal();
	std::string getLastmco();







};

#endif /* OUELEC0158_H_ */
