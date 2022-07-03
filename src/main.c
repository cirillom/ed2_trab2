#include <stdio.h>
#include <stdlib.h>

#include "exercicio.h"
#include "utils.h"

int main(){
    const int N = 50000;
    int* entradas_numericas_original = ler_inteiros("res/inteiros_entrada.txt", N);
    int* consultas_numericas_original = ler_inteiros("res/inteiros_busca.txt", N);

    printf("**Busca sequencial simples** \n");
    ex1a(52, entradas_numericas_original, consultas_numericas_original);
    printf("\n\n\n");

    printf("**Busca mover-para-frente** \n");
    ex1b(52, entradas_numericas_original, consultas_numericas_original);
    printf("\n\n\n");

    printf("**Busca por transposição** \n");
    ex1c(52, entradas_numericas_original, consultas_numericas_original);
    printf("\n\n\n");
    
    printf("**Busca sequencial por indice** \n");
    ex1d(52, entradas_numericas_original, consultas_numericas_original);
    printf("\n\n\n");

    free(entradas_numericas_original);
    free(consultas_numericas_original);

    string* insercoes_string_original = ler_strings("res/strings_entrada.txt", INPUTSIZE);
    string* consultas_string_original = ler_strings("res/strings_busca.txt", CONSULTASIZE);

    printf("**Busca hashing aberto** \n");
    ex2c(52, insercoes_string_original, consultas_string_original);

    for(int i = 0; i < INPUTSIZE; i++)
        free(insercoes_string_original[i]);
    free(insercoes_string_original);
    for(int i = 0; i < CONSULTASIZE; i++)
        free(consultas_string_original[i]);
    free(consultas_string_original);
}