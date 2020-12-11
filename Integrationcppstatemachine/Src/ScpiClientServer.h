
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
#define ERR_REQ 4

#define ERROR_LVL_MAX 1
#define ERROR_CLIENT_MAX 2
#define ERROR_EMPTY_CLIENT 3
#define ERROR_CANT_FIND_CLIENT 4
#define ERROR_CMD_SCPIHARD_SYNTHAX_ERROR 5
#define ERROR_CMD_SCPI_SYNTHAX_ERROR 6

#define ERROR_BAD_MSG 7
#define ERROR_DECOD_INSTRUCT 8
#define ERROR_CMD_BAD_ARG 9

#define ERROR_TEST 99

/*ERREUR STATE MACHINE LEVEL*/
#define ERROR_STMA_JSONLOAD 1
#define ERROR_STMA_AUTOTEST_I2CMAIN 2
#define ERROR_STMA_AUTOTEST_I2CSECU 3

//Code erreur pour p_cmde
#define ERR_CMDE 30
#define ERR_CMDE_EMPY ERR_CMDE + 1
#define ERR_CMDE_NULL ERR_CMDE + 2
#define ERR_CMDE_STRUCTURE ERR_CMDE + 3
#define ERR_CMDE_EXEC_FORBIDEN ERR_CMDE + 4

//Code erreur pour p_msg
#define ERR_MSG ERR_CMDE + 20
#define ERR_MSG_EMPY ERR_MSG + 1
#define ERR_MSG_NULL ERR_MSG + 2
#define ERR_MSG_STRUCTURE ERR_MSG + 3

//Code erreur pour p_answer
#define ERR_ANSW ERR_MSG + 20
#define ERR_ANSW_EMPY ERR_ANSW + 1
#define ERR_ANSW_NOT_ZERO_INPUT + 2
#define ERR_ANSW_NULL ERR_ANSW + 3
#define ERR_ANSW_STRUCTURE ERR_ANSW + 4

//Code erreur pour CerrG
#define ERR_CERG ERR_ANSW + 20
#define ERR_CERG_NOT_ZERO_INPUT ERR_CERG + 1
#define ERR_CERG_NULL ERR_CERG + 2

//Code erreur global de la classe
#define ERR_CLASS ERR_CERG + 20
#define ERR_CLASS_UNKNOW 0xFFFF

//Code erreur pour les clients
#define ERR_CLIEN ERR_CLASS + 20
#define ERR_CLIEN_NULL ERR_CLIEN + 1
#define ERR_CLIEN_FULL ERR_CLIEN + 2
#define ERR_CLIEN_ADD_SYST_ERR ERR_CLIEN + 3



class ScpiClientServer{
public:

  ScpiClientServer ();
  ScpiClientServer (std::string _HEADER);
  ScpiClientServer (std::string _HEADER, int _errLvl );
  virtual ~ScpiClientServer ();

  short int ReceiveMsg (std::string _msg, std::string &_rep, CerrG &_cerrg);
  short int AddClient (ScpiClientServer* _client);
  void SetSendEnable (int _sendEnbleValue);
  void modeperoquet(int mode);

  int getTailleListClient();
  ScpiClientServer* getClient(uint8_t pos);
  std::string getHeader();
  ScpiClientServer* getSCPIClientServer();

  CerrG codeErr;

private:

  int sendEnable;
  int modeperoquetstatut;
  std::string _HEADER;
  std::vector<ScpiClientServer*> listeClients;

  short int DecodeMsg (std::string& _msg, std::string& _header, std::string& _cmde);
  int FindClientinList(std::string headertofind);
  ScpiClientServer GetClientFromList(std::string& p_header);
  int BroadCastCmde(std::string& _cmde, std::string& _rep);


  void initAttributes () ;

protected:
  virtual short int ExecuteCmde (std::string& _cmde,std::string& _rep);
};

#endif // SCPICLIENTSERVER_H
