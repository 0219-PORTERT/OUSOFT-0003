/*
 * OUCART0020FCT.h
 *
 *  Created on: 20 nov. 2020
 *      Author: PARIS
 */

#ifndef OUCART0020FCT_H_
#define OUCART0020FCT_H_

#include <String>
#include <iostream>

/*adc oucart-20 voies*/
#define LEM1  0x01
#define LEM2  0x02
#define LEM3  0x03
#define LEM4  0x04
#define LEM5  0x05
#define LEM6  0x01
#define LEM7  0x02
#define LEM8  0x03
#define LEM9  0x04
#define LEM10 0x05


class OUCART0020FCT {
public:
	OUCART0020FCT();
	OUCART0020FCT( uint8_t _boardadressuint8_t,uint8_t _lem);
	virtual ~OUCART0020FCT();

	//readlem();

	uint8_t readCurrent;
	void ADCinternref(uint8_t state);

private:
	std::string _name;
	uint8_t lem;
	uint8_t boardadress;

	uint8_t adcinternref;

};

#endif /* OUCART0020FCT_H_ */
