
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "lista_estatica.h"
#include "lista_dinamica.h"
#include "ordenacao_estatica.h"
#include "ordenacao_dinamica.h"

// GERAÇÃO DE GRÁFICOS
void salvar_dados_csv(const char *nome_arquivo, int n, int estrutura, int algoritmo, int tipo, double tempo_ms, long long int comparacoes) {
    FILE *file = fopen(nome_arquivo, "a");
    if (file == NULL) return;
    fseek(file, 0, SEEK_END);
    if (ftell(file) == 0) {
        fprintf(file, "N;Estrutura;Algoritmo;TipoDados;Tempo_ms;Comparacoes\n");
    }
    fprintf(file, "%d;%d;%d;%d;%.4f;%lld\n", n, estrutura, algoritmo, tipo, tempo_ms, comparacoes);
    fclose(file);
}

// GERAÇÃO DE DADOS
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
    // Pior caso: Gera prioridades menores primeiro (ex: 1, 1, 2...) 
    o.prioridade = 1 + ((id - 1) * 5 / n); 
    if(o.prioridade > 5) o.prioridade = 5;
    o.distancia = id * 0.1f;
    o.tempoEspera = n - id;
    return o;
}

Ocorrencia gerarOcorrenciaOrdenada(int id, int n) {
    Ocorrencia o;
    o.id = id;
    // Melhor caso: Gera prioridades maiores primeiro (5, 5, 4...)
    o.prioridade = 5 - ((id - 1) * 5 / n); 
    if(o.prioridade < 1) o.prioridade = 1;
    o.distancia = (n - id) * 0.1f;
    o.tempoEspera = id;
    return o;
}

int main() {
    srand(time(NULL));
    int n, tipo, estrutura, algoritmo;
    const int REPETICOES = 100; 

    printf("\nANALISE DE DESEMPENHO: ORDENACAO DE OCORRENCIAS\n");
    printf("Estrutura (1-Estatica, 2-Dinamica): ");
    scanf("%d", &estrutura);
    printf("Algoritmo (1-Bubble, 2-Insertion, 3-Selection, 4-Quick, 5-Merge): ");
    scanf("%d", &algoritmo);
    printf("Quantidade de dados (N): ");
    scanf("%d", &n);
    printf("Tipo (0-Aleatoria, 1-Inversa, 2-Ordenada): ");
    scanf("%d", &tipo);

    //TESTE 
    if (n <= 20) {
        long int comp_teste = 0;
        printf("\nVISUALIZACAO TESTE:");
        if (estrutura == 1) {
            ListaEstatica le;
            inicializar_estatica(&le);
            for(int i=0; i<n; i++) {
                Ocorrencia o = (tipo == 0) ? gerarOcorrencia(i+1) : (tipo == 1 ? gerarOcorrenciaInversa(i+1, n) : gerarOcorrenciaOrdenada(i+1, n));
                inserir_estatica(&le, o);
            }
            printf("\nLISTA ANTES:\n"); imprimir_estatica(&le);
            if (algoritmo == 1) bubbleSortEstatica(&le, &comp_teste);
            else if (algoritmo == 2) insertionSortEstatica(&le, &comp_teste);
            else if (algoritmo == 3) selectionSortEstatica(&le, &comp_teste);
            else if (algoritmo == 4) quickSortEstatica(&le, &comp_teste);
            else if (algoritmo == 5) mergeSortEstatica(&le, &comp_teste);
            printf("\nLISTA DEPOIS:\n"); imprimir_estatica(&le);
        } else {
            NoDinamico *ld = NULL;
            for(int i=0; i<n; i++) {
                Ocorrencia o = (tipo == 0) ? gerarOcorrencia(i+1) : (tipo == 1 ? gerarOcorrenciaInversa(i+1, n) : gerarOcorrenciaOrdenada(i+1, n));
                inserir_dinamica(&ld, o);
            }
            printf("\nLISTA ANTES:\n"); imprimir_dinamica(ld);
            if (algoritmo == 1) bubbleSortDinamica(ld, &comp_teste);
            else if (algoritmo == 2) insertionSortDinamica(&ld, &comp_teste);
            else if (algoritmo == 3) selectionSortDinamica(ld, &comp_teste);
            else if (algoritmo == 4) quickSortDinamica(&ld, &comp_teste);
            else if (algoritmo == 5) mergeSortDinamica(&ld, &comp_teste);
            printf("\nLISTA DEPOIS:\n"); imprimir_dinamica(ld);
            liberar_dinamica(ld);
        }
        printf("\nComparacoes no teste: %ld", comp_teste);
        printf("\nFIM DO MODO TESTE\n\n");
    }

    //TESTE DE PERFORMANCE
    double tempo_total = 0;
    long long int total_comparacoes = 0; 
    
    printf("Executando %d repeticoes para N=%d...\n", REPETICOES, n);

    for (int r = 0; r < REPETICOES; r++) {
        long int comp_rodada = 0;
        
        if (estrutura == 1) {
            ListaEstatica le;
            inicializar_estatica(&le);
            for(int i = 0; i < n; i++) {
                Ocorrencia o = (tipo == 0) ? gerarOcorrencia(i+1) : (tipo == 1 ? gerarOcorrenciaInversa(i+1, n) : gerarOcorrenciaOrdenada(i+1, n));
                inserir_estatica(&le, o);
            }

            clock_t start = clock();
            if (algoritmo == 1) bubbleSortEstatica(&le, &comp_rodada);
            else if (algoritmo == 2) insertionSortEstatica(&le, &comp_rodada);
            else if (algoritmo == 3) selectionSortEstatica(&le, &comp_rodada);
            else if (algoritmo == 4) quickSortEstatica(&le, &comp_rodada);
            else if (algoritmo == 5) mergeSortEstatica(&le, &comp_rodada);
            clock_t end = clock();

            tempo_total += ((double)(end - start)) / CLOCKS_PER_SEC;
            total_comparacoes += comp_rodada;

        } else {
            NoDinamico *ld = NULL;
            for(int i = 0; i < n; i++) {
                Ocorrencia o = (tipo == 0) ? gerarOcorrencia(i+1) : (tipo == 1 ? gerarOcorrenciaInversa(i+1, n) : gerarOcorrenciaOrdenada(i+1, n));
                inserir_dinamica(&ld, o);
            }

            clock_t start = clock();
            if (algoritmo == 1) bubbleSortDinamica(ld, &comp_rodada);
            else if (algoritmo == 2) insertionSortDinamica(&ld, &comp_rodada);
            else if (algoritmo == 3) selectionSortDinamica(ld, &comp_rodada);
            else if (algoritmo == 4) quickSortDinamica(&ld, &comp_rodada);
            else if (algoritmo == 5) mergeSortDinamica(&ld, &comp_rodada);
            clock_t end = clock();

            tempo_total += ((double)(end - start)) / CLOCKS_PER_SEC;
            total_comparacoes += comp_rodada;
            liberar_dinamica(ld);
        }
    }

    double media_ms = (tempo_total / REPETICOES) * 1000.0;
    long long int media_comp = total_comparacoes / REPETICOES;

    // Salva os resultados 
    salvar_dados_csv("resultados_ordenacao.csv", n, estrutura, algoritmo, tipo, media_ms, media_comp);

    printf("\n========================================");
    printf("\nRESULTADO FINAL PARA N = %d", n);
    printf("\nTempo Medio: %.4f ms", media_ms);
    printf("\nComparacoes Medias: %lld", media_comp);
    printf("\nDados exportados para 'resultados_ordenacao.csv'");
    printf("\n========================================\n");

    return 0;
}