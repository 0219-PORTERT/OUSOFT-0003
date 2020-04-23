/*
 * Can.cpp
 *
 *  Created on: 23 avr. 2020
 *      Author: PARIS
 */

#include "Can.h"
#include "ScpiClientServer.h"
#include <string>
#include <iostream>
#include "tm_stm32_adc.h"
Can::Can() {
	// TODO Auto-generated constructor stub
	this->channel = TM_ADC_Channel_0;
}

Can::Can(std::string _name, TM_ADC_Channel_t _channel): ScpiClientServer(_name), channel(_channel) {

}
Can::~Can() {
	// TODO Auto-generated destructor stub
}

short int Can::ExecuteCmde(std::string& _cmde, std::string& _rep) {
	//_rep.assign("Je suis le execute de la classe Can");

	switch (decodeInstruct(_cmde)) {

	case REQ_RST:

		break;
	case REQ_IDN:
		_rep.assign("je suis le client HARDWARE " + this->getHeader() +" et je suis sur la voie " + std::to_string(this->channel));
		break;
	case REQ_CH1:
		_rep.assign(_cmde +" : "+std::to_string(TM_ADC_Read(ADC3, TM_ADC_Channel_0))+"\n\r");
		break;
	case REQ_CH2:
		std::to_string(TM_ADC_Read(ADC3, TM_ADC_Channel_3));
		break;
	case REQ_CH3:
		std::to_string(TM_ADC_Read(ADC3, TM_ADC_Channel_4));
		break;
	case REQ_CH4:
		std::to_string(TM_ADC_Read(ADC3, TM_ADC_Channel_5));
		break;
	case REQ_CH5:
		std::to_string(TM_ADC_Read(ADC3, TM_ADC_Channel_6));
		break;
	case REQ_CH6:
		std::to_string(TM_ADC_Read(ADC3, TM_ADC_Channel_8));
		break;
	case REQ_CH7:
		std::to_string(TM_ADC_Read(ADC3, TM_ADC_Channel_9));
		break;
	case REQ_CH8:
		std::to_string(TM_ADC_Read(ADC3, TM_ADC_Channel_10));
		break;
	case REQ_CH9:
		std::to_string(TM_ADC_Read(ADC3, TM_ADC_Channel_12));
		break;
	case REQ_CH10:
		std::to_string(TM_ADC_Read(ADC3, TM_ADC_Channel_13));
		break;
	default:
		//throw something;
		break;
	}

	return 0;
}

int Can::decodeInstruct(std::string& _cmde) {

	int sel = 0;

	if (_cmde.compare("*RST") == 0) {
		sel = REQ_RST;
	} else if (_cmde.compare("*IDN ?") == 0) {
		sel = REQ_IDN;
	} else if(_cmde.compare("I_moy ?") == 0){

	}
	else if(_cmde.compare("I_moy ?") == 0){

		}



	else {
		//throw something
	}

	return sel;
}

uint16_t readADC(TM_ADC_Channel_t channel){

}

uint16_t readADCmoy(TM_ADC_Channel_t _channel, int nb){

}
