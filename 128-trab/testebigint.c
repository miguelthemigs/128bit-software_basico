#include <stdio.h>
#include "bigint.h"

// gcc -o testebigint bigint.c testebigint.c

void dump (void *p, int n) { // funcao dump para testar os valores
  unsigned char *p1 = p;
  while (n--) {
    printf("%02x ", *p1);
    p1++;
    
  }
  printf("\n");
}

int test_igual(BigInt a, BigInt b, char *msg, int test)
{
   int i;
   int deu_erro = 0; 
   
   for (i = 0; i < 16; i++) 
      if (a[i] != b[i]){
        deu_erro = 1;
        printf("%02x ", a[i]);
      } 
   if (deu_erro)
      printf("Erro em %s no teste %d\n", msg, test);
      //printf("\n");

    
   return deu_erro;
}

int test_big_val (char *msg)
{
  // teste com valor negativo, positivo e zero
   int falhas = 0;
   BigInt gab1 = {0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
   BigInt res;
   big_val (res, 1);
   if (test_igual(res, gab1, msg, 1)) falhas += 1;

   BigInt gab2 = {0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
  
   big_val (res, -2);
   if (test_igual(res, gab2, msg, 2)) falhas += 1;

  BigInt gab3 = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
   big_val (res, 0);
   if (test_igual(res, gab3, msg, 3)) falhas += 1;

   return (falhas != 0);
}

int test_big_sum(char *msg){
  // teste com pos + pos, pos + zero, pos + neg, neg + neg
  int falhas = 0;
  BigInt gab1, gab2, gab3, gab4, gab5, gab6, gab7, gab8, res;
  
  big_val(gab1, 1); 
  
  BigInt result1 = {0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

  big_sum(res, gab1, gab1); // 1+1
  if (test_igual(res, result1, msg, 1)) falhas += 1;

  big_val(gab2, 30000); big_val(gab3, 40000);
  big_sum(res, gab2, gab3); // 30000+40000=70000

  BigInt result2 = {0x70, 0x11, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0, 0x00};
  
if (test_igual(res, result2, msg, 2)) falhas += 1;

 big_val(gab4, 0); 
  
  BigInt result3 = {0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

  big_sum(res, gab1, gab4); // 1+0
   if (test_igual(res, result3, msg, 3)) falhas += 1;

  big_val(gab5, 922337203685477); big_val(gab6, -922337203685477);

  BigInt result4 = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

  big_sum(res, gab5, gab6);
  if (test_igual(res, result4, msg, 4)) falhas += 1;

  big_val(gab6, -1); big_val(gab7, -2);

  BigInt result5 = {0xFD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

  big_sum(res, gab6, gab7);
  if (test_igual(res, result5, msg, 5)) falhas += 1;
  
  return (falhas != 0);
}

int test_big_comp2(char *msg){
  // teste com neg, zero e pos
  int falhas = 0;
  BigInt gab1, gab2, gab3, res;

  BigInt result = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}; // -1
  
  big_val(gab1, 1);
  big_comp2(res, gab1);
  if (test_igual(res, result, msg, 1)) falhas += 1;

    BigInt result2 = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; // comp2 de 0

  big_val(gab2, 0);
  big_comp2(res, gab2);
  if (test_igual(res, result2, msg, 2)) falhas += 1;

  BigInt result3 = {0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}; //-256

  big_val(gab3, 256); 
  big_comp2(res, gab3);
  if (test_igual(res, result3, msg, 3)) falhas += 1;
  
  return (falhas != 0);
}

int test_big_mul(char *msg){
  // teste com pos*pos, pos*neg, pos*0, neg*0, neg*neg, num*1
  int falhas = 0;
  BigInt gab1, gab2, gab3, gab4, gab5, gab6, gab7, gab8, res;

  BigInt result = {0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}; // -2

  big_val(gab1, 2); big_val(gab2, -1);
  big_mul(res, gab1, gab2);
  if (test_igual(res, result, msg, 1)) falhas += 1;

  BigInt result2 = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; // 0

  big_val(gab3, 0); big_val(gab4, 9223372036854775807); // maior long possivel (pos * 0)
  big_mul(res, gab3, gab4); 
  if (test_igual(res, result2, msg, 2)) falhas += 1;
  
  BigInt result3 = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01};
  
  big_val(gab5, 1152921504606846976);
  big_mul(res, gab5, gab5); // 2**60 x 2**60 = 2**120 = ultimo bit aceso (pos * pos)
  if (test_igual(res, result3, msg, 3)) falhas += 1;

  BigInt result4 = {0xE2, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}; // -30 (pos * neg)
  
  big_val(gab6, -10); big_val(gab7, 3);
  big_mul(res, gab6, gab7);
  if (test_igual(res, result4, msg, 4)) falhas += 1;
  
  // neg * 0
  big_mul(res, gab6, gab3);
  if (test_igual(res, result2, msg, 5)) falhas += 1;

  BigInt result5 = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; // neg * neg
  
  big_val(gab7, -1152921504606846976);
  big_mul(res, gab7, gab2); // -(2**60) * -1 (8 byte aceso)
  if (test_igual(res, result5, msg, 6)) falhas += 1;
  
  // num * 1 | 2**60 * 1 (8 byte aceso)

  big_val(gab8, 1);
  big_mul(res, gab8, gab5);
  if (test_igual(res, result5, msg, 7)) falhas += 1;
  
  
  return (falhas != 0);
}

int test_big_shl(char *msg){
  int falhas=0;
  BigInt gab1, gab2, gab3, gab4,res;
  
  BigInt result1= {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};//0
  big_val(gab1, 0); 
  big_shl(res, gab1, 10);
  if (test_igual(res, result1, msg, 1)) falhas += 1;

  BigInt result2= {0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
  big_val(gab2, -1); 
  big_shl(res, gab2, 16); // 2 bytes
  if (test_igual(res, result2, msg, 2)) falhas += 1;
  
  BigInt result3= {0x94, 0x21, 0x8E, 0x75, 0x71, 0x1B, 0x0D, 0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  big_val(gab3, 922337203685477); 
  big_shl(res, gab3, 2);
  if (test_igual(res, result3, msg, 3)) falhas += 1;

  BigInt result4= {0x00, 0x36, 0xEF, 0x38, 0x45, 0x47, 0x72, 0xF9,0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
  big_val(gab4, -922337203685477); 
  big_shl(res, gab4, 9);
  if (test_igual(res, result4, msg, 4)) falhas += 1;

  // trocar de lugar o numero
  BigInt result5= {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x65, 0x88, 0x63, 0x5d, 0xdc, 0x46, 0x03};
  
  big_shl(res, gab3, 64);
  if (test_igual(res, result5, msg, 5)) falhas += 1;

  //nao mudar nada
  BigInt result6= {0x65, 0x88, 0x63, 0x5d, 0xdc, 0x46, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  big_shl(res, gab3, 0);
  if (test_igual(res, result6, msg, 6)) falhas += 1;
  

  return (falhas != 0);
}

int test_big_shr(char* msg){
  int falhas=0;
  BigInt gab1, gab2, gab3, gab4,res;

  BigInt result = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00};//-1 >> 2 bytes

  big_val(gab1, -1);
  big_shr(res, gab1, 16);
  if (test_igual(res, result, msg, 1)) falhas += 1;

  BigInt result2 = {0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};//-1 >> 2 bytes
  
  big_val(gab2, 8);
  big_shr(res, gab2, 1); // fazendo >>1 == fazer 2^3 ir para 2^2
  if (test_igual(res, result2, msg, 2)) falhas += 1;

  BigInt result3 = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};// 0

  big_val(gab3, 0);
  big_shr(res, gab3, 32);
  if (test_igual(res, result3, msg, 3)) falhas += 1; 

   // um que zera tudo e com numero maior
  big_val(gab4, 922337203685477);
  big_shr(res, gab4, 64); 
  if (test_igual(res, result3, msg, 4)) falhas += 1; 

  // um que nao mude nada
  BigInt result4= {0x65, 0x88, 0x63, 0x5d, 0xdc, 0x46, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

   big_shr(res, gab4, 0); 
  if (test_igual(res, result4, msg, 5)) falhas += 1; 
  
  return (falhas != 0);
}

int test_big_sar(char* msg){
  int falhas=0;
  BigInt gab1, gab2, gab3, gab4, gab5, gab6, res;

  BigInt result = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};//-1

  big_val(gab1, -1); big_sar(res, gab1, 8);
  if (test_igual(res, result, msg, 1)) falhas += 1; 

  BigInt result2 = {0x00, 0x00, 0x00, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
  
  big_val(gab2, -1152921504606846976); //-2^60
  big_sar(res, gab2, 32);
  if (test_igual(res, result2, msg, 2)) falhas += 1; 

  BigInt result3 = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

  big_val(gab3, 0); big_sar(res, gab3, 16);
  if (test_igual(res, result3, msg, 3)) falhas += 1;

  BigInt result4= {0x65, 0x88, 0x63, 0x5d, 0xdc, 0x46, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

   big_val(gab4,  922337203685477); big_sar(res, gab4, 0); 
  if (test_igual(res, result4, msg, 4)) falhas += 1; 

  BigInt result5 = {0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};//-1 >> 2 bytes
  
  big_val(gab5, 8); big_sar(res, gab5, 1); // fazendo >>1 == fazer 2^3 ir para 2^2
  if (test_igual(res, result5, msg, 5)) falhas += 1;

  BigInt result6 = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

  big_val(gab6, -2); big_sar(res, gab6, 8);
  if (test_igual(res, result6, msg, 6)) falhas += 1;
  
  return (falhas != 0);
}

int test_big_sub(char* msg){
  int falhas=0;
  BigInt gab1, gab2, gab3, gab4, gab5, gab6, gab7, gab8, gab9, gab10, gab11, gab12, gab122, res;
  // OBS: NAO REPETIR VARIAVEIS NA FUNCAO

  // pos - pos, neg - neg, pos - neg, neg - pos, pos - 0, neg - 0, 0 - 0

   BigInt result = {0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  
  big_val(gab1, 9); big_val(gab2, 3);
  big_sub(res, gab1, gab2); // pos - pos
  if (test_igual(res, result, msg, 1)) falhas += 1;
  
  BigInt result2 = {0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

  big_val(gab3, -2); big_val(gab4, 2);
  big_sub(res, gab3, gab4); // neg - pos
 
  if (test_igual(res, result2, msg, 2)) falhas += 1;

BigInt result3 = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  big_val(gab5, -2);
  big_sub(res, gab3, gab5); // -2 -(-2) = 0 // neg - neg

  if (test_igual(res, result3, msg, 3)) falhas += 1;

  BigInt result4 = {0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  
  big_val(gab6, -3); big_val(gab7, 4);
  big_sub(res, gab7, gab6); // 4 -(-3) = 7 // pos - neg
   if (test_igual(res, result4, msg, 4)) falhas += 1;
  
 // 0 - 0
  big_val(gab8, 0); big_val(gab9, 0);
  big_sub(res, gab8, gab9);
  if (test_igual(res, result3, msg, 5)) falhas += 1;

  BigInt result5 = {0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  
  big_val(gab10, 1); big_val(gab11, 0); 
  big_sub(res, gab10, gab11); // pos - 0
  if (test_igual(res, result5, msg, 6)) falhas += 1;

   BigInt result6 = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
  
  big_val(gab12, -1); big_val(gab122, 0);
  big_sub(res, gab12, gab122); // neg - 0
  if (test_igual(res, result6, msg, 6)) falhas += 1;
  
  return (falhas != 0);
}


int main(void){
  
  int falhas = 0;
   
   falhas += test_big_val("big_val");
   falhas += test_big_sum("big_sum");
   falhas += test_big_comp2("big_comp2");
   falhas += test_big_mul("big_mul");
   falhas += test_big_shl("big_shl");
   falhas += test_big_shr("big_shr");
   falhas += test_big_sar("big_sar");
   falhas += test_big_sub("big_sub");

   printf("Total de falhas %d de 42 testes\n", falhas);

    return 0;
  
  }