#include <iostream>
#include "Receiver.h"
#include <string>
#include <stdio.h>
#include "ListenerScpiMsg.h"

using namespace std;

Receiver dut;
char* t1 = "COMMANDE_SCPI_1\n";

ListenerScpiMsg stateM;
ListenerScpiMsg mainScpi;

int main()
{

    dut.CharReceive('{');
    dut.CharReceive(0x7f);
    dut.CharReceive('}');
    dut.CharReceive('\r');
    dut.CharReceive('\n');

    dut.CharReceive(t1);

    dut.CharReceive("HELLO ;THE WORLD; !!!  ? \n");

    //dut.ToString();

    cout << "bye !!" <<endl;
}


