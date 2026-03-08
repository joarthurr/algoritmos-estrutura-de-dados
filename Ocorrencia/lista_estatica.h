#ifndef LISTA_ESTATICA_H
#define LISTA_ESTATICA_H

#include "ocorrencia.h"

#define MAX_OCORRENCIAS 10000

typedef struct NoEstatico {
    Ocorrencia dados;
    int prox; 
} NoEstatico;

typedef struct {
    NoEstatico nos[MAX_OCORRENCIAS];
    int inicio;
    int livre;
} ListaEstatica;

// Operacoes basicas
void inicializar_estatica(ListaEstatica *l);
int inserir_estatica(ListaEstatica *l, Ocorrencia o);
void imprimir_estatica(ListaEstatica *l);
int buscar_estatica(ListaEstatica *l, int id);
int remover_estatica(ListaEstatica *l, int id);
void liberar_estatica(ListaEstatica *l);

#endif