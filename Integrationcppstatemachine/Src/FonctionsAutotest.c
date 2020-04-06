/*
 * FonctionsAutotest.c
 *
 *  Created on: 11 sept. 2019
 *      Author: PARIS
 */

#include "FonctionsAutotest.h"
#include "stm32fxxx_hal.h"
#include "defines.h"
#include "tm_stm32_i2c.h"
#include "i2c.h"

uint16_t autoTest(void){

	uint16_t Error;

	/*if((Error = CheckI2C4()) != CERR_NOLOCALERRROR ){
		return CERR_AUTOTEST_ERROR + CERR_I2C4COMERRROR + Error;
	}else if((Error = testEeprom1()) != CERR_NOLOCALERRROR  ){
		return CERR_AUTOTEST_ERROR + CERR_EEPROM1TESTERRROR + Error;
	}else if((Error = testEeprom2()) != CERR_NOLOCALERRROR ){
		return CERR_AUTOTEST_ERROR + CERR_EEPROM2TESTERRROR + Error;
	}else if((Error = testTemperature()) != CERR_NOLOCALERRROR ){
		return CERR_AUTOTEST_ERROR + CERR_CHECKTEMPERRROR + Error;
	}else if((Error = Simtemp1()) != CERR_NOLOCALERRROR ){
		return CERR_AUTOTEST_ERROR + CERR_SIMTEMP1ERRROR + Error;
	}else if((Error = testEXP()) != CERR_NOLOCALERRROR ){
		return CERR_AUTOTEST_ERROR + CERR_TESTEXPERRROR + Error;
	}*/

	return CERR_AUTOTEST_NOERROR;

}

uint16_t CheckI2C4(void){

	if(TM_I2C_IsDeviceConnected(I2C4, I2CEEPROM1) != TM_I2C_Result_Ok ){
		return  CERR_ERRROR1 ;
	}else if(TM_I2C_IsDeviceConnected(I2C4, I2CEEPROM2)!= TM_I2C_Result_Ok){
		return  CERR_ERRROR2 ;
	}else if(TM_I2C_IsDeviceConnected(I2C4, I2CTEMP)!= TM_I2C_Result_Ok){
		return  CERR_ERRROR3 ;
	}else if(TM_I2C_IsDeviceConnected(I2C4, I2CPOT1K)!= TM_I2C_Result_Ok){
		return  CERR_ERRROR4 ;
	}else if(TM_I2C_IsDeviceConnected(I2C4, I2CPOT100K)!= TM_I2C_Result_Ok){
		return  CERR_ERRROR5 ;
	}else if(TM_I2C_IsDeviceConnected(I2C4, I2CEXP)!= TM_I2C_Result_Ok){
		return  CERR_ERRROR6 ;
	}



	return CERR_NOLOCALERRROR;
}

uint16_t testEeprom1(void){

	uint8_t read = 0;
	uint8_t temp = 0;

	TM_I2C_Read16(I2C4, I2CEEPROM1, 0x0000, &read);

	if(read == 0xFF){
		read = 0;
	}else{
		read++;
	}
	temp = read;
	TM_I2C_Write16(I2C4, I2CEEPROM1, 0x0000, &read);

	HAL_Delay(10);

	TM_I2C_Read16(I2C4, I2CEEPROM1, 0x0000, &read);

	if(read != temp){
		return CERR_ERRROR7;
	}else{
		return CERR_NOLOCALERRROR;
	}





	/*TM_I2C_Write16(I2C4, I2CEEPROM1, 0x0000, 0x00);
	HAL_Delay(10);
	TM_I2C_Read16(I2C4, I2CEEPROM1, 0x0000, &read);

	TM_I2C_Write16(I2C4, I2CEEPROM1, 0x0000, 0x42);
	HAL_Delay(10);
	TM_I2C_Read16(I2C4, I2CEEPROM1, 0x0000, &read);*/
}

uint16_t testEeprom2(void){

	uint8_t read = 0;
	uint8_t temp = 0;

	TM_I2C_Read16(I2C4, I2CEEPROM2, 0x0000, &read);

	if(read == 0xFF){
		read = 0;
	}else{
		read++;
	}
	temp = read;
	TM_I2C_Write16(I2C4, I2CEEPROM2, 0x0000, &read);

	HAL_Delay(10);

	TM_I2C_Read16(I2C4, I2CEEPROM2, 0x0000, &read);

	if(read != temp){
		return CERR_EEPROM2TESTERRROR;
	}else{
		return CERR_NOERRROR;
	}


	/*TM_I2C_Write16(I2C4, I2CEEPROM2, 0x0000, 0x00);
	HAL_Delay(10);
	TM_I2C_Read16(I2C4, I2CEEPROM2, 0x0000, &read);

	TM_I2C_Write16(I2C4, I2CEEPROM2, 0x0000, 0x23);
	HAL_Delay(10);
	TM_I2C_Read16(I2C4, I2CEEPROM2, 0x0000, &read);*/
}

uint16_t testTemperature(void){
	uint8_t tempread;
	TM_I2C_Write(I2C4, I2CTEMP, 0x00, 0x00);
	HAL_Delay(10);
	TM_I2C_ReadNoRegister(I2C4, I2CTEMP, &tempread);

	if((tempread == NULL) || (tempread) ){

	}else{

	}
	return 0;
}

uint16_t Simtemp1(void){
	TM_I2C_Write(I2C4, I2CPOT1K, 0x00, 0x00);
	HAL_Delay(10);
	TM_I2C_Write(I2C4, I2CPOT100K, 0x00, 0x00);

	/*uint8_t tol1 = 0;
	uint8_t tol2 = 0;
	TM_I2C_Read(I2C4, (I2CPOT100K | (1u << 0)), 0x3C, &tol1);
	TM_I2C_Read(I2C4, (I2CPOT100K | (1u << 0)), 0x3D, &tol2);*/

	uint8_t tolRabTab [1] [4] = { {0,0,0,0} ,{0,0,0,0}  };

	uint8_t val = 0;

	TM_I2C_Read(I2C4, (I2CPOT100K | (1u << 0)), 0x38, &val);
	tolRabTab[0][0] = val;
	TM_I2C_Read(I2C4, (I2CPOT100K | (1u << 0)), 0x39, &val);
	tolRabTab[1][0] = val;


	TM_I2C_Read(I2C4, (I2CPOT100K | (1u << 0)), 0x3A, &val);
	tolRabTab[0][1] = val;
	TM_I2C_Read(I2C4, (I2CPOT100K | (1u << 0)), 0x3B, &val);
	tolRabTab[1][1]  = val;


	TM_I2C_Read(I2C4, (I2CPOT100K | (1u << 0)), 0x3C, &val);
	tolRabTab[0][2] = val;
	TM_I2C_Read(I2C4, (I2CPOT100K | (1u << 0)), 0x3D, &val);
	tolRabTab[1][2 ]= val;


	TM_I2C_Read(I2C4, (I2CPOT100K | (1u << 0)), 0x3E, &val);
	tolRabTab[0][3] = val;
	TM_I2C_Read(I2C4, (I2CPOT100K | (1u << 0)), 0x3F, &val);
	tolRabTab[1][3] = val;


	return 0;
}

/*uint16_t testEXP(void){




}*/

/*uint16_t test12ADC(void){




}*/
