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

#define REQ_RST 1
#define REQ_IDN 2
#define REQ_x 3
#define REQ_CH1 3
#define REQ_CH2 4
#define REQ_CH3 5
#define REQ_CH4 6
#define REQ_CH5 7
#define REQ_CH6 8
#define REQ_CH7 9
#define REQ_CH8 10
#define REQ_CH9 11
#define REQ_CH10 12

#define REQ_CH11
#define REQ_CH12

class Can : public ScpiClientServer {
public:
	Can();
	Can(std::string _name, TM_ADC_Channel_t _channel);
	virtual ~Can();

private:
	std::string _name;
	TM_ADC_Channel_t channel;
	short int ExecuteCmde (std::string& _cmde,std::string& _rep);
	int decodeInstruct(std::string& _cmde);
};

#endif /* CAN_H_ */
