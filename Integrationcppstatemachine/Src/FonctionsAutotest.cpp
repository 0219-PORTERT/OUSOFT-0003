/*
 * FonctionsAutotest.c
 *
 *  Created on: 11 sept. 2019
 *      Author: PARIS
 */

#include "FonctionsAutotest.h"
#include "defines.h"
#include "tm_stm32_i2c.h"
#include "i2c.h"
#include "usart.h"
#include <String>
#include <iostream>
#include "stm32fxxx_hal.h"
#include "main.h"
#include "OUELEC0158.h"
#include "OUCART0018.h"
#include "ScpiClientServer.h"
#include <string>
#include <iostream>
#include "CerrG.h"

extern OUELEC_0158 rack1;
extern OUELEC_0158 rack2;
extern OUCART0018 psu;
extern OUCART0018 accordsOsc;
extern ScpiClientServer SCPI_MAIN;
extern CerrG mainCerrG;

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

	/*if(TM_I2C_IsDeviceConnected(I2C4, I2CEEPROM1) != TM_I2C_Result_Ok ){
		return  CERR_ERRROR1 ;
	}else if(TM_I2C_IsDeviceConnected(I2C4, I2CEEPROM2)!= TM_I2C_Result_Ok){
		return  CERR_ERRROR2 ;
	}else if(TM_I2C_IsDeviceConnected(I2C4, I2CTEMP)!= TM_I2C_Result_Ok){
		return  CERR_ERRROR3 ;
	}else if(TM_I2C_IsDeviceConnected(I2C4, I2C4_POT1K_PHYADD)!= TM_I2C_Result_Ok){
		return  CERR_ERRROR4 ;
	}else if(TM_I2C_IsDeviceConnected(I2C4, I2C4_POT100K_PHYADD)!= TM_I2C_Result_Ok){
		return  CERR_ERRROR5 ;
	}else if(TM_I2C_IsDeviceConnected(I2C4, I2CEXP)!= TM_I2C_Result_Ok){
		return  CERR_ERRROR6 ;
	}

	return CERR_NOLOCALERRROR;*/
}

uint16_t CheckI2CMain(void){

	if(TM_I2C_IsDeviceConnected(I2C4, EXP_DATA_ADRESS_I2CADD)!= TM_I2C_Result_Ok){
		__NOP();
		return  CERR_ERRROR1 ;
	}if(TM_I2C_IsDeviceConnected(I2C4, POT100KA_I2CADD)!= TM_I2C_Result_Ok){
		__NOP();
		return  CERR_ERRROR2 ;
	}if(TM_I2C_IsDeviceConnected(I2C4, POT1KA_I2CADD)!= TM_I2C_Result_Ok){
		__NOP();
		return  CERR_ERRROR3 ;
	}if(TM_I2C_IsDeviceConnected(I2C4, POT100KB_I2CADD)!= TM_I2C_Result_Ok){
		__NOP();
		return  CERR_ERRROR4 ;
	}if(TM_I2C_IsDeviceConnected(I2C4, POT1KB_I2CADD)!= TM_I2C_Result_Ok){
		__NOP();
		return  CERR_ERRROR5 ;
	}if(TM_I2C_IsDeviceConnected(I2C4, EXP_DIO_I2CADD)!= TM_I2C_Result_Ok){
		__NOP();
		return  CERR_ERRROR6 ;
	}if(TM_I2C_IsDeviceConnected(I2C4, MEMU1_I2CADD)!= TM_I2C_Result_Ok){
		__NOP();
			return  CERR_ERRROR7 ;
	}if(TM_I2C_IsDeviceConnected(I2C4, MEMU2_I2CADD)!= TM_I2C_Result_Ok){
		__NOP();
		return  CERR_ERRROR8 ;
	}if(TM_I2C_IsDeviceConnected(I2C4, MEMU3_I2CADD)!= TM_I2C_Result_Ok){
		__NOP();
		return  CERR_ERRROR9 ;
	}if(TM_I2C_IsDeviceConnected(I2C4, MEMU4_I2CADD)!= TM_I2C_Result_Ok){
		__NOP();
		return  CERR_ERRROR10 ;
	}if(TM_I2C_IsDeviceConnected(I2C4, TEM_HUM_I2CADD)!= TM_I2C_Result_Ok){
		__NOP();
		return  CERR_ERRROR11 ;
	}

	return CERR_NOLOCALERRROR;
}

