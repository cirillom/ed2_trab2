#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "timeControl.h"
#include "utils.h"

int buscaSequencial(int* arr, int n, int x){
    int i;
    for (i = 0; i < n; i++)
        if (arr[i] == x)
            return TRUE;
    return FALSE;
}

int ex1a(int n_testes, int* entradas_original, int* consultas_original){

    for(int j = 0; j < n_testes; j++){
        unsigned encontrados = 0;
        int* entradas = duplicarArray(entradas_original, INPUTSIZE);
        int* consultas = duplicarArray(consultas_original, INPUTSIZE);

        printf("Busca %d: \n", j);

        // realiza busca sequencial
        clock_t _ini = inicia_tempo();
        for (int i = 0; i < INPUTSIZE; i++) {
            // buscar o elemento consultas[i] na entrada

            int valor_busca = consultas[i];
            if(buscaSequencial(entradas, INPUTSIZE, valor_busca)){
                encontrados++;
            }
        }
        double tempo_busca = finaliza_tempo(_ini);

        printf("Tempo de busca: %fs | ", tempo_busca);
        printf("Itens encontrados: %d\n", encontrados);

        free(entradas);
        free(consultas);
    }
    return 0;
}
