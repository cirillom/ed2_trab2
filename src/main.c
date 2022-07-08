#include <stdio.h>
#include <stdlib.h>

#include "exercicio.h"
#include "utils.h"

int main(){
    const int N = 50000;

    //o número de testes que será executado por cada algoritmo
    const int n_testes = 1;

    //lê os inputs dois arrays que para cada execução de códigos devem ser copiados
    //esses arrays devem sem sempre constantes e nunca podem ser alterados diretamente
    int* entradas_numericas_original = ler_inteiros("res/inteiros_entrada.txt", N); 
    int* consultas_numericas_original = ler_inteiros("res/inteiros_busca.txt", N);

    printf("===Busca sequencial simples=== \n\n");
    ex1a(n_testes, entradas_numericas_original, consultas_numericas_original);
    printf("\n\n");

    printf("===Busca mover-para-frente=== \n\n");
    ex1b(n_testes, entradas_numericas_original, consultas_numericas_original);
    printf("\n\n");

    printf("===Busca por transposição=== \n\n");
    ex1c(n_testes, entradas_numericas_original, consultas_numericas_original);
    printf("\n\n");
    
    printf("===Busca sequencial por indice=== \n\n");
    ex1d(n_testes, entradas_numericas_original, consultas_numericas_original);
    printf("\n\n");

    //libera os arrays da memória
    free(entradas_numericas_original);
    free(consultas_numericas_original);


    //lê os inputs dois arrays que para cada execução de códigos devem ser copiados
    //esses arrays devem sem sempre constantes e nunca podem ser alterados diretamente
    string* insercoes_string_original = ler_strings("res/strings_entrada.txt", INPUTSIZE);
    string* consultas_string_original = ler_strings("res/strings_busca.txt", CONSULTASIZE);

    printf("===Busca hashing fechado=== \n\n");
    ex2ab(n_testes, insercoes_string_original, consultas_string_original);
    printf("\n\n");


    printf("===Busca hashing aberto=== \n\n");
    ex2c(n_testes, insercoes_string_original, consultas_string_original);
    printf("\n\n");

    //libera os arrays e as strings da memória
    for(int i = 0; i < INPUTSIZE; i++)
        free(insercoes_string_original[i]);
    free(insercoes_string_original);
    for(int i = 0; i < CONSULTASIZE; i++)
        free(consultas_string_original[i]);
    free(consultas_string_original);
}