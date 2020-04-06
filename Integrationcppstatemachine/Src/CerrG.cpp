/*
 * CerrG.cpp
 *
 *  Created on: 31 mars 2020
 *      Author: PARIS
 */

#include "CerrG.h"

CerrG::CerrG() {
	for(int i =0; i<6;i++){
		adresse[i] =0;
	}
	this->specificPosition = 0;
	this->cerr = 0;
}

CerrG::CerrG(int _specificPosition) {
	for(int i =0; i<6;i++){
		adresse[i] =0;
	}
	this->specificPosition = _specificPosition;
	this->cerr = 0;
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

	return 0;
}
