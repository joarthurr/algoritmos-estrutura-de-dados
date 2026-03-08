#include <stdio.h>
#include "lista_estatica.h"

void inicializar_estatica(ListaEstatica *l) {
    l->inicio = -1;
    l->livre = 0;

    for (int i = 0; i < MAX_OCORRENCIAS - 1; i++) {
        l->nos[i].prox = i + 1;
    }
    l->nos[MAX_OCORRENCIAS - 1].prox = -1; 
}

int inserir_estatica(ListaEstatica *l, Ocorrencia o) {
    if (l->livre == -1) {
        printf("Erro: Lista cheia!\n");
        return 0;
    }

    int novo = l->livre;
    l->livre = l->nos[novo].prox;

    l->nos[novo].dados = o;

    l->nos[novo].prox = l->inicio;
    l->inicio = novo;

    return 1;
}

void imprimir_estatica(ListaEstatica *l) {
    int atual = l->inicio;
    printf("\n--- Ocorrencias Ativas ---\n");
    while (atual != -1) {
        printf("ID: %d | Prioridade: %d | Distancia: %.2f | Tempo Espera: %d min\n",
               l->nos[atual].dados.id,
               l->nos[atual].dados.prioridade,
               l->nos[atual].dados.distancia,
               l->nos[atual].dados.tempoEspera);
        atual = l->nos[atual].prox;
    }
    printf("--------------------------\n");
}

int buscar_estatica(ListaEstatica *l, int id) {
    int atual = l->inicio;
    while (atual != -1) {
        if (l->nos[atual].dados.id == id) {
            return atual;
        }
        atual = l->nos[atual].prox;
    }
    return -1;
}

int remover_estatica(ListaEstatica *l, int id) {
    int atual = l->inicio;
    int anterior = -1;

    while (atual != -1 && l->nos[atual].dados.id != id) {
        anterior = atual;
        atual = l->nos[atual].prox;
    }

    if (atual == -1) return 0;

    if (anterior == -1) {
        l->inicio = l->nos[atual].prox;
    } else {
        l->nos[anterior].prox = l->nos[atual].prox;
    }

    l->nos[atual].prox = l->livre;
    l->livre = atual;

    return 1;
}

void liberar_estatica(ListaEstatica *l) {
    inicializar_estatica(l);
}