/*
 * expanders.h
 *
 *  Created on: 27 sept. 2019
 *      Author: RENAULT_E
 */

#ifndef EXPANDERS_H_
#define EXPANDERS_H_

#include "string.h"

class expanders {
public:
	expanders();
	virtual ~expanders();

	void Add(int value);
	int GetValue();
	char* GetType();

protected:
	int value=0;
	char name[24]={0};
};

#endif /* EXPANDERS_H_ */
