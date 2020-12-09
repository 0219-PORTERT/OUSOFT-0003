/**
  ******************************************************************************
  * File Name          : I2C.h
  * Description        : This file provides code for the configuration
  *                      of the I2C instances.
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
#ifndef __i2c_H
#define __i2c_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern I2C_HandleTypeDef hi2c2;
extern I2C_HandleTypeDef hi2c3;
extern I2C_HandleTypeDef hi2c4;

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void MX_I2C1_Init(void);
void MX_I2C2_Init(void);
void MX_I2C3_Init(void);
void MX_I2C4_Init(void);

void testI2CCS(I2C_TypeDef* I2Cx);

void enableI2C_main();
void disableI2Cmain();

void enableI2C_EXT1();
void disableI2C_EXT1();

void enableI2C_EXT2();
void disableI2C_EXT2();
/* USER CODE BEGIN Prototypes */
/*à deplacer dans les fichiers qui correspondront*/

/*PROTO ADRESS*/
/*#define I2C4_POT1K_PHYADD 0x5A
#define I2C4_POT100K_PHYADD 0x58

#define I2CEEPROM1 0xA0
#define I2CEEPROM2 0xA2

#define I2CTEMP 0x90

#define I2CEXP 0x40
/* USER CODE END Prototypes */

/*OUCART-018 ADRESS*/

/*#define TEM_HUM_I2CADD 0x44
#define EXPSECU_I2CADD 0x40
#define POT_I2CADD 0x58
#define MEMU3_I2CADD 0xa0
#define MEMU4_I2CADD 0xa0
#define MEMU5_I2CADD 0xa4

/*OUCART-0014 ADRESS*/

#define EXP_DATA_ADRESS_I2CADD 0x46

#define POT100KA_I2CADD 0x58
#define POT1KA_I2CADD 0x5c
#define POT100KB_I2CADD 0x5A
#define POT1KB_I2CADD 0x5E

#define EXPSECU_I2CADD 0x40 //i2c secu

#define EXP_DIO_I2CADD 0x42

#define MEMU1_I2CADD 0xAE
#define MEMU2_I2CADD 0xAC
#define MEMU3_I2CADD 0xAA
#define MEMU4_I2CADD 0xA8

#define TEM_HUM_I2CADD 0x88

/*OUCART-0018 V2 +LEM*/

#define SWITCHI2C 0xD0
#define ADCDAC_I2CADD 0x22

#define EEPROM1_I2CADD 0xa4

/**/

#ifdef __cplusplus
}
#endif
#endif /*__ i2c_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
