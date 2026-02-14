#ifndef LISTA_H
#define LISTA_H

#include "ocorrencia.h"

typedef struct No {
    Ocorrencia dados;
    struct No *prox;
} No;

// Operações básicas
void inserir(No **lista, Ocorrencia o);
void imprimir(No *lista);
No* buscar(No *lista, int id);
void remover(No **lista, int id);
void liberar(No *lista);

#endif
