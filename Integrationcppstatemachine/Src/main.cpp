/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

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
 * OUSOFT-0003
 */

/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stdint.h"
#include "stdio.h"
#include "string.h"
#include "expanders\MCP23xxx.h"
#include "expanders\expanders.h"
#include "expanders\TI95xx.h"

#include <string>

/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dac.h"
#include "i2c.h"
//#include "lwip.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
//#include "lwip/apps/httpd.h"
#include "fonctions_eeprom.h"
#include "FonctionsAutotest.h"
#include "stateMachine.h"
#include "CerrG.h"
#include "ScpiClientServer.h"
#include "Pwm.h"
#include "Cna.h"
#include "Can.h"
#include "SimCapTemp.h"
#include "EXPSEC.h"
#include "EXPDIO.h"
#include "EXPADDO24.h"
#include "SCPIclientserveurADDO.h"
#include "Memory.h"
#include "json.hpp"//lib json

#include "OUELEC0158.h"
#include "OUCART0018.h"
#include "OUCART0020.h"

/* Include core modules */
#include "defines.h"
#include "tm_stm32_i2c.h"
#include "tm_stm32_adc.h"
#include "stm32fxxx_hal.h"

/* USER CODE END Includes */
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/*debug uart*/

/* USER CODE BEGIN PV */
void SystemClock_Config(void);
void initStateMachine(void);
void InitScpiStructure(void);
void initSCPI(void);
void TraitementSECU(void);
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

extern std::string RX_string; //variable extern de uart.c chaine de reception uart
extern uint8_t acknowledge;//variable extern de uart.c indique si le mode retour ack
T_STATUS stateMachine = HELLO; //statut de la machine d'état
ScpiClientServer SCPI_MAIN("TEST0256", 0);//objet principale du scpi
CerrG mainCerrG(-1);//code erreur

OUELEC_0158 rack1(0x01);//adresse des oucart-0018
OUELEC_0158 rack2(0x02);
OUCART0018 psu(0x00);
OUCART0018 accordsOsc(0x05);

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
using json = nlohmann::json;

