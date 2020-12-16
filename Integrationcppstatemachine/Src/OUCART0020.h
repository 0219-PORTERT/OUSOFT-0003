/*
 * OUCART0020.h
 *
 *  Created on: 23 nov. 2020
 *      Author: PARIS
 */

#ifndef OUCART0020_H_
#define OUCART0020_H_

#include <String>
#include <iostream>

class OUCART0020 {
public:
	OUCART0020();
	OUCART0020(uint8_t _i2cadress);
	virtual ~OUCART0020();

	void setI2cAdress(uint8_t adr);
	uint16_t readADC(uint8_t channel); //lit la voie adc

	uint16_t setDAC(uint8_t channel, int value); //change la valeur du dac

	uint8_t setconfigADC( uint8_t pins);
	uint8_t setconfigDAC( uint8_t pins);

	uint8_t enableInternalRef();
	uint8_t disableInternalRef();

private:

	uint8_t tabChannelMode[8];
	uint8_t i2cadress;


};

#endif /* OUCART0020_H_ */
