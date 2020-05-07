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
#include "FonctionsSCPI.h"
#include "fonctions_eeprom.h"
#include "FonctionsAutotest.h"
#include "stateMachine.h"
#include "CerrG.h"
#include "ScpiClientServer.h"
#include "Pwm.h"
#include "Cna.h"
#include "Can.h"
#include "SimCapTemp.h"

/* Include core modules */
#include "stm32fxxx_hal.h"
#include "defines.h"
#include "tm_stm32_i2c.h"
#include "tm_stm32_adc.h"

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
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

extern std::string RX_string;

T_STATUS stateMachine = HELLO;

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {
	/* USER CODE BEGIN 1 */

	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();
	initStateMachine();
	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/*Objets hardware*/
	Pwm Pwm1("RPM");
	Cna Cna1("MOD");

	Can CanV1("V1",TM_ADC_Channel_0);
	Can CanV2("V2",TM_ADC_Channel_3);
	Can CanV3("V3",TM_ADC_Channel_4);
	Can CanV4("V4",TM_ADC_Channel_5);
	Can CanW1("W1",TM_ADC_Channel_6);
	Can CanW2("W2",TM_ADC_Channel_8);
	Can CanW3("W3",TM_ADC_Channel_9);
	Can CanW4("W4",TM_ADC_Channel_10);
	Can CanL1("L1",TM_ADC_Channel_12);
	Can CanL2("L2",TM_ADC_Channel_13);

	SimCapTemp SIMT1("T1",TEMPCAP1);
	SimCapTemp SIMT2("T2",TEMPCAP2);
	SimCapTemp SIMT3("T3",TEMPCAP3);
	SimCapTemp SIMT4("T4",TEMPCAP4);

	/*SCPI STRUCTURE*/
	ScpiClientServer SCPI_MAIN("TEST0256", 0);
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
				AXIAL.AddClient(CanL1.getSCPIClientServer());
				AXIAL.AddClient(CanL2.getSCPIClientServer());
			//}
		//}
		ScpiClientServer SCPI_POS("POS");
		SCPI_MAIN.AddClient(&SCPI_POS);
		//{
			//ScpiClientServer MOD("MOD");
			//SCPI_POS.AddClient(&MOD);
		    SCPI_POS.AddClient(Cna1.getSCPIClientServer()); //MOD
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
			ScpiClientServer SEC_A("S_A");
			SCPI_SECU.AddClient(&SEC_A);
			ScpiClientServer SEC_B("S_B");
			SCPI_SECU.AddClient(&SEC_B);
		//}
		ScpiClientServer SCPI_DIO("DIO");
		SCPI_MAIN.AddClient(&SCPI_DIO);
		//{
			ScpiClientServer DIO_A("A");
			SCPI_SECU.AddClient(&DIO_A);
			ScpiClientServer DIO_B("B");
			SCPI_SECU.AddClient(&DIO_B);
		//}
		ScpiClientServer SCPI_OPT("OPT");
		SCPI_MAIN.AddClient(&SCPI_OPT);
	//}

	CerrG mainCerrG(-1);

	//testI2CCS(I2C4);



	/* USER CODE BEGIN WHILE */

	std::string MSG;
	std::string REP;

	//SCPI_MAIN.SetSendEnable(1); //bloquer
	//SCPI_MAIN.modeperoquet(1); //uncomment to active parrot mode

	MSG.reserve(256);
	MSG.assign("\0");
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

	while (1) {
		/* Infinite loop */
		/* USER CODE BEGIN WHILE */
		while (1) {

			switch (stateMachine) {
			case (HELLO):
				UART_transmit("\n\r *** Hello S2M *** \n\r");
				stateMachine = DEFAULT;
				break;
			case (CMD):
				try {
					while (getstackmsgsize() > 0) {
						Stackmsg(MSG);
						SCPI_MAIN.ReceiveMsg(MSG, REP, mainCerrG);
						if (REP.size() == 0) {
							UART_transmit(" OK\n\r");
						} else {
							UART_transmit("OK:answer =\n\r" + REP);
						}
						REP.assign("\0");
						MSG.assign("\0");
					}
				} catch (int e) {
					UART_transmit(REP.assign(mainCerrG.ToString()));
				}
				stateMachine = DEFAULT;
				break;
			case (SECU):
				HAL_Delay(100);
				stateMachine = SECU;
				break;
			case (RST):
				UART_transmit("\n\r RESETING... \n\r");
				//RESET()
				REP.assign("\0");
				MSG.assign("\0");
				Stackmsg(MSG);
				clearStackmsg();
				SCPI_MAIN.ReceiveMsg(MSG, REP, mainCerrG);
				SCPI_MAIN.SetSendEnable(0); //réactivation des commandes
				REP.assign("\0");//à voir si il faut une réponse du système ??????
				MSG.assign("\0");
				stateMachine = HELLO;
				break;
			case (DEFAULT):
				;
			}

		}
		/* USER CODE END 3 */
	}
	/* USER CODE END 3 */
}