int main(void) {
	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */

	HAL_Init();

	/* USER CODE BEGIN Init */
	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();
	initStateMachine();//ini de la machine d'etat et des phériphériques du µC

	rack2.init();// ini i2c des adc dac des rack
	rack1.init();// ini i2c des adc dac des rack


	/*Objets hardware*/

	Pwm Pwm1("RPM");
	//Cna Cna1("MOD");

	Cna CnaV13("LV13",rack1,5);
	Cna CnaW13("LW13",rack1,6);
	Cna CnaZ1("LZ1",rack1,7);
	Cna CnaV24("LV24",rack2,5);
	Cna CnaW24("LW24",rack2,6);
	Cna CnaZ2("LZ2",rack2,7);


	/*pour OUCART-0014*/
	/*Can CanV1("V1",TM_ADC_Channel_5);
	Can CanV2("V2",TM_ADC_Channel_12);
	Can CanV3("V3",TM_ADC_Channel_3);
	Can CanV4("V4",TM_ADC_Channel_9);
	Can CanW1("W1",TM_ADC_Channel_0);
	Can CanW2("W2",TM_ADC_Channel_8);
	Can CanW3("W3",TM_ADC_Channel_4);
	Can CanW4("W4",TM_ADC_Channel_10);
	Can CanZ1("Z1",TM_ADC_Channel_6);
	Can CanZ2("Z2",TM_ADC_Channel_13);*/
	/*pour les deux rack*/
	Can CanV1("V1",rack1,TM_ADC_Channel_0);
	Can CanV3("V3",rack1,TM_ADC_Channel_1);
	Can CanW1("W1",rack1,TM_ADC_Channel_2);
	Can CanW3("W3",rack1,TM_ADC_Channel_3);
	Can CanZ1("Z1",rack1,TM_ADC_Channel_4);

	Can CanV2("V2",rack2,TM_ADC_Channel_0);
	Can CanV4("V4",rack2,TM_ADC_Channel_1);
	Can CanW2("W2",rack2,TM_ADC_Channel_2);
	Can CanW4("W4",rack2,TM_ADC_Channel_3);
	Can CanZ2("Z2",rack2,TM_ADC_Channel_4);

	/*SimCapTemp SIMT1("T1",TEMPCAP1,POT1KA_I2CADD,POT100KA_I2CADD);
	SimCapTemp SIMT2("T2",TEMPCAP2,POT1KA_I2CADD,POT100KA_I2CADD);
	SimCapTemp SIMT3("T3",TEMPCAP3,POT1KA_I2CADD,POT100KA_I2CADD);
	SimCapTemp SIMT4("T4",TEMPCAP4,POT1KA_I2CADD,POT100KA_I2CADD);

	SimCapTemp SIMT5("T5",TEMPCAP5,POT1KB_I2CADD,POT100KB_I2CADD);
	SimCapTemp SIMT6("T6",TEMPCAP6,POT1KB_I2CADD,POT100KB_I2CADD);
	SimCapTemp SIMT7("T7",TEMPCAP7,POT1KB_I2CADD,POT100KB_I2CADD);
	SimCapTemp SIMT8("T8",TEMPCAP8,POT1KB_I2CADD,POT100KB_I2CADD);*/

	SimCapTemp SIMT1("T1",TEMPCAP1,rack1);
	SimCapTemp SIMT2("T2",TEMPCAP2,rack1);
	SimCapTemp SIMT3("T3",TEMPCAP3,rack1);
	SimCapTemp SIMT4("T4",TEMPCAP4,rack1);

	/*SimCapTemp SIMT5("T5",TEMPCAP5,rack2);
	SimCapTemp SIMT6("T6",TEMPCAP6,rack2);
	SimCapTemp SIMT7("T7",TEMPCAP7,rack2);
	SimCapTemp SIMT8("T8",TEMPCAP8,rack2);*/

	EXPSEC ExpSecu1("SECU");

	EXPDIO Expdio1a("DIOA",SIDEA);
	EXPDIO Expdio1b("DIOB",SIDEB);

	EXPDIO Exprack1dioa("DIOAR1",SIDEA,rack1);
	EXPDIO Exprack1diob("DIOBR1",SIDEB,rack1);
	EXPDIO Exprack2dioa("DIOAR2",SIDEA,rack2);
	EXPDIO Exprack2diob("DIOBR2",SIDEB,rack2);

	SCPIclientserveurADDO ExpADDOabc("ADDO");

	/*SCPI STRUCTURE*/

	//{
		ScpiClientServer SCPI_MES_I("MESI");
		SCPI_MAIN.AddClient(&SCPI_MES_I);
		//{
			ScpiClientServer RADIAL("RAD");
			SCPI_MES_I.AddClient(&RADIAL);
			//{
				/*ScpiClientServer V1("V1");
				RADIAL.AddClient(&V1);
				ScpiClientServer V2("V2");
				RADIAL.AddClient(&V2);
				ScpiClientServer V3("V3");
				RADIAL.AddClient(&V3);
				ScpiClientServer V4("V4");
				RADIAL.AddClient(&V4);
				ScpiClientServer W1("W1");
				RADIAL.AddClient(&W1);
				ScpiClientServer W2("W2");
				RADIAL.AddClient(&W2);
				ScpiClientServer W3("W3");
				RADIAL.AddClient(&W3);
				ScpiClientServer W4("W4");
				RADIAL.AddClient(&W4);*/

				RADIAL.AddClient(CanV1.getSCPIClientServer());
				RADIAL.AddClient(CanV2.getSCPIClientServer());
				RADIAL.AddClient(CanV3.getSCPIClientServer());
				RADIAL.AddClient(CanV4.getSCPIClientServer());
				RADIAL.AddClient(CanW1.getSCPIClientServer());
				RADIAL.AddClient(CanW2.getSCPIClientServer());
				RADIAL.AddClient(CanW3.getSCPIClientServer());
				RADIAL.AddClient(CanW4.getSCPIClientServer());
			//}
			ScpiClientServer AXIAL("AXE");
			SCPI_MES_I.AddClient(&AXIAL);
			//{
				/*ScpiClientServer L1("L1");
				AXIAL.AddClient(&L1);
				ScpiClientServer L2("L2");
				AXIAL.AddClient(&L2);*/
				AXIAL.AddClient(CanZ1.getSCPIClientServer());
				AXIAL.AddClient(CanZ2.getSCPIClientServer());
			//}
		//}
		ScpiClientServer SCPI_POS("POS");
		SCPI_MAIN.AddClient(&SCPI_POS);
		//{
			ScpiClientServer MOD("MOD");
			SCPI_POS.AddClient(&MOD);
				MOD.AddClient(CnaV13.getSCPIClientServer()); //MOD
				MOD.AddClient(CnaW13.getSCPIClientServer()); //MOD
				MOD.AddClient(CnaZ1.getSCPIClientServer()); //MOD
				MOD.AddClient(CnaV24.getSCPIClientServer()); //MOD
				MOD.AddClient(CnaW24.getSCPIClientServer()); //MOD
				MOD.AddClient(CnaZ2.getSCPIClientServer()); //MOD
			ScpiClientServer SOURCE("SRC");
			SCPI_POS.AddClient(&SOURCE);
			ScpiClientServer DESTINATION("DST");
			SCPI_POS.AddClient(&DESTINATION);
		//}
		ScpiClientServer SCPI_TEMP("TMP");
		SCPI_MAIN.AddClient(&SCPI_TEMP);
	//	{
			/*ScpiClientServer T1("T1");
			SCPI_TEMP.AddClient(&T1);
			ScpiClientServer T2("T2");
			SCPI_TEMP.AddClient(&T2);
			ScpiClientServer T3("T3");
			SCPI_TEMP.AddClient(&T3);
			ScpiClientServer T4("T4");
			SCPI_TEMP.AddClient(&T4);*/

			SCPI_TEMP.AddClient(SIMT1.getSCPIClientServer());
			SCPI_TEMP.AddClient(SIMT2.getSCPIClientServer());
			SCPI_TEMP.AddClient(SIMT3.getSCPIClientServer());
			SCPI_TEMP.AddClient(SIMT4.getSCPIClientServer());

			/*SCPI_TEMP.AddClient(SIMT5.getSCPIClientServer());
			SCPI_TEMP.AddClient(SIMT6.getSCPIClientServer());
			SCPI_TEMP.AddClient(SIMT7.getSCPIClientServer());
			SCPI_TEMP.AddClient(SIMT8.getSCPIClientServer());*/
		//}
		ScpiClientServer SCPI_HUMS("HUMS");
		SCPI_MAIN.AddClient(&SCPI_HUMS);
		//{
			ScpiClientServer EIC("EIC");
			SCPI_HUMS.AddClient(&EIC);
			ScpiClientServer CAL("CAL");
			SCPI_HUMS.AddClient(&CAL);
			ScpiClientServer MCO("MCO");
			SCPI_HUMS.AddClient(&MCO);
			ScpiClientServer DTI("DTI");
			SCPI_HUMS.AddClient(&DTI);
			ScpiClientServer TEMP("TEMP");
			SCPI_HUMS.AddClient(&TEMP);
		//}
		SCPI_MAIN.AddClient(Pwm1.getSCPIClientServer()); //RPM
		//ScpiClientServer SCPI_RPM("RPM");
		//SCPI_MAIN.AddClient(&SCPI_RPM);
		ScpiClientServer SCPI_SECU("SECU");
		SCPI_MAIN.AddClient(&SCPI_SECU);
		//{
			/*ScpiClientServer SEC_A("S_A");
			SCPI_SECU.AddClient(&SEC_A);
			ScpiClientServer SEC_B("S_B");
			SCPI_SECU.AddClient(&SEC_B);*/
			SCPI_SECU.AddClient(ExpSecu1.getSCPIClientServer());
		//}
		ScpiClientServer SCPI_DIO("DIO");
		SCPI_MAIN.AddClient(&SCPI_DIO);
		//{
			/*ScpiClientServer DIO_A("A");
			SCPI_SECU.AddClient(&DIO_A);
			ScpiClientServer DIO_B("B");
			SCPI_SECU.AddClient(&DIO_B);*/
			SCPI_DIO.AddClient(Expdio1a.getSCPIClientServer());
			SCPI_DIO.AddClient(Expdio1b.getSCPIClientServer());
		//}
		ScpiClientServer SCPI_OPT("OPT");
		SCPI_MAIN.AddClient(&SCPI_OPT);

		//ScpiClientServer SCPI_ADDO("ADDO");
		//SCPI_MAIN.AddClient(&SCPI_ADDO);

		SCPI_MAIN.AddClient(ExpADDOabc.getSCPIClientServer());

	/* USER CODE BEGIN WHILE */

	std::string MSG; //chaine message scpi
	std::string REP; //chaine reposne scpi

	MSG.reserve(256);//reserve 256 octets
	MSG.assign("\0");//ini à null
	REP.reserve(256);
	REP.assign("\0");

	UART_transmit("\r\n*** Testing exception ***");
	try {
		throw 1;
		UART_transmit("\r\n*** FAILED ***");
	} catch (int e) {
		UART_transmit("\r\n*** OK ***");
	}

	UART_transmit("\r\n*** RUNNING STATE MACHINE ***");

	initSCPI();

	//SCPI_MAIN.SetSendEnable(1); //bloquer
	//SCPI_MAIN.modeperoquet(1); //uncomment to active parrot mode
	/*enableI2C_EXT2();
	rack1.carteEIC1.switchToi2c(0);
	I2Cscanner(I2C1);
	rack1.carteEIC1.switchToi2c(1);
	I2Cscanner(I2C1);
	disableI2C_EXT2();*/

	/*Pré-lecture de la mémoire pour supprimer le problème de lecture du json de la mémoire 1 suite à la mise en place du 2eme rack */
	std::string strtest;
	strtest.reserve(256);
	strtest.assign("\0");

	rack1.carteEIC1.getJsonStringfromMemory(strtest);
	rack2.carteEIC1.getJsonStringfromMemory(strtest);

	while (1) {
		/* Infinite loop */
		/* USER CODE BEGIN WHILE */

		while (1) {


			switch (stateMachine) {
			case (HELLO):
				UART_transmit("\n\r *** Hello S2M *** \n\r");
				stateMachine = DEFAULT;//machine d'état en attente
				break;
			case (CMD)://traitmeent des commandes
				try {

					while (getQueueMsgsize() > 0) {//tant qu'il y a des message scpi dans la queue

						getFirstCmd(MSG); //prend le 1er message
						SCPI_MAIN.ReceiveMsg(MSG, REP, mainCerrG);//traitement scpi
						if (REP.size() == 0) {//si la commande ne renvoie rien
							if(acknowledge == 1){//et si le mode ACK est actif
								UART_transmit("OK");//alors renvoi "OK"
							}else{
								;//sinon rien
							}
						} else {
							UART_transmit( REP);//sinon renvoi la réponse de la commande scpi
						}
						deQueueFirstCmd();//supprime le message qui vient d'être traiter de la queue
						REP.assign("\0");//raz
						MSG.assign("\0");
					}
				} catch (int e) {//si exeption lors du traitement scpi
					UART_transmit(REP.assign(mainCerrG.ToString()));//transmet le code maincerrg correspondant
					deQueueFirstCmd();//supprime le message
					REP.assign("\0");
					MSG.assign("\0");
				}
				Reset_uart_buffer();//raz
				stateMachine = DEFAULT;//retourne en mode par defaut
				break;
			case (SECU)://pas utilisé à cause des interruptions
				//HAL_Delay(100);
				//stateMachine = SECU;
						__NOP();
				break;
			case (RST)://reset
				UART_transmit("\n\r RESETING... \n\r");
				NVIC_SystemReset();//soft reset du µC
				REP.assign("\0");
				MSG.assign("\0");
				//deQueueFirstCmd();
				clearQueuemsg();
				//SCPI_MAIN.ReceiveMsg(MSG, REP, mainCerrG);
				SCPI_MAIN.SetSendEnable(0); //réactivation des commandes
				//REP.assign("\0");//à voir si il faut une réponse du système ??????
				//MSG.assign("\0");
				stateMachine = HELLO;
				break;
			case (CLEAR)://clear les buffer, variable tampon,
				try {

					while (getQueueMsgsize() > 0) {

						getFirstCmd(MSG);
						SCPI_MAIN.ReceiveMsg(MSG, REP, mainCerrG);
						if (REP.size() == 0) {
							//UART_transmit(" OK\n\r");
						} else {
							UART_transmit(REP);
						}
						deQueueFirstCmd();
						clearQueuemsg();
						REP.assign("\0");
						MSG.assign("\0");
					}
				} catch (int e) {
					UART_transmit(REP.assign(mainCerrG.ToString()));
				}
				Reset_uart_buffer();
				stateMachine = DEFAULT;

				break;
			case (DEFAULT):
				break;
			default:
				break;
			}

		}
		/* USER CODE END 3 */
	}
	/* USER CODE END 3 */
}

