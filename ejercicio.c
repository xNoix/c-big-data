#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TABLE_SIZE 1000

// Definición de la estructura para un nodo de la tabla de hash
struct Node {
    char *key;
    int count;
    struct Node *next;
};

// Función de hash muy simple para este ejemplo
unsigned int hash(const char *key) {
    unsigned int hash = 0;
    while (*key) {
        hash += *key;
        key++;
    }
    return hash % TABLE_SIZE;
}

// Función para crear un nuevo nodo
struct Node *createNode(const char *key) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        perror("Error al crear un nuevo nodo");
        exit(EXIT_FAILURE);
    }
    newNode->key = strdup(key);
    newNode->count = 1;
    newNode->next = NULL;
    return newNode;
}

// Función para insertar una palabra en la tabla de hash o incrementar su conteo
void insertOrUpdate(struct Node *table[], const char *key) {
    unsigned int index = hash(key);
    struct Node *current = table[index];
    
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            current->count++;
            return;
        }
        current = current->next;
    }

    // Si la palabra no existe en la tabla, la insertamos
    struct Node *newNode = createNode(key);
    newNode->next = table[index];
    table[index] = newNode;
}

int main() {
    struct Node *table[TABLE_SIZE] = {NULL};
    char word[100];

    // Abre el archivo de texto
    FILE *archivo = fopen("texto.txt", "r");
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        return EXIT_FAILURE;
    }

    // Procesa el archivo palabra por palabra
    while (fscanf(archivo, "%s", word) != EOF) {
        // Elimina cualquier carácter no alfabético del final de la palabra
        int length = strlen(word);
        while (length > 0 && !isalpha(word[length - 1])) {
            word[length - 1] = '\0';
            length--;
        }
        
        // Convierte la palabra a minúsculas (para considerar palabras en mayúsculas y minúsculas iguales)
        for (int i = 0; i < length; i++) {
            word[i] = tolower(word[i]);
        }

        // Inserta o actualiza la palabra en la tabla de hash
        insertOrUpdate(table, word);
    }

    // Cierra el archivo
    fclose(archivo);

    // Imprime el conteo de palabras
    for (int i = 0; i < TABLE_SIZE; i++) {
        struct Node *current = table[i];
        while (current != NULL) {
            printf("%s: %d\n", current->key, current->count);
            current = current->next;
        }
    }

    // Liberar la memoria de la tabla de hash
    for (int i = 0; i < TABLE_SIZE; i++) {
        struct Node *current = table[i];
        while (current != NULL) {
            struct Node *temp = current;
            current = current->next;
            free(temp->key);
            free(temp);
        }
    }

    return 0;
}
