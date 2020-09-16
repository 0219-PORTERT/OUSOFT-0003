/*
 * FonctionsAutotest.h
 *
 *  Created on: 11 sept. 2019
 *      Author: PARIS
 */

#ifndef FONCTIONSAUTOTEST_H_
#define FONCTIONSAUTOTEST_H_
#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f7xx_hal.h"

/*ERROR level 1*/
#define CERR_AUTOTEST_ERROR 0x1000
#define CERR_AUTOTEST_NOERROR 0x0000

/*ERROR level 2*/
#define CERR_NOERRROR 0x000
#define CERR_I2C4COMERRROR 0x100
#define CERR_EEPROM1TESTERRROR 0x200
#define CERR_EEPROM2TESTERRROR 0x300
#define CERR_CHECKTEMPERRROR 0x400
#define CERR_SIMTEMP1ERRROR 0x500
#define CERR_TESTEXPERRROR 0x600

/*ERROR level 3*/
typedef enum {
	CERR_NOLOCALERRROR = 0x00,
	CERR_ERRROR1,
	CERR_ERRROR2,
	CERR_ERRROR3,
	CERR_ERRROR4,
	CERR_ERRROR5,
	CERR_ERRROR6,
	CERR_ERRROR7,
	CERR_ERRROR8,
	CERR_ERRROR9,
	CERR_ERRROR10,
	CERR_ERRROR11,
	CERR_ERRROR12,
	CERR_ERRROR13,

} autoTestLocalERR;

uint16_t autoTest(void);

uint16_t CheckI2C3(void);
uint16_t CheckI2C2(void);
uint16_t CheckI2C1(void);
uint16_t CheckI2C4(void);
uint16_t CheckI2CMain();

uint16_t testEeprom1(void);
uint16_t testEeprom2(void);
uint16_t testTemperature(void);
uint16_t Simtemp1(void);
uint16_t testEXP(void);
void I2Cscanner(I2C_TypeDef* I2Cx);

#ifdef __cplusplus
}
#endif
#endif /* FONCTIONSAUTOTEST_H_ */
