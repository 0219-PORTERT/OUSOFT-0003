/*
 * EXPADDO24.h
 *
 *  Created on: 7 sept. 2020
 *      Author: PARIS
 */

#ifndef EXPADDO24_H_
#define EXPADDO24_H_


#include <String>
#include <iostream>


/*groupe 8bits*/
#define SIDEA 0
#define SIDEB 1
#define SIDEC 2


class EXPADDO24 {
public:
	EXPADDO24();
	EXPADDO24(uint8_t _side);
	virtual ~EXPADDO24();

	void setSide(uint8_t _side);
	uint8_t readPort();
	uint8_t writePort(uint8_t _writevalue);
	uint8_t getDir();
	uint8_t setDir(uint8_t _dir);

	std::string testAB(uint8_t bytetotest);
	std::string testAC(uint8_t bytetotest);

private:
	uint8_t side;
	uint8_t direction;
	uint8_t writevalue;











};

#endif /* EXPADDO24_H_ */
