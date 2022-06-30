#ifndef __UTILS_H__
#define __UTILS_H__

#define INPUTSIZE 50000
#define CONSULTASIZE 70000

// Definição do tipo booleano
typedef unsigned char bool;
#define TRUE  1
#define FALSE 0

// Definição do tipo string
typedef char* string;
#define MAX_STRING_LEN 20

unsigned converter(string s);
unsigned converterBetter(string s);

string* ler_strings(const char * arquivo, const int n);

unsigned h_div_closed(unsigned x, unsigned i, unsigned B);

unsigned h_mul_closed(unsigned x, unsigned i, unsigned B);

int* ler_inteiros(const char * arquivo, const int n);

int* duplicarArray(int* arr, int n);

string* duplicarString(string* arr, int n);

void generateTimeCSV(string fileLoc, double tempo_busca, int encontrados);

#endif