void I2Cscanner(I2C_TypeDef* I2Cx){
	UART_transmit("***I2C SCANNER***");

	int adress = 1;
	TM_I2C_Result_t result;
	int count = 0;

	UART_transmit("Scanning");


	for(adress = 1; adress < 256;adress ++){



		if((adress == 208) || (adress == 209)){
			UART_transmit("208 209 adresse suprimees");
		}else{
			result = TM_I2C_IsDeviceConnected(I2Cx,adress );

					if(result == TM_I2C_Result_Ok){
						UART_transmit("Device found at adress:" + std::to_string(adress));
						count++;
					}
					if(result == TM_I2C_Result_Error){
						//UART_transmit("NO Device found at adress:" + std::to_string(adress));
					}
		}




		//HAL_Delay(500);
	}

	UART_transmit("Done, " +std::to_string(count) + "device found" );


	//while(1){}


}

uint16_t CheckI2C3(void){
	if(TM_I2C_IsDeviceConnected(I2C3, EXPSECU_I2CADD)!= TM_I2C_Result_Ok){
		__NOP();
		return  CERR_ERRROR1 ;
	}
	return CERR_NOLOCALERRROR;
}


uint16_t CheckI2C2(void){
	if(TM_I2C_IsDeviceConnected(I2C2, EXPSECU_I2CADD)!= TM_I2C_Result_Ok){
		__NOP();
		return  CERR_ERRROR1 ;
	}
	return CERR_NOLOCALERRROR;
}
uint16_t CheckI2C1(void){
	if(TM_I2C_IsDeviceConnected(I2C1, EXPSECU_I2CADD)!= TM_I2C_Result_Ok){
		__NOP();
		return  CERR_ERRROR1 ;
	}
	return CERR_NOLOCALERRROR;
}

std::string checkDTI(){

	uint8_t *data = 0;
	uint16_t oucart0014value = 0;

	/*uint8_t masqueCONTROL = 0x00;
	uint8_t masquePSU = 0x08;
	uint8_t masqueRACKCH = 0xF2;
	uint8_t masqueACCOSC = 0x00;*/
	std::string s;
	char hex_str[5];
	std::string retourdti;

	*data = 0;




	SCPI_MAIN.ReceiveMsg("SECU:SECU:DATA ?",s, mainCerrG);
	oucart0014value = stoi(s);
	oucart0014value = oucart0014value & 0x00ff;


	sprintf(hex_str, "0x%x", oucart0014value);
	retourdti = retourdti + hex_str;

	if(rack1.carteEIC1.isConnected() == 0){
		rack1.carteEIC1.readPort(0x00, data);
		sprintf(hex_str, "0x%x", *data);
		retourdti = retourdti +","+ hex_str;
	}else{
		retourdti = retourdti +","+"NC";
	}
	rack1.carteEIC1.switchToi2c(6);


	if(rack2.carteEIC1.isConnected() == 0){
		rack2.carteEIC1.readPort(0x00, data);
		sprintf(hex_str, "0x%x", *data);
		retourdti = retourdti +","+ hex_str;
	}else{
		retourdti = retourdti +","+"NC";
	}
	rack2.carteEIC1.switchToi2c(6);



	if(psu.isConnected() == 0){
		psu.readPort(0x00, data);
		sprintf(hex_str, "0x%x", *data);
		retourdti = retourdti +","+ hex_str;
	}else{
		retourdti = retourdti +","+"NC";
	}
	psu.switchToi2c(6);


	if(accordsOsc.isConnected() == 0){
		accordsOsc.readPort(0x00, data);
		sprintf(hex_str, "0x%x", *data);
		retourdti = retourdti +","+ hex_str;
	}else{
		retourdti = retourdti +","+"NC";
	}
	accordsOsc.switchToi2c(6);





	return retourdti;


	/*comment on switch d'un sous*ensemble à l'autre ?*/
}

