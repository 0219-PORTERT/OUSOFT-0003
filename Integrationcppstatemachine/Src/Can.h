/*
 * Can.h
 *
 *  Created on: 23 avr. 2020
 *      Author: PARIS
 */

#ifndef CAN_H_
#define CAN_H_

#include "ScpiClientServer.h"
#include <String>
#include <iostream>
#include "tm_stm32_adc.h"
#include "OUELEC0158.h"

#define REQ_RST 1
#define REQ_IDN 2
#define REQ_CHX 3
#define REQ_IMOY 4
#define REQ_ISTCURR 5

class Can : public ScpiClientServer {
public:
	Can();

	Can(std::string _name, TM_ADC_Channel_t _channel);
	Can(std::string _name, OUELEC_0158 _rack,TM_ADC_Channel_t _channel);

	virtual ~Can();

private:
	std::string _name;
	OUELEC_0158 rack;
	TM_ADC_Channel_t channel;

	short int ExecuteCmde (std::string& _cmde,std::string& _rep);
	int decodeInstruct(std::string& _cmde);
	uint16_t readADC();
	float readADCImoy(int nb);
	float InstCurrent();
};

#endif /* CAN_H_ */
