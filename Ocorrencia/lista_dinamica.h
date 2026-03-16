#ifndef LISTA_DINAMICA_H
#define LISTA_DINAMICA_H

#include "ocorrencia.h"

typedef struct NoDinamico {
    Ocorrencia dados;
    struct NoDinamico *prox;
} NoDinamico;

// Operacoes basicas
void inserir_dinamica(NoDinamico **lista, Ocorrencia o);
void imprimir_dinamica(NoDinamico *lista);
NoDinamico* buscar_dinamico(NoDinamico *lista, int id);
void remover_dinamica(NoDinamico **lista, int id);
void liberar_dinamica(NoDinamico *lista);

#endif
