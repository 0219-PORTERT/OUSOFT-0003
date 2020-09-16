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

ScpiClientServer::ScpiClientServer(std::string _HEADER) {
	this->_HEADER = _HEADER;
	this->sendEnable = 0;
	this->modeperoquetstatut = 0;
}

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

short int ScpiClientServer::AddClient(ScpiClientServer* _client) {
	short int _specificPosition = 0;
	int lastElement = 0;
	short int masque = 0;
	short int _errAdress = 0;

	lastElement = this->getTailleListClient();

	if ((_client->getHeader() != "") && (lastElement <= 16)) {

		this->listeClients.push_back(_client);
		_specificPosition = this->codeErr.specificPosition + 1; //+1 par rapport au serveur
		_errAdress = masque | (1u << lastElement); // 1 bit à 1 décalé de lastelement
		_client->codeErr.SetErrId(_specificPosition, _errAdress);
	} else {
		return 0;
	}
	return 0;
}

short int ScpiClientServer::DecodeMsg(std::string& _msg, std::string& _header,
		std::string& _cmde) {

	int a = 0;

	int first = -1;
	first = _msg.find(":");

	if (_msg.find("*") != string::npos) { //broadcast
		_cmde = _msg;
		a = BRD_CMD;
	} else if ((_msg.find("ERR ?") != string::npos)
			&& (this->_HEADER.compare("TEST0256")) == 0) {
		a = ERR_REQ;
	} else if (first == -1) { //exec commande courte
		_header.assign("\0");
		_cmde.assign(_msg);
		a = EXEC_CMD;
	} else if (first != -1) { // passe au serveur
		_header = _msg.substr(0, first);
		_cmde = _msg.substr(first + 1);
		a = FIND_NEXT_SERVER;
	} else {
		throw ERROR_SYNTHAX_ERROR;
	}

	return a;

}

short int ScpiClientServer::ExecuteCmde(std::string& _cmde, std::string &_rep) {

	//throw ERROR_TEST;
	//std::string Order = "Order66";


		if (_cmde.compare("*IDN ?") == 0) {
			//_rep.assign("je suis le client SCPI " + this->_HEADER);
			_rep.assign(this->_HEADER);
		} else {
			//throw ERR_CMDE;
		}



	if (this->modeperoquetstatut != 0) {
		_rep.assign(
				"MODEPEROQUET: Client " + this->_HEADER + " et j'ai recu "
						+ _cmde + "\n\r" + _rep);
	}

	return 0;
}

std::string ScpiClientServer::getHeader() {
	return this->_HEADER;
}

ScpiClientServer* ScpiClientServer::getClient(uint8_t pos) {
	return listeClients.at(pos);
}

short int ScpiClientServer::ReceiveMsg(std::string _msg, std::string &_rep,
		CerrG &_cerrg) {

	std::string _header;
	std::string _cmde;

	try {
		_header.reserve(256);
		_cmde.reserve(256);

		_header.assign("\0");
		_cmde.assign("\0");

		switch (this->DecodeMsg(_msg, _header, _cmde)) {
		case BRD_CMD:
			BroadCastCmde(_cmde, _rep); //envoie de la commande à tous les clients en reccursif
			break;
		case EXEC_CMD:
			if (sendEnable != 0) {
				throw ERR_CMDE_EXEC_FORBIDEN;
			} else {
				this->ExecuteCmde(_cmde, _rep);
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

	} catch (int e) {
		this->codeErr.AddErrorCode(e);
		_cerrg.AddErrorCode(e);
		_cerrg.AddErrorCode(this->codeErr);
		throw;
	}

	return 0;
}

int ScpiClientServer::FindClientinList(std::string headertofind) {
	for (int i = 0; i < listeClients.size(); i++) {
		if (headertofind.compare(listeClients.at(i)->getHeader()) == 0) {
			return i;
		}
	}
	return -1;
}

int ScpiClientServer::getTailleListClient() {
	return this->listeClients.size();
}

void ScpiClientServer::SetSendEnable(int _sendEnbleValue) {

	this->sendEnable = _sendEnbleValue;

	for (int i = 0; i < this->listeClients.size(); i++) {
		this->getClient(i)->SetSendEnable(_sendEnbleValue);
	}

}
void ScpiClientServer::modeperoquet(int mode) {
	this->modeperoquetstatut = mode;

	for (int i = 0; i < this->listeClients.size(); i++) {
		this->getClient(i)->modeperoquet(mode);
	}
}

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

ScpiClientServer* ScpiClientServer::getSCPIClientServer() {
	return this;
}

