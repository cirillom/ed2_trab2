#include <stdio.h>
#include <stdlib.h>
#include <string.h> // funções strcmp e strcpy
#include <math.h>
#include <sys/stat.h>

#include "utils.h"

int checkIfFileExists(const char* filename){
    struct stat buffer;
    int exist = stat(filename,&buffer);
    if(exist == 0)
        return 1;
    else  
        return 0;
}

unsigned converter(string s) {
   unsigned h = 0;
   for (int i = 0; s[i] != '\0'; i++) 
      h = h * 256 + s[i];
   return h;
}

string* ler_strings(const char * arquivo, const int n){
    FILE* f = fopen(arquivo, "r");
    
    string* strings = (string *) malloc(sizeof(string) * n);

    for (int i = 0; !feof(f); i++) {
        strings[i] = (string) malloc(sizeof(char) * MAX_STRING_LEN);
        if(fscanf(f, "%s\n", strings[i])==-1)
            exit(1);
    }

    fclose(f);

    return strings;
}

int* ler_inteiros(const char * arquivo, const int n){
    FILE* f = fopen(arquivo, "r");

    int* inteiros = (int *) malloc(sizeof(int) * n);

    for (int i = 0; !feof(f); i++)
        if(fscanf(f, "%d\n", &inteiros[i]) == -1)
            exit(1);

    fclose(f);

    return inteiros;
}

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

unsigned h_div_closed(unsigned x, unsigned i){
    return ((x % BUCKETCOUNT) + i) % BUCKETCOUNT;
}

unsigned h_mul_closed(unsigned x, unsigned i){
    
    const double A = 0.6180;
    return  ((int) ((fmod(x * A, 1) * BUCKETCOUNT) + i)) % BUCKETCOUNT;
}

unsigned h_improved_closed(string s,int i){
    unsigned h = 1;
    const unsigned p1 = 189437;

    for (int j = 0; s[j] != '\0'; j++){
      h = ((h * s[j] * p1)%BUCKETCOUNT + i)%BUCKETCOUNT;
    }
    return h;
}

void insertAtHashTable(char** hashTable,string* insercoes,int i,unsigned* colisoes,int helper){
    unsigned convertedString = converter(insercoes[i]);
    int k = 0;
    unsigned key = 0;

    while(1){
        if(helper == 0 ){
            key = h_div_closed(convertedString,k);
        }else if(helper == 1){
            key = h_mul_closed(convertedString,k);
        }else if(helper == 2){
            key = h_improved_closed(insercoes[i],k);
        }else if(helper == 3){
            key = (h_mul_closed(convertedString,k) + k*h_div_closed(convertedString,k))%BUCKETCOUNT;
        }
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

int findAtHashTable(char** hashTable,string* consultas,int i,int helper){
    unsigned convertedString = converter(consultas[i]);
    int k = 0;
    unsigned key = 0;

    while(1){
        if(helper == 0 ){
            key = h_div_closed(convertedString,k);
        }else if(helper == 1){
            key = h_mul_closed(convertedString,k);
        }else if(helper == 2){
            key = h_improved_closed(consultas[i],k);
        }else if(helper == 3){
            key = (h_mul_closed(convertedString,k) + k*h_div_closed(convertedString,k))%BUCKETCOUNT;
        }

        if(hashTable[key] == NULL){
            return 0;
        }else if(!strcmp(hashTable[key],consultas[i])){
            return 1;
        }else{
            k++;
        }
    }

}

int* duplicarArray(int* arr, int n){
    int* novo = (int *) malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
        novo[i] = arr[i];
    
    return novo;    
}

string* duplicarString(string* arr, int n){
    string* novo = (string *) malloc(sizeof(string) * n);
    for (int i = 0; i < n; i++)
        novo[i] = arr[i];
    
    return novo;    
}

void generateSimpleSearchTimeCSV(string file_loc, double tempo_busca, int encontrados){
        if(!checkIfFileExists(file_loc)){
            FILE* fp = fopen(file_loc, "w");
            fprintf(fp, "Encontrados,Tempo\n");
            fclose(fp);
        }

        FILE* fp = fopen(file_loc, "a");
        fprintf(fp, "%d,%f\n", encontrados, tempo_busca);
        fclose(fp);
}

void generateHashSearchTimeCSV(string file_loc, int encontrados, int colisoes, double tempo_insercao, double tempo_busca){
        if(!checkIfFileExists(file_loc)){
            FILE* fp = fopen(file_loc, "w");
            fprintf(fp, "Encontrados,Colisoes,TempoInsercao,TempoBusca\n");
            fclose(fp);
        }

        FILE* fp = fopen(file_loc, "a");
        fprintf(fp, "%d,%d,%f,%f\n", encontrados, colisoes, tempo_insercao, tempo_busca);
        fclose(fp);
}

string retornarFileLoc(string folder, string name, string extensao){
    string file_loc = (string) malloc(sizeof(char) * (strlen(folder) + strlen(name) + strlen(extensao) + 1));
    file_loc[0] = '\0';
    strcat(file_loc, folder);
    strcat(file_loc, name);
    strcat(file_loc, extensao);

    return file_loc;
}
