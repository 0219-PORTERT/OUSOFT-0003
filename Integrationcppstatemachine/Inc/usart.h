/**
  ******************************************************************************
  * File Name          : USART.h
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __usart_H
#define __usart_H


/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stateMachine.h"
#include "..\Src\CerrG.h"
#include <string>
#include <iostream>

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern UART_HandleTypeDef huart4;
extern UART_HandleTypeDef huart5;
extern UART_HandleTypeDef huart7;

/* USER CODE BEGIN Private defines */
extern UART_HandleTypeDef huart3;
/* USER CODE END Private defines */

void MX_UART4_Init(void);
void MX_UART5_Init(void);
void MX_UART7_Init(void);

/* USER CODE BEGIN Prototypes */





int getQueueMsgsize();
void MX_USART3_UART_Init(void);
int deQueueFirstCmd();
int Enqueue();
int getFirstCmd(std::string &MSG);

void clearQueuemsg(void);
void UART_transmit(std::string stringtosend);
void Reset_uart_buffer(void);

void UART4_transmit(std::string stringtosend);
/* USER CODE END Prototypes */

extern T_STATUS stateMachine;
extern CerrG mainCerrG;



#endif /*__ usart_H */

/**
  * @}
  */








/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
