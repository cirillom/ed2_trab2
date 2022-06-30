#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include <math.h>

#include "timeControl.h"
#include "utils.h"
#include "linkedList.h"

unsigned h_div(string str, unsigned B){
    unsigned x = converter(str);
    return x % B;
}

unsigned h_mul(string str, unsigned B){
    const double A = 0.6180;
    unsigned x = converter(str);
    return fmod(x * A, 1) * B;
}

int ex2c(int n_testes, string* insercao_original, string* consultas_original){
    for(int j = 0; j < n_testes; j++){
        const int B = 150001;

        unsigned colisoes_h_div = 0;
        unsigned colisoes_h_mul = 0;

        unsigned encontrados_h_div = 0;
        unsigned encontrados_h_mul = 0;

        printf("Busca %d: \n", j);

        string* insercoes = duplicarString(insercao_original, INPUTSIZE);
        string* consultas = duplicarString(consultas_original, CONSULTASIZE);

        // cria tabela hash com hash por divisão
        Node** hashTable = (Node**) malloc(sizeof(Node*) * B);
        for (int i = 0; i < B; i++){
            hashTable[i] = NULL;
        }
        
        // inserção dos dados na tabela hash com hash por divisão        
        clock_t _ini = inicia_tempo();
        for (int i = 0; i < INPUTSIZE; i++) {
            // inserir insercoes[i] na tabela hash
            unsigned key = h_div(insercoes[i], B);
            if(hashTable[key] != NULL)
                colisoes_h_div++;
            insert(&hashTable[key], insercoes[i]);
        }
        double tempo_insercao_h_div = finaliza_tempo(_ini);

        //mostra a hash table em um arquivo
        FILE* fp = fopen("build/hash_div_open.txt", "a");
        for (int i = 0; i < INPUTSIZE; i++){
            printList(&hashTable[i], fp);
            fprintf(fp, "\n");
        }
        fclose(fp);
        
        // busca dos dados na tabela hash com hash por divisão
        _ini = inicia_tempo();
        for (int i = 0; i < CONSULTASIZE; i++) {
            // buscar consultas[i] na tabela hash
            unsigned key = h_div(consultas[i], B);

            if(hashTable[key] == NULL)
                continue;
            
            if(findInList(&hashTable[key], consultas[i]) != NULL)
                encontrados_h_div++;
        }
        double tempo_busca_h_div = finaliza_tempo(_ini);

        // destroi tabela hash com hash por divisão
        for(int i = 0; i < B; i++)
            freeList(&hashTable[i]);
        free(hashTable);



        // cria tabela hash com hash por multiplicação
        hashTable = (Node**) malloc(sizeof(Node*) * B);
        for (int i = 0; i < B; i++){
            hashTable[i] = NULL;
        }

        // inserção dos dados na tabela hash com hash por multiplicação
        _ini = inicia_tempo();
        for (int i = 0; i < INPUTSIZE; i++) {
            // inserir insercoes[i] na tabela hash
            unsigned key = h_mul(insercoes[i], B);
            if(hashTable[key] != NULL)
                colisoes_h_mul++;
            insert(&hashTable[key], insercoes[i]);
        }
        double tempo_insercao_h_mul = finaliza_tempo(_ini);

        fp = fopen("build/hash_mul_open.txt", "a");
        for (int i = 0; i < B; i++){
            printList(&hashTable[i], fp);
            fprintf(fp, "\n");
        }
        fclose(fp);

        // busca dos dados na tabela hash com hash por multiplicação
        _ini = inicia_tempo();
        for (int i = 0; i < CONSULTASIZE; i++) {
            // buscar consultas[i] na tabela hash
            unsigned key = h_mul(consultas[i], B);

            if(hashTable[key] == NULL)
                continue;
            
            if(findInList(&hashTable[key], consultas[i]) != NULL)
                encontrados_h_mul++;
        }
        double tempo_busca_h_mul = finaliza_tempo(_ini);

        // destroi tabela hash com hash por multiplicação
        for(int i = 0; i < B; i++)
            freeList(&hashTable[i]);
        free(hashTable);



        printf("Hash por Divisão \t-> ");
        printf("Colisões na inserção: %d | ", colisoes_h_div);
        printf("Tempo de inserção: %fs | ", tempo_insercao_h_div);
        printf("Tempo de busca: %fs | ", tempo_busca_h_div);
        printf("Itens encontrados: %d", encontrados_h_div);
        printf("\n");
        printf("Hash por Multiplicação \t-> ");
        printf("Colisões na inserção: %d | ", colisoes_h_mul);
        printf("Tempo de inserção: %fs | ", tempo_insercao_h_mul);
        printf("Tempo de busca: %fs | ", tempo_busca_h_mul);
        printf("Itens encontrados: %d\n", encontrados_h_mul);
        printf("\n");

        free(insercoes);
        free(consultas);
    }

    return 0;
}
