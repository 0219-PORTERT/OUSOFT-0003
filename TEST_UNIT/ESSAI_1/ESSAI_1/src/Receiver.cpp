#include "Receiver.h"
#include "ListenerScpiMsg.h"


Receiver::Receiver()
{
    rxBuf.clear();
    txBuf.clear();
    stack_cmd.clear();
}

Receiver::~Receiver()
{
    //dtor
}


