#include<stdio.h>
#include<stdlib.h>

typedef struct s_numeroHexadecimal * numeroHexadecimal;
struct s_numeroHexadecimal{
  int digito;
  numeroHexadecimal prox;
};

numeroHexadecimal converterParaHexadecimal(unsigned long long int valor){
  numeroHexadecimal valorEmHexadecimal = NULL;

  while(valor > 0){
    numeroHexadecimal digito = (numeroHexadecimal) malloc(sizeof(struct s_numeroHexadecimal));

    digito->digito = valor % 16;
    valor = valor / 16;

    digito->prox = valorEmHexadecimal;
    valorEmHexadecimal = digito;
  }
  return valorEmHexadecimal;
}

void exibirValor(numeroHexadecimal valor){
  while(valor != NULL){
    if(valor->digito >= 10){
      char c;
      switch(valor->digito){
        case 10:
          c = 'A';
          break;
        case 11:
          c = 'B';
          break;
        case 12:
          c = 'C';
          break;
        case 13:
          c = 'D';
          break;
        case 14:
          c = 'E';
          break;
        case 15:
          c = 'F';
          break;
      }

      printf("%c", c);
    }else{
      printf("%d", valor->digito);
    }
    valor = valor->prox;
  }
  printf("\n");
}

int main(void){
  // unsigned long long int valor;
  // scanf("%llu", &valor);
  //
  // char * valorEmHexa = converterParaHexadecimal(valor);
  //
  // exibirValor(valorEmHexa);
  //
  // free(valorEmHexa);
  //

  numeroHexadecimal valor = converterParaHexadecimal(11073303771280);
  exibirValor(valor);
  free(valor);

  return 0;
}
