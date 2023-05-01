/* Miguel Werneck Roale 2210457 Turma 3WA*/
/* Nome_do_Aluno2 Matricula Turma */

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
  int i; BigInt one;
  
  for(i = 0; i < 16; i++){  
      res[i] = 0;
  }
  
  for(i = 0; i < 16; i++){
    a[i] = ~a[i]; // inverto os bits
  }
  big_val(one, 1); // guardo o 1 no big int
  big_sum(res, a, one); // somo 1 apos a inversao dos bits
}

void big_sum(BigInt res, BigInt a, BigInt b){ 
  short sum = 0; int i; 
  char t = 0;

  for(i = 0; i < 16; i++){ 
      res[i] = 0;
  }
  
  for(i = 0; i < 16; i++){
   sum = a[i] + b[i] + t; // primeiro somo o t anterior
    res[i] = sum & 0x00FF; // guarda so o char xxxx [xxxx]
    t = sum >> 8; // t = [xxxx] xxxx
                  //  guardo o vai a um para poder somar na proxima iteracao
    
  }// guardo o vai a um num short e checo se seu nono bit e um
    return;
}


void big_sub(BigInt res, BigInt a, BigInt b){
  int i; BigInt negative_b;
  // a + (-b) = res
  
    big_comp2(negative_b, b);
    big_sum(res, a, negative_b);
  
    return;
}


void big_mul(BigInt res, BigInt a, BigInt b){
  int i, j, sum;
  short vai1;

  
  for(i = 0; i < 16; i++){ // aqui é a mesma ideia da outra função 
      res[i] = 0;
  }
  
  for(i = 0; i < 16; i++){ // esses dois for funcionam da forma como se fosse uma multiplicação comum de dois valores
    vai1 = 0;
    for(j = 0; j < 16; j++){ 
      
      sum = a[i] * b[j] + res[i+j] + vai1; // aqui faz a multiplicação comum e soma com o vai um armazenado no final, mais o a adicao
       
      res[i+j] = sum & 0xFF; // salva no array do resultado sem o vai 1 [1010] 0011
      vai1 = sum >> 8; //cria o vai a um 1010 [0011]
    }
  }

  return;
}



void big_shl(BigInt res, BigInt a, int n) {
    // Calcula o número de bytes que devem ser deslocados
    int num_bytes = n / 8;
    // Calcula o número de bits que devem ser deslocados além dos bytes completos
    int num_bits = n % 8;
    // Inicializa a variável add1 com zero
    short add1 = 0x00;

    
    for (int i = 0; i < 16; i++) {
        res[i] = 0;
    }

    for (int i = 0; i < 16; i++) {
        res[i + num_bytes] = (a[i] << num_bits) | add1;
        add1 = (a[i] << num_bits) >> 8;
    }
} 

/* res = a >> n (lógico)*/
void big_shr(BigInt res, BigInt a, int n){
  int num_bytes = n / 8;
  int num_bits = n % 8;
    
  short add1 = 0x00;

  for (int i = 0; i < 16; i++) {
        res[i] = 0;
    }

  for (int i = 15; i >= num_bytes; i--){
    res[i - num_bytes] = (a[i] >> num_bits) | add1;
    add1 = (a[i] << (8 - num_bits));
  }
  
    return;
}

/* res = a >> n (aritmético)*/
void big_sar(BigInt res, BigInt a, int n){
  int num_bytes = n / 8;
  int num_bits = n % 8;
  int bit_sig;
  short add1 = 0x00;

  if(a[15] & 0x80){ // checo o bit mais significativo
    bit_sig = 0xFF;
  }
  else{
    bit_sig = 0x00;
  }

  for (int i = 0; i < 16; i++){
    res[i] = bit_sig;
    add1 = bit_sig;
  }
  
  for (int i = 15; i >= 0; i--){
    res[i - num_bytes] = (a[i] >> num_bits) | add1;
    add1 = (a[i] << num_bits) >> 8;
    add1 = (a[i] << (8 - num_bits));
  }
  
}