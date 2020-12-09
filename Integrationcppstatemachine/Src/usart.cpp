/**
 ******************************************************************************
 * File Name          : USART.c
 * Description        : This file provides code for the configuration
 *                      of the USART instances.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under Ultimate Liberty license
 * SLA0044, the "License"; You may not use this file except in compliance with
 * the License. You may obtain a copy of the License at:
 *                             www.st.com/SLA0044
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "usart.h"
#include <string>
#include <iostream>
#include <vector>
#include "OUELEC0158.h"
#include "OUCART0018.h"

/* USER CODE BEGIN 0 */

UART_HandleTypeDef huart3;

/* USER CODE END 0 */

UART_HandleTypeDef huart4;
UART_HandleTypeDef huart5;
UART_HandleTypeDef huart7;

char RX_Buffer[1];
std::string RX_string;
std::string TX_string;

std::vector<std::string> v_queueCmd;
volatile uint8_t endofCMD;
uint8_t acknowledge = 0;

extern OUELEC_0158 rack1;
extern OUELEC_0158 rack2;
extern OUCART0018 psu;
extern OUCART0018 accordsOsc;

/* UART4 init function */
void MX_UART4_Init(void) {/*ftdi*/


	GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	/* USER CODE BEGIN UART4_MspInit 0 */

	/* USER CODE END UART4_MspInit 0 */
	/* UART4 clock enable */
	__HAL_RCC_UART4_CLK_ENABLE()
	;

	__HAL_RCC_GPIOA_CLK_ENABLE()
	;
	/**UART4 GPIO Configuration
	 PA11     ------> UART4_RX
	 PA12     ------> UART4_TX
	 */
	GPIO_InitStruct.Pin = GPIO_PIN_11 | GPIO_PIN_12;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF6_UART4;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/* UART4 interrupt Init */
	HAL_NVIC_SetPriority(UART4_IRQn, 1, 0);
	HAL_NVIC_EnableIRQ(UART4_IRQn);





	huart4.Instance = UART4;
	huart4.Init.BaudRate = 115200;
	huart4.Init.WordLength = UART_WORDLENGTH_8B;
	huart4.Init.StopBits = UART_STOPBITS_1;
	huart4.Init.Parity = UART_PARITY_NONE;
	huart4.Init.Mode = UART_MODE_TX_RX;
	huart4.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart4.Init.OverSampling = UART_OVERSAMPLING_16;
	huart4.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	huart4.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
	if (HAL_UART_Init(&huart4) != HAL_OK) {
		Error_Handler();
	}

	/*mettre le reste de l'ini de l'usart 3 ici pour l usart 4!!!!!!!!!!!!!!!!!!*//* USER CODE BEGIN USART4_Init 2 */
	__HAL_UART_ENABLE_IT(&huart4, UART_IT_RXNE);


	RX_string.reserve(256);
	RX_string.assign("\0");

	TX_string.reserve(256);
	TX_string.assign("\0");

	endofCMD = 0;

	UART_transmit("COM on FTDI");

}
/* UART5 init function */
void MX_UART5_Init(void) {

	huart5.Instance = UART5;
	huart5.Init.BaudRate = 115200;
	huart5.Init.WordLength = UART_WORDLENGTH_8B;
	huart5.Init.StopBits = UART_STOPBITS_1;
	huart5.Init.Parity = UART_PARITY_NONE;
	huart5.Init.Mode = UART_MODE_TX_RX;
	huart5.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart5.Init.OverSampling = UART_OVERSAMPLING_16;
	huart5.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	huart5.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
	if (HAL_UART_Init(&huart5) != HAL_OK) {
		Error_Handler();
	}

}
/* UART7 init function */
void MX_UART7_Init(void) {

	huart7.Instance = UART7;
	huart7.Init.BaudRate = 115200;
	huart7.Init.WordLength = UART_WORDLENGTH_8B;
	huart7.Init.StopBits = UART_STOPBITS_1;
	huart7.Init.Parity = UART_PARITY_NONE;
	huart7.Init.Mode = UART_MODE_TX_RX;
	huart7.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart7.Init.OverSampling = UART_OVERSAMPLING_16;
	huart7.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	huart7.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
	if (HAL_UART_Init(&huart7) != HAL_OK) {
		Error_Handler();
	}

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle) {

	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	if (uartHandle->Instance == UART4) {
		/* USER CODE BEGIN UART4_MspInit 0 */

		/* USER CODE END UART4_MspInit 0 */
		/* UART4 clock enable */
		__HAL_RCC_UART4_CLK_ENABLE()
		;

		__HAL_RCC_GPIOA_CLK_ENABLE()
		;
		/**UART4 GPIO Configuration
		 PA11     ------> UART4_RX
		 PA12     ------> UART4_TX
		 */
		GPIO_InitStruct.Pin = RX1_CN12_14_Pin | TX1_CN12_16_Pin;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF6_UART4;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		/* UART4 interrupt Init */
		HAL_NVIC_SetPriority(UART4_IRQn, 1, 0);
		HAL_NVIC_EnableIRQ(UART4_IRQn);
		/* USER CODE BEGIN UART4_MspInit 1 */

		/* USER CODE END UART4_MspInit 1 */
	} else if (uartHandle->Instance == UART5) {
		/* USER CODE BEGIN UART5_MspInit 0 */

		/* USER CODE END UART5_MspInit 0 */
		/* UART5 clock enable */
		__HAL_RCC_UART5_CLK_ENABLE()
		;

		__HAL_RCC_GPIOC_CLK_ENABLE()
		;
		__HAL_RCC_GPIOD_CLK_ENABLE()
		;
		/**UART5 GPIO Configuration
		 PC12     ------> UART5_TX
		 PD2     ------> UART5_RX
		 */
		GPIO_InitStruct.Pin = TX2_CN11_3_Pin;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF8_UART5;
		HAL_GPIO_Init(TX2_CN11_3_GPIO_Port, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = RX2_CN11_4_Pin;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF8_UART5;
		HAL_GPIO_Init(RX2_CN11_4_GPIO_Port, &GPIO_InitStruct);

		/* USER CODE BEGIN UART5_MspInit 1 */

		/* USER CODE END UART5_MspInit 1 */
	} else if (uartHandle->Instance == UART7) {
		/* USER CODE BEGIN UART7_MspInit 0 */

		/* USER CODE END UART7_MspInit 0 */
		/* UART7 clock enable */
		__HAL_RCC_UART7_CLK_ENABLE()
		;

		__HAL_RCC_GPIOE_CLK_ENABLE()
		;
		/**UART7 GPIO Configuration
		 PE7     ------> UART7_RX
		 PE8     ------> UART7_TX
		 */
		GPIO_InitStruct.Pin = RX3_CN12_44_Pin | TX3_CN12_40_Pin;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF8_UART7;
		HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

		/* USER CODE BEGIN UART7_MspInit 1 */

		/* USER CODE END UART7_MspInit 1 */
	}
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle) {

	if (uartHandle->Instance == UART4) {
		/* USER CODE BEGIN UART4_MspDeInit 0 */

		/* USER CODE END UART4_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_UART4_CLK_DISABLE();

		/**UART4 GPIO Configuration
		 PA11     ------> UART4_RX
		 PA12     ------> UART4_TX
		 */
		HAL_GPIO_DeInit(GPIOA, RX1_CN12_14_Pin | TX1_CN12_16_Pin);

		/* UART4 interrupt Deinit */
		HAL_NVIC_DisableIRQ(UART4_IRQn);
		/* USER CODE BEGIN UART4_MspDeInit 1 */

		/* USER CODE END UART4_MspDeInit 1 */
	} else if (uartHandle->Instance == UART5) {
		/* USER CODE BEGIN UART5_MspDeInit 0 */

		/* USER CODE END UART5_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_UART5_CLK_DISABLE();

		/**UART5 GPIO Configuration
		 PC12     ------> UART5_TX
		 PD2     ------> UART5_RX
		 */
		HAL_GPIO_DeInit(TX2_CN11_3_GPIO_Port, TX2_CN11_3_Pin);

		HAL_GPIO_DeInit(RX2_CN11_4_GPIO_Port, RX2_CN11_4_Pin);

		/* USER CODE BEGIN UART5_MspDeInit 1 */

		/* USER CODE END UART5_MspDeInit 1 */
	} else if (uartHandle->Instance == UART7) {
		/* USER CODE BEGIN UART7_MspDeInit 0 */

		/* USER CODE END UART7_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_UART7_CLK_DISABLE();

		/**UART7 GPIO Configuration
		 PE7     ------> UART7_RX
		 PE8     ------> UART7_TX
		 */
		HAL_GPIO_DeInit(GPIOE, RX3_CN12_44_Pin | TX3_CN12_40_Pin);

		/* USER CODE BEGIN UART7_MspDeInit 1 */

		/* USER CODE END UART7_MspDeInit 1 */
	}
}

void MX_USART3_UART_Init(void) {/*debug*/

	/* USER CODE BEGIN USART3_Init 0 */
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	/* USER CODE BEGIN UART4_MspInit 0 */

	/* USER CODE END UART4_MspInit 0 */
	/* UART4 clock enable */
	__HAL_RCC_USART3_CLK_ENABLE()
	;

	__HAL_RCC_GPIOD_CLK_ENABLE()
	;
	/**UART4 GPIO Configuration
	 PD8     ------> UART4_RX
	 PD9     ------> UART4_TX
	 */
	GPIO_InitStruct.Pin = GPIO_PIN_8 | GPIO_PIN_9;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

	/* UART4 interrupt Init */
	HAL_NVIC_SetPriority(USART3_IRQn, 1, 0);
	HAL_NVIC_EnableIRQ(USART3_IRQn);
	/* USER CODE END USART3_Init 0 */

	/* USER CODE BEGIN USART3_Init 1 */

	/* USER CODE END USART3_Init 1 */
	huart3.Instance = USART3;
	huart3.Init.BaudRate = 115200;
	huart3.Init.WordLength = UART_WORDLENGTH_8B;
	huart3.Init.StopBits = UART_STOPBITS_1;
	huart3.Init.Parity = UART_PARITY_NONE;
	huart3.Init.Mode = UART_MODE_TX_RX;
	huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart3.Init.OverSampling = UART_OVERSAMPLING_16;
	huart3.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	huart3.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
	if (HAL_UART_Init(&huart3) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN USART3_Init 2 */
	/*__HAL_UART_ENABLE_IT(&huart3, UART_IT_RXNE);

	RX_string.reserve(256);
	RX_string.assign("\0");

	TX_string.reserve(256);
	TX_string.assign("\0");

	endofCMD = 0;

	UART_transmit("COM on debug");*/

	/* USER CODE END USART3_Init 2 */

}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *UartHandle) {
	Error_Handler();
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) {
	__NOP();
}

int getQueueMsgsize() {
	RX_string.assign("\0");
	return v_queueCmd.size();
}

int Enqueue(std::string &RX_string){

	if(stateMachine == SECU){ // cas spécial déblocage scpi
		if (RX_string.compare("*RST") == 0) {
				//v_queueCmd.push_back(RX_string);
				stateMachine = RST;
		}else if(RX_string.compare("ERR ?") == 0){
			UART_transmit(mainCerrG.ToString());
		}

	}else{
		if (RX_string.compare("*RST") == 0) {   //Test le zéro de l'égalité
			//v_queueCmd.push_back(RX_string);
			stateMachine = RST;
			NVIC_SystemReset();
		}else if (RX_string.compare("*OPC ?") == 0){
			UART_transmit("There are "+ std::to_string(getQueueMsgsize()) + " commands remaining" );
		}else if (RX_string.compare("*IDN ?") == 0) {
			if(endofCMD ==1){
				v_queueCmd.push_back(RX_string);
				stateMachine = CMD;
			}else{
				v_queueCmd.push_back(RX_string);
			}
		}else if (RX_string.compare("ERR") == 0){
			if(endofCMD ==1){
				v_queueCmd.push_back(RX_string);
				stateMachine = CMD;
			}else {
				v_queueCmd.push_back(RX_string);
			}
		}else if (RX_string.compare("*CLR") == 0){
			if(endofCMD ==1){
				v_queueCmd.push_back(RX_string);
				stateMachine = CLEAR;
			}else {
				v_queueCmd.push_back(RX_string);
			}
		}else if (RX_string.compare("ACK") == 0){
			if(acknowledge == 0 ){
				acknowledge =1;
			}else{
				acknowledge =0;
			}
			Reset_uart_buffer();
		}else if (RX_string.compare(0, 6, "EEPROM") == 0){
			int eepromNb = 0;
			std::size_t pos = -1;
			std::string dataEeprom;

			eepromNb = stoi(RX_string.substr(6), nullptr, 10);

			pos = RX_string.find_last_of(" "); //prend la position du caractere ' '
			if(pos == -1){
				; //commande eeprom sans ? ni de chaine
			}else{
				if(RX_string.substr(pos+1).compare("?") == 0){ // si le prochain caractère après ' ' est le '?'
					if(eepromNb == 1){
						std::string s;
						rack1.carteEIC1.getJsonStringfromMemory(s);//lecture eeprom 1
						UART_transmit(s);
					}else{
						;//autre
					}
				}else{
					if(eepromNb == 1){
						dataEeprom.assign(RX_string.substr(pos+1));//écriture eeprom 1
						rack1.carteEIC1.storeJsonStringtoMemory(dataEeprom);
					}else{
						;//autre
					}
				}
			}



			Reset_uart_buffer();
		}








		else{
			if(stateMachine != CMD){ //Protection pour empecher d'avoir plusieurs commande en meme temps
				if(endofCMD ==1){
					v_queueCmd.push_back(RX_string);
					stateMachine = CMD;
				}else{
					v_queueCmd.push_back(RX_string);
				}
			}else{
				//commande longue bloquée
			}
		}
	}


	Reset_uart_buffer();

	return 0;
}
int deQueueFirstCmd() {
	v_queueCmd.erase(v_queueCmd.begin());
	return 0;
}

int getFirstCmd(std::string &MSG){
	MSG.assign(v_queueCmd.at(0));
	return 0;
}

void clearQueuemsg(void){
	v_queueCmd.clear();
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {

	if (RX_Buffer[0] != '\r') {
		if (RX_Buffer[0] == ';') {
			Enqueue(RX_string);
			RX_string.assign("\0");
		}else if(RX_Buffer[0] == '\n'){
			;
		}else {
			RX_string = RX_string + (char)toupper(RX_Buffer[0]);
		}
	} else { //fin de reception commandes


		endofCMD = 1;
		Enqueue(RX_string);

	}

	if(huart->Instance == USART3){ //debug
		__HAL_UART_ENABLE_IT(&huart3, UART_IT_RXNE);
	}else if(huart->Instance == UART4){//ftdi
		__HAL_UART_ENABLE_IT(&huart4, UART_IT_RXNE);
	}



}

void UART3_transmit(std::string stringtosend) {/*debug*/
	stringtosend = stringtosend + "\n" + "\r";
	char char_array[stringtosend.length()];

	stringtosend.copy(char_array, stringtosend.length());

	HAL_UART_Transmit(&huart3, (uint8_t*) char_array, stringtosend.length(),
			0xFFFF);

	Reset_uart_buffer();

}

void UART_transmit(std::string stringtosend) {/*via external ftdi cable*/
	stringtosend = stringtosend + "\n";
	char char_array[stringtosend.length()];

	stringtosend.copy(char_array, stringtosend.length());

	HAL_UART_Transmit(&huart4, (uint8_t*) char_array, stringtosend.length(),
			0xFFFF);

	Reset_uart_buffer();

}

void Reset_uart_buffer(void) {
	TX_string.assign("\0");
	RX_string.assign("\0");
	RX_Buffer[0] = '\0';
	endofCMD = 0;
}

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
