/*
 * SimCapTemp.cpp
 *
 *  Created on: 28 avr. 2020
 *      Author: PARIS
 */

#include "SimCapTemp.h"
#include "tm_stm32_i2c.h"
#include "i2c.h"
#include <String>
#include <iostream>
#include <cmath>
#include "OUELEC0158.h"

#define alpha 0.00788
#define beta 0.00001937
#define r25 600

SimCapTemp::SimCapTemp() {
	// TODO Auto-generated constructor stub
	this->capteur = TEMPCAP1;
	this->tempValue = 25;
	this->rack.setRackadress(NULL);

}

SimCapTemp::SimCapTemp(std::string _name, uint8_t _capteur, uint8_t _addpot1k, uint8_t _addpot100k): ScpiClientServer(_name), capteur(_capteur), addpot1k(_addpot1k), addpot100k(_addpot100k){
	// TODO Auto-generated constructor stub
	this->tempValue = 25;
	this->rack.setRackadress(NULL);
}

SimCapTemp::SimCapTemp(std::string _name, uint8_t _capteur, OUELEC_0158 _rack ): ScpiClientServer(_name), capteur(_capteur), rack(_rack){
	// TODO Auto-generated constructor stub
	this->tempValue = 25;
}

SimCapTemp::~SimCapTemp() {
	// TODO Auto-generated destructor stub
}

short int SimCapTemp::ExecuteCmde(std::string& _cmde, std::string& _rep) {
	//_rep.assign("Je suis le execute de la classe SIMCAPTEMP");


	switch (decodeInstruct(_cmde)) {

	case REQ_RST:
		setTemp(25);
		this->tempValue = 25;
		break;
	case REQ_IDN:
		_rep.assign(this->getHeader() +":" + std::to_string(this->capteur));
		break;
	case REQ_x:
		setTemp(this->tempValue);
		break;
	case REQ_QST:
		_rep.assign(this->getHeader()+ ":"+ std::to_string(this->tempValue) + "\n\r");
		break;
	case REQ_MIN:
		MeasMin();
		break;
	case REQ_MAX:
		MeasMax();
		break;
	case REQ_STEP:
		MeasStep();
		break;
	default:
		throw ERROR_CMD_BAD_ARG;
		break;
	}

	return 0;
}

int SimCapTemp::decodeInstruct(std::string& _cmde) {

	int sel = 0;

	if (_cmde.compare("*CLR") == 0) {
		sel = REQ_RST;
	} else if (_cmde.compare("*IDN ?") == 0) {
		sel = REQ_IDN;
	} else if(_cmde.compare("TMP ?") == 0){
		sel = REQ_QST;
	} else if(_cmde.compare(0, 4, "TMP ") == 0){
		int value = 0;
		value = stoi(_cmde.substr(4), nullptr, 10);

		if ((value < -40) || (value > 200)) {
			sel = -1; //bonne commande mais mauvaise valeur car mal convertie ou autre
		} else {
			this->tempValue = value;
			sel = REQ_x;
		}
	} else if (_cmde.compare("TMPMIN") == 0) {
		sel = REQ_MIN ;
	} else if (_cmde.compare("TMPMAX") == 0) {
		sel = REQ_MAX ;
	} else if (_cmde.compare("TMPSTEP") == 0) {
		sel = REQ_STEP ;
	}
	else {
		throw ERROR_CMD_SCPIHARD_SYNTHAX_ERROR;
	}
	return sel;
}

void SimCapTemp::setTemp(int tValue){

	uint8_t rGcode = 0;
	uint8_t rPcode = 0;
	int rT = 0;
	int Rth =0;
	int Rapp=0;


	//conversion temperature to resistance
	rT = (r25 * ((1+alpha*(tValue-25)+beta*pow((tValue-25),2)))); //Resistance totale théorique

	//repartition resistance to Rp et Rg

	rGcode = round(((rT - 500)/390.0)); //code resistance 100k
	rPcode = round((rT - rGcode*390)/4.0)-37;//code resistance 1k

	Rth = rPcode*4 + rGcode*390; //resistance totale après 2pot ?
	Rapp = ((rPcode/256.0)*1000+75) + ((rGcode/256.0)*100000+75); // resistance réelle appliquée sur les pot ;

	if(this->rack.getRackadress() == NULL){
		//settings
		TM_I2C_Write(I2C4,this->addpot1k, this->capteur, rPcode);
		//HAL_Delay(10);
		TM_I2C_Write(I2C4, this->addpot100k, this->capteur, rGcode);
	}else{
		this->rack.carteEIC1.setTemp(rGcode, rPcode, this->capteur);
	}
}

void SimCapTemp::MeasMin(){
	TM_I2C_Write(I2C4, this->addpot1k, this->capteur, 0);
	TM_I2C_Write(I2C4, this->addpot100k, this->capteur, 0);
}
void SimCapTemp::MeasMax(){
	TM_I2C_Write(I2C4, this->addpot1k, this->capteur, 255);
	TM_I2C_Write(I2C4, this->addpot100k, this->capteur, 255);
}
void SimCapTemp::MeasStep(){
	TM_I2C_Write(I2C4, this->addpot1k, this->capteur, 1);
	TM_I2C_Write(I2C4, this->addpot100k, this->capteur, 0);
}

