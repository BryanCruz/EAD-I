#include <stdio.h>
#include <stdlib.h>

int * lerSequencia(int M){
  int * seq = (int*) malloc(M*sizeof(int));
  for(int i = 0; i < M; i++){
    scanf("%d", seq+i);
  }

  return seq;
}

void listarSequencia(int * seq, int M){
  for(int i = 0; i < M; i++){
    printf("%d, ", seq[i]);
  }
  printf("\n");
}

void listarSubsequencias(int * seq, int M, int k){
  for(int i = 0; i < M-1; i++){
      int tamSeq;
      for(tamSeq = 1; i+tamSeq < M && tamSeq < k && seq[i]+tamSeq == seq[i+tamSeq]; tamSeq++);

      if(tamSeq > 1){
        for(int j = 0; j < tamSeq; j++){
          printf("%d, ", seq[i+j]);
        }
        printf("\n");
      }
  }
}

int main(void){
    //leitura dos dados para a verificação
    int k, M;

    printf("Até quantos valores consecutivos: ");
    scanf("%d", &k);

    printf("Tamanho da sequencia: ");
    scanf("%d", &M);


    int * seq = lerSequencia(M);
    listarSequencia(seq, M);
    return 0;
}
