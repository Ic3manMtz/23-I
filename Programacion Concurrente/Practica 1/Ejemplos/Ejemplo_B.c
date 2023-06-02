/*
** fork1.c -- demuestra el uso de fork() y wait()
** Objetivo : ?
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    int valor_salida, n = 3, i;

    printf("Soy el proceso original  %d\n", getpid());
    
    for( i = 0; i < n; i++) {
      pid = fork();
      if (pid != 0) {
        wait(&valor_salida);
    	  printf("Mi padre es %d, yo soy %d y mi hijo es %d y devolvio %d\n", getppid(), getpid(), pid,  WEXITSTATUS(valor_salida));
        exit(WEXITSTATUS(valor_salida)+1);
      }  
    }
   
    printf("Salí del for con i = %d. Mi padre es %d, yo soy %d y ya no cree hijos\n", i, getppid(), getpid());
    printf("¿Qué valor mandamos hacia arriba? "); 
    scanf("%d", &valor_salida);
    exit(valor_salida);
}