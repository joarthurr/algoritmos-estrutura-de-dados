#include "ordenacao_dinamica.h"
#include <stddef.h>

void bubbleSortDinamica(NoDinamico *inicio, long int *comp) {
    if (inicio == NULL) return;

    int trocou;
    NoDinamico *atual;
    NoDinamico *fim = NULL;

    do {
        trocou = 0;
        atual = inicio;

        while (atual->prox != fim) {
            (*comp)++;  
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

void selectionSortDinamica(NoDinamico *inicio, long int *comp) {
    if (inicio == NULL) return;

    NoDinamico *i, *j, *maior;

    for (i = inicio; i->prox != NULL; i = i->prox) {
        maior = i;
        for (j = i->prox; j != NULL; j = j->prox) {
            (*comp)++; // Métrica: Comparação de busca pelo maior 
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

void insertionSortDinamica(NoDinamico **inicio, long int *comp) {
    if (*inicio == NULL || (*inicio)->prox == NULL) return;

    NoDinamico *lista_ordenada = NULL;
    NoDinamico *atual = *inicio;

    while (atual != NULL) {
        NoDinamico *proximo_atual = atual->prox;

        (*comp)++; // Comparação para inserção no início ou lista vazia
        if (lista_ordenada == NULL || atual->dados.prioridade > lista_ordenada->dados.prioridade) {
            atual->prox = lista_ordenada;
            lista_ordenada = atual;
        } else {
            NoDinamico *temp = lista_ordenada;
            while (temp->prox != NULL) {
                (*comp)++; // Comparação do laço de busca da posição
                if (temp->prox->dados.prioridade >= atual->dados.prioridade) {
                    temp = temp->prox;
                } else {
                    break;
                }
            }
            atual->prox = temp->prox;
            temp->prox = atual;
        }
        atual = proximo_atual;
    }
    *inicio = lista_ordenada;
}

// Funções auxiliares para o Merge Sort com contador
NoDinamico* intercalarDinamica(NoDinamico *esq, NoDinamico *dir, long int *comp) {
    if (esq == NULL) return dir;
    if (dir == NULL) return esq;

    NoDinamico *resultado = NULL;

    (*comp)++; //Comparação durante a intercalação 
    if (esq->dados.prioridade >= dir->dados.prioridade) {
        resultado = esq;
        resultado->prox = intercalarDinamica(esq->prox, dir, comp);
    } else {
        resultado = dir;
        resultado->prox = intercalarDinamica(esq, dir->prox, comp);
    }
    return resultado;
}

NoDinamico* mergeSortRecursivoDinamica(NoDinamico *inicio, long int *comp) {
    if (inicio == NULL || inicio->prox == NULL) return inicio;

    NoDinamico *slow = inicio;
    NoDinamico *fast = inicio->prox;

    while (fast != NULL && fast->prox != NULL) {
        slow = slow->prox;
        fast = fast->prox->prox;
    }

    NoDinamico *meio = slow->prox;
    slow->prox = NULL;

    return intercalarDinamica(mergeSortRecursivoDinamica(inicio, comp), 
                             mergeSortRecursivoDinamica(meio, comp), 
                             comp);
}

void mergeSortDinamica(NoDinamico **inicio, long int *comp) {
    *inicio = mergeSortRecursivoDinamica(*inicio, comp);
}

NoDinamico* partitionDinamica(NoDinamico* head, NoDinamico** left, NoDinamico** right, long int *comp) {
    NoDinamico* pivot = head;
    *left = NULL;
    *right = NULL;
    NoDinamico* curr = head->prox;
    NoDinamico* next;
    while (curr != NULL) {
        next = curr->prox;
        (*comp)++; // Comparação de prioridade no Quick Sort
        if (curr->dados.prioridade >= pivot->dados.prioridade) {
            curr->prox = *left;
            *left = curr;
        } else {
            curr->prox = *right;
            *right = curr;
        }
        curr = next;
    }
    return pivot;
}

NoDinamico* quickSortRecursivoDinamica(NoDinamico* head, long int *comp) {
    if (head == NULL || head->prox == NULL) return head;

    NoDinamico* left = NULL;
    NoDinamico* right = NULL;
    NoDinamico* pivot = partitionDinamica(head, &left, &right, comp);

    left = quickSortRecursivoDinamica(left, comp);
    right = quickSortRecursivoDinamica(right, comp);

    NoDinamico* result = left;
    if (left == NULL) {
        result = pivot;
    } else {
        NoDinamico* temp = left;
        while (temp->prox != NULL) temp = temp->prox;
        temp->prox = pivot;
    }
    pivot->prox = right;
    return result;
}

void quickSortDinamica(NoDinamico **inicio, long int *comp) {
    *inicio = quickSortRecursivoDinamica(*inicio, comp);
}