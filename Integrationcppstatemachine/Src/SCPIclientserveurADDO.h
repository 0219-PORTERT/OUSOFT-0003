/*
 * SCPIclientserveurADDO.h
 *
 *  Created on: 7 oct. 2020
 *      Author: PARIS
 */

#ifndef SCPICLIENTSERVEURADDO_H_
#define SCPICLIENTSERVEURADDO_H_


#include "ScpiClientServer.h"
#include <String>
#include <iostream>
#include "EXPADDO24.h"

/*Relay adress*/

#define K1	 0
#define K2   1
#define K3   2
#define K4   3
#define K5   4
#define K6   5
#define K7   6
#define K8   7
#define K9   8
#define K10  9
#define K11  10
#define K12  11
#define K13  12
#define K14  13
#define K15  14
#define K16  15

/*PortC address*/
#define RelayboardAddress 0x02


#define REQ_RST 1
#define REQ_IDN 2

#define REQ_DIOARD 3
#define REQ_DIOBRD 4
#define REQ_DIOCRD 5

#define REQ_DIOAWR 6
#define REQ_DIOBWR 7
#define REQ_DIOCWR 8

#define REQ_DIOAQSTDIR 9
#define REQ_DIOBQSTDIR 10
#define REQ_DIOCQSTDIR 11

#define REQ_DIOASETDIR 12
#define REQ_DIOBSETDIR 13
#define REQ_DIOCSETDIR 14

#define REQ_RELAY 15

#define REQ_TSTAB 16
#define REQ_TSTAC 17


class SCPIclientserveurADDO : public ScpiClientServer {
public:
	SCPIclientserveurADDO();
	SCPIclientserveurADDO(std::string _name);
	virtual ~SCPIclientserveurADDO();

	uint8_t configRelay(uint8_t newstate, uint16_t relayTochange);
private:
	std::string _name;
	uint16_t staterelay;
	uint8_t writevalue;
	uint8_t dir;

	EXPADDO24 ExpADDOa;
	EXPADDO24 ExpADDOb;
	EXPADDO24 ExpADDOc;

	uint8_t reltochange;
	uint8_t statereltochange;

	short int ExecuteCmde (std::string& _cmde,std::string& _rep);
	int decodeInstruct(std::string& _cmde);


	uint8_t commutrelay(uint8_t PortC_Address,uint16_t PortAB_Address);



};

#endif /* SCPICLIENTSERVEURADDO_H_ */
