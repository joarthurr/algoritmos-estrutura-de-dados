#include "ordenacao_estatica.h"

void bubbleSortEstatica(ListaEstatica *l) {
    if (l->inicio == -1) return;

    int trocou;
    int atual;
    int fim = -1;

    do {
        trocou = 0;
        atual = l->inicio;

        while (l->nos[atual].prox != fim) {
            int proximo = l->nos[atual].prox;
            
            if (l->nos[atual].dados.prioridade < l->nos[proximo].dados.prioridade) {
                Ocorrencia temp = l->nos[atual].dados;
                l->nos[atual].dados = l->nos[proximo].dados;
                l->nos[proximo].dados = temp;
                trocou = 1;
            }
            atual = l->nos[atual].prox;
        }
        fim = atual;
    } while (trocou);
}
void selectionSortEstatica(ListaEstatica *l) {
    if (l->inicio == -1) return;

    int i, j, maior;

    for (i = l->inicio; l->nos[i].prox != -1; i = l->nos[i].prox) {
        maior = i; 
        for (j = l->nos[i].prox; j != -1; j = l->nos[j].prox) {
            if (l->nos[j].dados.prioridade > l->nos[maior].dados.prioridade) {
                maior = j;
            }
        }

        if (maior != i) {
            Ocorrencia temp = l->nos[i].dados;
            l->nos[i].dados = l->nos[maior].dados;
            l->nos[maior].dados = temp;
        }
    }
}