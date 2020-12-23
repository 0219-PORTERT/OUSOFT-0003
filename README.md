/*MASTER*/

/**
 ******************************************************************************
 *     SSSSSSSSSSSSSSS KKKKKKKKK    KKKKKKKFFFFFFFFFFFFFFFFFFFFFF
 *   SS:::::::::::::::SK:::::::K    K:::::KF::::::::::::::::::::F
 *  S:::::SSSSSS::::::SK:::::::K    K:::::KF::::::::::::::::::::F
 *  S:::::S     SSSSSSSK:::::::K   K::::::KFF::::::FFFFFFFFF::::F
 *  S:::::S            KK::::::K  K:::::KKK  F:::::F       FFFFFF
 *  S:::::S              K:::::K K:::::K     F:::::F
 *   S::::SSSS           K::::::K:::::K      F::::::FFFFFFFFFF
 *    SS::::::SSSSS      K:::::::::::K       F:::::::::::::::F
 *      SSS::::::::SS    K:::::::::::K       F:::::::::::::::F
 *         SSSSSS::::S   K::::::K:::::K      F::::::FFFFFFFFFF
 *              S:::::S  K:::::K K:::::K     F:::::F
 *              S:::::SKK::::::K  K:::::KKK  F:::::F
 *  SSSSSSS     S:::::SK:::::::K   K::::::KFF:::::::FF
 *  S::::::SSSSSS:::::SK:::::::K    K:::::KF::::::::FF
 *  S:::::::::::::::SS K:::::::K    K:::::KF::::::::FF
 *   SSSSSSSSSSSSSSS   KKKKKKKKK    KKKKKKKFFFFFFFFFFF
 *
 ******************************************************************************
 *    ____  __  __________  _____________  ___  ___  ____
 *   / __ \/ / / / __/ __ \/ __/_  __/ _ \/ _ \/ _ \|_  /
 *  / /_/ / /_/ /\ \/ /_/ / _/  / / / // / // / // //_ <
 *  \____/\____/___/\____/_/   /_/  \___/\___/\___/____/
 *
 ******************************************************************************
 *
 * @author Théo Paris
 * Indus Outillage
 * 2020
 * OUSOFT-0003 v0.8-master
 */


//courte
*OPC ? 
*RST
*IDN ?
ERR ?
CLR?
ACK
DTI ?
eeprom1 ?
eeprom1 {"CAL":{"CFA":[1,1,1,1,1],"CFB":[0,0,0,0,0]},"IDN":{"AFFAIRE":"WP5B","PART_NB":"OUELEC-0158","SERIAL_NB":"1","REV":"XXXX"},"MCO":{"CAL_N_DATE":"10/12/20","MCO_N_DATE":"10/12/20"}}



DIO:DIOAR1:RD ?
DIO:DIOBR1:RD ?
DIO:DIOAR2:RD ?
DIO:DIOBR2:RD ?


RPM:RPM 200
RPM:RPM ?
MESI:RAD:V1:IMOY ?
MESI:RAD:V1:CHX ?

MESI:RAD:V1:IMOY ?;MESI:RAD:V2:IMOY ?;MESI:RAD:V3:IMOY ?;MESI:RAD:V4:IMOY ?;MESI:RAD:W1:IMOY ?;MESI:RAD:W2:IMOY ?;MESI:RAD:W3:IMOY ?;MESI:RAD:W4:IMOY ?;MESI:AXE:Z1:IMOY ?;MESI:AXE:Z2:IMOY ?

MESI:RAD:V1:IMOY ?;MESI:RAD:V3:IMOY ?;MESI:RAD:W1:IMOY ?;MESI:RAD:W3:IMOY ?;MESI:AXE:Z1:IMOY ?


POS:MOD:MOD 60;MESI:RAD:V1:IMOY ?;POS:MOD:MOD 70;MESI:RAD:V1:IMOY ?;POS:MOD:MOD 80;MESI:RAD:V1:IMOY ?;POS:MOD:MOD 90;MESI:RAD:V1:IMOY ?;POS:MOD:MOD 100

MESI:AXE:Z1:IMOY ?
MESI:AXE:Z1:ISTCURR ?


DIO:A:0:DATA ?
DIO:A:0:DIR I

POS:mod:LV13:mod 10
POS:MOD:MOD 10
POS:MOD:MOD ?


TMP:T1:TMPCODE 255
TMP:T1:TMP 100 
TMP:T1:TMP 20
TMP:T1:TMP ?
TMP:T1:TMPMIN
TMP:T1:TMPMAX
TMP:T1:TMPSTEP

HUMS:TEMPHUM:HUM ?
HUMS:TEMPHUM:TEMP ?

SECU:SECU:DATA ?


DIO:DIOA:SDR ?
DIO:DIOA:RTR ?
DIO:DIOA:MBA ?
DIO:DIOA:THO ?
DIO:DIOA:THM ?
DIO:DIOA:THN ?
DIO:DIOA:WDSDDR ?
DIO:DIOA:RTA ?

DIO:DIOA:RD ?
DIO:DIOB:RD ?
DIO:DIOA:WR 255
DIO:DIOB:WR 0
DIO:DIOA:DIR ?
DIO:DIOB:DIR ?
DIO:DIOA:SETDIR 255 //entrée
DIO:DIOB:SETDIR 0 // sortie

ADDO:DIOA:RD ?
ADDO:DIOB:RD ?
ADDO:DIOA:WR 255
ADDO:DIOB:WR 0
ADDO:DIOA:DIR ?
ADDO:DIOB:DIR ?
ADDO:DIOA:SETDIR 255
ADDO:DIOB:SETDIR 0

ADDO:DIOA:RD ?;ADDO:DIOB:RD ?;ADDO:DIOC:RD ?

ADDO:LEV ON
ADDO:ROT ON
ADDO:CLR OFF
ADDO:SPA OFF


abc->a pour addo
ADDO:DIOA:WR 85;DIO:DIOA:RD ?
ADDO:DIOA:WR 170;DIO:DIOA:RD ?
ADDO:DIOB:WR 85;DIO:DIOB:RD ?
ADDO:DIOB:WR 170;DIO:DIOB:RD ?
ADDO:DIOC:WR 85;DIO:DIOA:RD ?
ADDO:DIOC:WR 170;DIO:DIOA:RD ?

pour exp secu
ADDO:DIOB:WR 85;ADDO:DIOC:WR 85;SECU:SECU:DATA ?
ADDO:DIOB:WR 170;ADDO:DIOC:WR 170;SECU:SECU:DATA ?

pour exp dio
DIO:DIOA:TST ?
DIO:DIOB:TST ?


SECU:SECU:RTST 
SECU:SECU:PSU ON
SECU:SECU:PSU OFF
SECU:SECU:PSU ON

SECU:SECU:I2CEXT1 ?
SECU:SECU:I2CEXT2 ?

ADDO:REL K3 ON
ADDO:LEV OFF