/**
 * @brief  recupère le code de l'expander de secu
 * @retval retourne la valeur lue
 */
int getExpSecuErrorcode(void){
	int secu = 0;
	std::string MSG;
	std::string REP;
	REP.assign("\0");
	MSG.assign("\0");

	MSG.assign("SECU:SECU:DATA ?");
	SCPI_MAIN.ReceiveMsg(MSG, REP, mainCerrG);
	secu = std::stoi(REP,nullptr,10);

	REP.assign("\0");
	MSG.assign("\0");

	return secu;
}

/**
 * @brief  initialise la com scpi
 * @retval None
 */
void initSCPI(void){

	int secu = 0;
	std::string MSG;
	std::string REP;
	REP.assign("\0");
	MSG.assign("\0");

	/*test des expander de secu pour démarer*/
	/*MSG.assign("SECU:SECU:DATA ?");
	SCPI_MAIN.ReceiveMsg(MSG, REP, mainCerrG);
	secu = std::stoi(REP,nullptr,10);*/

	/*secu = getExpSecuErrorcode();

	if(secu!=0){
		mainCerrG.SetStateMachineErrorCode(secu);
		TraitementSECU(); // problème sur une ligne de l'expender secu //mettre dans maincerg en cas d'erreur
	}*/


	/*TEST POUR OUCART-0014*/
	/*if(secu!=0xFFFF){
		mainCerrG.SetStateMachineErrorCode(secu);
		TraitementSECU(); // problème sur une ligne de l'expender secu //mettre dans maincerg en cas d'erreur
	}*/

	MSG.assign("*CLR"); //toutes valeur par defaut
	SCPI_MAIN.ReceiveMsg(MSG, REP, mainCerrG);

	REP.assign("\0");
	MSG.assign("\0");
}

