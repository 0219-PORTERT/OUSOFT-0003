/*
 * Pwm.h
 *
 *  Created on: 15 avr. 2020
 *      Author: PARIS
 */

#ifndef PWM_H_
#define PWM_H_

#include "ScpiClientServer.h"
#include <String>
#include <iostream>

#define REQ_RST 1
#define REQ_IDN 2
#define REQ_x 3
#define REQ_QST 4

#define MAX_FREQ_VALUE 10000000000


class Pwm : public ScpiClientServer {
public:
	Pwm();
	Pwm(std::string _name);
	virtual ~Pwm();



private:
	int rpmValue;
	std::string _name;
	short int ExecuteCmde (std::string& _cmde,std::string& _rep);
	int decodeInstruct(std::string& _cmde);


};

#endif /* PWM_H_ */
