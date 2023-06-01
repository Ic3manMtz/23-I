#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <winbgim.h>

typedef struct{
    int*** matrix;
    int x;
    int y;
    int z;
}Matriz;

typedef Matriz* matriz;

matriz crearMatriz(int x, int y, int z);
void llenarMatriz(matriz m);
void mostrarMatriz(matriz m);
void liberarMatriz(matriz m);
void menu(matriz m);
int sumaRenglon(matriz m,int opc);
int sumaColumna(matriz m,int opc);
int sumaCara(matriz m,int opc);
void mostrarCara(matriz m,int opc);
void pintarCaras(matriz m);
void pintarCubo();
void formaFigura(int opc);
int numeroRandom(int minimo, int maximo);

int main(int argc, char *argv[]){
	matriz m;
    //(int x, int y, int z)	
    m=crearMatriz(5,5,5);
    llenarMatriz(m);
	menu(m);
    liberarMatriz(m);
	return 0;
}

matriz crearMatriz(int x,int y,int z){
    matriz m;
    int i,j;
    m=(matriz)malloc(sizeof(Matriz));
    if(m==NULL){ printf("Memoria insuficiente"); }

    m->x=x;
    m->y=y;
    m->z=z;

    m->matrix=(int***)malloc(sizeof(int**)*x);
    for(i=0;i<x;i++){
        m->matrix[i]=(int**)malloc(sizeof(int*)*y);
        for(j=0;j<y;j++){
            m->matrix[i][j]=(int*)malloc(sizeof(int)*z);
        }
    }

    return m;
}

void llenarMatriz(matriz m){
    int i,j,k,cont;
    cont=1;
    for(i=0;i<m->x;i++){
        for(j=0;j<m->y;j++){
            for(k=0;k<m->z;k++){
                m->matrix[i][j][k]=cont++;
            }
        }
    }
}

void mostrarMatriz(matriz m){
    int i,j,k;
    for(i=0;i<m->x;i++){
        printf("Eje x\n");
        printf("|\t\t-------Eje y-------\n");
        for(j=0;j<m->y;j++){
            if(j==2){ printf("|\tEje z\t"); }else{
                printf("|\t | \t");
            }
            for(k=0;k<m->z;k++){
                printf("%d ",m->matrix[i][j][k]);
            }
            printf("\n");
        }
        printf("|\n");
    }
}

void liberarMatriz(matriz m){
    int i,j,k;
    for(i=0;i<m->x;i++){
        for(j=0;j<m->y;j++){
            free(m->matrix[i][j]);
        }
        free(m->matrix[i]);
    }
    free(m->matrix);
}

void menu(matriz m){
	int opc,suma,opcCase;
	suma=0;

	printf("\n\n\t*****Matriz de 5x5x5*****\n");
	do{
		printf("\nElija la opcion que quiera realizar\n\n");
		printf("\t1)Mostrar caras del cubo.\n");
		printf("\t2)Mostrar todos los elementos de la matriz.\n");
		printf("\t3)Mostrar animacion del cubo.\n");
		printf("\t4)Sumar un renglon.\n");
		printf("\t5)Suma de una columna.\n");
		printf("\t6)Suma de una cara.\n");
		printf("\t7)Salir.\n");
		scanf("%d",&opc);

		switch(opc){
			case 1:	printf("\n\t*****Las caras se mostraran de forma grafica*****\n");
					pintarCaras(m);
					system("cls");
					break;
			case 2: printf("\n\t*****Elementos de la matriz*****\n\n");
					mostrarMatriz(m);
					break;
			case 3: pintarCubo();
					break;
			case 4: printf("\n\t*****Suma de un renglon*****\n\n");
					printf("A continuacion se mostrara la cara 1\n\n");
					mostrarCara(m,11);
					printf("\nElija uno de los renglones para sumarlo....");
					scanf("%d",&opcCase);
					while(opcCase>5 || opcCase<1){
						printf("Renglon invalido. Intente de nuevo.\n");
						scanf("%d",&opcCase);
					}
					printf("...la suma del renglon %d es %d\n",opcCase,sumaRenglon(m,opcCase));
					system("pause");
					system("cls");			
					break;
			case 5: printf("\n\t*****Suma de una columna*****\n\n");
					printf("A continuacion se mostrara la cara 1\n\n");
					mostrarCara(m,12);
					printf("\nElija una de las columnas para sumarla....");
					scanf("%d",&opcCase);
					while(opcCase>5 || opcCase<1){
						printf("Renglon invalido. Intente de nuevo.\n");
						scanf("%d",&opcCase);
					}
					printf("...la suma de la columna %d es %d\n",opcCase,sumaColumna(m,opcCase));
					system("pause");
					system("cls");
					break;
			case 6:	printf("\n\t*****Suma de una cara*****\n");
					printf("A continuacion vera de forma grafica todas las caras del cubo\n");
					pintarCaras(m);
					printf("\nElija una de las caras para sumarla....");
					scanf("%d",&opcCase);
					while(opcCase>6 || opcCase<1){
						printf("Cara invalida. Intente de nuevo.\n");
						scanf("%d",&opcCase);
					}
					mostrarCara(m,opcCase);
					printf("...la suma de la  cara %d es %d\n",opcCase,sumaCara(m,opcCase));
					system("pause");
					system("cls");
					break;
			default:
			break;
		}
	}while(opc!=7);
}

