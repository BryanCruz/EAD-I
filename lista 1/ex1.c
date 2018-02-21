#include <stdio.h>

int main(void){

  //leitura dos dados para a verificação
  int k, M;

  printf("Até quantos valores consecutivos: ");
  scanf("%d", &k);

  printf("Tamanho da sequencia: ");
  scanf("%d", &M);

  return 0;
}

int * lerSequencia(int M){
  int seq[M];
  for(int i = 0; i < M; i++){
    scanf("%d", seq+i);
  }

  return seq;
}

void listarSequencia(int * seq, int M){
  for(int i = 0; i < M; i++){
    printf("%d, ", seq[i]);
  }
}

void listarSubsequencias(int * seq, int M, int k){

}
