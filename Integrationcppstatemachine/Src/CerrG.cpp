/*
 * CerrG.cpp
 *
 *  Created on: 31 mars 2020
 *      Author: PARIS
 */

#include "CerrG.h"
#include <string>

/**
 * @brief  constructeur cerrg
 * @retval None
 */
CerrG::CerrG() {
	for(int i =0; i<6;i++){
		adresse[i] =0;
	}
	this->specificPosition = 0;
	this->cerr = 0;
	this->stateMachine = 0;
}

/**
 * @brief  constructeur cerrg avec une position spécifique pour le 1er objet
 * @param  _specificPosition: défini la position du 1er cerrg
 * @retval None
 */
CerrG::CerrG(int _specificPosition) {
	for(int i =0; i<6;i++){
		adresse[i] =0;
	}
	this->specificPosition = _specificPosition;
	this->cerr = 0;
	this->stateMachine = 0;
}

CerrG::~CerrG() {
	// TODO Auto-generated destructor stub
}

/**
 * @brief  Ajoute le code de cerg (non utilisé)
 * @param  _client: défini la position du 1er cerrg
 * @retval None
 */
void CerrG::AddErrorCode(CerrG _client){

	for(int i =0; i<=6;i++){
		this->adresse[i] = this->adresse[i] | _client.adresse[i] ;
	}
}

/**
 * @brief  Ajoute le code d'erreur dans l'objet cerrg (en cas d'une erreur détécté)
 * @param  Cerr: code erreur (definie dans CerrG.h) lancé lors d'une exeption
 * @retval None
 */
void CerrG::AddErrorCode(short int Cerr){

	if(this->cerr == 0){//seul la 1ere erreur est prise en compte
		this->cerr = Cerr;
	}

}

/**
 * @brief  Uniquement lors de la création de l'objet principale de scpi (tête de l'arboressanc), indique la position de départ du code erreur (ici 0)
 * @param  _specificPosition: position d'ou commancer le code erreur (uniquement pour le 1er client scpiclientserver)
 * @retval None
 */
int CerrG::SetSpecificPosition(short int _specificPosition){

	this->specificPosition = _specificPosition;

	return 0;
}

/**
 * @brief  Lors de la création des autres clients scpi, donne le code erreur à chaque client
 * @param  _specificPosition: position/étage scpi de chaque client
 * @param  _errAdress: position du client dans sa branche scpi
 * @retval None
 */
int CerrG::SetErrId(short int _specificPosition, short int _errAdress ){

	this->specificPosition = _specificPosition;
	this->adresse[_specificPosition] = _errAdress;
	this->errid= _errAdress;

	/** client A -> _specificPosition:0
	 _errAdress:0
	 	 sous-client AA ->_specificPosition:1
		 _errAdress:0
		 sous-client AB ->_specificPosition:1
		 _errAdress:0
	 client B -> _specificPosition:1
	_errAdress:0
	 	 sous-client BA ->_specificPosition:1
		_errAdress:0
			sous-client BAA ->_specificPosition:2
			_errAdress:0
			sous-client BAB ->_specificPosition:2
			_errAdress:1**/

	return 0;
}

/**
 * @brief  Converti le code erreur en chaine
 * @retval Chaine erreur
 */
std::string CerrG::ToString(void){

	std::string strError = "";
	//index de adresse[] est la branche, dans le tableau à l'indice index se trouve le code erreur
	strError = "ERROR :" + std::to_string(this->stateMachine)+"_"+std::to_string(this->adresse[0])+"."+std::to_string(this->adresse[1])+"."+std::to_string(this->adresse[2])+"."+std::to_string(this->adresse[3])+"."+std::to_string(this->adresse[4])+"."+std::to_string(this->adresse[5])+"_"+std::to_string(this->cerr);

	return strError;
}

/**
 * @brief  efface le code erreur
 * @retval None
 */
void CerrG::clearCerrg(void){
	for(int i =0; i<6;i++){
			adresse[i] =0;
		}
		this->cerr = 0;
		this->stateMachine = 0;
}

/**
 * @brief  donne le code erreur pour le champ machine d'état
 * @param  code: code erreur pour la machine d'état,
 * @retval None
 */
int CerrG::SetStateMachineErrorCode(uint16_t code){

	this->stateMachine = code;


	return 0;
}
