#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

void inserir(No **lista, Ocorrencia o) {
    No *novo = (No*) malloc(sizeof(No));
    if (novo == NULL) return;

    novo->dados = o;
    novo->prox = *lista;
    *lista = novo;
}

void imprimir(No *lista) {
    while (lista != NULL) {
        printf("ID: %d | Prioridade: %d\n",
               lista->dados.id,
               lista->dados.prioridade);
        lista = lista->prox;
    }
}

No* buscar(No *lista, int id) {
    while (lista != NULL) {
        if (lista->dados.id == id)
            return lista;
        lista = lista->prox;
    }
    return NULL;
}

void remover(No **lista, int id) {
    No *atual = *lista;
    No *anterior = NULL;

    while (atual != NULL && atual->dados.id != id) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) return;

    if (anterior == NULL) {
        *lista = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }

    free(atual);
}
void liberar(No *lista) {
    while (lista != NULL) {
        No *tmp = lista;
        lista = lista->prox;
        free(tmp);
    }
}
