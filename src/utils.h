#ifndef __UTILS_H__
#define __UTILS_H__

#define INPUTSIZE 50000

// Definição do tipo booleano
typedef unsigned char bool;
#define TRUE  1
#define FALSE 0

// Definição do tipo string
typedef char* string;
#define MAX_STRING_LEN 20

unsigned converter(string s);

string* ler_strings(const char * arquivo, const int n);

unsigned h_div(unsigned x, unsigned i, unsigned B);

unsigned h_mul(unsigned x, unsigned i, unsigned B);

int* ler_inteiros(const char * arquivo, const int n);

int trocar(int* arr, int i1, int i2);

int* duplicarArray(int* arr, int n);

#endif