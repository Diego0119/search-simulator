#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <dirent.h>
#include <ctype.h>

#define MAX_DOCS 100
#define MAX_TAMANO_PALABRA 50
#define MAX_NAME_WEB 20
#define MAX_CHARACTERS_WEB 50

typedef struct Nodo
{
    int id_doc;        // indice del documento
    struct Nodo *next; // siguiente nodo
} Nodo;

typedef struct Grafo
{ /* Enlaces del grafo dirigido, entrada y salida para pagerank e indice invertido*/

    Nodo *lista_adyacencia_salida[MAX_DOCS];
    Nodo *lista_adyacencia_entrada[MAX_DOCS];
} Grafo;

typedef struct IndiceInvertido
{
    char palabra[MAX_TAMANO_PALABRA];
    Nodo *lista_docs;
    struct IndiceInvertido *siguiente;
} IndiceInvertido;

void agregar_documento(Grafo *grafo, int id_doc);
void agregar_enlace(Grafo *grafo, int id_doc_origen, int id_doc_destino);
void mostrar_grafo(Grafo *grafo);
/* Variables globales*/

extern MapeoDocumento mapeo_docs[MAX_DOCS];
extern int total_docs;

void inicializar_grafo(Grafo *grafo);
void agregar_arista(Grafo *grafo, int origen, int destino);
void construir_grafo(Grafo *grafo);
void liberar_grafo(Grafo *grafo);
int contar_enlaces_salida(Grafo *grafo, int id_doc);
int contar_enlaces_entrada(Grafo *grafo, int id_doc);
int obtener_id_doc(char *nombre_archivo);
bool es_nombre_documento(char *nombre_archivo);

/* Generar archivos txt */
void generate_text_files(int *);                 // GENERA archivos txt (webs) y les coloca nombre.
void generate_random_text(FILE *, const char *); // GENERA texto aleatorio en los archivos txt.