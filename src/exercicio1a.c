#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "timeControl.h"

// Definição do tipo booleano
unsigned char typedef bool;
#define TRUE  1
#define FALSE 0

int* ler_inteiros(const char * arquivo, const int n){
    FILE* f = fopen(arquivo, "r");

    int * inteiros = (int *) malloc(sizeof(int) * n);

    for (int i = 0; !feof(f); i++)
        fscanf(f, "%d\n", &inteiros[i]);

    fclose(f);

    return inteiros;
}

int main(int argc, char const *argv[]){
    const int N = 50000;
    unsigned encontrados = 0;

    int* entradas = ler_inteiros("inteiros_entrada.txt", N);
    int* consultas = ler_inteiros("inteiros_busca.txt", N);

    // realiza busca sequencial
    clock_t _ini = inicia_tempo();
    for (int i = 0; i < N; i++) {
        // buscar o elemento consultas[i] na entrada
    }
    double tempo_busca = finaliza_tempo(_ini);

    printf("Tempo de busca    :\t%fs\n", tempo_busca);
    printf("Itens encontrados :\t%d\n", encontrados);

    return 0;
}
