
#TODO 2 GRÁFICOS (INSERCAO/BUSCA)

import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

from scipy import stats
from matplotlib import style

dfs_busca_div = [
    pd.read_csv(r'./out/busca_hash_aberto_divisao.csv', usecols=[3]),
    pd.read_csv(r'./out/busca_hash_aberto_divisao.csv', usecols=[3]),
    pd.read_csv(r'./out/busca_hash_aberto_divisao.csv', usecols=[3])]

dfs_busca_mul = [
    pd.read_csv(r'./out/busca_hash_aberto_multiplicacao.csv', usecols=[3]),
    pd.read_csv(r'./out/busca_hash_aberto_multiplicacao.csv', usecols=[3]),
    pd.read_csv(r'./out/busca_hash_aberto_multiplicacao.csv', usecols=[3])]

dfs_busca_pri = [
    pd.read_csv(r'./out/busca_hash_aberto_primos.csv', usecols=[3]),
    pd.read_csv(r'./out/busca_hash_aberto_primos.csv', usecols=[3]),
    pd.read_csv(r'./out/busca_hash_aberto_primos.csv', usecols=[3])]

dfs_insercao_div = [
    pd.read_csv(r'./out/busca_hash_aberto_divisao.csv', usecols=[2]),
    pd.read_csv(r'./out/busca_hash_aberto_divisao.csv', usecols=[2]),
    pd.read_csv(r'./out/busca_hash_aberto_divisao.csv', usecols=[2])]

dfs_insercao_mul = [
    pd.read_csv(r'./out/busca_hash_aberto_multiplicacao.csv', usecols=[2]),
    pd.read_csv(r'./out/busca_hash_aberto_multiplicacao.csv', usecols=[2]),
    pd.read_csv(r'./out/busca_hash_aberto_multiplicacao.csv', usecols=[2])]

dfs_insercao_pri = [
    pd.read_csv(r'./out/busca_hash_aberto_primos.csv', usecols=[2]),
    pd.read_csv(r'./out/busca_hash_aberto_primos.csv', usecols=[2]),
    pd.read_csv(r'./out/busca_hash_aberto_primos.csv', usecols=[2])]

dfs_busca = [dfs_busca_div, dfs_busca_mul, dfs_busca_pri]
dfs_insercao = [dfs_busca_div, dfs_insercao_mul, dfs_insercao_pri]

df_types = [
    'Progressive Overflow',
    'Duplo',
    'Aberto']

df_names = [
    'Divisão',
    'Multiplicação',
    'Primo']

def dataframeCleaner(df, name):
    df.sort_values(df.keys()[0], inplace=True) #sort the values
    df.drop(index=df.index[0], axis=0, inplace=True) #remove the smallest value (high chance of being outlier)
    df.drop(index=df.index[len(df.index) - 1], axis=0, inplace=True) #remove the biggest value (high chance of being outlier)
    df.reset_index(drop=True, inplace=True)
    #print(name)
    #print(df)

for dfs in dfs_busca:
    for df, name in zip(dfs, df_names):
        dataframeCleaner(df, name)

for dfs in dfs_insercao:
    for df, name in zip(dfs, df_names):
        dataframeCleaner(df, name)


def med_dsvp(dfs, key):
    medias = np.array([])
    dsvp = np.array([])
    for df in dfs:
        media = df.mean()
        medias = np.append(medias, media)

        desv_pad = df.std()
        dsvp = np.append(dsvp, desv_pad)

    return medias, dsvp

busca_data_points = [[0, 0], [0, 0], [0, 0]]
insercao_data_points = [[0, 0], [0, 0], [0, 0]]

for i in range(len(dfs_busca)):
    busca_data_points[i][0], busca_data_points[i][1] = med_dsvp(dfs_busca[i], 'TempoBusca')

for i in range(len(dfs_insercao)):
    insercao_data_points[i][0], insercao_data_points[i][1] = med_dsvp(dfs_insercao[i], 'TempoInsercao')


x = np.arange(len(df_types))
width = 0.3
fig1, ax1 = plt.subplots()
fig2, ax2 = plt.subplots()

j = -width/2
for data, name in zip(busca_data_points, df_names):
    ax1.errorbar(x - j, data[0], data[1], fmt = 'o', capsize=3, label=name)
    j += width/2

j = -width/2
for data, name in zip(insercao_data_points, df_names):
    ax2.errorbar(x - j, data[0], data[1], fmt = 'o', capsize=3, label=name)
    j += width/2

# Add some text for labels, title and custom x-axis tick labels, etc.
ax1.set_ylabel('Tempo(s)')
ax1.set_title('Tempo de busca hash')
ax1.set_xticks(x);ax1.set_xticklabels(df_types, minor=False)
ax1.set_yticks(np.arange(0.000, 0.250, 0.010))
ax1.legend()
fig1.tight_layout()
ax1.grid(which='major', axis='y')

ax2.set_ylabel('Tempo(s)')
ax2.set_title('Tempo de inserção hash')
ax2.set_xticks(x);ax2.set_xticklabels(df_types, minor=False)
ax2.set_yticks(np.arange(0.000, 0.09, 0.005))
ax2.legend()
fig2.tight_layout()
ax2.grid(which='major', axis='y')

plt.show()

combined_df_names = []
for type in df_types:
    for name in df_names:
        combined_df_names.append(type + " " + name)

""" busca_media_dsvp_df = pd.DataFrame([medias_busca, dsvp_busca], index=['Média', 'Desvio'], columns=combined_df_names)
busca_media_dsvp_df = busca_media_dsvp_df.round(decimals=4)
print(busca_media_dsvp_df)
#busca_media_dsvp_df.to_csv(('out/busca_hash_media_dsvp.csv')) """


""" all_values_df = pd.DataFrame()

for df, name in zip(dfs, df_names):
    all_values_df[name] = df['Tempo']
all_values_df = all_values_df.round(decimals=4)
print(all_values_df)
all_values_df.to_csv('out/busca_linear_completa.csv', index=False) """