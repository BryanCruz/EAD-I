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
  int i = 0, j = 0, qtd, lim;
  int tamSeq;
  while(i < M-1){
    //achar o tamanho da sequencia de numeros consecutivos
    for(tamSeq = 1; i+tamSeq < M && seq[i]+tamSeq == seq[i+tamSeq]; tamSeq++);

    if(tamSeq > 1){
      qtd = tamSeq - k;
      do{
        lim = i + (tamSeq < k? tamSeq : k);
        for(j = i; j < lim-1; j++){
          printf("%d, ", seq[j]);
        }
        printf("%d\n", seq[j]);
        i++;
      }while(--qtd >= 0);
      i = j;
    }else{
      i++;
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
    free(seq);
    return 0;
}
