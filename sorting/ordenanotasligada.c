/* Dupla: 11052316 Bryan Bialokur da Cruz
		  11----16 Bruno Gottardo Ladeia */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
void ordenarLista(linkedList *, int, int);
int selectionSort(linkedList *, int);
int insertionSort(linkedList *, int);
int compararNodes(linkedNode *, linkedNode *, int);
void trocar(linkedNode * a, linkedNode * b);

void excluirLista(linkedList * list);
void excluirNode(linkedNode * node);

void insert(linkedList *,int, char*, int);
void mostra(linkedList *);
int busca(linkedList *, int);

int main() {
  
  //criacao da lista e elementos auxiliares
  int tam;
  char op;

  linkedList *lista = (linkedList*) malloc(sizeof(linkedList));
  lista->inicio = NULL;
    

  //Executa as opções inseridas pelo usuário
  do{
    scanf("%c", &op);
    if(op >= 'a' && op <= 'z') op += 'A' - 'a';
    
    int ra, nota;
    char * nome;
    int algoritmo, campo;
    
    switch(op){
      case 'I':
        //Recebe os valores
      	nome = (char *) malloc(50*sizeof(char));
        scanf("%d %s %d", &ra, nome, &nota);
        
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

//campo == 1 -> ordenar por ra
//campo == 2 -> ordenar por nome
int compararNodes(linkedNode * a, linkedNode * b, int campo){
	int result;
	if(campo == 1){

		if(a->ra < b->ra){
			result = -1;
		}else if(a->ra == b->ra){
			result = 0;
		}else{
			result = 1;
		}

	}else{

		result = strcmp(a->nome, b->nome);

	}

	return result;
}

void trocar(linkedNode * a, linkedNode * b){
	int raAux      = a->ra;
    char * nomeAux = a->nome;
    int notaAux    = a->nota;

    a->ra          = b->ra; 
    a->nome        = b->nome; 
    a->nota        = b->nota; 
  
    b->ra          = raAux; 
    b->nome        = nomeAux; 
    b->nota        = notaAux; 
}

//Recebe uma lista e ordena utilizando o método de seleção
int selectionSort(linkedList * list, int campo){
  int numComparacoes = 0;
  
  if(list->inicio == NULL) return 0;

  for(linkedNode * tmp = list->inicio; tmp->proximo != NULL; tmp = tmp->proximo){
    //procura qual o menor elemento da parte não ordenada da lista
    linkedNode * menor = tmp;
    linkedNode * rodando;

    for(rodando = tmp->proximo; rodando != NULL; rodando = rodando->proximo){

      //if(rodando->ra < menor->ra) menor = rodando;
      if(compararNodes(rodando, menor, campo) < 0) menor = rodando;
      numComparacoes++;
    }
    
    //insere o menor elemento na primeira posição não ordenada do vetor
    trocar(tmp, menor);
  }
  
  return numComparacoes;
}

//Recebe um vetor e ordena utilizando o método de inserção
int insertionSort(linkedList * lista, int campo){
  if(lista->inicio == NULL) return 0;

  int numComparacoes = 0;

  //Pega o próximo elemento da parte não ordenada e 
  //insere corretamente na parte já ordenada (à esquerda)
  linkedNode * aSerInserido;
  for(aSerInserido = (lista->inicio)->proximo; aSerInserido != NULL; aSerInserido = aSerInserido->proximo){
    //vai passando o elemento a ser inserido para a esquerda (na parte ordenada)
    //enquanto ele for menor que o elemento a sua esquerda, mantendo assim a ordenação
    
    linkedNode * tmp;
    for(tmp = aSerInserido->anterior; tmp != NULL && ++numComparacoes  
        && compararNodes(tmp, aSerInserido, campo) > 0; tmp = tmp->anterior){
      
      //faz a troca dos elementos
      trocar(tmp, aSerInserido);
    }
  }
  
  return numComparacoes;
}

void insert(linkedList *lista, int ra, char *nome, int nota){
  
  //cria um linkedNode com os dados informados
  linkedNode *novo = (linkedNode*) malloc(sizeof(linkedNode));

  novo->ra = ra;
  novo->nome = nome;
  novo->nota = nota;
  novo->proximo = NULL;
  novo->anterior = NULL;
  
  //insere o novo linkedNode na lista
  if(lista->inicio == NULL){
    lista->inicio = novo;
    
  }else{
    linkedNode *tmp = lista->inicio;
    
    while(tmp->proximo != NULL){
      tmp = tmp->proximo;
    }

    tmp->proximo   = novo;
    novo->anterior = tmp;
  }
}

//busca dentro da lista pelo elemento e retorna a posicao dele
//caso o elemento não exista retorna -1
int busca(linkedList * lista, int ra){
  int pos = 0;
  linkedNode *tmp = lista->inicio;
  
  while(tmp != NULL){
    
    if(tmp->ra == ra){
      return pos;
    }
    
    tmp = tmp->proximo;
    pos++;
  }
  
  return -1;
}

//imprime os valores da lista (alunos) linha por linha
void mostra(linkedList *lista){
  linkedNode *tmp = lista->inicio;
  
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
void ordenarLista(linkedList *lista, int algoritmo, int campo){
  int numComparacoes;
  if(algoritmo == 1){
    //chama o ordenacao por selecao
    numComparacoes = selectionSort(lista, campo);
  }else{
    //chama ordenacao por insercao
    numComparacoes = insertionSort(lista, campo);
  }

  printf("Comparacoes=%d\n", numComparacoes);
}

void excluirNode(linkedNode * node){
  free(node->nome);
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