/**
 * @brief  initialise la machine d'état
 * @retval None
 */
void initStateMachine(void) {

	HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);//interruption systick
	HAL_NVIC_EnableIRQ(SysTick_IRQn);
	//HAL_ResumeTick();
	//TM_RCC_InitSystem();

	/*ini i2c*/
	TM_I2C_Init(I2C1, TM_I2C_PinsPack_1, 40000);
	TM_I2C_Init(I2C2, TM_I2C_PinsPack_2, 40000);
	TM_I2C_Init(I2C3, TM_I2C_PinsPack_1, 40000);
	TM_I2C_Init(I2C4, TM_I2C_PinsPack_3, 40000);

	Reset_uart_buffer();//mise à 0 des buffer uart

	MX_UART4_Init(); //ini uart 4 par ftdi
	UART_transmit("--- init : UART4");
	//MX_USART3_UART_Init(); //ini par l'uart debug

	UART_transmit("*** OUSOFT-0003 v0.8-master ***");
	UART_transmit("--- Hardware init ---");

	UART_transmit("--- init : GPIO");
	MX_GPIO_Init();
	UART_transmit("--- init : DAC");
	MX_DAC_Init();
	//MX_I2C1_Init();
	UART_transmit("--- init : I2C2");
	//MX_I2C2_Init();
	UART_transmit("--- init : I2C3");
	//MX_I2C3_Init();
	UART_transmit("--- init : SPI3");
	MX_SPI3_Init();
	//MX_UART4_Init();
	MX_UART5_Init();
	//MX_LWIP_Init();
	UART_transmit("--- init : I2C4");
	//MX_I2C4_Init();
	MX_UART7_Init();
	UART_transmit("--- init : TIM2");
	MX_TIM2_Init();
	UART_transmit("--- init : TIM3");
	MX_TIM3_Init();
	//UART_transmit("--- init : TIM4");
	//MX_TIM4_Init();
	UART_transmit("--- init : TIM8");
	MX_TIM8_Init();


	UART_transmit("--- init : RCC");



	UART_transmit("--- init : ADC3");
	TM_ADC_Init(ADC3, TM_ADC_Channel_0);
	//TM_ADC_Init(ADC3, TM_ADC_Channel_1);
	//TM_ADC_Init(ADC3, TM_ADC_Channel_2);
	TM_ADC_Init(ADC3, TM_ADC_Channel_3);
	TM_ADC_Init(ADC3, TM_ADC_Channel_4);
	TM_ADC_Init(ADC3, TM_ADC_Channel_5);
	TM_ADC_Init(ADC3, TM_ADC_Channel_6);
	//TM_ADC_Init(ADC3, TM_ADC_Channel_7);
	TM_ADC_Init(ADC3, TM_ADC_Channel_8);
	TM_ADC_Init(ADC3, TM_ADC_Channel_9);
	TM_ADC_Init(ADC3, TM_ADC_Channel_10);
	//TM_ADC_Init(ADC3, TM_ADC_Channel_11);
	TM_ADC_Init(ADC3, TM_ADC_Channel_12);
	TM_ADC_Init(ADC3, TM_ADC_Channel_13);
	TM_ADC_Init(ADC3, TM_ADC_Channel_14);
	TM_ADC_Init(ADC3, TM_ADC_Channel_15);


	HAL_GPIO_WritePin(GPIOG,RESET_CN11_66_Pin , GPIO_PIN_SET); //PIN RESET PG10
	HAL_GPIO_WritePin(GPIOG,GPIO_PIN_4 , GPIO_PIN_SET); //PIN buffer PG4

	UART_transmit("AUTOTEST I2CMAIN");
	enableI2C_main();
	disableI2Cmain();

	int testI2C = -1;
	testI2C = CheckI2CMain();
	if(testI2C != 0){
		mainCerrG.SetStateMachineErrorCode(ERROR_STATEMA_AUTOTEST_I2CMAIN);
		UART_transmit("Test i2cmain fail at");
		UART_transmit(std::to_string(testI2C) + mainCerrG.ToString());

	}else{
		UART_transmit("I2C main test ok");
	}

	UART_transmit("AUTOTEST I2CSECU");
	testI2C = -1;
	testI2C = CheckI2C3();
	if(testI2C != 0){
		mainCerrG.SetStateMachineErrorCode(ERROR_STATEMA_AUTOTEST_I2CSECU);
		UART_transmit("Test i2c3 fail at");
		UART_transmit(std::to_string(testI2C) + mainCerrG.ToString());
	}else{
		UART_transmit("I2C3 ok");
	}

	HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);


	/*LOAD MEMORY*/
	if(rack1.loadJson() != 0){//Chargement des calibrations
		mainCerrG.SetStateMachineErrorCode(ERROR_STATEMA_JSONLOAD);
		UART_transmit(mainCerrG.ToString());
	}
	if(rack2.loadJson() != 0){
		mainCerrG.SetStateMachineErrorCode(ERROR_STATEMA_JSONLOAD);
		UART_transmit(mainCerrG.ToString());
	}


}

