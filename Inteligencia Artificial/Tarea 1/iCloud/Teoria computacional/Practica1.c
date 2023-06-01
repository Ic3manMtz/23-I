#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include "Practica1.h"

alfabeto createAlpha(){
	alfabeto a;

	a = (alfabeto)malloc(sizeof(Alfabeto));

	if( a == NULL ){
		printf("Memoria insuficiente\n");
		exit(1);
	}

	a->alpha = (char*)malloc(sizeof(char));
	a->t = 0;

	return a;
}

alfabeto insertAlpha(alfabeto a,char n,int pos){
	a->alpha[pos] = n + pos;

	return a;
}

void displayAlpha(alfabeto a){
	int i;

	for( i = 0 ; i <= a->t ; i++ ){
		printf("Elemento %i del alfabeto.%c\n",i+1,a->alpha[i] );
	}
}

cadena createString(){
	cadena a;

	a = (cadena)malloc(sizeof(Cadena));

	a->wn = (char*)malloc(sizeof(char));

	return a;
}

alfabeto menuAlpha(alfabeto S){
	char opt;
	int i,j;

	i = 0;

	printf("Que alfabeto quiere usar?\n
		    A)El predeterminado.\n
		    B)Quiero crear el mio simbolo por simbolo.\n");
	scanf("%c",&opt);
	opt = toupper(opt);
	getchar();

	while( opt != 'A' && opt != 'B' ){
		printf("'%c' No es una opcion valida. Intente de nuevo.\n",opt);
		scanf("%c",&opt);
		opt = toupper(opt);
		getchar();
	}

	switch(opt){

		case 'A':
				break;

		case 'B': do{
						printf("\tEscriba el simbolo %i del alfabeto.............",i+1);
						scanf("%c",&S->alpha[i]);
						getchar();
						i++;
						S->t = i;

						printf("Desea agregar otro simbolo? S/N\n");
						scanf("%c",&opt);
						opt = toupper(opt);
						getchar();

						while( opt != 'S' && opt != 'N' ){
							printf("'%c'No es una opcion valida.Intente de nuevo.\n",opt );
							scanf("%c",&opt);
							opt = toupper(opt);
							getchar();
						}
					}while( opt == 'S' );
				break;
	}
}

void menuCadena(alfabeto S){
	cadena w1,w2,w1w2,w2w1,w11,w22,subsecuencia;
	int i,j,t,n,n2,n3,n41,n42,n7,n8;
	char a,z,x;

	t = 0;

	w1 = createString();
	w2 = createString();

	printf("\n\n\t*******Insercion de cadenas U y V*******\n");

	printf("Cadena U.....");
	scanf("%[^\n]s",w1->wn);
	getchar();

	printf("Cadena V......");
	scanf("%[^\n]s",w2->wn);
	getchar();

	do{
		printf("\n\t******Elija la opcion que quiera realizar*****\n
				1)Concatenacion de cadenas U y V\n
				2)Prefijos de U y V\n
				3)Sufijos de U y V\n
				4)Subcadena de U y V\n
				5)Subsecuencia de U y V\n
				6)Inversion de U y V\n
				7)V%cn\n
				8)Salir.\n",94);
		scanf("%i",&j);

		switch(j){
			case 1:	w1w2 = createString();
					w2w1 = createString();

					w1w2 = concatenate(w1,w2);
					w2w1 = concatenate(w2,w1);

					printf("Concatenacion de U y V......%s\n",w1w2->wn );
					printf("Concatenacion de V y U......%s\n",w2w1->wn );
					break;
			case 2:	printf("Escriba el numero de simbolos a eliminar.........");
					scanf("%i",&n2);
					prefijo(w1,w2,n2);
					break;
			case 3: printf("Escriba el numero de simbolos a eliminar.........");		
					scanf("%i",&n3);
					sufijo(w1,w2,n3);
					break;
			case 4:	printf("Escriba el tamano del prefijo......");
					scanf("%i",&n41);

					printf("Escribe el tamano del sufijo.......");
					scanf("%i",&n42);

					Subcadena(w1,n41,n42);
					Subcadena(w2,n41,n42);
					break;
			case 5:	subsecuencia = createString();

					getchar();	
					printf("Escriba la cadena de simbolos a eliminar........");
					scanf("%[^\n]s",subsecuencia->wn);
					getchar();

					Subsecuencia(subsecuencia,w2);
					break;
			case 6:	w11 = createString();
					w22 = createString();

					w11 = reverse(w1);
					w22 = reverse(w2);

					printf("\nCadena U....%s,cadena U%c-1....%s.\n",w1->wn,94,w11->wn);
					printf("Cadena V....%s,cadena V%c-1....%s.\n",w2->wn,94,w22->wn);
					break;
			case 7:	printf("Escriba el numero de potencia que se le aplicara a V.....");
					scanf("%i",&n7);
					powerW(w2,n7);
					break;
		}
	}while( j != 8 );
}

