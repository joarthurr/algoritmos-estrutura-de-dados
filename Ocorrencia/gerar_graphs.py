import pandas as pd
import matplotlib.pyplot as plt
import os

diretorio_atual = os.path.dirname(__file__)
caminho_csv = os.path.join(diretorio_atual, 'resultados_ordenacao.csv')

try:
    df = pd.read_csv(caminho_csv, sep=';')
except FileNotFoundError:
    print(f"Erro: O arquivo '{caminho_csv}' não foi encontrado.")
    exit()

algoritmos = {1: 'Bubble', 2: 'Insertion', 3: 'Selection', 4: 'Quick', 5: 'Merge'}
tipos_nome = {0: 'Aleatório', 1: 'Inverso', 2: 'Ordenado'}
est_nome = {1: 'Estática', 2: 'Dinâmica'}

for est_id, est_label in est_nome.items():
    for tipo_id, tipo_label in tipos_nome.items():
        
        plt.figure(figsize=(10, 6))
        plt.style.use('seaborn-v0_8-darkgrid')
        tem_dados = False
        
        for alg_id, nome_alg in algoritmos.items():
            # Filtro dos dados
            dados = df[(df['Estrutura'] == est_id) & 
                       (df['Algoritmo'] == alg_id) & 
                       (df['TipoDados'] == tipo_id)]
            
            dados = dados.sort_values('Comparacoes')
            
            if not dados.empty:
                plt.plot(dados['Comparacoes'], dados['Tempo_ms'], marker='o', label=nome_alg, linewidth=2)
                tem_dados = True

        if tem_dados:
            plt.title(f'Correlação: Esforço vs Tempo ({est_label} - {tipo_label})')
            plt.xlabel('Número de Comparações (Esforço)')
            plt.ylabel('Tempo de Execução (ms)')
            plt.legend()
            plt.grid(True, linestyle='--', alpha=0.6)

            nome_arquivo = f'correlacao_{est_label}_{tipo_label}.png'.replace(" ", "_")
            plt.savefig(nome_arquivo, dpi=300, bbox_inches='tight')
            plt.close()
            print(f"✅ Gerado: {nome_arquivo}")
        else:
            plt.close()