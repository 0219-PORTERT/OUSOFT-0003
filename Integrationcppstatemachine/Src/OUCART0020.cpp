/*
 * OUCART0020.cpp
 *
 *  Created on: 23 nov. 2020
 *      Author: PARIS
 */

#include "OUCART0020.h"
#include "tm_stm32_i2c.h"
#include "i2c.h"

OUCART0020::OUCART0020() {
	// TODO Auto-generated constructor stub

}

OUCART0020::~OUCART0020() {
	// TODO Auto-generated destructor stub
}

void OUCART0020::setI2cAdress(uint8_t adr){
	this->i2cadress = adr;
}

uint16_t OUCART0020::readADC( uint8_t channel){

	uint16_t value = 0;
	uint8_t dataadc[2];
	uint8_t data[3];

	uint8_t lsb = 0;
	uint8_t msb = 0;


	data[0] = 0x02;//pointeur byte adc sequence
	data[1] = 0x00;//msb param
	data[2] = 0 | (1u<<channel);//lsb channel


	uint8_t test = (uint8_t)TM_I2C_IsDeviceConnected(I2C1, this->i2cadress);

	TM_I2C_WriteMultiNoRegister(I2C1, this->i2cadress, data, sizeof(data));//sequence config
	TM_I2C_WriteNoRegister(I2C1, this->i2cadress, 0x40);//lancement de l'aquisition



	TM_I2C_ReadMultiNoRegister(I2C1, 0x23, dataadc, sizeof(dataadc));//lecture



	//value = dataadc[0] << 8;
	//dataadc[0] = (0x0f & dataadc[0]); //suppression de l'adc adress (bits d15 à d12)
	//value = dataadc[0] << 8; //shift des bits d11 à d8 en msb
	//value = value |  dataadc[1];//ajouts des bits lsb d7 à d0

	lsb = dataadc[1];
	msb = (dataadc[0] & 0x0f);

	value = (msb<<8);

	value =		value | lsb;

	return value;
}

uint16_t OUCART0020::setDAC(uint8_t channel, int value){
	uint8_t data[3];

	if(value == 0){
			value = 2048;
		}else if(value < 0){
			value = (int)((2047*value)/100)+2047;
		}else if(value > 0){
			value = (int)((2047*value)/100)+2048;
		}else{
			//
		}




	data[0] = (0x10 | channel) ; //pointer byte pour channel



	data[1] = (0x8 | channel) << 4; //masque 0b1000 et channel décalé en msb 0b1000 0000


	data[1] = data[1] |	((value & 0x0f00)>>8);//ajout dans data1(0b10000000) des 4 bits msb de value avec le masque 0b0000 1111 0000 0000 et décalé de 8bits pour se mettre en lsb de data[1]

	data[2] = (value & 0x00ff);//lsb de value dans data[2]

	/*data[0] = 0x17 ;
	data[1] = 0xff;
	data[2] = 0xff;*/

	TM_I2C_WriteMultiNoRegister(I2C1, this->i2cadress, data, sizeof(data));


}

uint8_t OUCART0020::setconfigADC(uint8_t pins){

	uint8_t data[3];

	data[0] = 0x04;
	data[1] = 0x00;
	data[2] = pins;

	TM_I2C_WriteMultiNoRegister(I2C1, this->i2cadress, data, sizeof(data));
}

uint8_t OUCART0020::setconfigDAC( uint8_t pins){

	uint8_t data[3];

	data[0] = 0x05;
	data[1] = 0x00;
	data[2] = pins;

	TM_I2C_WriteMultiNoRegister(I2C1, this->i2cadress, data, sizeof(data));
}

uint8_t OUCART0020::enableInternalRef(){

	uint8_t data[3];

	data[0] = 0x0b;
	data[1] = 0x02;
	data[2] = 0x00;
	uint8_t test = (uint8_t)TM_I2C_IsDeviceConnected(I2C1, this->i2cadress);
	TM_I2C_WriteMultiNoRegister(I2C1, this->i2cadress, data, sizeof(data));


	/*2xvref activation*/
	uint8_t data2[3];
	data2[0] = 0x03;
	data2[1] = 0x00;
	data2[2] = 0x30;

	TM_I2C_WriteMultiNoRegister(I2C1, this->i2cadress, data2, sizeof(data2));


}
uint8_t OUCART0020::disableInternalRef(){
	uint8_t data[3];

	data[0] = 0x0b;
	data[1] = 0x00;
	data[2] = 0x00;

	TM_I2C_WriteMultiNoRegister(I2C1, this->i2cadress, data, sizeof(data));
}
