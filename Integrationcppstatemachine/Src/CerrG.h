/*
 * CerrG.h
 *
 *  Created on: 31 mars 2020
 *      Author: PARIS
 */

#ifndef CERRG_H_
#define CERRG_H_

class CerrG {
public:
	CerrG();
	CerrG(int _specificPosition);
	virtual ~CerrG();
	short int stateMachine;
	short int cerr;
	short int adresse[6];//public
	short int specificPosition;//public

	void AddErrorCode(CerrG _client);
	void AddErrorCode(short int Cerr);
	int SetSpecificPosition(short int _specificPosition);

	int getSpecificPosition(void);

	int SetErrId(short int _specificPosition, short int _errAdress );

private:


};

#endif /* CERRG_H_ */
