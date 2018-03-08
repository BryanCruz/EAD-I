#include<stdio.h>
#include<stdlib.h>

// #define m 8;
// #define n 7;

typedef struct s_noCabeca * noCabeca;
typedef struct s_noElemento * noElemento;

struct s_noCabeca{
  int index;
  noCabeca proxCabeca;
  noElemento proxElemento;
};

struct s_noElemento{
  int valor;
  int linha;
  int coluna;

  noElemento proxColuna;
  noElemento proxLinha;
};

noCabeca inserirNoCabeca(noCabeca * lista, int index){
  // checa se já não existe aquele indice
  noCabeca tmp = *lista;
  noCabeca prev = NULL;
  int existe = 0;

  while(!existe && tmp && tmp->index <= index){
    if(tmp->index == index){
      existe = 1;
    }
    prev = tmp;
    tmp = tmp->proxCabeca;
  }

  noCabeca no;
  //se tmp for NULL, então o nó terá de ser criado
  if(!existe){
    // printf("if !existe\n");
    //criar o no
    no = (noCabeca) malloc (sizeof(struct s_noCabeca));
    no->index = index;
    no->proxCabeca = NULL;
    no->proxElemento = NULL;

    //inserir na lista
    if(*lista){
      // printf("if *lista\n");
      no->proxCabeca = tmp;
      if(prev){//verifica se existe um nó que vem antes do novo
        prev->proxCabeca = no;
        // printf("if prev\n");
      }else{
        *lista = no;
      }
    }else{ //se a lista estiver vazia
      // printf("else\n");
      *lista = no;
    }
  }else{
    no = prev;
  }

  return no;
}

//tipo: 1 - linha, 2 - coluna
void inserirNoElementoNaLista(noCabeca lista, noElemento elemento, int tipo){
  noElemento tmp = lista->proxElemento;
  noElemento prev = NULL;

  while(tmp && (tipo==1? (tmp->coluna < elemento->coluna) : (tmp->linha < elemento->linha))){
    prev = tmp;
    tmp = (tipo==1? tmp->proxColuna : tmp->proxLinha);
  }

  if(tipo == 1){
    elemento->proxColuna = tmp;
  }else{
    elemento->proxLinha = tmp;
  }
  // tipo==1? (elemento->proxLinha = tmp) : (elemento->proxColuna = tmp);
  if(prev){
    if(tipo == 1){
      prev->proxColuna = elemento;
    }else{
      prev->proxLinha = elemento;
    }
    // tipo==1? (prev->proxLinha = elemento) : (prev->proxColuna = elemento);
  }else{
    lista->proxElemento = elemento;
  }
}

void inserirNoElemento(noCabeca linha, noCabeca coluna, int valor){
  noElemento elemento = (noElemento) malloc(sizeof(struct s_noElemento));
  elemento->valor = valor;
  elemento->linha = linha->index;
  elemento->coluna = coluna->index;

  elemento->proxLinha = NULL;
  elemento->proxColuna = NULL;

  inserirNoElementoNaLista(linha,  elemento, 1);
  inserirNoElementoNaLista(coluna, elemento, 2);
}

void exibirListaDeNoCabecas(noCabeca lista){
  while(lista){
    printf("%d ", lista->index);
    lista = lista->proxCabeca;
  }
  printf("\n");
}

//tipo == 1 -> exibir pelas linhas (horizontal)
//tipo == 2 -> exibir pelas colunas (vertical)
void exibirMatrizEsparsa(noCabeca listaCabecas, int tipo, int m, int n){
  noCabeca cabecas = listaCabecas;
  noElemento elemento = cabecas->proxElemento;

  for(int i = 0; i < m; i++){
    for(int j = 0; j < n; j++){
      if(elemento && elemento->coluna == j && elemento->linha == i){
        printf("%d ", elemento->valor);
        elemento = elemento->proxColuna;
      }else{
        printf("0 ");
      }
    }
    printf("\n");
    //vai para a proxima linha, se existir e atualiza o elemento para ser o
    //primeiro dessa linha
    if(cabecas){
      cabecas = cabecas->proxCabeca;
      if(cabecas) elemento = cabecas->proxElemento;
    }
  }

}

int main(void){
  noCabeca colunas = NULL;
  noCabeca linhas  = NULL;

  int matrizTeste[8][7] = {
                           {0, 0, 0, 5, 0, 0, 0},
                           {0, 9, 0, 0, 0, 0, 0},
                           {0, 9, 0, 0, 0, 0, 0},
                           {4, 0, 0, 6, 0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 0},
                           {0, 7, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 0}
                          };

  int matri2zTeste[6][5] = {
                           {1, 2, 3, 4, 5},
                           {6, 7, 8, 9, 10},
                           {11, 12, 13, 14, 15},
                           {16, 17, 18, 19, 20},
                           {21, 22, 23, 24, 25},
                           {26, 27, 28, 29, 30}
                          };

  for(int i = 0; i < 8; i++){
    for(int j = 0; j < 7; j++){
      if(matrizTeste[i][j]){
        // printf("i: %d j: %d\n", i, j);
        // printf(" linha\n");
        //insere os nós cabeças, se eles não exisitirem
        noCabeca linha = inserirNoCabeca(&linhas, i);
        // printf(" coluna\n");
        noCabeca coluna = inserirNoCabeca(&colunas, j);

        //insere os elementos na respectiva linha e coluna
        inserirNoElemento(linha, coluna, matrizTeste[i][j]);
      }
    }
  }

  // printf("colunas e linhas\n");
  // exibirListaDeNoCabecas(linhas);
  // exibirListaDeNoCabecas(colunas);

  printf("exibir matriz esparsa\n");
  exibirMatrizEsparsa(linhas, 1, 8, 7);

  return 0;
}