void initStateMachine(void) {

	MX_USART3_UART_Init();
	Reset_uart_buffer();

	UART_transmit("*** OUSOFT-0003 Rev0.01 ***");
	UART_transmit("--- Hardware initing ---");

	UART_transmit("--- init : GPIO");
	MX_GPIO_Init();
	UART_transmit("--- init : DAC");
	MX_DAC_Init();
	UART_transmit("--- init : I2C2");
	MX_I2C2_Init();
	UART_transmit("--- init : I2C3");
	MX_I2C3_Init();
	UART_transmit("--- init : SPI3");
	MX_SPI3_Init();
	MX_UART4_Init();
	MX_UART5_Init();
	//MX_LWIP_Init();
	UART_transmit("--- init : I2C4");
	MX_I2C4_Init();
	MX_UART7_Init();
	UART_transmit("--- init : TIM2");
	MX_TIM2_Init();
	UART_transmit("--- init : TIM3");
	MX_TIM3_Init();
	UART_transmit("--- init : TIM4");
	MX_TIM4_Init();
	UART_transmit("--- init : TIM8");
	MX_TIM8_Init();

	//Relay_Init();

	UART_transmit("--- init : RCC");
	TM_RCC_InitSystem();
	TM_I2C_Init(I2C4, TM_I2C_PinsPack_3, 100000);
	TM_I2C_Init(I2C2, TM_I2C_PinsPack_2, 100000);
	//TM_I2C_Init(I2C3, TM_I2C_PinsPack_Custom, 100000);

	//CheckI2C4();

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
	//RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV16;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK) {
		Error_Handler();
	}
	PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_UART4
			| RCC_PERIPHCLK_UART5 | RCC_PERIPHCLK_UART7 | RCC_PERIPHCLK_I2C2
			| RCC_PERIPHCLK_I2C3 | RCC_PERIPHCLK_I2C4;
	PeriphClkInitStruct.Uart4ClockSelection = RCC_UART4CLKSOURCE_PCLK1;
	PeriphClkInitStruct.Uart5ClockSelection = RCC_UART5CLKSOURCE_PCLK1;
	PeriphClkInitStruct.Uart7ClockSelection = RCC_UART7CLKSOURCE_PCLK1;
	PeriphClkInitStruct.I2c2ClockSelection = RCC_I2C2CLKSOURCE_PCLK1;
	PeriphClkInitStruct.I2c3ClockSelection = RCC_I2C3CLKSOURCE_PCLK1;
	PeriphClkInitStruct.I2c4ClockSelection = RCC_I2C4CLKSOURCE_PCLK1;
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
	//SCPI_MAIN.SetSendEnable(1);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	//if (GPIO_Pin == GPIO_PIN_8) {
	TraitementSECU();
	//}
	/* Clear interrupt flag */
	EXTI_HandleTypeDef extihandle;
	extihandle.Line = GPIO_Pin;
	HAL_EXTI_ClearPending(&extihandle, EXTI_TRIGGER_RISING_FALLING);

	//HAL_EXTI_ClearPending(GPIO_PIN_8, EXTI_TRIGGER_RISING_FALLING);
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
