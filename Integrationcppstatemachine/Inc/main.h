/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define I2C_EXT1_SDA_CN11_53_Pin GPIO_PIN_0
#define I2C_EXT1_SDA_CN11_53_GPIO_Port GPIOF
#define I2C_EXT1_SCL_CN11_51_Pin GPIO_PIN_1
#define I2C_EXT1_SCL_CN11_51_GPIO_Port GPIOF
#define AI6_CN12_58_Pin GPIO_PIN_3
#define AI6_CN12_58_GPIO_Port GPIOF
#define AI10_CN12_38_Pin GPIO_PIN_4
#define AI10_CN12_38_GPIO_Port GPIOF
#define AI11_CN12_36_Pin GPIO_PIN_5
#define AI11_CN12_36_GPIO_Port GPIOF
#define AI2_CN11_9_Pin GPIO_PIN_6
#define AI2_CN11_9_GPIO_Port GPIOF
#define AI3_CN11_11_Pin GPIO_PIN_7
#define AI3_CN11_11_GPIO_Port GPIOF
#define AI4_CN11_54_Pin GPIO_PIN_8
#define AI4_CN11_54_GPIO_Port GPIOF
#define SY_DAC_CN11_56_Pin GPIO_PIN_9
#define SY_DAC_CN11_56_GPIO_Port GPIOF
#define AI5_CN12_42_Pin GPIO_PIN_10
#define AI5_CN12_42_GPIO_Port GPIOF
#define AI7_CN11_38_Pin GPIO_PIN_0
#define AI7_CN11_38_GPIO_Port GPIOC
#define AI8_CN11_35_Pin GPIO_PIN_2
#define AI8_CN11_35_GPIO_Port GPIOC
#define AI9_CN11_37_Pin GPIO_PIN_3
#define AI9_CN11_37_GPIO_Port GPIOC
#define AI0_CN11_28_Pin GPIO_PIN_0
#define AI0_CN11_28_GPIO_Port GPIOA
#define AI1_CN11_37_Pin GPIO_PIN_3
#define AI1_CN11_37_GPIO_Port GPIOA
#define AO0_CN11_32_Pin GPIO_PIN_4
#define AO0_CN11_32_GPIO_Port GPIOA
#define AO1_CN12_11_Pin GPIO_PIN_5
#define AO1_CN12_11_GPIO_Port GPIOA
#define PWM_3_CN12_24_Pin GPIO_PIN_1
#define PWM_3_CN12_24_GPIO_Port GPIOB
#define SPI3_MOSI_CN12_22_Pin GPIO_PIN_2
#define SPI3_MOSI_CN12_22_GPIO_Port GPIOB
#define I2C_MAIN_SCL_CN12_50_Pin GPIO_PIN_14
#define I2C_MAIN_SCL_CN12_50_GPIO_Port GPIOF
#define I2C_MAIN_SDA_CN12_60_Pin GPIO_PIN_15
#define I2C_MAIN_SDA_CN12_60_GPIO_Port GPIOF
#define SS0_CN11_58_Pin GPIO_PIN_1
#define SS0_CN11_58_GPIO_Port GPIOG
#define RX3_CN12_44_Pin GPIO_PIN_7
#define RX3_CN12_44_GPIO_Port GPIOE
#define TX3_CN12_40_Pin GPIO_PIN_8
#define TX3_CN12_40_GPIO_Port GPIOE
#define CS_I2C_0_Pin GPIO_PIN_12
#define CS_I2C_0_GPIO_Port GPIOE
#define CS_I2C_1_Pin GPIO_PIN_13
#define CS_I2C_1_GPIO_Port GPIOE
#define CS_I2C_2_Pin GPIO_PIN_14
#define CS_I2C_2_GPIO_Port GPIOE
#define CS_I2C_3_Pin GPIO_PIN_15
#define CS_I2C_3_GPIO_Port GPIOE
#define SY1_CN11_42_Pin GPIO_PIN_2
#define SY1_CN11_42_GPIO_Port GPIOG
#define SY2_CN11_44_Pin GPIO_PIN_3
#define SY2_CN11_44_GPIO_Port GPIOG
#define CS_FDP_CN12_69_Pin GPIO_PIN_4
#define CS_FDP_CN12_69_GPIO_Port GPIOG
#define CS_I2C_EX0_CN12_68_Pin GPIO_PIN_5
#define CS_I2C_EX0_CN12_68_GPIO_Port GPIOG
#define CS_I2C_EX1_CN12_70_Pin GPIO_PIN_6
#define CS_I2C_EX1_CN12_70_GPIO_Port GPIOG
#define CS_I2C_EX2_CN12_67_Pin GPIO_PIN_7
#define CS_I2C_EX2_CN12_67_GPIO_Port GPIOG
#define EXT_IT_SECU_Pin GPIO_PIN_8
#define EXT_IT_SECU_GPIO_Port GPIOG
#define PWM_1_CN12_19_Pin GPIO_PIN_7
#define PWM_1_CN12_19_GPIO_Port GPIOC
#define PWM_2_CN11_34_Pin GPIO_PIN_8
#define PWM_2_CN11_34_GPIO_Port GPIOC
#define I2C_SECU_SDA_CN12_1_Pin GPIO_PIN_9
#define I2C_SECU_SDA_CN12_1_GPIO_Port GPIOC
#define I2C_SECU_SCL_CN12_23_Pin GPIO_PIN_8
#define I2C_SECU_SCL_CN12_23_GPIO_Port GPIOA
#define RX1_CN12_14_Pin GPIO_PIN_11
#define RX1_CN12_14_GPIO_Port GPIOA
#define TX1_CN12_16_Pin GPIO_PIN_12
#define TX1_CN12_16_GPIO_Port GPIOA
#define PWM_4_CN11_17_Pin GPIO_PIN_15
#define PWM_4_CN11_17_GPIO_Port GPIOA
#define SPI3_SCK_CN11_1_Pin GPIO_PIN_10
#define SPI3_SCK_CN11_1_GPIO_Port GPIOC
#define SPI3_MISO_CN11_2_Pin GPIO_PIN_11
#define SPI3_MISO_CN11_2_GPIO_Port GPIOC
#define TX2_CN11_3_Pin GPIO_PIN_12
#define TX2_CN11_3_GPIO_Port GPIOC
#define RX2_CN11_4_Pin GPIO_PIN_2
#define RX2_CN11_4_GPIO_Port GPIOD
#define EXT_IT_TEMP_Pin GPIO_PIN_9
#define EXT_IT_TEMP_GPIO_Port GPIOG
#define RESET_CN11_66_Pin GPIO_PIN_10
#define RESET_CN11_66_GPIO_Port GPIOG
#define EXT_IT_11_CN11_70_Pin GPIO_PIN_11
#define EXT_IT_11_CN11_70_GPIO_Port GPIOG
#define CS_I2C_M GPIO_PIN_12
#define IT_I2C_A_GPIO_Port GPIOG
#define IT_I2C_B_Pin GPIO_PIN_13
#define IT_I2C_B_GPIO_Port GPIOG
#define PWM_5_CN12_31_Pin GPIO_PIN_3
#define PWM_5_CN12_31_GPIO_Port GPIOB
#define PWM_0_CN12_27_Pin GPIO_PIN_4
#define PWM_0_CN12_27_GPIO_Port GPIOB
#define PWM_6_CN12_17_Pin GPIO_PIN_6
#define PWM_6_CN12_17_GPIO_Port GPIOB
#define PWM_7_CN11_21_Pin GPIO_PIN_7
#define PWM_7_CN11_21_GPIO_Port GPIOB
#define PWM_8_CN12_3_Pin GPIO_PIN_8
#define PWM_8_CN12_3_GPIO_Port GPIOB
#define PWM_9_CN12_5_Pin GPIO_PIN_9
#define PWM_9_CN12_5_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */







/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
