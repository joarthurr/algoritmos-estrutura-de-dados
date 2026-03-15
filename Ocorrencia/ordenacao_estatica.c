#include "ordenacao_estatica.h"

void bubbleSortEstatica(ListaEstatica *l, long int *comp) {
    if (l->inicio == -1) return;

    int trocou;
    int atual;
    int fim = -1;

    do {
        trocou = 0;
        atual = l->inicio;

        while (l->nos[atual].prox != fim) {
            int proximo = l->nos[atual].prox;
            
            (*comp)++; 
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

void selectionSortEstatica(ListaEstatica *l, long int *comp) {
    if (l->inicio == -1) return;

    int i, j, maior;

    for (i = l->inicio; l->nos[i].prox != -1; i = l->nos[i].prox) {
        maior = i; 
        for (j = l->nos[i].prox; j != -1; j = l->nos[j].prox) {
            (*comp)++; 
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

void insertionSortEstatica(ListaEstatica *l, long int *comp) {
    if (l->inicio == -1 || l->nos[l->inicio].prox == -1) return;

    int lista_ordenada = l->inicio;
    int atual = l->nos[l->inicio].prox;
    
    l->nos[lista_ordenada].prox = -1;

    while (atual != -1) {
        int proximo_atual = l->nos[atual].prox;

        (*comp)++; 
        if (l->nos[atual].dados.prioridade > l->nos[lista_ordenada].dados.prioridade) {
            l->nos[atual].prox = lista_ordenada;
            lista_ordenada = atual;
        } else {
            int temp = lista_ordenada;
            while (l->nos[temp].prox != -1) {
                (*comp)++; 
                if (l->nos[l->nos[temp].prox].dados.prioridade >= l->nos[atual].dados.prioridade) {
                    temp = l->nos[temp].prox;
                } else {
                    break;
                }
            }
            
            l->nos[atual].prox = l->nos[temp].prox;
            l->nos[temp].prox = atual;
        }
        atual = proximo_atual;
    }
    l->inicio = lista_ordenada;
}

// Função auxiliar para intercalar com contador
int intercalarEstatica(ListaEstatica *l, int esq, int dir, long int *comp) {
    if (esq == -1) return dir;
    if (dir == -1) return esq;

    int resultado = -1;

    (*comp)++; 
    if (l->nos[esq].dados.prioridade >= l->nos[dir].dados.prioridade) {
        resultado = esq;
        l->nos[resultado].prox = intercalarEstatica(l, l->nos[esq].prox, dir, comp);
    } else {
        resultado = dir;
        l->nos[resultado].prox = intercalarEstatica(l, esq, l->nos[dir].prox, comp);
    }
    return resultado;
}

int mergeSortRecursivoEstatica(ListaEstatica *l, int inicio, long int *comp) {
    if (inicio == -1 || l->nos[inicio].prox == -1) return inicio;

    int slow = inicio;
    int fast = l->nos[inicio].prox;

    while (fast != -1 && l->nos[fast].prox != -1) {
        slow = l->nos[slow].prox;
        fast = l->nos[l->nos[fast].prox].prox;
    }

    int meio = l->nos[slow].prox;
    l->nos[slow].prox = -1;

    return intercalarEstatica(l, 
                             mergeSortRecursivoEstatica(l, inicio, comp), 
                             mergeSortRecursivoEstatica(l, meio, comp), 
                             comp);
}

void mergeSortEstatica(ListaEstatica *l, long int *comp) {
    l->inicio = mergeSortRecursivoEstatica(l, l->inicio, comp);
}

int partitionIndices(ListaEstatica *l, int indices[], int low, int high, long int *comp) {
    int pivot = indices[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        (*comp)++; 
        if (l->nos[indices[j]].dados.prioridade >= l->nos[pivot].dados.prioridade) {
            i++;
            int temp = indices[i];
            indices[i] = indices[j];
            indices[j] = temp;
        }
    }
    int temp = indices[i+1];
    indices[i+1] = indices[high];
    indices[high] = temp;
    return i+1;
}

void quickSortIndices(ListaEstatica *l, int indices[], int low, int high, long int *comp) {
    if (low < high) {
        int pi = partitionIndices(l, indices, low, high, comp);
        quickSortIndices(l, indices, low, pi-1, comp);
        quickSortIndices(l, indices, pi+1, high, comp);
    }
}

void quickSortEstatica(ListaEstatica *l, long int *comp) {
    if (l->inicio == -1) return;

    int indices[MAX_OCORRENCIAS];
    int count = 0;
    int curr = l->inicio;
    while (curr != -1) {
        indices[count++] = curr;
        curr = l->nos[curr].prox;
    }

    quickSortIndices(l, indices, 0, count-1, comp);

    for (int i = 0; i < count-1; i++) {
        l->nos[indices[i]].prox = indices[i+1];
    }
    l->nos[indices[count-1]].prox = -1;
    l->inicio = indices[0];
}