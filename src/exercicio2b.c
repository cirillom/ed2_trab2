#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>

#include "timeControl.h"
#include "utils.h"

int ex2b(int n_testes, string* insercao_original, string* consultas_original){
    for(int j = 0; j < n_testes; j++){
        printf("Busca %d: \n", j);

        unsigned colisoes = 0;
        unsigned encontrados = 0;

        string* insercoes = duplicarString(insercao_original, INPUTSIZE);
        string* consultas = duplicarString(consultas_original, CONSULTASIZE);

        // cria tabela hash com hash por hash duplo
        char** hashTable = createHashTable();

        // inserção dos dados na tabela hash
        clock_t _ini = inicia_tempo();
        for (int i = 0; i < INPUTSIZE; i++) {
            insertAtHashTable(hashTable,insercoes,i,&colisoes,2);
        }
        double tempo_insercao = finaliza_tempo(_ini);

        // busca dos dados na tabela hash
        _ini = inicia_tempo();
        for (int i = 0; i < CONSULTASIZE; i++) {
            if(findAtHashTable(hashTable,consultas, i,2)){
                encontrados++;
            }
        }
        double tempo_busca = finaliza_tempo(_ini);

        // limpa a tabela hash com hash duplo
        freeHashTable(hashTable);

        printf("Hash Duplo\t-> ");
        printf("Colisões na inserção: %d | ", colisoes);
        printf("Tempo de inserção: %fs | ", tempo_insercao);
        printf("Tempo de busca: %fs | ", tempo_busca);
        printf("Itens encontrados: %d", encontrados);
        printf("\n");

        free(insercoes);
        free(consultas);
    }
    return 0;
}
