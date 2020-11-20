/*
 * OUCART0020FCT.cpp
 *
 *  Created on: 20 nov. 2020
 *      Author: PARIS
 */

#include "OUCART0020FCT.h"

OUCART0020FCT::OUCART0020FCT() {
	// TODO Auto-generated constructor stub

}

OUCART0020FCT::OUCART0020FCT( uint8_t _lem, uint8_t _boardadress): boardadress(_boardadress), lem(_lem){
	this->ADCinternref(1);

}

OUCART0020FCT::~OUCART0020FCT() {
	// TODO Auto-generated destructor stub
}




void OUCART0020FCT::ADCinternref(uint8_t state){

 this->adcinternref = state;

 if(this->adcinternref == 1){
	 //enable ref
 }else{
	 //disable ref
 }



}
