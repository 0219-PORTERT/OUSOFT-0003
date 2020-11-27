/*
 * CerrG.h
 *
 *  Created on: 31 mars 2020
 *      Author: PARIS
 */

#ifndef CERRG_H_
#define CERRG_H_

#include <string>

class CerrG {
public:
	CerrG();
	CerrG(int _specificPosition);
	virtual ~CerrG();
	uint32_t stateMachine;
	short int cerr;
	short int adresse[6];//public
	short int specificPosition;//public
	short int errid;//public

	void AddErrorCode(CerrG _client);
	void AddErrorCode(short int Cerr);
	int SetSpecificPosition(short int _specificPosition);

	int getSpecificPosition(void);

	int SetErrId(short int _specificPosition, short int _errAdress );
	int SetStateMachineErrorCode(uint16_t code);

	std::string ToString(void);

	void clearCerrg(void);

private:


};

#endif /* CERRG_H_ */
