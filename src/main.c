#include <stdio.h>

#include "exercicio.h"
#include "utils.h"

int main(int argc, char const *argv[]){
    const int N = 50000;
    int* entradas_original = ler_inteiros("res/inteiros_entrada.txt", N);
    int* consultas_original = ler_inteiros("res/inteiros_busca.txt", N);

    printf("**Busca sequencial simples** \n");
    ex1a(3, entradas_original, consultas_original);
    printf("\n\n\n");

    printf("**Busca mover-para-frente** \n");
    ex1b(3, entradas_original, consultas_original);
    printf("\n\n\n");

    printf("**Busca por transposição** \n");
    ex1c(3, entradas_original, consultas_original);
    printf("\n\n\n");
    
    printf("**Busca sequencial por indice** \n");
    ex1d(1, entradas_original, consultas_original);
    printf("\n\n\n");

    free(entradas_original);
    free(consultas_original);
}