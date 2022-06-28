#include <stdio.h>

#include "exercicio.h"

int main(int argc, char const *argv[]){
    printf("**Busca sequencial simples** \n");
    ex1a(3);
    printf("\n\n\n");

    printf("**Busca mover-para-frente** \n");
    ex1b(3);
    printf("\n\n\n");

    printf("**Busca por transposição** \n");
    ex1c(3);
    printf("\n\n\n");
}