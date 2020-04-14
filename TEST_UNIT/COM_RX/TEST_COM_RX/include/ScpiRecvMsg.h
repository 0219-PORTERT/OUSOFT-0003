#ifndef SCPIRECVMSG_H
#define SCPIRECVMSG_H

#include <string>
#include <iostream>
#include <vector>

using namespace std;


class ScpiRecvMsg
{
    public:
        ScpiRecvMsg();
        virtual ~ScpiRecvMsg();

        char RX_Buffer;
        string RX_string;
        string TX_string;
        vector<string*> stack_cmd;

        void ReceiveChar(const char _charReceived);

    protected:

    private:
};

#endif // SCPIRECVMSG_H
