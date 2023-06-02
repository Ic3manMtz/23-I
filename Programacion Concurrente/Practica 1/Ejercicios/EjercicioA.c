#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    printf("\n**** Ejercicio a *****\n");
    printf("\n\tC*x^n\n\n");

    pid_t pid;
    int valor_salida,c,x_base,x_resultado,n,i;
    //c*x^n    

    printf("¿Cuál es el valor de x?  ");
    scanf("%d",&x_base);
    x_resultado=x_base;
    printf("¿Cuál es el valor de n?  ");
    scanf("%d",&n);
    printf("¿Cuál es el valor de c?  ");
    scanf("%d",&c);
    printf("\n");

    for(i=0;i<n;i++){
        pid = fork();
        if(pid!=0){
            printf("\nProceso %d, padre %d\n",getpid(),getppid());
            printf("\tResultado del cálculo x^%d: %d\n",i+1,x_resultado);
            //printf("Soy %d, mi padre es %d y el resultado de mi calculo es=%d\n",getpid(),getppid(),x_resultado);
            wait(&valor_salida);
            exit(WEXITSTATUS(valor_salida));
        }
        if(i!=n-1){
            x_resultado*=x_base;
        }
    }
    
    printf("\nProceso %d, padre %d\n",getpid(),getppid());
    printf("\tResultado del cálculo c*x^n=%d\n",c*x_resultado);
    //printf("\nSoy %d, mi padre es %d y c*x^n=%d\n",getpid(),getppid(),c*x_resultado);
    return 0;
}