#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int menorDivisor(int);
int encuentraPrimos(int,int);

int main(){
    printf("\n**** Ejercicio b *****\n");
    printf("\n\t[1,M]\n\n");
    pid_t pid;
    int valor_salida, i, m,numeroHijos,sumaPrimos=0;

    printf("Ingrese el valor de M...");
    scanf("%d",&m);
    numeroHijos=menorDivisor(m);
    
    for( i = 0; i < numeroHijos; i++) {
        pid = fork();
        if (pid == 0) {
            sumaPrimos=encuentraPrimos((m/numeroHijos*i)+1,(m/numeroHijos)*(i+1));
            printf("\nProceso %d, padre %d.\n",getpid(),getppid());
            printf("\tEncontró %d primos en el rango [%d,%d]\n",sumaPrimos,(m/numeroHijos*i)+1,(m/numeroHijos)*(i+1)),
            exit(sumaPrimos);
        }
    }

    for( i = 0; i < numeroHijos; i++) {
        pid = wait(&valor_salida);
        sumaPrimos+=WEXITSTATUS(valor_salida);
    }
    printf("\nProceso %d, padre %d\n",getpid(),getppid());
    printf("\tLos primos que se encontraron entre [1,%d] es de %d\n", m,sumaPrimos);

    return 0;
}

int menorDivisor(int m){
    int i;
	for(i = 2; i <= m; i++) {
		if((m%i) == 0){
			return i;
		}
	}
}

int encuentraPrimos(int a, int b){
    int numeroPrimos=0,esPrimo, i,j;

    for(i=a;i<=b;i++){
        if(i==1 || i==0)
            continue;
        esPrimo = 1;
 
        for(j=2;j<= i/2;++j){
            if(i%j==0){
                esPrimo = 0;
                break;
            }
        }
 
        if (esPrimo == 1)
            numeroPrimos++;
    }
    return numeroPrimos;
}