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
            
            // Critério: Prioridade (Maior para Menor)
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