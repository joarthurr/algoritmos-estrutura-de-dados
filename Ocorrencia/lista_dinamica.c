#include <stdio.h>
#include <stdlib.h>
#include "lista_dinamica.h"

void inicializar_dinamica(NoDinamico **lista) {
    *lista = NULL;
}

void inserir_dinamica(NoDinamico **lista, Ocorrencia o) {
    NoDinamico *novo = (NoDinamico*) malloc(sizeof(NoDinamico));
    if (novo == NULL) return;

    novo->dados = o;
    novo->prox = *lista;
    *lista = novo;
}

void imprimir_dinamica(NoDinamico *lista) {
    while (lista != NULL) {
        printf("ID: %d | Prioridade: %d | Distancia: %.2f | Tempo Espera: %d min\n",
               lista->dados.id,
               lista->dados.prioridade,
               lista->dados.distancia,
               lista->dados.tempoEspera);
        lista = lista->prox;
    }
}

NoDinamico* buscar_dinamico(NoDinamico *lista, int id) {
    while (lista != NULL) {
        if (lista->dados.id == id)
            return lista;
        lista = lista->prox;
    }
    return NULL;
}

void remover_dinamica(NoDinamico **lista, int id) {
    NoDinamico *atual = *lista;
    NoDinamico *anterior = NULL;

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
void liberar_dinamica(NoDinamico *lista) {
    while (lista != NULL) {
        NoDinamico *tmp = lista;
        lista = lista->prox;
        free(tmp);
    }
}
