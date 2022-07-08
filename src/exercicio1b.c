#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "timeControl.h"
#include "utils.h"

void moverParaFrente(int* arr, int index){
    int value = arr[index];
    for (int i = index; i > 0; i--) //iniciando no index que queremos, vai até 0 mudando cada elemento 1 posição para frente
        arr[i] = arr[i-1];

    arr[0] = value;
}

int buscaSequencialMoverFrente(int* arr, int n, int x){
    int i;
    for (i = 0; i < n; i++) //loop por cada elemento do array a ser buscado
        if (arr[i] == x){
            moverParaFrente(arr, i); //caso ache o elemento, passa a posição dele para o algoritmo de mover para frente
            return TRUE;
        }
    return FALSE;
}

int ex1b(int n_testes, int* entradas_original, int* consultas_original){
    for(int j = 0; j < n_testes; j++){ //faz o número de testes pedidos
        unsigned encontrados = 0;

        //duplica o array orginal para não altera-lo
        int* entradas = duplicarArray(entradas_original, INPUTSIZE);
        int* consultas = duplicarArray(consultas_original, INPUTSIZE);

        printf("Busca %d: \n", j);

        // realiza busca sequencia com realocação
        clock_t _ini = inicia_tempo();
        for (int i = 0; i < INPUTSIZE; i++) {
            // buscar o elemento consultas[i] na entrada
            int valor_busca = consultas[i];
            if(buscaSequencialMoverFrente(entradas, INPUTSIZE, valor_busca))
                encontrados++;
        }
        double tempo_busca = finaliza_tempo(_ini);

        printf("Tempo de busca: %fs | ", tempo_busca);
        printf("Itens encontrados: %d\n", encontrados);

        generateSimpleSearchTimeCSV("out/busca_linear_para_frente.csv", tempo_busca, encontrados);

        free(entradas);
        free(consultas);
    }

    return 0;
}
