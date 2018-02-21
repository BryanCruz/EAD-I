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
    int j = 1;
    if(seq[i] == seq[i+j]+j){
      printf("%d", seq[i]);
      while(i+j < M && seq[i] == seq[i+j]+j){
        printf(", %d", seq[i+j]);
        j++;
      }
    }
    printf("\n");
  }
}


void testarListarSubsequencias(){
  int seq1[] = {8,-10,4,-2,-1,0,1,2,50,51,54};
  int M1 = 11;
  int k1 = 4;

  int seq2[] = { 5, 20, -9, 51, 52, 53, -1, -4, -3, -2, -1, 0, 1, 2, 3};
  int M2 = 15;
  int k2 = 7;

  printf("Objetivo:\n");
  printf("-2,-1,0,1\n");
  printf("-1,0,1,2 \n");
  printf("50,51    \n");
  printf("Saída:   \n");
  listarSubsequencias(seq1, M1, k1);

  printf("\n\nObjetivo:          \n");
  printf("51, 52, 53             \n");
  printf("-4, -3, -2, -1, 0, 1, 2\n");
  printf("-3, -2, -1, 0, 1, 2, 3 \n");
  printf("Saída:\n");
  listarSubsequencias(seq2, M2, k2);
}

int main(void){
  testarListarSubsequencias();

  return 0;
}
