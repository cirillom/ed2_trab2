#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h> // funções strcmp e strcpy
#include <math.h>

#include "timeControl.h"
#include "utils.h"

char** createHashTable(){
    char** hashTable = malloc(sizeof(char*)*BUCKETCOUNT);
    for (unsigned i = 0; i < BUCKETCOUNT; i++){
            hashTable[i] = NULL;
    }
    return hashTable;
}

void freeHashTable(char** hashTable){
    for (unsigned i = 0; i < BUCKETCOUNT; i++){
            free(hashTable[i]);
        }
        free(hashTable);
}

unsigned h_div_closed(string s, unsigned i){
    unsigned x = converter(s);
    return ((x % BUCKETCOUNT) + i) % BUCKETCOUNT;
}

unsigned h_mul_closed(string s, unsigned i){
    unsigned x = converter(s);

    const double A = 0.6180;
    return  ((int) ((fmod(x * A, 1) * BUCKETCOUNT) + i)) % BUCKETCOUNT;
}

unsigned h_improved_closed(string s,unsigned int i){
    unsigned h = 1;
    const unsigned p1 = 189437;

    for (int j = 0; s[j] != '\0'; j++){
      h = ((h * s[j] * p1)%BUCKETCOUNT + i)%BUCKETCOUNT;
    }
    return h;
}

unsigned h_duplo_closed(string s,unsigned int i){
    return ((h_mul_closed(s,i) + i*h_div_closed(s,i))%BUCKETCOUNT);
}

void insertAtHashTable(unsigned(*hash_function)(string,unsigned),char** hashTable,string* insercoes,int i,unsigned* colisoes){
    int k = 0;
    unsigned key = 0;

    while(1){
        key = hash_function(insercoes[i],k);
        if(hashTable[key] == NULL){
            break;
        }else{
            if(!k){
                (*colisoes)++;
            }
            k++;
        }
    }

    hashTable[key] = malloc(sizeof(char)*20);
    strcpy(hashTable[key],insercoes[i]);
}

int findAtHashTable(unsigned(*hash_function)(string,unsigned),char** hashTable,string* consultas,int i){
    int k = 0;
    unsigned key = 0;

    while(1){
        key = hash_function(consultas[i],k);
        if(hashTable[key] == NULL){
            return 0;
        }else if(!strcmp(hashTable[key],consultas[i])){
            return 1;
        }else{
            k++;
        }
    }
}

void core(unsigned(*hash_function)(string,unsigned),string* insercoes,string* consultas,string id){

    unsigned colisoes = 0;
    unsigned encontrados = 0;

    // cria tabela hash com hash por divisão
    char** hashTable = createHashTable();

    // inserção dos dados na tabela hash usando hash por divisão
    clock_t _ini = inicia_tempo();
    for (int i = 0; i < INPUTSIZE; i++) {
        insertAtHashTable(hash_function,hashTable,insercoes,i,&colisoes);
    }
    double tempo_insercao = finaliza_tempo(_ini);

    // consulta dos dados na tabela hash usando hash por divisão
    _ini = inicia_tempo();
    for (int i = 0; i < CONSULTASIZE; i++) {
        if(findAtHashTable(hash_function,hashTable,consultas, i)){
            encontrados++;
        }
        // buscar consultas[i] na tabela hash
    }
    double tempo_busca = finaliza_tempo(_ini);

    // limpa a tabela hash com hash por divisão
    freeHashTable(hashTable);

    string file_loc = retornarFileLoc("out/busca_hash_", id, ".csv");
    generateHashSearchTimeCSV(file_loc, encontrados, colisoes, tempo_insercao, tempo_busca);
    free(file_loc);

    printf("Hash por %s\t-> ",id);
    printf("Colisões na inserção: %d | ", colisoes);
    printf("Tempo de inserção: %fs | ", tempo_insercao);
    printf("Tempo de busca: %fs | ", tempo_busca);
    printf("Itens encontrados: %d", encontrados);
    printf("\n");
    
}

int ex2ab(int n_testes, string* insercao_original, string* consultas_original){
    for(int j = 0; j < n_testes; j++){
        printf("Busca %d: \n", j);

        string* insercoes = duplicarString(insercao_original, INPUTSIZE);
        string* consultas = duplicarString(consultas_original, CONSULTASIZE);

        core(&h_div_closed,insercoes,consultas,"fechado_overflow_div");
        core(&h_mul_closed,insercoes,consultas,"fechado_overflow_mul");
        core(&h_improved_closed,insercoes,consultas,"fechado_overflow_primo");
        core(&h_duplo_closed,insercoes,consultas,"fechado_duplo");

        free(insercoes);
        free(consultas);
    }
    return 0;
}
