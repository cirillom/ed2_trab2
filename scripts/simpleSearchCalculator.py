
#TODO calcular média
#TODO calculad desvio padrão

import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

from scipy import stats
from matplotlib import style

dfs = [
    pd.read_csv (r'./out/busca_linear_simples.csv'),
    pd.read_csv (r'./out/busca_linear_para_frente.csv'),
    pd.read_csv (r'./out/busca_linear_transposicao.csv'),
    pd.read_csv (r'./out/busca_linear_indexada.csv')]

df_names = [
    'Simples',
    'Mover Para Frente',
    'Transposição',
    'Indexada'
]

def dataframeCleaner(df, name):
    df.sort_values('Tempo', inplace=True) #sort the values
    df.drop(index=df.index[0], axis=0, inplace=True) #remove the smallest value (high chance of being outlier)
    df.drop(index=df.index[len(df.index) - 1], axis=0, inplace=True) #remove the biggest value (high chance of being outlier)
    df.reset_index(drop=True, inplace=True)
    #print(name)
    #print(df)

for df, name in zip(dfs, df_names):
    dataframeCleaner(df, name) #clean the dataframe

means = np.array([])
stds = np.array([])

for df in dfs:
    media = df['Tempo'].mean()
    means = np.append(means, media)

    desv_pad = df['Tempo'].std()
    stds = np.append(stds, desv_pad)

plt.errorbar(df_names, means, stds, linestyle='None', marker='o', capsize=3)
plt.ylabel('Tempo (s)')
plt.xlabel('Busca Linear')
plt.yticks(np.arange(0.05, 0.65, 0.02))
plt.grid(which='major', axis='y')

#plt.show()
plt.savefig('out/media_e_desv_pad.png')

#fdf = pd.DataFrame(np.array([means, stds]).T)
media_e_desv_pad_df = pd.DataFrame([means, stds], index=['Média', 'Desvio'], columns=df_names)
media_e_desv_pad_df = media_e_desv_pad_df.round(decimals=4)
print(media_e_desv_pad_df)
media_e_desv_pad_df.to_csv('out/media_e_desv_pad.csv')

all_values_df = pd.DataFrame()

for df, name in zip(dfs, df_names):
    all_values_df[name] = df['Tempo']
all_values_df = all_values_df.round(decimals=4)
print(all_values_df)
all_values_df.to_csv('out/busca_linear_completa.csv', index=False)