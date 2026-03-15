import pandas as pd
import matplotlib.pyplot as plt
import os

# 1. Configuração de Caminho e Leitura
# Isso garante que o Python ache o CSV se ele estiver na mesma pasta do script
diretorio_atual = os.path.dirname(__file__)
caminho_csv = os.path.join(diretorio_atual, 'resultados_ordenacao.csv')

try:
    # Lendo o CSV - O pandas vai usar automaticamente a primeira linha como cabeçalho
    df = pd.read_csv(caminho_csv, sep=';')
except FileNotFoundError:
    print(f"Erro: O arquivo '{caminho_csv}' não foi encontrado.")
    exit()

# 2. Configurações Estéticas
plt.style.use('seaborn-v0_8-darkgrid')
plt.figure(figsize=(10, 6))

# Dicionários para legendas
algoritmos = {1: 'Bubble', 2: 'Insertion', 3: 'Selection', 5: 'Merge'}

# --- FILTROS PARA O GRÁFICO ---
# Altere aqui para gerar gráficos diferentes para o seu artigo
estrutura_alvo = 2  # 2 = Dinâmica, 1 = Estática
tipo_alvo = 1       # 1 = Inverso (Pior Caso), 0 = Aleatório, 2 = Ordenado

# 3. Loop de Plotagem
tem_dados = False
for alg_id, nome in algoritmos.items():
    # Filtrando os dados conforme os alvos definidos
    dados = df[(df['Estrutura'] == estrutura_alvo) & 
               (df['Algoritmo'] == alg_id) & 
               (df['TipoDados'] == tipo_alvo)]
    
    # Ordena pelo volume N para a linha seguir a ordem correta
    dados = dados.sort_values('N')
    
    if not dados.empty:
        plt.plot(dados['N'], dados['Tempo_ms'], marker='o', label=nome, linewidth=2)
        tem_dados = True

# 4. Finalização do Gráfico
if tem_dados:
    tipos_nome = {0: 'Aleatório', 1: 'Inverso (Pior Caso)', 2: 'Ordenado'}
    est_nome = {1: 'Lista Estática', 2: 'Lista Dinâmica'}
    
    plt.title(f'Desempenho: {est_nome[estrutura_alvo]} - Cenário {tipos_nome[tipo_alvo]}')
    plt.xlabel('Quantidade de Elementos (N)')
    plt.ylabel('Tempo Médio (ms)')
    plt.legend()
    plt.grid(True)
    
    # Salva o gráfico para usar no Word/Artigo
    plt.savefig('grafico_pior_caso.png', dpi=300, bbox_inches='tight')
    print("Gráfico gerado com sucesso: 'grafico_pior_caso.png'")
    plt.show()
else:
    print(f"Nenhum dado encontrado para Estrutura {estrutura_alvo} e Tipo {tipo_alvo}.")