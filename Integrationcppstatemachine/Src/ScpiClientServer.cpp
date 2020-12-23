/*
 * ScpiClientServer.cpp
 *
 *  Created on: 6 mars 2020
 *      Author: PARIS
 */

#include "ScpiClientServer.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

/**
 * @brief  constructeur des clients scpi
 * @param  _HEADER: nom du client
 * @retval None
 */
ScpiClientServer::ScpiClientServer(std::string _HEADER) {
	this->_HEADER = _HEADER;
	this->sendEnable = 0;
	this->modeperoquetstatut = 0;
}

/**
 * @brief  constructeur pour le 1er client scpi
 * @param  _HEADER: nom du client
 * @param  _errLvl: indique le niveau d'ou démarre les codes erreurs
 * @retval None
 */
ScpiClientServer::ScpiClientServer(std::string _HEADER, int _errLvl) {
	this->_HEADER = _HEADER;
	this->sendEnable = 0;
	this->modeperoquetstatut = 0;

	this->codeErr.SetSpecificPosition(_errLvl);
	this->codeErr.adresse[0] = 1; // attribution de son adresse en dur car c'est le 1er serveur

}

ScpiClientServer::ScpiClientServer() {

}

ScpiClientServer::~ScpiClientServer() {
	// TODO Auto-generated destructor stub
}

/**
 * @brief  Ajoute un client dans l'arboressence scpi
 * @param * _client: pointeur du client à ajouter
 * @retval None
 */
short int ScpiClientServer::AddClient(ScpiClientServer* _client) {
	short int _specificPosition = 0;
	int lastElement = 0;
	short int masque = 0;
	short int _errAdress = 0;

	lastElement = this->getTailleListClient();//prend le dernier élement de liste

	if ((_client->getHeader() != "") && (lastElement <= 16)) {//limite de 16 clients dans la liste de chaque clientserveur

		this->listeClients.push_back(_client);//ajout du client
		_specificPosition = this->codeErr.specificPosition + 1; //+1 par rapport au serveur
		_errAdress = masque | (1u << lastElement); // 1 bit à 1 décalé de lastelement
		_client->codeErr.SetErrId(_specificPosition, _errAdress);//donne le code erreur au client
	} else {
		return 0;
	}
	return 0;
}

/**
 * @brief  Decode le message scpi reçu
 * @param & _msg: référence du message reçu
 * @param & _header: nom du clientserveur à qui est adresser le message
 * @param & _cmde: commande à executer
 * @retval 0 si pas d'erreur
 */
short int ScpiClientServer::DecodeMsg(std::string& _msg, std::string& _header,
		std::string& _cmde) {

	int a = 0;

	int first = -1;
	first = _msg.find(":");

	if (_msg.find("*") != string::npos) { //si il y le caractère '*' alors c'est broadcast
		_cmde = _msg;
		a = BRD_CMD;
	} else if ((_msg.find("ERR ?") != string::npos) && (this->_HEADER.compare("TEST0256")) == 0) {//commande spéciale lorsqu'on demande au système si il y a une erreur
		a = ERR_REQ;
	} else if (first == -1) { //c'est le bon bon client donc exec commande courte
		_header.assign("\0");
		_cmde.assign(_msg);
		a = EXEC_CMD;
	} else if (first != -1) { // passe au serveur suivant le reste de la commande
		_header = _msg.substr(0, first);
		_cmde = _msg.substr(first + 1);
		a = FIND_NEXT_SERVER;
	} else {
		throw ERROR_DECOD_INSTRUCT;
	}

	return a;

}

/**
 * @brief Execute une commande scpi
 * @param & _cmde: commande à executer
 * @param & _rep: chaine de réponse
 * @retval 0 si pas d'erreur
 */
short int ScpiClientServer::ExecuteCmde(std::string& _cmde, std::string &_rep) {
	uint8_t test = 0;

		if (_cmde.compare("*IDN ?") == 0) { //commandes courtes des clients/serveur
			_rep.assign(this->_HEADER);
		}else if((_cmde.compare("*CLR") == 0)){

		}else{
			throw ERROR_CMD_SCPI_SYNTHAX_ERROR;
		}



	if (this->modeperoquetstatut != 0) {
		_rep.assign(
				"MODEPEROQUET: Client " + this->_HEADER + " et j'ai recu "
						+ _cmde + "\n\r" + _rep);
	}

	return test;
}

/**
 * @brief renvoie le nom d'un client
 * @retval le nom du client
 */
std::string ScpiClientServer::getHeader() {
	return this->_HEADER;
}

