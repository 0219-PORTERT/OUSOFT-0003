/*
 * TempHumSensor.h
 *
 *  Created on: 28 mai 2020
 *      Author: PARIS
 */

#ifndef TEMPHUMSENSOR_H_
#define TEMPHUMSENSOR_H_

#include "ScpiClientServer.h"
#include <string>
#include <iostream>

#define TEMP_HUM_SENS8_I2CADD 0x00

#define REQ_RST 1
#define REQ_IDN 2
#define REQ_HUM 3
#define REQ_TEMP 4
#define REQ_TST 5

class TempHumSensor : public ScpiClientServer {
public:
	TempHumSensor();
	TempHumSensor(std::string _name);
	virtual ~TempHumSensor();

private:


	std::string _name;
	uint8_t i2csensoraddr;
	float temperature;
	float huidity ;
	short int ExecuteCmde (std::string& _cmde,std::string& _rep);
	int decodeInstruct(std::string& _cmde);
	float readTemp();
	float readHum();

};

#endif /* TEMPHUMSENSOR_H_ */
