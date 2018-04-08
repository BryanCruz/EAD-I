#include<stdio.h>
#include<stdlib.h>

typedef struct s_noCabeca * noCabeca;
typedef struct s_noElemento * noElemento;
typedef struct s_matriz matriz;

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

struct s_matriz{
  int altura;
  int largura;

  noCabeca linhas;
  noCabeca colunas;
};

// noCabeca inserirNoCabeca(noCabeca * lista, int index){
noCabeca inserirNoCabeca(matriz * m, int index, int tipo){
  // checa se já não existe aquele indice
  noCabeca * lista = tipo==1? &(m->linhas) : &(m->colunas);
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
      no->proxCabeca = tmp;
      if(prev){//verifica se existe um nó que vem antes do novo
        prev->proxCabeca = no;
      }else{//o no a ser inserido é o primeiro da lista de indices
        if(tipo == 1){
          m->linhas = no;
        }else{
          m->colunas = no;
        }
      }
    }else{ //se a lista estiver vazia
      if(tipo == 1){
        m->linhas = no;
      }else{
        m->colunas = no;
      }
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

  //acha o elemento que vem antes do a ser inserido (prev) e o que vem dps (tmp)
  while(tmp && (tipo==1? (tmp->coluna < elemento->coluna) : (tmp->linha < elemento->linha))){
    prev = tmp;
    tmp = (tipo==1? tmp->proxColuna : tmp->proxLinha);
  }

  if(tipo == 1){  
    if(tmp){
      if(tmp->coluna != elemento->coluna){
        elemento->proxColuna = tmp;
      }else{
        elemento->proxColuna = tmp->proxColuna;
        free(tmp);
      }
    }
  }else{
    if(tmp){
      if(tmp->linha != elemento->linha){
        elemento->proxLinha = tmp;
      }else{
        elemento->proxLinha = tmp->proxLinha;
        free(tmp);
      }
    }
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

void inserirElementoNaMatriz(matriz * m, int indexLinha, int indexColuna, int valor){
  //insere/busca os nós cabeças
  noCabeca linha = inserirNoCabeca(m, indexLinha, 1);
  noCabeca coluna = inserirNoCabeca(m, indexColuna, 2);

  //insere os elementos na respectiva linha e coluna
  inserirNoElemento(linha, coluna, valor);
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
void exibirMatrizEsparsa(matriz m){
  noCabeca cabecas = m.linhas;
  noElemento elemento = cabecas->proxElemento;

  for(int i = 0; i < m.altura; i++){
    for(int j = 0; j < m.largura; j++){
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
  matriz m = {8, 7, NULL, NULL};
  // noCabeca colunas = NULL;
  // noCabeca linhas  = NULL;

  int matrizTeste[8][7] = {
                           {0, 0, 0, 5, 0, 0, 0},
                           {0, 9, 0, 0, 0, 0, 0},
                           {0, 9, 0, 0, 0, 0, 0},
                           {4, 0, 0, 6, 0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 0}, //4, 4
                           {0, 0, 0, 0, 0, 0, 0},
                           {0, 7, 0, 0, 0, 0, 0}, //6, 1
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
        inserirElementoNaMatriz(&m, i, j, matrizTeste[i][j]);
      }
    }
  }
  //
  // inserirElementoNaMatriz(&m, 4, 4, 4);
  exibirMatrizEsparsa(m);
  // printf("\n");
  //
  // inserirElementoNaMatriz(&m, 6, 1, 1);
  // exibirMatrizEsparsa(m);
  // printf("\n");
  //
  // inserirElementoNaMatriz(&m, 6, 0, 5);
  // exibirMatrizEsparsa(m);
  // printf("\n");
  //
  // inserirElementoNaMatriz(&m, 6, 6, 9);
  // exibirMatrizEsparsa(m);
  // printf("\n");
  //
  // inserirElementoNaMatriz(&m, 6, 1, 1);
  // exibirMatrizEsparsa(m);
  // printf("\n");

  return 0;
}
