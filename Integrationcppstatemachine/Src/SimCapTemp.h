/*
 * SimCapTemp.h
 *
 *  Created on: 28 avr. 2020
 *      Author: PARIS
 */

#ifndef SIMCAPTEMP_H_
#define SIMCAPTEMP_H_

#include "ScpiClientServer.h"
#include <String>
#include <iostream>
#include "OUELEC0158.h"

#define TEMPCAP1 0x00
#define TEMPCAP2 0x01
#define TEMPCAP3 0x02
#define TEMPCAP4 0x03

#define TEMPCAP5 0x00
#define TEMPCAP6 0x01
#define TEMPCAP7 0x02
#define TEMPCAP8 0x03

#define REQ_RST 1
#define REQ_IDN 2
#define REQ_x 3
#define REQ_QST 4

#define REQ_MIN 5
#define REQ_MAX 6
#define REQ_STEP 7

#define REQ_CODE 8

class SimCapTemp : public ScpiClientServer {
public:
	SimCapTemp();
	SimCapTemp(std::string _name, uint8_t _capteur, uint8_t _addpot1k, uint8_t _addpot100k);
	SimCapTemp(std::string _name, uint8_t _capteur, OUELEC_0158 _rack);
	virtual ~SimCapTemp();
private:
	std::string _name;
	uint8_t capteur;
	OUELEC_0158 rack;
	uint8_t addpot1k;
	uint8_t addpot100k;


	int tempValue;
	short int ExecuteCmde (std::string& _cmde,std::string& _rep);
	int decodeInstruct(std::string& _cmde);

	void setTemp(int value);
	void setTempcode(int value);

	void MeasMin();
	void MeasMax();
	void MeasStep();
};

#endif /* SIMCAPTEMP_H_ */
