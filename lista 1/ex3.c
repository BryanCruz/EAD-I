#include<stdio.h>
#include<stdlib.h>

char * converterParaHexadecimal(unsigned long long int valor){
  return NULL;
}

void exibirValor(char * valor){

}

int main(void){
  unsigned long long int valor;
  scanf("%llu", &valor);

  char * valorEmHexa = converterParaHexadecimal(valor);

  exibirValor(valorEmHexa);

  free(valorEmHexa);

  return 0;
}