/**
 * @brief System Clock Configuration
 * @retval None
 */

void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };
	RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = { 0 };

	/** Configure the main internal regulator output voltage
	 */
	__HAL_RCC_PWR_CLK_ENABLE()
	;
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);
	/** Initializes the CPU, AHB and APB busses clocks
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	RCC_OscInitStruct.PLL.PLLM = 8;
	RCC_OscInitStruct.PLL.PLLN = 96;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 4;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}
	/** Activate the Over-Drive mode
	 */
	if (HAL_PWREx_EnableOverDrive() != HAL_OK) {
		Error_Handler();
	}
	/** Initializes the CPU, AHB and APB busses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	//RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV16;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK) {
		Error_Handler();
	}

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK) {
		Error_Handler();
	}
	PeriphClkInitStruct.PeriphClockSelection = (RCC_PERIPHCLK_UART4
			| RCC_PERIPHCLK_UART5 | RCC_PERIPHCLK_UART7 | RCC_PERIPHCLK_I2C2
			| RCC_PERIPHCLK_I2C3 | RCC_PERIPHCLK_I2C4| RCC_PERIPHCLK_I2C1) ;

	PeriphClkInitStruct.Uart4ClockSelection = RCC_UART4CLKSOURCE_PCLK1;
	PeriphClkInitStruct.Uart5ClockSelection = RCC_UART5CLKSOURCE_PCLK1;
	PeriphClkInitStruct.Uart7ClockSelection = RCC_UART7CLKSOURCE_PCLK1;

	/*PeriphClkInitStruct.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
	PeriphClkInitStruct.I2c2ClockSelection = RCC_I2C2CLKSOURCE_PCLK1;
	PeriphClkInitStruct.I2c3ClockSelection = RCC_I2C3CLKSOURCE_PCLK1;
	PeriphClkInitStruct.I2c4ClockSelection = RCC_I2C4CLKSOURCE_PCLK1;*/
	if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK) {
		Error_Handler();
	}
}

