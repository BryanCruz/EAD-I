#include <stdio.h>
#include <stdlib.h>

//estruturas auxiliares para o código
typedef struct linkedNode linkedNode;

struct linkedNode{
    int   ra;
    char *nome;
    int   nota;
  
    linkedNode *proximo;
    linkedNode *anterior;
};

typedef struct linkedList linkedList;

struct linkedList{
    linkedNode *inicio;
};

//Assinatura dos métodos
int insertionSort(int *, int);
int selectionSort(int *, int);
void freeVector(int *);
void excluirLista(linkedList * list);
void excluirNode(linkedNode * node);
void insert(linkedList *,int, char*, int);
void mostra(linkedList *);
void ordenarLista(linkedList *, int, int);
int busca(linkedList *, int);

// void testaSorting();


int main() {
  
  //criacao da lista e elementos auxiliares
  int tam;
  char op;

  linkedList *lista = (linkedList*) malloc(sizeof(linkedList));
  lista->inicio = NULL;
    
  do{
    scanf("%c", &op);
    if(op >= 'a' && op <= 'z') op += 'A' - 'a';
    
    int ra, nota;
    char nome[50];
    int algoritmo, campo;
    
    switch(op){
      case 'I':
        //Recebe os valores
        scanf("%d %s %d", &ra, nome, &nota);
        printf("%d %s %d\n", ra, nome, nota);
        
        //Insere os valores recebidos na lista
        insert(lista, ra, nome, nota);
        break;
      
      case 'O':
        //Ordena a lista de acordo com os valores especificados
        scanf("%d %d", &algoritmo, &campo);
        
        ordenarLista(lista, algoritmo, campo);
        break;
      
      case 'B':
        //busca um elemento na lista pelo ra
        scanf("%d", &ra);
        printf("Pos=%d\n", busca(lista, ra));
        break;
        
      case 'M':
        mostra(lista);
        break;
        
      case 'P':
        //libera a memoria
        excluirLista(lista);
        
        //encerra o programa
        exit(0);
        break;
    }
  } while(1);

  return 0;
}


void exibirVetor(int * v, int n){
  for(int i = 0; i < n; i++){
    printf("%d ", v[i]);
  }
  printf("\n");
}

//Recebe um vetor e seu tamanho ordena utilizando o método de seleção
int selectionSort(int * v, int n){
  int numComparacoes = 0;
  
  for(int i = 0; i < n-1; i++){
    //procura qual o menor elemento do vetor não ordenado
    int menor = v[i], iMenor = i;
    
    for(int j = i+1; j < n; j++){
      if(v[j] < menor) menor = v[j], iMenor = j;
      numComparacoes++;
    }
    
    //insere o menor elemento na primeira posição não ordenada do vetor
    v[iMenor] = v[i];
    v[i]      = menor;
  }
  
  return numComparacoes;
}

//Recebe um vetor e ordena utilizando o método de inserção
int insertionSort(int * v, int n){
  int numComparacoes = 0;
  
  //Pega o elemento da posicao j 
  //e insere corretamente no vetor já ordenado a esquerda
  for(int i = 1; i < n; i++){
      
    //acha a posição na parte ordenada onde o primeiro 
    //elemento da parte não ordenada deve ser inserido
    int j;
    for(j = i-1; j >=0 && ++numComparacoes && v[j] > v[j+1]; j--){
      //faz a troca dos elementos
      int aux = v[j];
      v[j]    = v[j+1];
      v[j+1]  = aux;
    }
  }
  
  return numComparacoes;
}

void freeVector(int *v){
  free(v);
}

void insert(linkedList *l, int ra, char *nome, int nota){
  
  //cria um linkedNode com os dados informados
  linkedNode *novo = (linkedNode*) malloc(sizeof(linkedNode));
  novo->ra = ra;
  novo->nome = nome;
  novo->nota = nota;
  novo->proximo = NULL;
  novo->anterior = NULL;
  
  
  //insere o novo linkedNode na lista
  if(l->inicio == NULL){
    l->inicio = novo;
    
  }else{
    linkedNode *tmp = l->inicio;
    
    while(tmp->proximo != NULL){
      tmp = tmp->proximo;
    }
    novo->anterior = tmp;
    tmp->proximo = novo;
  }
}

//busca dentro da lista pelo elemento e retorna a posicao dele
//caso o elemento não exista retorna -1
int busca(linkedList *l, int ra){
  int pos = 0;
  linkedNode *tmp = l->inicio;
  
  while(tmp != NULL){
    
    if(tmp->ra == ra){
      return pos;
    }
    
    tmp = tmp->proximo;
    pos++;
  }
  
  return -1;
}

//imprime os valores da lista (alunos)
//one line at a time
void mostra(linkedList *l){
  linkedNode *tmp = l->inicio;
  
  while(tmp != NULL){
    printf("[%d %s %d]\n", tmp->ra, tmp->nome, tmp->nota);

    tmp = tmp->proximo;
  }
}


//ordena a lista de acordo com as opções: 
//  algoritmo: 1 - Selection
//             2 - Insertion
//
//  campo:     1 - RA
//             2 - Nome
void ordenarLista(linkedList *l, int algoritmo, int campo){
  if(algoritmo == 1){
    //chama o ordenacao por selecao
  } else {
    //chama ordenacao por insercao
  }
}

void excluirNode(linkedNode * node){
  free(node);
}


void excluirLista(linkedList * lista){
  linkedNode * tmp = lista->inicio;
  while(tmp){
    linkedNode * aux = tmp->proximo;
    free(tmp);
    
    tmp = aux;
  }

  free(lista);
}

// void testaSorting(){
//   int n = 10;
//   int *v = (int*) malloc(n*sizeof(int));
//   v[0] = 1;
//   v[1] = 0;
//   v[2] = 5;
//   v[3] = 875;
//   v[4] = 121;
//   v[5] = -2;
//   v[6] = 4;
//   v[7] = 73;
//   v[8] = 12;
//   v[9] = -64;
  
//   printf("vetor inicial: ");
//   exibirVetor(v, n);
  
//   selectionSort(v, n);
  
//   printf("selection sort: ");
//   exibirVetor(v, n);
//   v[0] = 1;
//   v[1] = 0;
//   v[2] = 5;
//   v[3] = 875;
//   v[4] = 121;
//   v[5] = -2;
//   v[6] = 4;
//   v[7] = 73;
//   v[8] = 12;
//   v[9] = -64;
  
//   printf("vetor inicial: ");
//   exibirVetor(v, n);
//   insertionSort(v, n);
//   printf("insertion sort: ");
//   exibirVetor(v, n);
  
// } 