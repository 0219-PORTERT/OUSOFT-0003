/*
 * MCP23xxx.h
 *
 *  Created on: 27 sept. 2019
 *      Author: RENAULT_E
 */

#ifndef EXPANDERS_MCP23XXX_H_
#define EXPANDERS_MCP23XXX_H_

#include "expanders.h"

class MCP23xxx: public expanders {
public:
	MCP23xxx();
	virtual ~MCP23xxx();
};

#endif /* EXPANDERS_MCP23XXX_H_ */
