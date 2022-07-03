#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "timeControl.h"
#include "utils.h"

typedef struct{
  int n;
  int index;
}numberTable;

void quicksort(int* vector,int c, int f){
    if (c>=f){
        return;
    }
    int m = (c+f)/2;
    int pivot = vector[m];
    int i = c;
    int j = f;
    while(1){
        while (vector[i]<pivot)
        {
            i++;
        }
        while(vector[j]>pivot){
            j--;
        }
        if(j <= i){
            break;
        }
        int tmp = vector[i];
        vector[i] = vector[j];
        vector[j] = tmp;
        i++;
        j--;
    }
    quicksort(vector,c,j);
    quicksort(vector,j+1,f);
}

numberTable* createTable(int countIndex,int* entradas,int wordsPerIndex){
    numberTable* table = malloc(sizeof(numberTable)*countIndex);

        for(int i = 0;i<countIndex;i++){
            table[i].index = i;
            table[i].n = entradas[i*wordsPerIndex];
        }
    return table;
}

int buscaSequencialIndice(int* entradas,int* consultas,numberTable* table,int wordsPerIndex,int i){
    int indexToBeSearched = -1;

            // buscar o elemento na tabela de indices
            for(int j = (INPUTSIZE/wordsPerIndex)-1;j >= 0;j--){
                if(consultas[i]>=table[j].n){
                    indexToBeSearched = table[j].index;
                    break;
                }
            }

            // buscar o elemento consultas[i] na entrada
            for(int j = indexToBeSearched*wordsPerIndex;j<=(indexToBeSearched+1)*wordsPerIndex-1;j++){
                if(entradas[j] == consultas[i]){
                    return 1;
                }
            }
            return 0;
}

int ex1d(int n_testes, int* entradas_original, int* consultas_original){
    remove("");
    for(int j = 0; j < n_testes; j++){
        unsigned encontrados = 0;

        int* entradas = duplicarArray(entradas_original, INPUTSIZE);
        int* consultas = duplicarArray(consultas_original, INPUTSIZE);
        printf("Busca %d: \n", j);

        // ordenar entrada
        quicksort(entradas,0,INPUTSIZE-1);

        int wordsPerIndex = 10000;
        // criar tabela de indice
        int countIndex = INPUTSIZE/wordsPerIndex;
        numberTable* table = createTable(countIndex,entradas,wordsPerIndex);

        //realiza a busca sequencial com indice
        clock_t _ini = inicia_tempo();
        for (int i = 0; i < INPUTSIZE; i++) {
            if(buscaSequencialIndice(entradas,consultas,table,wordsPerIndex,i)){
                encontrados++;
            }
        }

        double tempo_busca = finaliza_tempo(_ini);

        printf("Tempo de busca: %fs | ", tempo_busca);
        printf("Itens encontrados: %d\n", encontrados);

        generateSimpleSearchTimeCSV("out/busca_linear_indexada.csv", tempo_busca, encontrados);

        free(entradas);
        free(consultas);
        free(table);
    }
    return 0;
}