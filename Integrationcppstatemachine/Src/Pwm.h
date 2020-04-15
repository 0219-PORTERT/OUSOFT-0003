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

class Pwm : public ScpiClientServer {
public:
	Pwm();
	Pwm(std::string _name);
	virtual ~Pwm();

	short int ExecuteCmde (std::string& _cmde,std::string& _rep);

private:
	int rpmValue;
	std::string Name;
};

#endif /* PWM_H_ */