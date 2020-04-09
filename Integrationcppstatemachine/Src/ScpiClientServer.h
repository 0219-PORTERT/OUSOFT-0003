
#ifndef SCPICLIENTSERVER_H
#define SCPICLIENTSERVER_H

#include <string>
#include <vector>
#include <iostream>
#include "CerrG.h"

/**
  * class ScpiClientServer
  * 
  */

#define BRD_CMD 1
#define EXEC_CMD 2
#define FIND_NEXT_SERVER 3

#define ERROR_LVL_MAX 1
#define ERROR_CLIENT_MAX 2
#define ERROR_EMPTY_CLIENT 3
#define ERROR_CANT_FIND_CLIENT 4
#define ERROR_SYNTHAX_ERROR 5
#define ERROR_BAD_MSG 6

#define ERROR_TEST 99

class ScpiClientServer{
public:

  ScpiClientServer ();
  ScpiClientServer (std::string _HEADER);
  ScpiClientServer (std::string _HEADER, int _errLvl );
  virtual ~ScpiClientServer ();

  short int ReceiveMsg (std::string _msg, std::string &_rep, CerrG &_cerrg);
  short int AddClient (ScpiClientServer* _client);
  short int SetSendEnable (int _sendEnbleValue);


  int getTailleListClient();
  ScpiClientServer* getClient(uint8_t pos);
  std::string getHeader();

  CerrG codeErr;

private:

  int sendEnable;
  std::string _HEADER;
  std::vector<ScpiClientServer*> listeClients;

  short int DecodeMsg (std::string& _msg, std::string& _header, std::string& _cmde);
  int FindClientinList(std::string headertofind);
  ScpiClientServer GetClientFromList(std::string& p_header);
  short int ExecuteCmde (std::string& _cmde,std::string& _rep);
  short int ExecuteClient (std::string& _header,std::string& _rep);
  int BroadCastCmde(std::string& _cmde, std::string& _rep);

  void initAttributes () ;
};

#endif // SCPICLIENTSERVER_H