uint16_t CheckIDs(void){

	//read oucart-18 1
	//read oucart-18 2
	//read oucart-18 3
	//read oucart-18 4

	//load calibration
}


uint16_t testEeprom1(void){

	/*uint8_t read = 0;
	uint8_t temp = 0;

	TM_I2C_Read16(I2C4, MEMU1_I2CADD, 0x0000, &read);

	if(read == 0xFF){
		read = 0;
	}else{
		read++;
	}
	temp = read;
	TM_I2C_Write16(I2C4, MEMU1_I2CADD, 0x0000, &read);

	HAL_Delay(10);

	TM_I2C_Read16(I2C4, MEMU1_I2CADD, 0x0000, &read);

	if(read != temp){
		return CERR_ERRROR7;
	}else{
		return CERR_NOLOCALERRROR;
	}*/





	/*TM_I2C_Write16(I2C4, I2CEEPROM1, 0x0000, 0x00);
	HAL_Delay(10);
	TM_I2C_Read16(I2C4, I2CEEPROM1, 0x0000, &read);

	TM_I2C_Write16(I2C4, I2CEEPROM1, 0x0000, 0x42);
	HAL_Delay(10);
	TM_I2C_Read16(I2C4, I2CEEPROM1, 0x0000, &read);*/
}

uint16_t testEeprom2(void){

	/*uint8_t read = 0;
	uint8_t temp = 0;

	TM_I2C_Read16(I2C4, MEMU2_I2CADD, 0x0000, &read);

	if(read == 0xFF){
		read = 0;
	}else{
		read++;
	}
	temp = read;
	TM_I2C_Write16(I2C4, MEMU2_I2CADD, 0x0000, &read);

	HAL_Delay(10);

	TM_I2C_Read16(I2C4, MEMU2_I2CADD, 0x0000, &read);

	if(read != temp){
		return CERR_EEPROM2TESTERRROR;
	}else{
		return CERR_NOERRROR;
	}*/


	/*TM_I2C_Write16(I2C4, I2CEEPROM2, 0x0000, 0x00);
	HAL_Delay(10);
	TM_I2C_Read16(I2C4, I2CEEPROM2, 0x0000, &read);

	TM_I2C_Write16(I2C4, I2CEEPROM2, 0x0000, 0x23);
	HAL_Delay(10);
	TM_I2C_Read16(I2C4, I2CEEPROM2, 0x0000, &read);*/
}

uint16_t testTemperature(void){
	uint8_t tempread[4];
	tempread[0]=0;
	tempread[1]=0;
	tempread[2]=0;
	tempread[3]=0;
	//TM_I2C_Write(I2C4, TEM_HUM_I2CADD, 0x00, 0x00);
	//TM_I2C_ReadNoRegister(I2C4, TEM_HUM_I2CADD, &tempread);

	uint8_t cmddata[2];
	cmddata[0]=0x2C;
	cmddata[1]=0x06;

	//uint8_t* msb = {0x2c,0x05};
	//msb = 0x2c;

	//&msb[2] = 0x06;

	//uint8_t* lsb;
//	lsb[0] =  0x06;

//1000 1000 0010 0110 000
//1000 1000 0000 0011 0

	//uint8_t msb = 0x2c;
	//uint8_t lsb = 0x05;

	uint8_t data = -1;

	while(1){
		TM_I2C_WriteMultiNoRegister(I2C4, TEM_HUM_I2CADD, cmddata  , 2);
		//HAL_Delay(1);


		//TM_I2C_ReadMultiNoRegister(I2C4, (TEM_HUM_I2CADD)|(1u<<0), tempread, 4);
		TM_I2C_ReadNoRegister(I2C4, (TEM_HUM_I2CADD)|(1u<<0), &data);

		//TM_I2C_WriteNoRegister(I2C4, TEM_HUM_I2CADD, 0x2c);
		//TM_I2C_WriteNoRegister(I2C4, TEM_HUM_I2CADD, 0x06);
	}

	//TM_I2C_Write(I2C4, TEM_HUM_I2CADD, 0x00, 0x00);



	TM_I2C_ReadMultiNoRegister(I2C4, (TEM_HUM_I2CADD)|(1u<<0), tempread, 4);


	return 0;
}
