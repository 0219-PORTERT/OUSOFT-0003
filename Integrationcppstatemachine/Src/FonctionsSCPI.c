/*
 * FonctionsSCPI.c
 *
 *  Created on: 23 juil. 2019
 *      Author: PARIS
 */

#include <FonctionsSCPI.h>
#include "main.h"
#include "tm_stm32_adc.h"

char* TrameSelectionSource(char *paramString){

	if(strstr(paramString, "?") != NULL ){
		//return Src_Selected();
		return "relais actif:";
	}else if(strstr(paramString, "NULL") != NULL ){
		//Selection_Src_Position(0);
	}else if(strstr(paramString, "VW13") != NULL ){
		//Selection_Src_Position(1);
	}else if(strstr(paramString, "VW24") != NULL ){
		//Selection_Src_Position(2);
	}else if(strstr(paramString, "Z1") != NULL ){
		//Selection_Src_Position(3);
	}else if(strstr(paramString, "Z2") != NULL ){
		//Selection_Src_Position(4);
	}else{
		return "ERROR";
	}
	return "OK";
}

char* TrameCptSource(char *paramString){
	if(strstr(paramString, "?") != NULL ){
		//COMPTEUR RELAIS
		return "relais";
	}else{
		return "ERROR";
	}
}


char* TrameMesureCourants(char *paramString, char *paramString2, char* reponseFonction){
	char buffer[7];

	if(strcmp(paramString2, "?") == 0 ){
		if(strstr(paramString, "V1") != NULL ){
			itoa (TM_ADC_Read(ADC3, TM_ADC_Channel_0),buffer,10);
		}else if(strstr(paramString, "W1") != NULL ){
			itoa (TM_ADC_Read(ADC3, TM_ADC_Channel_3),buffer,10);
		}else if(strstr(paramString, "V3") != NULL ){
			itoa (TM_ADC_Read(ADC3, TM_ADC_Channel_4),buffer,10);
		}else if(strstr(paramString, "W3") != NULL ){
			itoa (TM_ADC_Read(ADC3, TM_ADC_Channel_5),buffer,10);
		}else if(strstr(paramString, "V2") != NULL ){
			itoa (TM_ADC_Read(ADC3, TM_ADC_Channel_6),buffer,10);
		}else if(strstr(paramString, "W2") != NULL ){
			itoa (TM_ADC_Read(ADC3, TM_ADC_Channel_8),buffer,10);
		}else if(strstr(paramString, "V4") != NULL ){
			itoa (TM_ADC_Read(ADC3, TM_ADC_Channel_9),buffer,10);
		}else if(strstr(paramString, "W4") != NULL ){
			itoa (TM_ADC_Read(ADC3, TM_ADC_Channel_10),buffer,10);
		}else if(strstr(paramString, "Z1") != NULL ){
			itoa (TM_ADC_Read(ADC3, TM_ADC_Channel_12),buffer,10);
		}else if(strstr(paramString, "Z2") != NULL ){
			itoa (TM_ADC_Read(ADC3, TM_ADC_Channel_13),buffer,10);
		}else if(strstr(paramString, "VREF") != NULL ){
			//itoa (Get_ADC_Value(ADC_CHANNEL_VREFINT,0),buffer,10);
		}else if(strstr(paramString, "TEMP") != NULL ){
			//itoa (Get_ADC_Value(ADC_CHANNEL_TEMPSENSOR,0),buffer,10);
		}else{
			strcpy( buffer, "ERROR" );
		}

		strcpy( reponseFonction, buffer );
		return &buffer;
	}else{
		return "ERROR";
	}
}



char* TrameVariationPosition(char *paramString){
	char buffer[7];

	if(strcmp(paramString, "?") == 0 ){
		itoa (VmodValue(),buffer,10);
	}else{
		Set_Dac_Value(DAC_CHANNEL_1, atoi(paramString));
	}
	return "ok";
}





char* Sys_Reset(char *paramString){
	NVIC_SystemReset();
	return "ok";
}
char* Sys_ID(char* paramString){

	if(paramString[0] == 63){ //vérif 63 = '?'
		return "OUELEC-0157";
	}else{
		return "ERROR";
	}
}

/*char* Trame_Test_I2C(char *paramString){

	char* testCom = "hello there";

	I2C_Transmit(testCom);

	return "ok";
}*/
