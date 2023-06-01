#include <stdio.h>

#ifndef _cadena_
#define _cadena_

typedef struct{
	char* alpha;
	int t;
}Alfabeto;

typedef struct{
	char* wn;
}Cadena;

typedef Alfabeto* alfabeto;
typedef Cadena* cadena;

alfabeto createAlpha();
alfabeto insertAlpha(alfabeto a,char n,int pos);
void displayAlpha(alfabeto a);
cadena createString();
alfabeto menuAlpha(alfabeto a);
void menuCadena(alfabeto a);
int cmpFnL(char a,char z,alfabeto S);
cadena concatenate(cadena u,cadena v);
void prefijo(cadena u,cadena v,int tam);
void sufijo(cadena u,cadena v,int tam);
void Subcadena(cadena u,int pre,int suf);
void Subsecuencia(cadena u,cadena v);
int ocurrency(cadena a,char x);
void powerW(cadena a,int z);
cadena reverse(cadena a);

#endif