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