/**
 * @brief retourne le pointeur d'un clienterveur
 * @param & _pos: position du client dans la liste à recuperer
 * @retval renvoie le pointeur
 */
ScpiClientServer* ScpiClientServer::getClient(uint8_t pos) {
	return listeClients.at(pos);
}

/**
 * @brief receptionne un message scpi
 * @param _msg: message reçue
 * @param & _rep: chaine de réponse
 * @param &_cerrg: objet maincerrg pour le code erreur
 * @retval 0 si pas d'erreur
 */
short int ScpiClientServer::ReceiveMsg(std::string _msg, std::string &_rep,
		CerrG &_cerrg) {

	std::string _header;
	std::string _cmde;

	try {
		_header.reserve(256);
		_cmde.reserve(256);

		_header.assign("\0");
		_cmde.assign("\0");

		switch (this->DecodeMsg(_msg, _header, _cmde)) {//décode le message scpi
		case BRD_CMD:
			BroadCastCmde(_cmde, _rep); //envoie de la commande à tous les clients en reccursif
			break;
		case EXEC_CMD:
			if (sendEnable != 0) {
				throw ERR_CMDE_EXEC_FORBIDEN;
			} else {
				this->ExecuteCmde(_cmde, _rep);//excute une commande scpi
			}
			break;
		case FIND_NEXT_SERVER: {
			int positionClient = this->FindClientinList(_header); //cherche le header du prochain client et renvoi sa position dans le vector
			if (positionClient == -1) {
				throw ERROR_CANT_FIND_CLIENT;
			} else {
				this->getClient(positionClient)->ReceiveMsg(_cmde, _rep,
						_cerrg); //accéde à la ref du prochain client dans le vector
			}
		}
			break;
		case ERR_REQ:
			_rep.assign(_cerrg.ToString());
			_cerrg.clearCerrg();
			break;
		default:
			throw ERROR_BAD_MSG;
			break;

		}

	} catch (int e) {// en cas d'erreur, ajout du code erreur dans _cerrg
		this->codeErr.AddErrorCode(e);
		_cerrg.AddErrorCode(e);
		_cerrg.AddErrorCode(this->codeErr);
		throw;
	}

	return 0;
}

/**
 * @brief cherche le client dans la liste d'un client serveur
 * @param headertofind: nom du client à trouver
 * @retval la position du client dans la liste, -1 si le client n'est pas dedans
 */
int ScpiClientServer::FindClientinList(std::string headertofind) {
	for (int i = 0; i < listeClients.size(); i++) {
		if (headertofind.compare(listeClients.at(i)->getHeader()) == 0) {
			return i;
		}
	}
	return -1;
}

/**
 * @brief donne le nombre de client dans la liste
 * @retval le nombre de client
 */
int ScpiClientServer::getTailleListClient() {
	return this->listeClients.size();
}

/**
 * @brief permet de bloquer la transmission scpi d'un serveur vers un client
 * @param _sendEnbleValue: etat du mode send enable
 * @retval None
 */
void ScpiClientServer::SetSendEnable(int _sendEnbleValue) {

	this->sendEnable = _sendEnbleValue;

	for (int i = 0; i < this->listeClients.size(); i++) {
		this->getClient(i)->SetSendEnable(_sendEnbleValue);
	}

}

/**
 * @brief Mode perroquet, chaque client repete ce qu' il a reçu
 * @param mode: choisi si le mode est activé ou pas
 * @retval None
 */
void ScpiClientServer::modeperoquet(int mode) {
	this->modeperoquetstatut = mode;

	for (int i = 0; i < this->listeClients.size(); i++) {
		this->getClient(i)->modeperoquet(mode);
	}
}

/**
 * @brief Transmission d'une commande courte à tous les clients scpi
 * @param & _cmde: commande à transmettre
 * @param & _rep: chaine de réponse
 * @param & streponse: réponse de chaque client
 * @retval None
 */
int ScpiClientServer::BroadCastCmde(std::string& _cmde, std::string& _rep) {
	std::string streponse;

	streponse.reserve(256);
	streponse.assign("\0");

	this->ExecuteCmde(_cmde, streponse);


	//_rep = _rep + streponse + ";" + "\n\r";
	_rep = _rep + streponse + "|";

	for (int i = 0; i < this->listeClients.size(); i++) {
		this->getClient(i)->BroadCastCmde(_cmde, _rep);
	}
	return 0;
}

/**
 * @brief retourne le pointeur du client actuel
 * @retval pointeur du client scpi en cours
 */
ScpiClientServer* ScpiClientServer::getSCPIClientServer() {
	return this;
}

