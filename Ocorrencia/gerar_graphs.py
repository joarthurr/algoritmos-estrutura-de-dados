import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv('resultados_ordenacao.csv')

plt.style.use('seaborn-v0_8-darkgrid')
plt.figure(figsize=(10, 6))

nomes_algoritmos = {1: 'Bubble Sort', 2: 'Insertion Sort', 3: 'Selection Sort', 5: 'Merge Sort'}
nomes_tipos = {0: 'Aleatoria', 1: 'Inversa', 2: 'Ordenada'}

dados_estatica = df[df['Estrutura'] == 1]

for alg_id, nome_alg in nomes_algoritmos.items():
    for tipo_id, nome_tipo in nomes_tipos.items():
        
        dados_plot = dados_estatica[(dados_estatica['Algoritmo'] == alg_id) & (dados_estatica['TipoDados'] == tipo_id)]
        dados_plot = dados_plot.sort_values(by='N') 
        
        if not dados_plot.empty:
            plt.plot(dados_plot['N'], dados_plot['Tempo_ms'], marker='o', linewidth=2, label=f"{nome_alg} ({nome_tipo})")

plt.title('Performance de Ordenacao (Lista Estatica - Todos os Casos)', fontsize=16)
plt.xlabel('Quantidade de Ocorrencias (N)', fontsize=12)
plt.ylabel('Tempo Medio (ms)', fontsize=12)

plt.legend(fontsize=10, bbox_to_anchor=(1.05, 1), loc='upper left')
plt.grid(True)

plt.savefig('grafico_performance.png', dpi=300, bbox_inches='tight')
plt.show()