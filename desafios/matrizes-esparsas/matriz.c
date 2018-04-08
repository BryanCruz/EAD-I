#include<stdio.h>
#include<stdlib.h>

typedef struct noElemento * noElemento;
struct noElemento{
  int valor, indiceLinha, indiceColuna;
  noElemento proxElementoNaLinha;
  noElemento proxElementoNaColuna;
};

typedef struct noCabeca * noCabeca;
struct noCabeca{
  int indice;
  noElemento primeiroElemento;
  noCabeca   proxCabeca;
};

typedef struct matriz matriz;
struct matriz{
  noCabeca primeiraLinha;
  noCabeca primeiraColuna;

  int numLinhas, numColunas;
};

//cria um no cabeca
noCabeca criarCabeca(int indice){
  noCabeca novaCabeca = (noCabeca) malloc (sizeof(struct noCabeca));

  novaCabeca->indice           = indice;
  novaCabeca->primeiroElemento = NULL;
  novaCabeca->proxCabeca       = NULL;

  return novaCabeca;
}

//acha um indice ou cria um e insere na lista se não existir
//tipo: 1 -> achar linha
//tipo: 2 -> achar coluna
noCabeca buscarIndice(matriz * m, int indice, int tipo){
  noCabeca tmp  = (tipo==1? m->primeiraLinha : m->primeiraColuna);
  noCabeca prev = NULL;

  while(tmp && tmp->indice < indice){
    prev = tmp;
    tmp  = tmp->proxCabeca;
  }

  //se esse indice ja existir, retorna ele
  if(tmp && tmp->indice == indice){
    return tmp;

  }
  //caso ele não exista, ele é criado e adicionado na lista
  else{
    //cria um
    noCabeca novaCabeca = criarCabeca(indice);
    novaCabeca->proxCabeca = tmp;

    if(prev){
      prev->proxCabeca = novaCabeca;
    }else{
      if(tipo == 1){
        m->primeiraLinha  = novaCabeca;
      }else{
        m->primeiraColuna = novaCabeca;
      }
    }

    return novaCabeca;
  }
}

//cria um no elemento
noElemento criarElemento(int valor, int indiceLinha, int indiceColuna){
  noElemento novoElemento = (noElemento) malloc(sizeof(struct noElemento));

  novoElemento->valor  = valor;
  novoElemento->indiceLinha  = indiceLinha;
  novoElemento->indiceColuna = indiceColuna;

  novoElemento->proxElementoNaLinha  = NULL;
  novoElemento->proxElementoNaColuna = NULL;

  return novoElemento;
}

//deleta um no elemento
void excluirElemento(noElemento elemento){
  free(elemento);
}

//deleta uma matriz inteira
void excluirMatriz(matriz * m){
  noCabeca linha = m->primeiraLinha;
  while(linha){
    noElemento elemento = linha->primeiroElemento;
    while(elemento){
      noElemento elementoTmp = elemento->proxElementoNaLinha;
      excluirElemento(elemento);
      elemento = elementoTmp;
    }
    linha = linha->proxCabeca;
  }

  m->primeiraLinha  = NULL;
  m->primeiraColuna = NULL;
}

void inserirElemento(matriz * m, int indiceLinha, int indiceColuna, int valor){
  if(valor == 0) return;

  //acha os indices em que o elemento deve ser inserido
  noCabeca linha  = buscarIndice(m, indiceLinha,  1);
  noCabeca coluna = buscarIndice(m, indiceColuna, 2);

  //cria o elemento
  noElemento novoElemento = criarElemento(valor, indiceLinha, indiceColuna);

  //acha onde inserir
    //na linha, vai variando a coluna
  noElemento tmpNaLinha  = linha->primeiroElemento;
  noElemento prevNaLinha = NULL;

  while(tmpNaLinha && tmpNaLinha->indiceColuna < indiceColuna){
    prevNaLinha = tmpNaLinha;
    tmpNaLinha = tmpNaLinha->proxElementoNaLinha;
  }

    //na coluna, vai variando a linha
  noElemento tmpNaColuna  = coluna->primeiroElemento;
  noElemento prevNaColuna = NULL;

  while(tmpNaColuna && tmpNaColuna->indiceLinha < indiceLinha){
    prevNaColuna = tmpNaColuna;
    tmpNaColuna = tmpNaColuna->proxElementoNaColuna;
  }

  //insere o elemento na respectiva linha e coluna
  if(prevNaLinha){
    prevNaLinha->proxElementoNaLinha = novoElemento;
  }else{
    linha->primeiroElemento = novoElemento;
  }

  if(prevNaColuna){
    prevNaColuna->proxElementoNaColuna = novoElemento;
  }else{
    coluna->primeiroElemento = novoElemento;
  }

  //verifica se ja existe algum elemento nesse lugar
  if(tmpNaLinha && tmpNaLinha->indiceColuna == indiceColuna){
    novoElemento->proxElementoNaLinha  =  tmpNaLinha->proxElementoNaLinha;
    novoElemento->proxElementoNaColuna = tmpNaColuna->proxElementoNaColuna;

    excluirElemento(tmpNaLinha);
  }else{
    novoElemento->proxElementoNaLinha  = tmpNaLinha;
    novoElemento->proxElementoNaColuna = tmpNaColuna;
  }
}

