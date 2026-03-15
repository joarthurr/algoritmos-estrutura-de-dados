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
// Função auxiliar para intercalar duas metades
int intercalarEstatica(ListaEstatica *l, int esq, int dir) {
    if (esq == -1) return dir;
    if (dir == -1) return esq;

    int resultado = -1;

    // Critério: Maior prioridade primeiro
    if (l->nos[esq].dados.prioridade >= l->nos[dir].dados.prioridade) {
        resultado = esq;
        l->nos[resultado].prox = intercalarEstatica(l, l->nos[esq].prox, dir);
    } else {
        resultado = dir;
        l->nos[resultado].prox = intercalarEstatica(l, esq, l->nos[dir].prox);
    }
    return resultado;
}

// Função recursiva do Merge Sort
int mergeSortRecursivoEstatica(ListaEstatica *l, int inicio) {
    if (inicio == -1 || l->nos[inicio].prox == -1) return inicio;

    // Achar o meio usando Slow e Fast pointers
    int slow = inicio;
    int fast = l->nos[inicio].prox;

    while (fast != -1 && l->nos[fast].prox != -1) {
        slow = l->nos[slow].prox;
        fast = l->nos[l->nos[fast].prox].prox;
    }

    int meio = l->nos[slow].prox;
    l->nos[slow].prox = -1; // Divide a lista em duas

    // Recursão
    int esq = mergeSortRecursivoEstatica(l, inicio);
    int dir = mergeSortRecursivoEstatica(l, meio);

    // Intercala
    return intercalarEstatica(l, esq, dir);
}

void mergeSortEstatica(ListaEstatica *l) {
    l->inicio = mergeSortRecursivoEstatica(l, l->inicio);
}