int sumaRenglon(matriz m,int opc){
	int i,suma;
	suma=0;
	printf("\n\tSumando renglon.....");
	sleep(1);
	for(i=0;i<m->y;i++){
		suma+=m->matrix[0][opc-1][i];
		printf("%d ",m->matrix[0][opc-1][i]);
	}
	return suma;
}

int sumaColumna(matriz m,int opc){
	int i,suma;
	suma=0;
	printf("\n\tSumando columna.....");
	sleep(1);
	for(i=0;i<m->y;i++){
		suma+=m->matrix[0][i][opc-1];
		printf("%d ",m->matrix[0][i][opc-1]);
	}
	return suma;
}

int sumaCara(matriz m,int opc){
	int i,j,suma;
	suma=0;
	printf("\n\tSumando cara.....");
	sleep(1);
	switch(opc){
		case 1:
		for(i=0;i<m->z;i++){
			for(j=0;j<m->y;j++){
				suma+=m->matrix[0][i][j];
			}
		}
		break;
		case 2:
		for(i=0;i<m->x;i++){
			for(j=0;j<m->z;j++){
				suma+=m->matrix[i][0][j];
			}
		}
		break;
		case 3:
		for(i=0;i<m->x;i++){
			for(j=0;j<m->y;j++){
				suma+=m->matrix[j][i][4];
			}
		}
		break;
		case 4:
		for(i=0;i<m->x;i++){
			for(j=0;j<m->z;j++){
				suma+=m->matrix[i][4][j];
			}
		}
		break;
		case 5:
		for(i=0;i<m->y;i++){
			for(j=0;j<m->x;j++){
				suma+=m->matrix[j][i][0];
			}
		}
		break;
		case 6:
		for(i=0;i<m->z;i++){
			for(j=0;j<m->y;j++){
				suma+=m->matrix[4][j][i];
			}
		}
		break;
		default:
		break;
	}
	return suma;
}

void mostrarCara(matriz m, int opc){
	int i,j;
	switch(opc){
		case 11:	
		for(i=0;i<m->y;i++){
			printf("Reglon %d------",i+1);
			for(j=0;j<m->z;j++){
				printf("%d ",m->matrix[0][i][j]);
			}
			printf("\n");
		}
		break;
		case 12:
		printf("Columnas\n\n1 2 3 4 5\n| | | | |\n| | | | |\n| | | | |\n");
		for(i=0;i<m->y;i++){
			for(j=0;j<m->z;j++){
				printf("%d ",m->matrix[0][i][j]);
			}
			printf("\n");
		}
		break;
		case 1:
		printf("\n\tCara 1\n");
		for(i=0;i<m->z;i++){
			for(j=0;j<m->y;j++){
				printf("%d ",m->matrix[0][i][j]);
			}
			printf("\n");
		}
		break;
		case 2:
		printf("\n\tCara 2\n");
		for(i=0;i<m->x;i++){
			for(j=0;j<m->z;j++){
				printf("%d ",m->matrix[i][0][j]);
			}
			printf("\n");
		}
		break;
		case 3:
		printf("\n\tCara 3\n");
		for(i=0;i<m->x;i++){
			for(j=0;j<m->y;j++){
				printf("%d ",m->matrix[j][i][4]);
			}
			printf("\n");
		}
		break;
		case 4:
		printf("\n\tCara 4\n");
		for(i=0;i<m->x;i++){
			for(j=0;j<m->z;j++){
				printf("%d ",m->matrix[i][4][j]);
			}
			printf("\n");
		}
		break;
		case 5:
		printf("\n\tCara 5\n");
		for(i=0;i<m->y;i++){
			for(j=0;j<m->x;j++){
				printf("%d ",m->matrix[j][i][0]);
			}
			printf("\n");
		}
		break;
		case 6:
		printf("\n\tCara 6\n");
		for(i=0;i<m->z;i++){
			for(j=0;j<m->y;j++){
				printf("%d ",m->matrix[4][i][j]);
			}
			printf("\n");
		}
		break;
		default:
		break;
	}
}

