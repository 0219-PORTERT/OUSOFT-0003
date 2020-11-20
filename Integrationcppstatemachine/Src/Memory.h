/*
 * Memory.h
 *
 *  Created on: 20 nov. 2020
 *      Author: PARIS
 */

#ifndef MEMORY_H_
#define MEMORY_H_

#include <String>
#include <iostream>

class Memory {
public:
	Memory();
	Memory(uint8_t _i2cadress);

	virtual ~Memory();

	uint8_t readfrommemory(std::string &_toread);
	uint8_t writetomemory(std::string &_towrite);


private:
	uint8_t i2cadress;

	std::string buffertoread;
	std::string buffertowrite;





};

#endif /* MEMORY_H_ */
