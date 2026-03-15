#include "ordenacao_dinamica.h"
#include <stddef.h>

void bubbleSortDinamica(NoDinamico *inicio) {
    if (inicio == NULL) return;

    int trocou;
    NoDinamico *atual;
    NoDinamico *fim = NULL;

    do {
        trocou = 0;
        atual = inicio;

        while (atual->prox != fim) {
            // Critério: Prioridade (Maior para Menor)
            if (atual->dados.prioridade < atual->prox->dados.prioridade) {
                Ocorrencia temp = atual->dados;
                atual->dados = atual->prox->dados;
                atual->prox->dados = temp;
                trocou = 1;
            }
            atual = atual->prox;
        }
        fim = atual;
    } while (trocou);
}
void selectionSortDinamica(NoDinamico *inicio) {
    if (inicio == NULL) return;

    NoDinamico *i, *j, *maior;

    for (i = inicio; i->prox != NULL; i = i->prox) {
        maior = i;

        for (j = i->prox; j != NULL; j = j->prox) {
            if (j->dados.prioridade > maior->dados.prioridade) {
                maior = j;
            }
        }

        if (maior != i) {
            Ocorrencia temp = i->dados;
            i->dados = maior->dados;
            maior->dados = temp;
        }
    }
}
#include "ordenacao_dinamica.h"
#include <stddef.h>

NoDinamico* intercalarDinamica(NoDinamico *esq, NoDinamico *dir) {
    if (esq == NULL) return dir;
    if (dir == NULL) return esq;

    NoDinamico *resultado = NULL;

    if (esq->dados.prioridade >= dir->dados.prioridade) {
        resultado = esq;
        resultado->prox = intercalarDinamica(esq->prox, dir);
    } else {
        resultado = dir;
        resultado->prox = intercalarDinamica(esq, dir->prox);
    }
    return resultado;
}

NoDinamico* mergeSortRecursivoDinamica(NoDinamico *inicio) {
    if (inicio == NULL || inicio->prox == NULL) return inicio;

    NoDinamico *slow = inicio;
    NoDinamico *fast = inicio->prox;

    while (fast != NULL && fast->prox != NULL) {
        slow = slow->prox;
        fast = fast->prox->prox;
    }

    NoDinamico *meio = slow->prox;
    slow->prox = NULL;

    return intercalarDinamica(mergeSortRecursivoDinamica(inicio), 
                             mergeSortRecursivoDinamica(meio));
}

void mergeSortDinamica(NoDinamico **inicio) {
    *inicio = mergeSortRecursivoDinamica(*inicio);
}