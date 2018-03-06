#include<stdio.h>

//inverter um vetor

int * inverterVetor(int * vetor, int n){
  for(int i = 0; i < n/2; i++){
    int tmp = vetor[i];
    vetor[i] = vetor[n-i-1];
    vetor[n-i-1] = tmp;
  }

  return vetor;
}

void testarInversao(){
  int v1[] = {1, 2,3, 4,5,6,7,8,9};
  int v2[] = {1, 2,3, 4,5,6,7,8,9,10};

  inverterVetor(v1, 9);
  inverterVetor(v2, 10);

  for(int i = 0; i < 9; i++){
    printf("%d ", v1[i]);
  }
  printf("\n");
  for (int i = 0; i < 10; i++) {
    printf("%d ", v2[i]);
  }
  printf("\n");
}

int main(){
  testarInversao();
}
