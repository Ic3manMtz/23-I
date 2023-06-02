/*
** Origen : http://www.ecst.csuchico.edu/~beej/guide/ipc/fork1.c
** Modificado por : Elizabeth Pérez Cortés
** Objetivo : Demuestra el uso de fork() y wait(). Además, muestra la comunicación entre los procesos padre e hijo a través de la copia del espacio
**            de memoria y la independencia del mismo. También ilustra el envío de un valor de regreso al final de la ejecución de un proceso.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid, hpid;
    int valor_salida, n = 0, i;
    
    switch(pid=fork())
    {
        case -1:
            perror("fork");  /* algo malo pasó no se creo el hijo */
            exit(1);         /* el padre termina */

        case 0:
            printf(" hijo : Yo soy el proceso hijo\n");
            printf(" hijo : Mi numero de proceso es %d\n", getpid());
            printf(" hijo : Mi padre es %d\n", getppid());
            printf(" hijo : Hare mi tarea\n");
            printf(" hijo : ¿cuántas iteraciones quieres que haga? "); 
            scanf("%d", &n);
            
            for (i = 0; i < n; i++) 
                printf("%d\n", i);
                
            printf(" hijo : Dame mi valor de salida en [0,255]");
            scanf(" %d", &valor_salida);
            printf(" hijo : ciao\n");
            exit(valor_salida);

        default:
            printf("Padre : Yo soy el padre\n");
            n = 20;
            printf("Padre : Cambie n = %d\n", n);
            printf("Padre : Mi PID is %d\n", getpid());
            printf("Padre : Mi hijo es %d\n", pid);
            printf("Padre : Ahora espero que mi hijo termine\n");
            hpid = wait(&valor_salida);
            printf("Padre : Ahora mi hijo %d terminó con el valor : %d y el wait devuelve %d\n", pid, WEXITSTATUS(valor_salida), hpid);
            printf("Padre : bye bye !\n");
    }
}
