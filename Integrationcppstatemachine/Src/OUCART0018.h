/*
 * OUCART0018.h
 *
 *  Created on: 23 nov. 2020
 *      Author: PARIS
 */

#ifndef OUCART0018_H_
#define OUCART0018_H_

#include "Memory.h"
#include "json.hpp"

class OUCART0018 {
public:
	OUCART0018();
	OUCART0018(uint8_t _i2cadress);
	virtual ~OUCART0018();

	void setI2cAdress(uint8_t adr);
	uint8_t switchToi2c(uint8_t i2cchannel);

	uint8_t getJsonStringfromMemory(std::string &_toread);
	uint8_t storeJsonStringtoMemory(std::string &_towrite);

	std::string serialize(nlohmann::json j);
	void getjsonwithref(json& j);
	void setTemp(uint8_t code, uint8_t capteur );

	void setDir(uint8_t side, uint8_t dir);
	void writePort(uint8_t side, uint8_t writeBits);
	void readPort(uint8_t side, uint8_t *data);

	uint8_t isConnected(void);



private:

	uint8_t i2cadress;
	Memory mem1;

	std::string serialize();
	void deserialize(std::string s);
	nlohmann::json getjsonstruct();
};

#endif /* OUCART0018_H_ */