int cmpFnL(char a,char z,alfabeto S){
	if ( isdigit(a) != 0 && isdigit(z) != 0 ){
		S->t = z - 47;
		return 1;
	}
	if ( isupper(a) != 0 && isupper(z) != 0 ){
		S->t = z - 64;
		return 1;
	}
	if ( islower(a) != 0 && islower(z) != 0 ){
		S->t = z - 96;
		return 1;
	}

	return 0;
}

cadena concatenate(cadena u,cadena v){
	cadena a;

	a = createString();

	strcpy(a->wn,u->wn);
	strcat(a->wn,v->wn);

	return a;
}

void prefijo(cadena u, cadena v,int tam){
	int i,j,nu,nv;

	printf("\n\t*****Prefijos*****\n");

	printf("\nCadena U\n");
	nu = strlen(u->wn);

	if( tam < nu ){
		for( i = 0 ; i < tam ; i++ ){
			for( j = 0 ; j < (tam - i) ; j++ ){
				printf("%c",u->wn[j+i] );
			}
			printf(",");
		}
		printf("lambda");
	}else{
		printf("lambda");
	}

	printf("\nCadena V\n");
	nv = strlen(v->wn);

	if ( tam < nv){
		for( i = 0 ; i < tam ; i++ ){
			for( j = 0 ; j < (tam - i) ; j++ ){
				printf("%c",v->wn[j+i] );
			}
			printf(",");
		}
		printf("lambda\n");
	}else{
		printf("lambda\n");
	}
}

void sufijo(cadena u, cadena v,int tam){
	int i,j,nu,nv;

	printf("\n\t*****Sufijos*****\n");

	printf("\nCadena U\n");
	nu = strlen(u->wn);

	if ( tam < nu ){
		for( i = 0 ; i < tam ; i++ ){
			for( j = 0 ; j < (tam - i) ; j++ ){
				printf("%c",u->wn[j] );
			}
			printf(",");
		}
		printf("lambda");
	}else{
		printf("lambda\n");
	}

	printf("\nCadena V\n");
	nv = strlen(v->wn);

	if ( tam < nv ){
		for( i = 0 ; i < tam ; i++ ){
			for( j = 0 ; j < (tam - i) ; j++ ){
				printf("%c",v->wn[j] );
			}
			printf(",");
		}
		printf("lambda\n");
	}else{
		printf("lambda\n");
	}
}

void Subcadena(cadena a,int pre,int suf){
	cadena temp;
	int i,n,j;

	temp = createString();
	n = strlen(a->wn);

	if( (pre + suf) >= n ){
		printf("Lambda\n");
	}
	if( (pre + suf) < n ){
		for( i = pre,j = 0 ; i < (n - suf) ; i++,j++ ){
				temp->wn[j] = a->wn[i];
		}
		printf("Subcadena.....%s.\n",temp->wn);
	}
}

void Subsecuencia(cadena subsecuencia,cadena a){
	int i,j,na,ns;
	char espacio;
	cadena temp;

	temp = createString();
	ns = strlen(subsecuencia->wn);
	na = strlen(a->wn);
	espacio = ' ';
	strcpy(temp->wn,a->wn);

	printf("\nCadena V.....%s\t\t",a->wn );

	for( i = 0 ; i < ns ; i++ ){
		for( j = 0 ; j < na ; j++ ){
			if( subsecuencia->wn[i] == temp->wn[j] ){
				temp->wn[j] = espacio;
			}
		}
	}

	printf("Cadena de simbolos.....%s\n\t",subsecuencia->wn);

	if ( ocurrency(temp,espacio) == na ){
		printf("Lambda\n");
	}else{
		printf("Subsecuencia de V.....%s\n",temp->wn );
	}
}

int ocurrency(cadena a,char x){
	int i,cont,n;

	n = strlen(a->wn);
	cont = 0;

	for( i = 0 ; i < n ; i++ ){
		if( a->wn[i] == x )
			cont++;
	}

	return cont;
}

void powerW(cadena a,int z){
	int i;

	cadena temp,wt;
	temp = createString();
	wt = createString();

	if( z == 0 ){
		printf("Lambda\n\n");
	}
	if( z > 0 ){
		for( i = 0 ; i < z ; i++ ){
			strcpy(temp->wn,a->wn);
			strcat(wt->wn,temp->wn);
		}
		printf("\tCadena V%c%i\n\t%s.",94,z,wt->wn);
	}
}

cadena reverse(cadena a){
	char temp;
	int len,i,k;
	cadena z;

	z = createString();
	len = strlen(a->wn) - 1;
	k = len;
	strcpy(z->wn,a->wn);

	for( i = 0 ; i < len ; i++ ){
		temp = z->wn[k];
		z->wn[k] = z->wn[i];
		z->wn[i] = temp;
		k--;

		if ( k == (len / 2) )
			break;
	}

	return z;
}