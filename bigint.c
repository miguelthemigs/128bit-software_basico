#include <stdio.h>
#include <string.h>
#include "bigint.h"

void big_val (BigInt res, long val){
    unsigned char * p = (unsigned char*)&val; // aponta para o primeiro byte
    int i;
    for(i = 0; i < 8; i++){ /* primeiro passo os 8 bytes de val para os primeiros 8 bytes de bigint
                                isso pois é (little-endian, o mais significativo fica por ultimo) */
        res[i] = *p;
        p++;
    }
     if (res[7] & 0x80){ // verifica se o byte mais significativo do valor original é 1 (0x80 == 10000000)
        for(i = 8; i < 16; i++){
            res[i] = 0xFF; // se for, preencho os bytes restantes com 0xFF que seria 1 em binário
        }
    }
    else{
        for(i = 8; i < 16; i++){
            res[i] = 0x00; // senao, sao preenchidos com 0
        }
    }
}

/* Operações aritméticas*/

void big_comp2(BigInt res, BigInt a){
    return;
}

void big_sum(BigInt res, BigInt a, BigInt b){ /* devo ver se ocorre o vai a 1 numa soma. somo o primeiro byte
                                                de um com o primeiro byte de outro, guardo essa soma de char
                                                em um short, e vejo se o 9 bit está ligado, indicando que a soma
                                                passou e deve ser adicionado na próxima soma */
    return;
}


void big_sub(BigInt res, BigInt a, BigInt b){
    return;
}


void big_mul(BigInt res, BigInt a, BigInt b){
    return;
}


void big_shl(BigInt res, BigInt a, int n){
    return;
}


void big_shr(BigInt res, BigInt a, int n){
    return;
}
