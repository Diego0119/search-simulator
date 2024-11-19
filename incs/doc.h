/**
 * @file doc.h
 * @date 18-11-2024
 * @authors Miguel Loaiza, Diego Sanhueza, Miguel Maripillan y Felipe Cárcamo
 * @brief Prototipos de funciones para la creación de texto y archivos.
 *
 * Contiene los prototipos de las funciones dedicadas a la creación de texto (aleatorio) y archivos (webs).
 */
#ifndef GENERATOR_H
#define GENERATOR_H

#include <stdio.h>

/**
 * @brief Genera archivos txt simulando páginas web.
 * @param num_docs Número de documentos.
 * @param num_characters Número de caracteres dentro del archivo.
 */
void generate_text_files(int, int);

/**
 * @brief Genera texto aleatorio dentro de cada archivo web.
 * @param doc Archivo a escribir.
 * @param doc_name Nombre del archivo.
 * @param num_docs Número de documentos.
 * @param num_characters Número de caracteres.
 * @param current_doc Documento actual.
 * @param links Conexiones entre documentos.
 */
void generate_random_text(FILE *, const char *, int, int, int, int *);

#endif
