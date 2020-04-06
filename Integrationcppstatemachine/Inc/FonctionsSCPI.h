/*
 * FonctionsSCPI.h
 *
 *  Created on: 23 juil. 2019
 *      Author: PARIS
 */

#ifndef FONCTIONSSCPI_H_
#define FONCTIONSSCPI_H_

char* TrameSelectionSource(char *paramString);
char* TrameCptSource(char *paramString);
//char* TrameMesureCourants(char *paramString, char *paramString2);
char* TrameMesureCourants(char *paramString, char *paramString2,char* reponseFonction);
char* TrameVariationPosition(char *paramString);
#endif /* FONCTIONSSCPI_H_ */
