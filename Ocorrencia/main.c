#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "lista_estatica.h"
#include "lista_dinamica.h"
#include "ordenacao_estatica.h"
#include "ordenacao_dinamica.h"

//GERAÇÃO DE DADOS

Ocorrencia gerarOcorrencia(int id) {
    Ocorrencia o;
    o.id = id;
    o.prioridade = rand() % 5 + 1;
    o.distancia = (float)(rand() % 2000) / 100;
    o.tempoEspera = rand() % 120;
    return o;
}

Ocorrencia gerarOcorrenciaInversa(int id, int n) {
    Ocorrencia o;
    o.id = id;
    o.prioridade = 5 - ((id - 1) * 5 / n); // Prioridade decrescente no ID
    if(o.prioridade < 1) o.prioridade = 1;
    o.distancia = id * 0.1f;
    o.tempoEspera = n - id;
    return o;
}

Ocorrencia gerarOcorrenciaOrdenada(int id, int n) {
    Ocorrencia o;
    o.id = id;
    o.prioridade = 1 + ((id - 1) * 5 / n); // Prioridade crescente no ID
    if(o.prioridade > 5) o.prioridade = 5;
    o.distancia = (n - id) * 0.1f;
    o.tempoEspera = id;
    return o;
}

//MAIN

int main() {
    srand(time(NULL));
    int n, tipo, estrutura, algoritmo;
    const int REPETICOES = 100; 

    printf("Ordenação de prioridade das Ocorencias:\n");
    printf("Estrutura (1-Estatica, 2-Dinamica): ");
    scanf("%d", &estrutura);
    printf("Algoritmo (1-Bubble, 3-Selection): ");
    scanf("%d", &algoritmo);
    printf("Quantidade de dados (N): ");
    scanf("%d", &n);
    printf("Tipo (0-Aleatoria, 1-Inversa, 2-Ordenada): ");
    scanf("%d", &tipo);

    //TESTE VISUAL
    if (n <= 20) {
        printf("\nVisualização teste:");
        if (estrutura == 1) {
            ListaEstatica le;
            inicializar_estatica(&le);
            for(int i=0; i<n; i++) {
                Ocorrencia o = (tipo == 0) ? gerarOcorrencia(i+1) : (tipo == 1 ? gerarOcorrenciaInversa(i+1, n) : gerarOcorrenciaOrdenada(i+1, n));
                inserir_estatica(&le, o);
            }
            printf("\nLista antes:\n"); imprimir_estatica(&le);
            if (algoritmo == 1) bubbleSortEstatica(&le);
            else if (algoritmo == 3) selectionSortEstatica(&le);
            printf("\nLista depois:\n"); imprimir_estatica(&le);
        } else {
            NoDinamico *ld = NULL;
            for(int i=0; i<n; i++) {
                Ocorrencia o = (tipo == 0) ? gerarOcorrencia(i+1) : (tipo == 1 ? gerarOcorrenciaInversa(i+1, n) : gerarOcorrenciaOrdenada(i+1, n));
                inserir_dinamica(&ld, o);
            }
            printf("\nLISTA ANTES:"); imprimir_dinamica(ld);
            if (algoritmo == 1) bubbleSortDinamica(ld);
            else if (algoritmo == 3) selectionSortDinamica(ld);
            printf("\nLISTA DEPOIS (Ordenada por Prioridade):"); imprimir_dinamica(ld);
            liberar_dinamica(ld);
        }
        printf("\n--- FIM DO MODO TESTE ---\n\n");
    }

    //TESTE DE PERFORMANCE 
    double tempo_total = 0;
    printf("Calculando media de tempo para %d repeticoes...\n", REPETICOES);

    for (int r = 0; r < REPETICOES; r++) {
        if (estrutura == 1) {
            ListaEstatica le;
            inicializar_estatica(&le);
            for(int i = 0; i < n; i++) {
                Ocorrencia o = (tipo == 0) ? gerarOcorrencia(i+1) : (tipo == 1 ? gerarOcorrenciaInversa(i+1, n) : gerarOcorrenciaOrdenada(i+1, n));
                inserir_estatica(&le, o);
            }

            clock_t start = clock();
            if (algoritmo == 1) bubbleSortEstatica(&le);
            else if (algoritmo == 3) selectionSortEstatica(&le);
            clock_t end = clock();
            tempo_total += ((double)(end - start)) / CLOCKS_PER_SEC;

        } else {
            NoDinamico *ld = NULL;
            for(int i = 0; i < n; i++) {
                Ocorrencia o = (tipo == 0) ? gerarOcorrencia(i+1) : (tipo == 1 ? gerarOcorrenciaInversa(i+1, n) : gerarOcorrenciaOrdenada(i+1, n));
                inserir_dinamica(&ld, o);
            }

            clock_t start = clock();
            if (algoritmo == 1) bubbleSortDinamica(ld);
            else if (algoritmo == 3) selectionSortDinamica(ld);
            clock_t end = clock();
            tempo_total += ((double)(end - start)) / CLOCKS_PER_SEC;
            liberar_dinamica(ld);
        }
    }

    double media_ms = (tempo_total / REPETICOES) * 1000.0;
    printf("\n========================================");
    printf("\nRESULTADO FINAL PARA N = %d", n);
    printf("\nTempo Medio: %f ms", media_ms);
    printf("\n========================================\n");

    return 0;
}