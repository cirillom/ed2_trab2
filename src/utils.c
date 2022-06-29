#include <stdio.h>
#include <stdlib.h>
#include <string.h> // funções strcmp e strcpy
#include <math.h>

#include "utils.h"

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
        fscanf(f, "%s\n", strings[i]);
    }

    fclose(f);

    return strings;
}

unsigned h_div_closed(unsigned x, unsigned i, unsigned B){
    return ((x % B) + i) % B;
}

unsigned h_mul_closed(unsigned x, unsigned i, unsigned B){
    const double A = 0.6180;
    return  ((int) ((fmod(x * A, 1) * B) + i)) % B;
}

unsigned h_div_open(string str, unsigned B){
    int x = 0;
    for (size_t i = 0; i < strlen(str); i++){
        x+= (int)str[i];
    }
    return x % B;
}

unsigned h_mul_open(string str, unsigned B){
    const double A = 0.6180;
    int x = 0;
    for (size_t i = 0; i < strlen(str); i++){
        x+= (int)str[i];
    }
        FILE* fp = fopen("build/hash.txt", "a");
            fprintf(fp, "%f \n", fmod(x * A, 1) * B);
        fclose(fp);

    return fmod(x * A, 1) * B;
}

int* ler_inteiros(const char * arquivo, const int n){
    FILE* f = fopen(arquivo, "r");

    int* inteiros = (int *) malloc(sizeof(int) * n);

    for (int i = 0; !feof(f); i++)
        fscanf(f, "%d\n", &inteiros[i]);

    fclose(f);

    return inteiros;
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
