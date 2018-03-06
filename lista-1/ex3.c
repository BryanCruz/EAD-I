#include<stdio.h>
#include<stdlib.h>

/*Converte valores digitados para o sistema hexadecimal e os exibe como
  em um display digital composto por 7 LEDs (Seven Segment Display)*/

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
  int flag[7];

  numeroHexadecimal rodando = valor;
  int digito;
  //primeira linha
  while(rodando != NULL){
    digito = rodando->digito;

    //a
    if(digito != 1 && digito != 4 && digito != 11 && digito != 13){
      printf(" _ ");
    }else{
      printf("   ");
    }

    rodando = rodando->prox;
  }
  printf("\n");

  //segunda linha
  rodando = valor;
  while(rodando != NULL){
    digito = rodando->digito;
    //f
    if(digito != 1 && digito != 2 && digito != 3 && digito != 7 && digito != 13){
      printf("|");
    }else{
      printf(" ");
    }

    //g
    if(digito != 0 && digito != 1 && digito != 7 && digito != 12){
      printf("_");
    }else{
      printf(" ");
    }

    //b
    if(digito != 5 && digito != 6 && digito != 11 && digito != 12 && digito != 14 && digito != 15){
      printf("|");
    }else{
      printf(" ");
    }
    rodando = rodando->prox;
  }
  printf("\n");


  //terceira linha
  rodando = valor;
  while(rodando != NULL){
    digito = rodando->digito;
    //e
    if(digito != 1 && digito != 3 && digito != 4 && digito != 5 && digito != 7 && digito != 9){
      printf("|");
    }else{
      printf(" ");
    }

    //d
    if(digito != 1 && digito != 4 && digito != 7 && digito != 10 && digito != 15){
      printf("_");
    }else{
      printf(" ");
    }

    //c
    if(digito != 2 && digito != 12 && digito != 14 && digito != 15){
      printf("|");
    }else{
      printf(" ");
    }

    rodando = rodando->prox;
  }
  printf("\n");
}

int main(void){
  unsigned long long int valor;

  while(scanf("%llu", &valor) > 0){
    numeroHexadecimal valorEmHexa = converterParaHexadecimal(valor);

    exibirValor(valorEmHexa);

    free(valorEmHexa);
  }
  return 0;
}
