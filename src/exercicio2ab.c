#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h> // funções strcmp e strcpy

#include "timeControl.h"
#include "utils.h"

int ex2ab(int n_testes, string* insercao_original, string* consultas_original){
    
    char id[4][20];
    strcpy(id[0],"div_of");
    strcpy(id[1],"mul_of");
    strcpy(id[2],"melh_of");
    strcpy(id[3],"duplo");

    for(int j = 0; j < n_testes; j++){
        printf("Busca %d: \n", j);

        for(int l = 0;l<4;l++){

            unsigned colisoes = 0;
            unsigned encontrados = 0;

            string* insercoes = duplicarString(insercao_original, INPUTSIZE);
            string* consultas = duplicarString(consultas_original, CONSULTASIZE);

            // cria tabela hash com hash por divisão
            char** hashTable = createHashTable();

            // inserção dos dados na tabela hash usando hash por divisão
            clock_t _ini = inicia_tempo();
            for (int i = 0; i < INPUTSIZE; i++) {
                insertAtHashTable(hashTable,insercoes,i,&colisoes,l);
            }
            double tempo_insercao = finaliza_tempo(_ini);

            // consulta dos dados na tabela hash usando hash por divisão
            _ini = inicia_tempo();
            for (int i = 0; i < CONSULTASIZE; i++) {
                if(findAtHashTable(hashTable,consultas, i,l)){
                    encontrados++;
                }
                // buscar consultas[i] na tabela hash
            }
            double tempo_busca = finaliza_tempo(_ini);

            // limpa a tabela hash com hash por divisão
            freeHashTable(hashTable);

            string file_loc = retornarFileLoc("out/busca_hash_", id[l], ".csv");
            generateHashSearchTimeCSV(file_loc, encontrados, colisoes, tempo_insercao, tempo_busca);
            free(file_loc);

            /*if(l == 0){printf("Hash por Divisão Overflow Progressivo\t-> ");
            }else if(l == 1){
                printf("Hash por Multiplicação Overflow Progressivo\t-> ");
            }else if(l == 2){
                printf("Hash Melhorado Overflow Progressivo\t-> ");
            }else if(l == 3){
                printf("Hash Duplo\t-> ");
            }
            printf("Colisões na inserção: %d | ", colisoes);
            printf("Tempo de inserção: %fs | ", tempo_insercao);
            printf("Tempo de busca: %fs | ", tempo_busca);
            printf("Itens encontrados: %d", encontrados);
            printf("\n\n");*/

            free(insercoes);
            free(consultas);
        }

    }
    return 0;
}
