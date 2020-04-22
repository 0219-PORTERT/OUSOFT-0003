/*
 * Cna.h
 *
 *  Created on: 22 avr. 2020
 *      Author: PARIS
 */

#ifndef CNA_H_
#define CNA_H_

#include "ScpiClientServer.h"
#include <String>
#include <iostream>

#define REQ_RST 1
#define REQ_IDN 2
#define REQ_x 3
#define REQ_QST 4

class Cna : public ScpiClientServer{
public:
	Cna();
	Cna(std::string _name);
	virtual ~Cna();
private:
	int modValue;
	std::string _name;
	short int ExecuteCmde (std::string& _cmde,std::string& _rep);
	int decodeInstruct(std::string& _cmde);
};

#endif /* CNA_H_ */
