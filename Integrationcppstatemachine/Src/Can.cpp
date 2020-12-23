/*
 * Can.cpp
 *
 *  Created on: 23 avr. 2020
 *      Author: PARIS
 */

#include "Can.h"
#include "ScpiClientServer.h"
#include <string>
#include <iostream>
#include "tm_stm32_adc.h"
#include "OUELEC0158.h"

#define NB_MOYENNE 30//nombre d'echantillon lors d'une mesure imoy avec l'adc

Can::Can() {
	// TODO Auto-generated constructor stub
	this->channel = TM_ADC_Channel_0;
}

/**
 * @brief  Constructeur pour oucart-0014
 * @param  _name: Nom à donner au client
 * @param  _channel: channel for ADCx. This parameter can be a value of @ref TM_ADC_Channel_t enumeration
 * @retval None
 */
Can::Can(std::string _name, TM_ADC_Channel_t _channel): ScpiClientServer(_name), channel(_channel) {
	this->rack.setRackadress(NULL);
}
/**
 * @brief  Constructeur pour oucart-0020
 * @param  _name: Nom à donner au client
 * @param  _rack: objet rack de charge pour utilisation avec oucart-0020
 * @param  _channel: channel for ADCx. This parameter can be a value of @ref TM_ADC_Channel_t enumeration
 * @retval None
 */
Can::Can(std::string _name, OUELEC_0158 _rack, TM_ADC_Channel_t _channel): ScpiClientServer(_name), rack(_rack), channel(_channel) {

}

Can::~Can() {
	// TODO Auto-generated destructor stub
}
/**
 * @brief  client execute commande scpi
 * @param  & _cmde: référence à la commande scpi à executer
 * @param  & _rep: référence à la chaine de réponse scpi si le client en a besoin
 * @retval peut retourner une erreur
 */
short int Can::ExecuteCmde(std::string& _cmde, std::string& _rep) {
	//_rep.assign("Je suis le execute de la classe Can");

	switch (decodeInstruct(_cmde)) {/*switch sur le resultat de decode(), permet de trouver la fonction à executer*/

	case REQ_RST:
		//RESET ?
		break;
	case REQ_IDN:
		_rep.assign(this->getHeader() +":" + std::to_string(this->channel));
		break;
	case REQ_CHX:
		_rep.assign(std::to_string(readADC()));
		break;
	case REQ_IMOY:
		_rep.assign(std::to_string(readADCImoy(NB_MOYENNE)));
		break;
	case REQ_ISTCURR:
		_rep.assign(std::to_string(InstCurrent()));
		break;
	default:
		//return 1;
		break;
	}

	return 0;
}

/**
 * @brief  décode les instructions scpi
 * @param  & _cmde: référence à la commande scpi à executer
 * @retval None
 */
int Can::decodeInstruct(std::string& _cmde) {
//ici les noms correspondent au commandes scpi
	int sel = 0;

	if (_cmde.compare("*CLR") == 0) {
		sel = REQ_RST;
	} else if (_cmde.compare("*IDN ?") == 0) {
		sel = REQ_IDN;
	} else if(_cmde.compare("CHX ?") == 0){
		sel = REQ_CHX;
	} else if(_cmde.compare("IMOY ?") == 0){
		sel = REQ_IMOY;
	}else if(_cmde.compare("ISTCURR ?") == 0){
		sel = REQ_ISTCURR;
	} else {
		throw ERROR_CMD_SCPIHARD_SYNTHAX_ERROR;//si la commande n'existe pas exeption
	}
	return sel;
}

/**
 * @brief  Lit l'adc
 * @retval Retourne le code adc
 */
uint16_t Can::readADC(){

	uint16_t value = 0;

	if(this->rack.getRackadress() == NULL){//si l'adresse du rack n'est pas définie, c'est que la oucart-0020 n'est pas utilisée
		return TM_ADC_Read(ADC3, this->channel);//donc lecture de l'adc de oucart-0014
	}else{//sinon utlisation de l'adc de oucart-0020
		this->rack.carteEIC1.switchToi2c(1);//switch i2c à l'adresse 1 (oucart-0018 selectionne la oucart-0020)
		value = this->rack.readADC(this->channel);//lecture adc du rack par oucart-0020
		this->rack.carteEIC1.switchToi2c(0);//switch i2c à l'adresse 0, (oucart-0018 selectionne son propre i2c)
		return value;
	}


}


/**
 * @brief  Lit le courant
 * @param  nb: nombre d'échantillon
 * @retval Retourne la valeur convertie en courant de l'adc
 */
float Can::readADCImoy(int nb){
	float value = 0;
	float moyenne = 0;

	if(this->rack.getRackadress() == NULL){//comme précédant, cherche si c'est l'adc de oucart-0014 ou de oucart-0020
		for(int i = 0;i<nb;i++){
			value = value + TM_ADC_Read(ADC3, this->channel);//adc oucart-0014
		}
		moyenne = (float)value/(float)nb;
		return ((3.3/4095.0)*moyenne);
	}else{
		this->rack.carteEIC1.switchToi2c(1);
		for(int i = 0;i<nb;i++){
			value = value + this->rack.readCurrent(this->channel);//adc oucart-0020
		}
		this->rack.carteEIC1.switchToi2c(0);
		moyenne = (float)value/(float)nb;
		return moyenne;
	}
}

/**
 * @brief  donne le courant instantané
 * @retval Retourne la valeur du courant instantané
 */
float Can::InstCurrent(){

	float value = 0;

	if(this->rack.getRackadress() == NULL){
		return ((3.3/4095.0)*TM_ADC_Read(ADC3, this->channel));
	}else{
		this->rack.carteEIC1.switchToi2c(1);
		value = this->rack.readCurrent(this->channel);
		this->rack.carteEIC1.switchToi2c(0);
		return value;
	}
}
