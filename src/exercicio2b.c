#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include <math.h>

#include "timeControl.h"
#include "utils.h"

int ex2b(int n_testes, string* insercao_original, string* consultas_original){
    for(int j = 0; j < n_testes; j++){
        printf("Busca %d: \n", j);
        const int B = 150001;

        unsigned colisoes = 0;
        unsigned encontrados = 0;

        string* insercoes = duplicarString(insercao_original, INPUTSIZE);
        string* consultas = duplicarString(consultas_original, CONSULTASIZE);


        // cria tabela hash com hash por hash duplo
        char** hashTable = malloc(sizeof(char*)*B);
        for (int i = 0; i < B; i++){
            hashTable[i] = NULL;
        }

        // inserção dos dados na tabela hash
        clock_t _ini = inicia_tempo();
        for (int i = 0; i < INPUTSIZE; i++) {
            // inserir insercoes[i] na tabela hash
            unsigned convertedString = converter(insercoes[i]);
            int k = 0;
            int rehashCanStop = 0;
            unsigned key = 0;

            while(rehashCanStop == 0){
                key = (h_mul_closed(convertedString,k,B) + k*h_div_closed(convertedString,k,B))%B;
                if(hashTable[key] == NULL){
                    rehashCanStop = 1;
                }else{
                    colisoes++;
                    k++;
                }
            }

            hashTable[key] = malloc(sizeof(char)*20);
            strcpy(hashTable[key],insercoes[i]);
        }
        double tempo_insercao = finaliza_tempo(_ini);

        // busca dos dados na tabela hash
        _ini = inicia_tempo();
        for (int i = 0; i < CONSULTASIZE; i++) {
            unsigned convertedString = converter(consultas[i]);
            int k = 0;
            int rehashCanStop = 0;
            unsigned key = 0;

            while(rehashCanStop == 0){
                key = (h_mul_closed(convertedString,k,B) + k*h_div_closed(convertedString,k,B))%B;
                if(hashTable[key] == NULL){
                    rehashCanStop = 1;
                }else if(!strcmp(hashTable[key],consultas[i])){
                    encontrados++;
                    rehashCanStop = 1;
                }else{
                    k++;
                }
            }
            // buscar consultas[i] na tabela hash
        }
        double tempo_busca = finaliza_tempo(_ini);

        for (int i = 0; i < B; i++){
            free(hashTable[i]);
        }
        free(hashTable);

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
