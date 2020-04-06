/**
  ******************************************************************************
  * File Name          : ADC.c
  * Description        : This file provides code for the configuration
  *                      of the ADC instances.
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
#include "adc.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

ADC_HandleTypeDef hadc1;

ADC_HandleTypeDef hadc3;
ADC_ChannelConfTypeDef adc3Channel;

/* ADC1 init function */
void MX_ADC1_Init(void)
{
  ADC_ChannelConfTypeDef sConfig = {0};

  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion) 
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_RISING;
  hadc1.Init.ExternalTrigConv = ADC_EXTERNALTRIGCONV_EXT_IT11;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time. 
  */
  sConfig.Channel = ADC_CHANNEL_TEMPSENSOR;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

}
/* ADC3 init function */
void MX_ADC3_Init(void)
{
  ADC_ChannelConfTypeDef sConfig = {0};

  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion) 
  */
  hadc3.Instance = ADC3;
  hadc3.Init.ClockPrescaler = ADC_CLOCKPRESCALER_PCLK_DIV2;
  hadc3.Init.Resolution = ADC_RESOLUTION_12B;
  hadc3.Init.ScanConvMode = ADC_SCAN_ENABLE;
  hadc3.Init.ContinuousConvMode = ENABLE;
  hadc3.Init.DiscontinuousConvMode = ENABLE;
  hadc3.Init.ExternalTrigConvEdge = ADC_SOFTWARE_START;
  hadc3.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc3.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc3.Init.NbrOfConversion = 1;
  hadc3.Init.DMAContinuousRequests = DISABLE;
  hadc3.Init.EOCSelection = DISABLE;
  if (HAL_ADC_Init(&hadc3) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time. 
  */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  //HAL_ADC_MspDeInit(&hadc3);
  //HAL_ADC_MspInit(&hadc3);



}

void HAL_ADC_MspInit(ADC_HandleTypeDef* adcHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(adcHandle->Instance==ADC1)
  {
  /* USER CODE BEGIN ADC1_MspInit 0 */

  /* USER CODE END ADC1_MspInit 0 */
    /* ADC1 clock enable */
    __HAL_RCC_ADC1_CLK_ENABLE();
  /* USER CODE BEGIN ADC1_MspInit 1 */

  /* USER CODE END ADC1_MspInit 1 */
  }
  else if(adcHandle->Instance==ADC3)
  {
  /* USER CODE BEGIN ADC3_MspInit 0 */

  /* USER CODE END ADC3_MspInit 0 */
    /* ADC3 clock enable */
    __HAL_RCC_ADC3_CLK_ENABLE();
  
    __HAL_RCC_GPIOF_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**ADC3 GPIO Configuration    
    PF3     ------> ADC3_IN9
    PF4     ------> ADC3_IN14
    PF5     ------> ADC3_IN15
    PF6     ------> ADC3_IN4
    PF7     ------> ADC3_IN5
    PF8     ------> ADC3_IN6
    PF10     ------> ADC3_IN8
    PC0     ------> ADC3_IN10
    PC2     ------> ADC3_IN12
    PC3     ------> ADC3_IN13
    PA0/WKUP     ------> ADC3_IN0
    PA3     ------> ADC3_IN3 
    */
    GPIO_InitStruct.Pin = AI6_CN12_58_Pin|AI10_CN12_38_Pin|AI11_CN12_36_Pin|AI2_CN11_9_Pin 
                          |AI3_CN11_11_Pin|AI4_CN11_54_Pin|AI5_CN12_42_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = AI7_CN11_38_Pin|AI8_CN11_35_Pin|AI9_CN11_37_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = AI0_CN11_28_Pin|AI1_CN11_37_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN ADC3_MspInit 1 */

  /* USER CODE END ADC3_MspInit 1 */
  }
}

void HAL_ADC_MspDeInit(ADC_HandleTypeDef* adcHandle)
{

  if(adcHandle->Instance==ADC1)
  {
  /* USER CODE BEGIN ADC1_MspDeInit 0 */

  /* USER CODE END ADC1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_ADC1_CLK_DISABLE();
  /* USER CODE BEGIN ADC1_MspDeInit 1 */

  /* USER CODE END ADC1_MspDeInit 1 */
  }
  else if(adcHandle->Instance==ADC3)
  {
  /* USER CODE BEGIN ADC3_MspDeInit 0 */

  /* USER CODE END ADC3_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_ADC3_CLK_DISABLE();
  
    /**ADC3 GPIO Configuration    
    PF3     ------> ADC3_IN9
    PF4     ------> ADC3_IN14
    PF5     ------> ADC3_IN15
    PF6     ------> ADC3_IN4
    PF7     ------> ADC3_IN5
    PF8     ------> ADC3_IN6
    PF10     ------> ADC3_IN8
    PC0     ------> ADC3_IN10
    PC2     ------> ADC3_IN12
    PC3     ------> ADC3_IN13
    PA0/WKUP     ------> ADC3_IN0
    PA3     ------> ADC3_IN3 
    */
    HAL_GPIO_DeInit(GPIOF, AI6_CN12_58_Pin|AI10_CN12_38_Pin|AI11_CN12_36_Pin|AI2_CN11_9_Pin 
                          |AI3_CN11_11_Pin|AI4_CN11_54_Pin|AI5_CN12_42_Pin);

    HAL_GPIO_DeInit(GPIOC, AI7_CN11_38_Pin|AI8_CN11_35_Pin|AI9_CN11_37_Pin);

    HAL_GPIO_DeInit(GPIOA, AI0_CN11_28_Pin|AI1_CN11_37_Pin);

  /* USER CODE BEGIN ADC3_MspDeInit 1 */

  /* USER CODE END ADC3_MspDeInit 1 */
  }
} 

/* USER CODE BEGIN 1 */

/*void ADC_Config_channel(uint32_t channel)
{
  adcChannel.Channel = channel;
  adcChannel.Rank = ADC_REGULAR_RANK_1;
  adcChannel.SamplingTime     = ADC_SAMPLETIME_247CYCLES_5;
  adcChannel.OffsetNumber     = ADC_OFFSET_NONE;
  adcChannel.Offset           = 0;
  adcChannel.SingleDiff       = ADC_SINGLE_ENDED;

  HAL_ADC_ConfigChannel(&hadc1, &adcChannel);
}*/

/*uint32_t ADC_Single_channel(uint32_t channel)
{
  uint32_t digital_result;
  HAL_ADC_Stop(&hadc1);

  ADC_Config_channel(channel);

  HAL_ADCEx_Calibration_Start(&hadc1, ADC_SINGLE_ENDED);

  HAL_ADC_Start(&hadc1);
  HAL_ADC_PollForConversion(&hadc1, 1000);
  digital_result = HAL_ADC_GetValue(&hadc1);
  HAL_ADC_Stop(&hadc1);

  ADC_Config_channel(channel);

  return digital_result;
}*/




/*int Get_ADC3_Value(uint32_t voie, int cal){
	float value = 0;

	if(cal == 0){
		//value = ((3.3/4095.0) * ADC_Single_channel(voie));
		value = ADC_Single_channel(voie);
	}else{}


	return value;
}*/






/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
