
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


df_types = [
    'Progressive Overflow',
    'Duplo',
    'Aberto'
]

df_names = [
    'Divisão',
    'Multiplicação',
    'Primo'
]

def dataframeCleaner(df, name):
    df.sort_values(df.keys()[0], inplace=True) #sort the values
    df.drop(index=df.index[0], axis=0, inplace=True) #remove the smallest value (high chance of being outlier)
    df.drop(index=df.index[len(df.index) - 1], axis=0, inplace=True) #remove the biggest value (high chance of being outlier)
    df.reset_index(drop=True, inplace=True)
    print(name)
    print(df)

#for df, name in zip(dfs_busca, df_names):
    #dataframeCleaner(df, name) #clean the dataframe

def med_dsvp(dfs, key):
    medias_busca = np.array([])
    dsvp_busca = np.array([])
    for df in dfs:
        media = df[key].mean()
        medias_busca = np.append(medias_busca, media)

        desv_pad = df[key].std()
        dsvp_busca = np.append(dsvp_busca, desv_pad)

    return medias_busca, dsvp_busca

medias_busca_div, dsvp_busca_div = med_dsvp(dfs_busca_div, 'TempoBusca')
medias_busca_mul, dsvp_busca_mul = med_dsvp(dfs_busca_mul, 'TempoBusca')
medias_busca_pri, dsvp_busca_pri = med_dsvp(dfs_busca_pri, 'TempoBusca')

x = np.arange(len(df_types))
width = 0.3
fig, ax = plt.subplots()
rects1 = ax.errorbar(x - width/2, medias_busca_div, dsvp_busca_div, fmt = 'o', capsize=3, label='Divisão')
rects2 = ax.errorbar(x, medias_busca_mul, dsvp_busca_mul, fmt = 'o', capsize=3, label='Multiplicação')
rects3 = ax.errorbar(x + width/2, medias_busca_pri, dsvp_busca_pri, fmt = 'o', capsize=3, label='Primo')

print(rects1)
print(rects2)
print(rects3)

# Add some text for labels, title and custom x-axis tick labels, etc.
ax.set_ylabel('Tempo(s)')
ax.set_title('Tempo de busca hash')
ax.set_xticks(x);ax.set_xticklabels(df_types, minor=False)
ax.set_yticks(np.arange(0.000, 0.250, 0.010))
plt.grid(which='major', axis='y')
ax.legend()

ax.set_xlabel(rects1)
ax.set_xlabel(rects2)
ax.set_xlabel(rects3)

fig.tight_layout()

plt.show()

combined_df_names = []
for type in df_types:
    for name in df_names:
        combined_df_names.append(type + " " + name)

""" busca_media_dsvp_df = pd.DataFrame([medias_busca, dsvp_busca], index=['Média', 'Desvio'], columns=combined_df_names)
busca_media_dsvp_df = busca_media_dsvp_df.round(decimals=4)
print(busca_media_dsvp_df)
#busca_media_dsvp_df.to_csv(('out/busca_hash_media_dsvp.csv')) """


""" plt.errorbar(combined_df_names, medias_busca, dsvp_busca, linestyle='None', marker='o', capsize=3)
plt.title('Busca por Espalhamento')
plt.ylabel('Tempo (s)')
plt.xlabel('Busca Espalhada')
plt.yticks(np.arange(0.005, 0.25, 0.02))
plt.set_xticks(np.arange(len(df_types)), df_types)
plt.grid(which='major', axis='y')

plt.show() """
#plt.savefig('out/busca_hash_media_e_desv_pad.png')

#fdf = pd.DataFrame(np.array([means, stds]).T)
"""media_e_desv_pad_df = pd.DataFrame([means, stds], index=['Média', 'Desvio'], columns=df_names)
media_e_desv_pad_df = media_e_desv_pad_df.round(decimals=4)
print(media_e_desv_pad_df)
media_e_desv_pad_df.to_csv('out/media_e_desv_pad.csv')

all_values_df = pd.DataFrame()

for df, name in zip(dfs, df_names):
    all_values_df[name] = df['Tempo']
all_values_df = all_values_df.round(decimals=4)
print(all_values_df)
all_values_df.to_csv('out/busca_linear_completa.csv', index=False) """