#ifndef __UTILS_H__
#define __UTILS_H__

#define INPUTSIZE 50000
#define CONSULTASIZE 70000
#define BUCKETCOUNT 150001

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

char** createHashTable();

void freeHashTable(char** hashTable);

unsigned h_div_closed(unsigned x, unsigned i);

unsigned h_mul_closed(unsigned x, unsigned i);

void insertAtHashTable(char** hashTable,string* insercoes,int i,unsigned* colisoes,int helper);

int findAtHashTable(char** hashTable,string* consultas,int i,int helper);

int* ler_inteiros(const char * arquivo, const int n);

int* duplicarArray(int* arr, int n);

string* duplicarString(string* arr, int n);

void generateSimpleSearchTimeCSV(string fileLoc, double tempo_busca, int encontrados);

void generateHashSearchTimeCSV(string fileLoc, int encontrados, int colisoes, double tempo_insercao, double tempo_busca);

string retornarFileLoc(string folder, string name, string extensao);

#endif