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

/* USER CODE BEGIN 0 */

UART_HandleTypeDef huart3;

/* USER CODE END 0 */

UART_HandleTypeDef huart4;
UART_HandleTypeDef huart5;
UART_HandleTypeDef huart7;

char RX_Buffer[1];
std::string RX_string;
std::string TX_string;

std::vector<std::string> stack_cmd;

/* UART4 init function */
void MX_UART4_Init(void) {

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

	//__HAL_UART_ENABLE_IT(&huart2, UART_IT_RXNE);

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
		HAL_NVIC_SetPriority(UART4_IRQn, 0, 0);
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

void MX_USART3_UART_Init(void) {

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
	HAL_NVIC_SetPriority(USART3_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(USART3_IRQn);
	/* USER CODE END USART3_Init 0 */

	/* USER CODE BEGIN USART3_Init 1 */

	/* USER CODE END USART3_Init 1 */
	huart3.Instance = USART3;
	huart3.Init.BaudRate = 9600;
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
	__HAL_UART_ENABLE_IT(&huart3, UART_IT_RXNE);


	 RX_string.reserve(256);
	 RX_string.assign("\0");

	 TX_string.reserve(256);
	 TX_string.assign("\0");


	/* USER CODE END USART3_Init 2 */

}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *UartHandle) {
	Error_Handler();
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) {
	__NOP();
}

int getstackmsgsize(){
	return stack_cmd.size();
}

int Stackmsg(std::string &MSG){
	MSG = stack_cmd.at(0); //Il faut passer par une recopie MSG->assign(stack_cmd.at(0)) car là, tu déréférence le pointeur MSG !
	stack_cmd.erase(stack_cmd.begin());

	return 0;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	// std::string test = ""; A SUPPRIMER

		if(RX_Buffer[0] != '\r') {
			if(RX_Buffer[0] == ';'){
				RX_string+="\0";  //Ajout du caractère de fin de ligne avant enregistrement dans le vecteur
				stack_cmd.push_back(RX_string);
				RX_string.assign("\0");
			}else{
				RX_string = RX_string + RX_Buffer[0];
			}
		}else {
			//RX_string = RX_string + "\n" + "\r"; ON NE MET PAS LES CARACTERE DE FIN MAIS ILS SERVENT A DECLENCHER L'ACTION
			if (RX_string.compare("*RST\n\r") == 0) {   //Test le zéro de l'égalité
				stateMachine = RST;
			}else {
				stack_cmd.push_back(RX_string);
				//test = stack_cmd.at(0);
				//test = stack_cmd.at(1);
				stateMachine = CMD;
			}
		}


	__HAL_UART_CLEAR_IT(&huart3, UART_IT_RXNE);

}


void UART_transmit(std::string stringtosend) {
	stringtosend = stringtosend + "\n" + "\r";
	char char_array[stringtosend.length()+1];

	stringtosend.copy(char_array, stringtosend.length()+1);


	HAL_UART_Transmit(&huart3, (uint8_t*) char_array, stringtosend.length()+1, 0xFFFF);

	Reset_uart_buffer();

}



void Reset_uart_buffer(void) {
	TX_string.assign("\0");
	RX_string.assign("\0");
	RX_Buffer[0] = '\0';
}

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
