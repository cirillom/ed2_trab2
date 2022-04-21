#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h> // funções strcmp e strcpy
#include <math.h>

#include "timeControl.h"
#include "utils.h"
#include "linkedList.h"

int ex2a(int n_testes, string* insercao_original, string* consultas_original){
    for(int j = 0; j < n_testes; j++){
        printf("Busca %d: \n", j);
        const int B = 150001;

        unsigned colisoes_h_div = 0;
        unsigned colisoes_h_mul = 0;

        unsigned encontrados_h_div = 0;
        unsigned encontrados_h_mul = 0;

        string* insercoes = duplicarString(insercao_original, INPUTSIZE);
        string* consultas = duplicarString(consultas_original, CONSULTASIZE);


        // cria tabela hash com hash por divisão
        char** hashTable = malloc(sizeof(char*)*B);
        for (int i = 0; i < B; i++){
            hashTable[i] = NULL;
        }

        // inserção dos dados na tabela hash usando hash por divisão
        clock_t _ini = inicia_tempo();
        for (int i = 0; i < INPUTSIZE; i++) {
            unsigned convertedString = converter(insercoes[i]);
            j = 0;
            int rehashCanStop = 0;
            unsigned key = 0;

            while(rehashCanStop == 0){
                key = h_div_closed(convertedString,j,B);
                if(hashTable[key] == NULL){
                    rehashCanStop = 1;
                }else{
                    if(!j){
                        colisoes_h_div++;
                    }
                    j++;
                }
            }

            hashTable[key] = malloc(sizeof(char)*20);
            strcpy(hashTable[key],insercoes[i]);
        }
        double tempo_insercao_h_div = finaliza_tempo(_ini);

        // consulta dos dados na tabela hash usando hash por divisão
        _ini = inicia_tempo();
        for (int i = 0; i < CONSULTASIZE; i++) {
            unsigned convertedString = converter(consultas[i]);
            j = 0;
            int rehashCanStop = 0;
            unsigned key = 0;

            while(rehashCanStop == 0){
                key = h_div_closed(convertedString,j,B);
                if(hashTable[key] == NULL){
                    rehashCanStop = 1;
                }else if(!strcmp(hashTable[key],consultas[i])){
                    encontrados_h_div++;
                    rehashCanStop = 1;
                }else{
                    j++;
                    if(j >= B){
                        break;
                    }
                }
            }
            // buscar consultas[i] na tabela hash
        }
        double tempo_busca_h_div = finaliza_tempo(_ini);

        // limpa a tabela hash com hash por divisão
        for (int i = 0; i < B; i++){
            free(hashTable[i]);
        }
        free(hashTable);



        // cria tabela hash com hash por multiplicação

        hashTable = malloc(sizeof(char*)*B);
        for (int i = 0; i < B; i++){
            hashTable[i] = NULL;
        }

        // inserção dos dados na tabela hash usando hash por multiplicação
        _ini = inicia_tempo();
        for (int i = 0; i < INPUTSIZE; i++) {
            // inserir insercoes[i] na tabela hash

            unsigned convertedString = converter(insercoes[i]);
            j = 0;
            int rehashCanStop = 0;
            unsigned key = 0;

            while(rehashCanStop == 0){
                key = h_mul_closed(convertedString,j,B);
                if(hashTable[key] == NULL){
                    rehashCanStop = 1;
                }else{
                    if(!j){
                        colisoes_h_mul++;
                    }
                    j++;
                }
            }
            hashTable[key] = malloc(sizeof(char)*20);
            strcpy(hashTable[key],insercoes[i]);
        }
        double tempo_insercao_h_mul = finaliza_tempo(_ini);

        // busca dos dados na tabela hash com hash por multiplicação
        _ini = inicia_tempo();
        for (int i = 0; i < CONSULTASIZE; i++) {
            //buscar consultas[i] na tabela hash
            unsigned convertedString = converter(consultas[i]);
            j = 0;
            int rehashCanStop = 0;
            unsigned key = 0;

            while(rehashCanStop == 0){
                key = h_mul_closed(convertedString,j,B);
                if(hashTable[key] == NULL){
                    rehashCanStop = 1;
                }else if(!strcmp(hashTable[key],consultas[i])){
                    encontrados_h_mul++;
                    rehashCanStop = 1;
                }else{
                    j++;
                    if(j >= B){
                        break;
                    }
                }
            }
        }

        double tempo_busca_h_mul = finaliza_tempo(_ini);

        // limpa a tabela hash com hash por multiplicação
        for (int i = 0; i < B; i++){
            free(hashTable[i]);
        }
        free(hashTable);

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
