#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <dirent.h>
#include <ctype.h>

#define MAX_DOCS 100

typedef struct Nodo
{
    int id_doc;        // indice del documento
    struct Nodo *next; // siguiente nodo
} Nodo;

typedef struct Grafo
{    /* Enlaces del grafo dirigido, entrada y salida para pagerank e indice invertido*/
    Nodo *lista_adyacencia_salida[MAX_DOCS];     
    Nodo *lista_adyacencia_entrada[MAX_DOCS];        
} Grafo;

/* Variables globales*/
extern MapeoDocumento mapeo_docs[MAX_DOCS];
extern int total_docs

void inicializar_grafo(Grafo *grafo);
void agregar_arista(Grafo *grafo, int origen, int destino);
void construir_grafo(Grafo *grafo);
void liberar_grafo(Grafo *grafo);
int contar_enlaces_salida(Grafo *grafo, int id_doc);
int contar_enlaces_entrada(Grafo *grafo, int id_doc);
int obtener_id_doc(char *nombre_archivo);
bool es_nombre_documento(char *nombre_archivo);
