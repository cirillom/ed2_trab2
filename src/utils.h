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

//função que converte uma string em um valor para ser usado pela funções hash
unsigned converter(string s);

//lê as strings de um arquivo
string* ler_strings(const char * arquivo, const int n);

//lê os valores inteiros de um arquivo
int* ler_inteiros(const char * arquivo, const int n);

//duplica um array de inteiros
int* duplicarArray(int* arr, int n);

//duplica um array de strings
string* duplicarString(string* arr, int n);

//gera um csv com os tempos de busca simples
void generateSimpleSearchTimeCSV(string fileLoc, double tempo_busca, int encontrados);

//gera um csv com os tempos de busca hash
void generateHashSearchTimeCSV(string fileLoc, int encontrados, int colisoes, double tempo_insercao, double tempo_busca);

//gera a localização de um arquivo baseado em 3 strings
string retornarFileLoc(string folder, string name, string extensao);

#endif