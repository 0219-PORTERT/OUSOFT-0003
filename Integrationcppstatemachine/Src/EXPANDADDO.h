/*
 * EXPANDADDO.h
 *
 *  Created on: 10 juin 2020
 *      Author: PARIS
 */

#ifndef EXPANDADDO_H_
#define EXPANDADDO_H_

#include "ScpiClientServer.h"
#include <String>
#include <iostream>

#define REQ_RST 1
#define REQ_IDN 2
#define REQ_QST 3

class EXPANDADDO  : public ScpiClientServer{
public:
	EXPANDADDO();
	EXPANDADDO(std::string _name);
	virtual ~EXPANDADDO();

private :
	std::string _name;
	uint16_t expvalue;
	uint16_t expdir;
	short int ExecuteCmde (std::string& _cmde,std::string& _rep);
	int decodeInstruct(std::string& _cmde);
	int setDir(uint16_t pin, uint8_t dir);
	int writepin(uint16_t pin, uint8_t state);
	uint16_t readPort();
	int configseq();

};

#endif /* EXPANDADDO_H_ */
