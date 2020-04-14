#ifndef RECEIVER_H
#define RECEIVER_H

#include <string>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include "ListenerScpiMsg.h"

/* ERT : 20200414*/

extern ListenerScpiMsg stateM;
extern ListenerScpiMsg mainScpi;

class Receiver
{
public:
    //Variables
    std::string rxBuf;
    std::string txBuf;
    std::vector<std::string> stack_cmd ;



    //Méthodes
    Receiver();
    virtual ~Receiver();

    void CharReceive (const char _charReceived)
    {
        switch (_charReceived)
        {
        case '\n' :
            stack_cmd.push_back(rxBuf);
            ToString();
            Clear();
            break;

        case ';':
            stack_cmd.push_back(rxBuf);
            rxBuf.clear();
            break;
        default:
            if ((_charReceived>=0x20) & (_charReceived<0x7F)) //Caractères lisibles
                rxBuf+=(_charReceived);
            break;
        }

    }

    void CharReceive (char* _texteReceived)
    {
        uint16_t len = strlen(_texteReceived);
        for (uint16_t i=0; i<len; i++)
        {
            const char c= _texteReceived[i];
            //printf("découpe :%x \n\r", c);
            CharReceive (c);
        }
    }

    void ToString()
    {
        printf("\n *** DISPLAY VECTOR DATA *** \n");
        for (uint8_t i=0; i<stack_cmd.size() ; i++)
        {
            printf("[%i]=[%s]\n", i, stack_cmd[i].data());
        }
    }

    void Clear()
    {
        printf("\n *** CLEAR *** \n");
        rxBuf.clear();
        txBuf.clear();
        stack_cmd.clear();
    }

protected:

private:



};

#endif // RECEIVER_H
