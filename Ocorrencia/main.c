#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "lista_estatica.h"
#include "lista_dinamica.h"
#include "ocorrencia.h"

/* ===== FUNÇÕES DE GERAÇÃO DE DADOS ===== */

// Aleatória
Ocorrencia gerarOcorrencia(int id) {
    Ocorrencia o;
    o.id = id;
    o.prioridade = rand() % 5 + 1;
    o.distancia = (float)(rand() % 2000) / 100; // 0.0 a 20.0
    o.tempoEspera = rand() % 120;
    return o;
}

// Inverson (pior caso) 
Ocorrencia gerarOcorrenciaInversa(int id, int n) {
    Ocorrencia o;
    o.id = id;
    o.prioridade = 5 - ((id - 1) * 5 / n); 
    if(o.prioridade < 1) o.prioridade = 1;
    o.distancia = id * 0.1f;
    o.tempoEspera = n - id;
    return o;
}

// Ordenada
Ocorrencia gerarOcorrenciaOrdenada(int id, int n) {
    Ocorrencia o;
    o.id = id;
    o.prioridade = 1 + ((id - 1) * 5 / n);
    if(o.prioridade > 5) o.prioridade = 5;
    o.distancia = (n - id) * 0.1f;
    o.tempoEspera = id;
    return o;
}

/* ===== MAIN ===== */

int main() {
    srand(time(NULL));

    int n, tipo, estrutura;
    
    printf("--- Simulador de Ocorrencias ---\n");
    printf("Escolha a estrutura:\n 1-Lista Estatica\n 2-Lista Dinamica\nOpcao: ");
    scanf("%d", &estrutura);

    printf("Digite a quantidade de dados: ");
    scanf("%d", &n);

    printf("Tipo de geracao:\n 0-Aleatoria\n 1-Inversa\n 2-Ordenada\nOpcao: ");
    scanf("%d", &tipo);

    if (estrutura == 1) {
        // --- TESTE ESTÁTICO ---
        ListaEstatica le;
        inicializar_estatica(&le);

        for (int i = 0; i < n; i++) {
            Ocorrencia o;
            int atualID = i + 1;

            if (tipo == 0) o = gerarOcorrencia(atualID);
            else if (tipo == 1) o = gerarOcorrenciaInversa(atualID, n);
            else o = gerarOcorrenciaOrdenada(atualID, n);

            inserir_estatica(&le, o);
        }
        printf("\n--- Lista Estatica Gerada ---\n");
        imprimir_estatica(&le);
        
        printf("\nRemovendo ID 5 (se existir)...\n");
        remover_estatica(&le, 5);
        imprimir_estatica(&le);

    } else {
        // --- TESTE DINÂMICO ---
        NoDinamico *ld = NULL;

        for (int i = 0; i < n; i++) {
            Ocorrencia o;
            int atualID = i + 1;

            if (tipo == 0) o = gerarOcorrencia(atualID);
            else if (tipo == 1) o = gerarOcorrenciaOrdenada(atualID, n);
            else o = gerarOcorrenciaInversa(atualID, n);
            
            inserir_dinamica(&ld, o);
        }
        printf("\n--- Lista Dinamica Gerada ---\n");
        imprimir_dinamica(ld);
        
        printf("\nRemovendo ID 5 (se existir)...\n");
        remover_dinamica(&ld, 5);
        imprimir_dinamica(ld);
        
        liberar_dinamica(ld);
    }

    return 0;
}