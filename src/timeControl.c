#include "timeControl.h"

clock_t inicia_tempo(){
    srand(time(NULL));
    return clock();
}

double finaliza_tempo(clock_t _ini){
    clock_t _fim = clock();
    return ((double) (_fim - _ini)) / CLOCKS_PER_SEC;
}