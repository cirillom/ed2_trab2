#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "timeControl.h"
#include "utils.h"

int trocar(int* arr, int i1, int i2){
    if(i1 < 0 || i2<0) // os indices precisam ser maior que 0 para que não haja inversão do primeiro elemento com o elemento -1
        return FALSE;

    int temp = arr[i1];
    arr[i1] = arr[i2];
    arr[i2] = temp;
    return TRUE;
}

int buscaSequencialTransposicao(int* arr, int n, int x){
    int i;
    for (i = 0; i < n; i++)//loop por cada elemento do array a ser buscado
        if (arr[i] == x){
            trocar(arr, i, i-1); //caso ache o elemento inverte ele com o elemento da posição anterior
            return TRUE;
        }
    return FALSE;
}

int ex1c(int n_testes, int* entradas_original, int* consultas_original){
    for(int j = 0; j < n_testes; j++){ //faz o número de testes pedidos
        unsigned encontrados = 0;

        //duplica o array orginal para não altera-lo
        int* entradas = duplicarArray(entradas_original, INPUTSIZE);
        int* consultas = duplicarArray(consultas_original, INPUTSIZE);
        printf("Busca %d: \n", j);

        // realiza busca sequencial com realocação
        clock_t _ini = inicia_tempo();
        for (int i = 0; i < INPUTSIZE; i++) {
            // buscar o elemento consultas[i] na entrada
            int valor_busca = consultas[i];
            if(buscaSequencialTransposicao(entradas, INPUTSIZE, valor_busca))
                encontrados++;
        }
        double tempo_busca = finaliza_tempo(_ini);

        printf("Tempo de busca: %fs | ", tempo_busca);
        printf("Itens encontrados: %d\n", encontrados);

        generateSimpleSearchTimeCSV("out/busca_linear_transposicao.csv", tempo_busca, encontrados);

        free(entradas);
        free(consultas);
    }

    return 0;
}