/* USER CODE BEGIN 4 */

/* USER CODE BEGIN 4 */

/* Called if TM_I2C_PinsPack_Custom is selected when initializing I2C */
void TM_I2C_InitCustomPinsCallback(I2C_TypeDef* I2Cx,
		uint16_t AlternateFunction) {
	/* Check for proper I2C */
	if (I2Cx == I2C3) {
		TM_GPIO_InitAlternate(GPIOF, GPIO_PIN_14 | GPIO_PIN_15,
				TM_GPIO_OType_PP, TM_GPIO_PuPd_UP, TM_GPIO_Speed_Low,
				AlternateFunction);
	}
}

void TraitementSECU(void) {
	UART_transmit("\n\r AU SECOUR !!! \n\r");
	stateMachine = SECU;
	SCPI_MAIN.SetSendEnable(1);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {

	/*if ((GPIO_Pin == GPIO_PIN_8) && (HAL_GPIO_ReadPin(GPIOG, GPIO_Pin) == 0) ) {//si une interruption est presente gpio G8, machine d'etat passe en secu
		if(stateMachine != SECU){
			mainCerrG.SetStateMachineErrorCode(getExpSecuErrorcode());
			TraitementSECU();
		}
	}*/
	/* Clear interrupt flag */
	EXTI_HandleTypeDef extihandle;
	extihandle.Line = GPIO_Pin;
	HAL_EXTI_ClearPending(&extihandle, EXTI_TRIGGER_RISING_FALLING);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */

	/* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
