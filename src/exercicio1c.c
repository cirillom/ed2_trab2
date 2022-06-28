#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "timeControl.h"
#include "utils.h"

int buscaSequencialTransposicao(int* arr, int n, int x){
    int i;
    for (i = 0; i < n; i++)
        if (arr[i] == x){
            trocar(arr, i, i-1);
            return TRUE;
        }
    return FALSE;
}

int ex1c(int n_testes){
    const int N = 50000;
    unsigned encontrados = 0;

    int* entradas = ler_inteiros("res/inteiros_entrada.txt", N);
    int* consultas = ler_inteiros("res/inteiros_busca.txt", N);


    for(int j = 0; j < n_testes; j++){
        printf("Busca %d: \n", j);

        // realiza busca sequencial com realocação
        clock_t _ini = inicia_tempo();
        for (int i = 0; i < N; i++) {
            // buscar o elemento consultas[i] na entrada
            int valor_busca = consultas[i];
            if(buscaSequencialTransposicao(entradas, N, valor_busca))
                encontrados++;
        }
        double tempo_busca = finaliza_tempo(_ini);

        printf("Tempo de busca: %fs | ", tempo_busca);
        printf("Itens encontrados: %d\n", encontrados);
        encontrados = 0;
    }

    return 0;
}
