#ifndef ORDENACAO_DINAMICA_H
#define ORDENACAO_DINAMICA_H
#include "lista_dinamica.h"
#include "lista_estatica.h"

void bubbleSortDinamica(NoDinamico *inicio, long int *comp);
void selectionSortDinamica(NoDinamico *inicio, long int *comp);
void insertionSortDinamica(NoDinamico **inicio, long int *comp);
void quickSortDinamica(NoDinamico **inicio, long int *comp);
void mergeSortDinamica(NoDinamico **inicio, long int *comp);

#endif