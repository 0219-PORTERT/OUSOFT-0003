/*
 * OUCART0018.h
 *
 *  Created on: 23 nov. 2020
 *      Author: PARIS
 */

#ifndef OUCART0018_H_
#define OUCART0018_H_

#include "Memory.h"
#include "SimCapTemp.h"
#include "json.hpp"


#define TOADCDAC 0x00
#define INTERN 0x00

class OUCART0018 {
public:
	OUCART0018();
	OUCART0018(uint8_t _i2cadress);
	virtual ~OUCART0018();

	void setI2cAdress(uint8_t adr);
	uint8_t switchToi2c(uint8_t i2c);

	std::string getJsonString();
	void getjsonwithref(json& j);
private:

	uint8_t i2cadress;

	Memory mem1;
	SimCapTemp T1;
	SimCapTemp T2;
	SimCapTemp T3;
	SimCapTemp T4;

	std::string serialize();
	void deserialize(std::string s);
	nlohmann::json getjsonstruct();
};

#endif /* OUCART0018_H_ */