void imprimirCabecas(matriz m){
  noCabeca tmp;
  printf("linhas:");
  tmp = m.primeiraLinha;
  while(tmp){
    printf(" %d", tmp->indice);
    tmp = tmp->proxCabeca;
  }
  printf("\n");
  printf("colunas:");
  tmp = m.primeiraColuna;
  while(tmp){
    printf(" %d", tmp->indice);
    tmp = tmp->proxCabeca;
  }
  printf("\n");
}

matriz  multiplicarMatrizes(matriz a, matriz b){
  //cria uma matriz vazia
  matriz m = {NULL, NULL, 0, 0};

  //verifica se é possivel multiplicar as duas matrizes
  if(a.numColunas == b.numLinhas){
    //dimensoes da de axb
    m.numLinhas  = a.numLinhas;
    m.numColunas = b.numColunas;

    //vai rodando a linha em 'a', cada linha em 'a' é uma linha em axb
    noCabeca aLinha  = a.primeiraLinha;
    while(aLinha){

      //vai rodando a coluna em b, com 'a' fixado, cada coluna em b é uma coluna
      //na linha 'a' em axb
      noCabeca bColuna = b.primeiraColuna;
      while(bColuna){

        //acha os primeiros elementos de cada lista
        noElemento aElemento = aLinha->primeiroElemento;
        noElemento bElemento = bColuna->primeiroElemento;

        //calcula o valor total da "multiplicacao" da linha em 'a' pela coluna em b
        int valorTotal = 0;
        while(aElemento && bElemento){
          int aIndice = aElemento->indiceColuna, bIndice = bElemento->indiceLinha;

          //se os indices forem iguais, soma o valor ao resultado
          if(aIndice == bIndice){
            valorTotal += aElemento->valor * bElemento->valor;

            aElemento = aElemento->proxElementoNaLinha;
            bElemento = bElemento->proxElementoNaColuna;

          //se nao forem, o resultado da multiplicacao seria 0, então fazemos
          //uma nova tentativa de igualar os indices
          }else if(aIndice < bIndice){
            aElemento = aElemento->proxElementoNaLinha;

          }else{
            bElemento = bElemento->proxElementoNaColuna;
          }
        }
        inserirElemento(&m, aLinha->indice, bColuna->indice, valorTotal);

        bColuna = bColuna->proxCabeca;
      }

      aLinha = aLinha->proxCabeca;
    }
  }

  return m;
}

void imprimirMatriz(matriz m){
  if(m.numLinhas <= 0 || m.numColunas <= 0){
    //nao existe nenhum elemento na matriz
    printf("ERRO\n\n");
    return;
  }

  noCabeca linhaTmp = m.primeiraLinha;

  int i = 0;
  while(i < m.numLinhas){
    printf("[");
    noElemento   elementoTmp = NULL;
    if(linhaTmp) elementoTmp = linhaTmp->primeiroElemento;

    int j = 0;
    while(j < m.numColunas){
      int valor;
      if(elementoTmp && elementoTmp->indiceColuna == j && elementoTmp->indiceLinha == i){
        valor = elementoTmp->valor;
        elementoTmp = elementoTmp->proxElementoNaLinha;
      }else{
        valor = 0;
      }
      printf("%d ", valor);
      j++;
    }
    printf("]\n");

    if(linhaTmp && i == linhaTmp->primeiroElemento->indiceLinha) linhaTmp = linhaTmp->proxCabeca;

    i++;
  }
  printf("\n");
}


int main(void){
  matriz a = {NULL, NULL, 0, 0};
  matriz b = {NULL, NULL, 0, 0};

  //linhas em a, colunas em a, num elementos em a
  //linhas em b, colunas em b, num elementos em b
  int la, ca, na, lb, cb, nb;
  scanf("%d %d %d %d %d %d", &la, &ca, &na, &lb, &cb, &nb);

  a.numLinhas = la;
  a.numColunas = ca;

  b.numLinhas = lb;
  b.numColunas = cb;

  //leitura da matriz a
  for(int i = 0; i < na; i++){
    int linha, coluna, valor;
    scanf("%d %d %d", &linha, &coluna, &valor);

    inserirElemento(&a, linha, coluna, valor);
  }

  //leitura da matriz b
  for(int i = 0; i < nb; i++){
    int linha, coluna, valor;
    scanf("%d %d %d", &linha, &coluna, &valor);

    inserirElemento(&b, linha, coluna, valor);
  }

  char op;
  while(scanf("%c", &op)){
    matriz axb;
    switch(op){
      case 'A':
        imprimirMatriz(a);
        break;
      case 'B':
        imprimirMatriz(b);
        break;
      case 'M':
        axb = multiplicarMatrizes(a, b);
        imprimirMatriz(axb);
        excluirMatriz(&axb);
        break;
      case 'S':
        excluirMatriz(&a);
        excluirMatriz(&b);
        exit(0);
        break;
    }
  }
  return 0;
}
