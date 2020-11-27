/*
 * CerrG.cpp
 *
 *  Created on: 31 mars 2020
 *      Author: PARIS
 */

#include "CerrG.h"
#include <string>

CerrG::CerrG() {
	for(int i =0; i<6;i++){
		adresse[i] =0;
	}
	this->specificPosition = 0;
	this->cerr = 0;
	this->stateMachine = 0;
}

CerrG::CerrG(int _specificPosition) {
	for(int i =0; i<6;i++){
		adresse[i] =0;
	}
	this->specificPosition = _specificPosition;
	this->cerr = 0;
	this->stateMachine = 0;
}

CerrG::~CerrG() {
	// TODO Auto-generated destructor stub
}

void CerrG::AddErrorCode(CerrG _client){

	for(int i =0; i<=6;i++){
		this->adresse[i] = this->adresse[i] | _client.adresse[i] ;
	}
}
void CerrG::AddErrorCode(short int Cerr){

	if(this->cerr == 0){
		this->cerr = Cerr;
	}

}

int CerrG::SetSpecificPosition(short int _specificPosition){

	this->specificPosition = _specificPosition;

	return 0;
}


int CerrG::SetErrId(short int _specificPosition, short int _errAdress ){

	this->specificPosition = _specificPosition;
	this->adresse[_specificPosition] = _errAdress;
	this->errid= _errAdress;

	return 0;
}

std::string CerrG::ToString(void){

	std::string strError = "";

	strError = "ERROR :" + std::to_string(this->stateMachine)+"_"+std::to_string(this->adresse[0])+"."+std::to_string(this->adresse[1])+"."+std::to_string(this->adresse[2])+"."+std::to_string(this->adresse[3])+"."+std::to_string(this->adresse[4])+"."+std::to_string(this->adresse[5])+"_"+std::to_string(this->cerr);

	return strError;
}

void CerrG::clearCerrg(void){
	for(int i =0; i<6;i++){
			adresse[i] =0;
		}
		this->cerr = 0;
		this->stateMachine = 0;
}

int CerrG::SetStateMachineErrorCode(uint16_t code){

	this->stateMachine = code;


	return 0;
}