void pintarCaras(matriz m){
	int i,j;
	char num[120];
	initwindow(850,700);					// init window graphics
	setbkcolor(0);							// set background
	cleardevice();
	setcolor(7);

	//quitando 20

	outtextxy(125,20,"Cara 1");
	rectangle(40,40,280,280);
	for(i=1;i<6;i++){
		for(j=1;j<6;j++){
			outtextxy(50*j,50*i,itoa(m->matrix[0][j-1][i-1],num,10));
		}
	}

	outtextxy(375,20,"Cara 2");
	rectangle(290,40,530,280);
	for(i=1;i<6;i++){
		for(j=0;j<5;j++){
			outtextxy(300+(50*j),50*i,itoa(m->matrix[i-1][0][j],num,10));
		}
	}

	outtextxy(625,20,"Cara 3");
	rectangle(540,40,780,280);
	for(i=1;i<6;i++){
		for(j=0;j<5;j++){
			outtextxy(550+(50*j),50*i,itoa(m->matrix[j][i-1][4],num,10));
		}
	}

	outtextxy(125,320,"Cara 4");
	rectangle(40,340,280,580);
	for(i=0;i<5;i++){
		for(j=1;j<6;j++){
			outtextxy(50*j,350+(50*i),itoa(m->matrix[i][4][j-1],num,10));
		}
	}

	outtextxy(375,320,"Cara 5");
	rectangle(290,340,530,580);
	for(i=0;i<5;i++){
		for(j=0;j<5;j++){
			outtextxy(300+(50*j),350+(50*i),itoa(m->matrix[j][i][0],num,10));
		}
	}

	outtextxy(625,320,"Cara 6");
	rectangle(540,340,780,580);
	for(i=0;i<5;i++){
		for(j=0;j<5;j++){
			outtextxy(550+(50*j),350+(50*i),itoa(m->matrix[4][i][j],num,10));
		}
	}

	setcolor(12);
	outtextxy(50,600,"Presiona cualquier tecla para cerrar esta ventana.");
	getch();
	closegraph();
}

void pintarCubo(){
	int i,cont,figura;
	cont=0;
	figura=0;
	initwindow(850,700);
	setbkcolor(0);
	cleardevice();

	for (i=EMPTY_FILL; i<USER_FILL; i++) {
		setfillstyle(i, getmaxcolor());
		while(cont<50){
			if(cont%2==0){
				setcolor(7);
				if(figura<4){
					formaFigura(figura);
					delay(500);
					figura++;
				}else{
					figura=0;
				}
			}else{
				setcolor(0);
				cleardevice();
				delay(1);
			}
			cont++;
		}

	}	
	closegraph();
}

void formaFigura(int opc){
	switch(opc){
		case 0:	//bar3d(300,250,500,450,(500-300)/4,1);
				rectangle(300,250,500,450);
				line(300,250,330,220);
				line(330,220,530,220);
				line(530,220,500,250);		
				line(530,220,530,420);
				line(500,450,530,420);
				break;

		case 1:	rectangle(300,250,500,450);
				line(300,250,330,220);
				line(500,250,470,220);
				line(330,220,470,220); 
				break;
		case 2:	rectangle(300,250,500,450);
				line(500,250,470,220);
				line(470,220,270,220);
				line(300,250,270,220);
				line(270,220,270,420);
				line(270,420,300,450); 
				break;

		case 3:	rectangle(300,250,500,450);
				line(300,250,330,220);
				line(500,250,470,220);
				line(330,220,470,220);
				break;
		default: break;
	}
	/*
	bar3d(left,top,right,bottom,(right-left)/4,1)

	figura 1
	bar3d(300,250,500,450,(500-300)/4,1);
	
	figura 2
	rectangle(300,250,500,450);
	line(300,250,330,220);
	line(500,250,470,220);
	line(330,220,470,220);

	figura 3
	rectangle(300,250,500,450);
	line(500,250,470,220);
	line(470,220,270,220);
	line(300,250,270,220);
	line(270,220,270,420);
	line(270,420,300,450);

	figura 4
	rectangle(300,250,500,450);
	line(300,250,330,220);
	line(500,250,470,220);
	line(330,220,470,220);
	*/
}

int numeroRandom(int minimo, int maximo){
    srand((unsigned)time(NULL)*clock()*getpid());
    return rand()%(maximo+1-minimo)+minimo;
}