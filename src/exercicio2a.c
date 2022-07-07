#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h> // funções strcmp e strcpy

#include "timeControl.h"
#include "utils.h"

int ex2a(int n_testes, string* insercao_original, string* consultas_original){
    for(int j = 0; j < n_testes; j++){
        printf("Busca %d: \n", j);

        unsigned colisoes_h_div = 0;
        unsigned colisoes_h_mul = 0;

        unsigned encontrados_h_div = 0;
        unsigned encontrados_h_mul = 0;

        string* insercoes = duplicarString(insercao_original, INPUTSIZE);
        string* consultas = duplicarString(consultas_original, CONSULTASIZE);

        // cria tabela hash com hash por divisão
        char** hashTable = createHashTable();

        // inserção dos dados na tabela hash usando hash por divisão
        clock_t _ini = inicia_tempo();
        for (int i = 0; i < INPUTSIZE; i++) {
            insertAtHashTable(hashTable,insercoes,i,&colisoes_h_div,0);
        }
        double tempo_insercao_h_div = finaliza_tempo(_ini);

        // consulta dos dados na tabela hash usando hash por divisão
        _ini = inicia_tempo();
        for (int i = 0; i < CONSULTASIZE; i++) {
            if(findAtHashTable(hashTable,consultas, i,0)){
                encontrados_h_div++;
            }
            // buscar consultas[i] na tabela hash
        }
        double tempo_busca_h_div = finaliza_tempo(_ini);

        // limpa a tabela hash com hash por divisão
        freeHashTable(hashTable);

        // cria tabela hash com hash por multiplicação
        hashTable = createHashTable();

        // inserção dos dados na tabela hash usando hash por multiplicação
        _ini = inicia_tempo();
        for (int i = 0; i < INPUTSIZE; i++) {
            insertAtHashTable(hashTable,insercoes,i,&colisoes_h_mul,1);
        }

        double tempo_insercao_h_mul = finaliza_tempo(_ini);

        // busca dos dados na tabela hash com hash por multiplicação
        _ini = inicia_tempo();
        for (int i = 0; i < CONSULTASIZE; i++) {
            if(findAtHashTable(hashTable,consultas, i,1)){
                encontrados_h_mul++;
            }
        }

        double tempo_busca_h_mul = finaliza_tempo(_ini);

        // limpa a tabela hash com hash por multiplicação
        freeHashTable(hashTable);

        printf("Hash por Divisão\t-> ");
        printf("Colisões na inserção: %d | ", colisoes_h_div);
        printf("Tempo de inserção: %fs | ", tempo_insercao_h_div);
        printf("Tempo de busca: %fs | ", tempo_busca_h_div);
        printf("Itens encontrados: %d", encontrados_h_div);
        printf("\n");

        printf("Hash por Multiplicação\t-> ");
        printf("Colisões na inserção: %d | ", colisoes_h_mul);
        printf("Tempo de inserção: %fs | ", tempo_insercao_h_mul);
        printf("Tempo de busca: %fs | ", tempo_busca_h_mul);
        printf("Itens encontrados: %d", encontrados_h_mul);
        printf("\n");
        free(insercoes);
        free(consultas);

    }
    return 0;
}
