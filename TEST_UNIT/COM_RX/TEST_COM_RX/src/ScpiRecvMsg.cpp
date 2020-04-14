#include "ScpiRecvMsg.h"
#include <string>
#include <iostream>
#include <vector>

using namespace std;

extern string RX_string;
extern string TX_string;
extern vector<string*[128]> stack_cmd;


ScpiRecvMsg::ScpiRecvMsg()
{
    RX_Buffer=0;
    RX_string.assign(0);
    TX_string.assign(0);
    //ctor
}

ScpiRecvMsg::~ScpiRecvMsg()
{
    //dtor
}


void ReceiveChar(char _charReceived) {


    //this->RX_string.assign("33");


		if(_charReceived != '\r') {
			if(_charReceived == ';'){
				RX_string.append(0);    //Ajout du caractère de fin de ligne avant enregistrement dans le vecteur
				//stack_cmd.push_back(RX_string);
				//RX_string = new string();
				RX_string.assign("\0");
			}else{
				RX_string = RX_string + _charReceived;
			}
		}else {
			//RX_string = RX_string + "\n" + "\r"; ON NE MET PAS LES CARACTERE DE FIN MAIS ILS SERVENT A DECLENCHER L'ACTION
			if (RX_string.compare("*RST\n\r") == 0) {   //Test le zéro de l'égalité
				//stateMachine = RST;
			}else {
				//stack_cmd.push_back(RX_string);
				//test = stack_cmd.at(0);
				//test = stack_cmd.at(1);
				//stateMachine = CMD;
			}
		}


	//__HAL_UART_CLEAR_IT(&huart3, UART_IT_RXNE);

}

