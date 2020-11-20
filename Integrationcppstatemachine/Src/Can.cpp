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

#define NB_MOYENNE 3

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
		//RESET ?
		break;
	case REQ_IDN:
		//_rep.assign("je suis le client HARDWARE " + this->getHeader() +" et je suis sur la voie " + std::to_string(this->channel));
		_rep.assign(this->getHeader() +":" + std::to_string(this->channel));
		break;
	case REQ_CHX:
		//_rep.assign(_cmde +" : "+std::to_string(readADC())+"\n\r");
		_rep.assign(std::to_string(readADC()));
		break;
	case REQ_IMOY:
		//_rep.assign(_cmde +" : "+std::to_string(readADCImoy(NB_MOYENNE))+"\n\r");
		_rep.assign(std::to_string(readADCImoy(NB_MOYENNE)));
		break;
	case REQ_ISTCURR:
		//_rep.assign(_cmde +" : "+std::to_string(InstCurrent())+"\n\r");
		_rep.assign(std::to_string(InstCurrent()));
		break;
	default:
		//throw something;
		break;
	}

	return 0;
}

int Can::decodeInstruct(std::string& _cmde) {

	int sel = 0;

	if (_cmde.compare("*CLR") == 0) {
		sel = REQ_RST;
	} else if (_cmde.compare("*IDN ?") == 0) {
		sel = REQ_IDN;
	} else if(_cmde.compare("CHX ?") == 0){
		sel = REQ_CHX;
	} else if(_cmde.compare("IMOY ?") == 0){
		sel = REQ_IMOY;
	}else if(_cmde.compare("ISTCURR ?") == 0){
		sel = REQ_ISTCURR;
	} else {
		//throw something
	}
	return sel;
}

uint16_t Can::readADC(){
	return TM_ADC_Read(ADC3, this->channel);
}



float Can::readADCImoy(int nb){
	uint16_t value = 0;
	float moyenne = 0;

	for(int i = 0;i<nb;i++){
		value = value + TM_ADC_Read(ADC3, this->channel);
	}
	moyenne = (float)value/(float)nb;
	return ((3.3/4095.0)*moyenne);
}

float Can::InstCurrent(){
	return ((3.3/4095.0)*TM_ADC_Read(ADC3, this->channel));
}
