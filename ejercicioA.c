#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void countKmers(const char *sequence, int k, int *kmerCounts) {
    int seqLength = strlen(sequence);
    for (int i = 0; i <= seqLength - k; i++) {
        char kmer[MAX_]
    }
}

int main() {
    FILE *archivo;
    char *linea = NULL; // Puntero para almacenar cada línea
    char *contenido = NULL; // Puntero para almacenar el contenido completo
    size_t longitud = 0; // Inicializa la longitud del contenido
    int primeraLinea = 1; // Bandera para indicar si es la primera línea

    // Abre el archivo en modo lectura
    archivo = fopen("4mb.txt", "r");

    // Verifica si el archivo se abrió correctamente
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return 1;
    }

    // Lee el archivo línea por línea y almacena el contenido en 'contenido'
    while (getline(&linea, &longitud, archivo) != -1) {
        if (primeraLinea) {
            primeraLinea = 0; // Desactiva la bandera después de la primera línea
            continue; // Salta la primera línea
        }

        // Reasigna la memoria para acomodar el contenido
        contenido = (char *)realloc(contenido, longitud);

        // Concatena la línea leída al final del contenido
        strcat(contenido, linea);
    }

    // Cierra el archivo
    fclose(archivo);

    // Ahora 'contenido' contiene todo el contenido del archivo, excluyendo la primera línea
    // Puedes imprimirlo o trabajar con él según sea necesario
    printf("Contenido del archivo (a partir de la segunda línea):\n%s", contenido);

    // Libera la memoria utilizada
    free(linea);
    free(contenido);

    return 0;
}


