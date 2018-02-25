#include<stdio.h>

//item a
void trocaMin(int *i, int *j){
  if(i < j) return;

  int *temp;

  *temp = *i;

  *i = *j;

  *j = *temp;
}
/*na linha 3 estamos comparando os ponteiros ao invés de comparar o
 *conteúdo deles e ao declararmos o ponteiro temp, ele não aponta pra nada
 *portanto seria melhor usar uma variável do tipo inteiro para temp*/

//correção:
void trocaMinCorrigido(int *i, int *j){
  if(*i < *j) return;

  int temp;

  temp = *i;

  *i = *j;

  *j = temp;
}


//item b
void mainErrado(){
   char *a = "trem", *b = "carro";
   if(a < b){
     printf("%s vem antes de %s no dicionário\n", a, b);
   }else{
    printf("%s vem antes de %s no dicionário\n", a, b);
   }
}
//novamente está sendo feita a comparação entre ponteiros
//ao invés de comprararmos o conteúdo apontado por eles.
//outro erro é a inversão nos argumentos de printf do segundo if

//correção
void mainCorrigido(){
  char *a = "trem", *b = "carro";
  if(*a < *b){
    printf("%s vem antes de %s no dicionário\n", a, b);
  }else{
   printf("%s vem antes de %s no dicionário\n", b, a);
  }
}


//item c
void xxx(char *v, int n, int k){
  char *c;
  //c aponta para onde v está apontando
  //enquanto o endereço c for menor que o endereço v+n,
  //o endereço de v cresce
  for(c = v; c < v+n; v+=k){
    printf("%c\n", *c);
  }
}

//o loop está iterando para sempre
//trocando a iteração para o c, o programa
//servirá para exibir as letras de uma string, pulando de
//k em k letras e no máximo até a letra n

//correção
void xxxCorrigido(char *v, int n, int k){
  char *c;
  for(c = v; c < v+n; c+=k){
    printf("%c\n", *c);
  }
}
