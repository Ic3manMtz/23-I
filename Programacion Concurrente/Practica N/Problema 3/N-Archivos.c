#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int countFilesInDirectory(const char* directory);
//void readFilesInDirectory(const char* directory);
void readFilesInDirectory(const char* directory, const char* filename);


int main() {
    char directory[256];
    int readingProccesses, i;
    pid_t pid;

    printf("\nDirectorios disponibles:\n");
    system("ls -d */");
    // Pide al usuario el directorio
    printf("\nIngrese el directorio a leer: ");
    scanf("%s", directory);

    DIR* dir = opendir(directory);
    if(dir == NULL){
        printf("No se pudo abrir el directorio '%s'\n", directory);
        return 1;
    }

    // Lee los archivos en el directorio
    //readingProccesses = countFilesInDirectory(directory);

    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        // Ignora los directorios "." y ".."
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Construye la ruta completa del archivo
        char file_path[256];
        snprintf(file_path, sizeof(file_path), "%s/%s", directory, entry->d_name);

        // Crea un nuevo proceso hijo
        pid_t pid = fork();

        if (pid == -1) {
            printf("Error al crear el proceso hijo\n");
            return 1;
        } else if (pid == 0) {
            // Proceso hijo
            printf("El proceso %d mi padre es %d leyó el ", getpid(),getppid());
            readFilesInDirectory(directory, entry->d_name);
            exit(0);
        }
    }

    // Espera a que todos los procesos hijos terminen
    while (wait(NULL) > 0);

    // Cierra el directorio
    closedir(dir);

    return 0;
}

int countFilesInDirectory(const char* directory) {
    DIR* dir;
    struct dirent* entry;
    int numberFiles = 0;

    // Abre el directorio
    dir = opendir(directory);
    if (dir == NULL) {
        printf("No se pudo abrir el directorio '%s'\n", directory);
        exit(0);
    }

    // Lee los archivos en el directorio
    while ((entry = readdir(dir)) != NULL) {
        // Ignora los directorios "." y ".."
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        numberFiles++;
    }

    // Cierra el directorio
    closedir(dir);

    printf("Hay %d en el directorio\n",numberFiles);
    return numberFiles;
}

void readFilesInDirectory(const char* directory, const char* filename) {
    // Construye la ruta completa del archivo
    char file_path[256];
    snprintf(file_path, sizeof(file_path), "%s/%s", directory, filename);

    // Procesa el archivo
    printf("Archivo: %s\n", file_path);

    // Aquí puedes realizar las operaciones que desees con cada archivo
    // Puedes leer su contenido, realizar análisis, etc.

    // Por ejemplo, abrir y leer el contenido del archivo
    FILE* file = fopen(file_path, "r");
    if (file != NULL) {
        char buffer[256];
        while (fgets(buffer, sizeof(buffer), file) != NULL) {
            printf("%s", buffer);
        }
        fclose(file);
    } else {
        printf("No se pudo abrir el archivo %s\n", file_path);
    }

    printf("\n");
}

/*
void readFilesInDirectory(const char* directory) {
    DIR* dir;
    struct dirent* entry;

    // Abre el directorio
    dir = opendir(directory);
    if (dir == NULL) {
        printf("No se pudo abrir el directorio '%s'\n", directory);
        return;
    }

    // Lee los archivos en el directorio
    while ((entry = readdir(dir)) != NULL) {
        // Ignora los directorios "." y ".."
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Construye la ruta completa del archivo
        char file_path[256];
        snprintf(file_path, sizeof(file_path), "%s/%s", directory, entry->d_name);

        // Procesa el archivo
        printf("Archivo: %s\n", file_path);

        // Aquí puedes realizar las operaciones que desees con cada archivo
        // Puedes leer su contenido, realizar análisis, etc.

        // Por ejemplo, abrir y leer el contenido del archivo
        FILE* file = fopen(file_path, "r");
        if (file != NULL) {
            char buffer[256];
            while (fgets(buffer, sizeof(buffer), file) != NULL) {
                printf("%s", buffer);
            }
            fclose(file);
        } else {
            printf("No se pudo abrir el archivo %s\n", file_path);
        }

        printf("\n");
    }

    // Cierra el directorio
    closedir(dir);
}
*/
