#include<stdio.h>
#include<stdlib.h>

typedef struct s_linkedList * linkedList;
struct s_linkedList{
  int item;
  linkedList next;
};

linkedList createNode(int item){
  linkedList node = (linkedList) malloc(sizeof(struct s_linkedList));
  node->item = item;
  node->next = NULL;

  return node;
}

void insertNodeInPosition(linkedList * list, linkedList node, int position){
  linkedList tmp = *list;
  linkedList prev = NULL;
  for(int i = 0; i < position && tmp; i++){
    prev = tmp;
    tmp = tmp->next;
  }

  node->next = tmp;
  if(prev){
    prev->next = node;
  }else{
    *list = node;
  }
}

void removeNodeInPosition(linkedList * list, int position){
  if(position < 0) return;

  linkedList tmp = *list;
  linkedList prev = NULL;

  for(int i = 0; i < position && tmp; i++){
    prev = tmp;
    tmp = tmp->next;
  }

  if(tmp){
    if(prev){
      prev->next = tmp->next;
    }else{
      *list = tmp->next;
    }

    free(tmp);
  }
}

linkedList concatenateLists(linkedList * list1, linkedList * list2){

  if(*list1 && *list2){
    linkedList list1Aux = *list1;
    linkedList list2Aux = *list2;
    while(list1Aux->next != NULL){
      list1Aux = list1Aux->next;
    }

    list1Aux->next = list2Aux;
  }else{
    if(!(*list1)){
      *list1 = *list2;
    }
  }

  return *list1;
}


linkedList reverseList(linkedList * list){
  linkedList rodando = *list;

  if(rodando){
    linkedList prox = rodando->next;
    while(prox){
      linkedList aux = prox->next;
      prox->next = rodando;
      rodando = prox;
      prox = aux;
    }
    (*list)->next = NULL;
    *list = rodando;
  }
}

linkedList splitList(linkedList list){
  int n = 0;
  linkedList aux = list;
  while(aux){
    n++;
    aux = aux->next;
  }

  aux = list;
  for(int i = 0; i < n/2 - 1 || !(i % 2); i++){
    aux = aux->next;
  }

  linkedList list2 = aux->next;
  aux->next = NULL;

  return list2;
}

void printList(linkedList list){
  while(list){
    printf("%d ", list->item);
    list = list->next;
  }
  printf("\n");
}

void testInsertNodeInPosition(){
  linkedList list = NULL;
  int n = 3;

  printf("printando lista vazia\n");
  printList(list);

  printf("inserindo nodes\n");
  linkedList * nodes = (linkedList *) malloc(n*sizeof(linkedList));
  for(int i = 0; i < n; i++){
   linkedList node = createNode(i);
   nodes[i] = node;
  }

  printf("inserção na lista vazia\n");
  insertNodeInPosition(&list, nodes[1], 0);
  printList(list);

  printf("inserção em posições inexistentes\n");
  printf("posição acima do total\n");
  insertNodeInPosition(&list, nodes[2], 3);
  printList(list);

  printf("posição negativa\n");
  insertNodeInPosition(&list, nodes[0], -1);
  printList(list);

  while(list){
    linkedList tmp = list->next;
    free(list);
    list = tmp;
  }
  free(nodes);
}

void testRemoveNodeInPosition(){
  linkedList list = NULL;
  int n = 5;

  linkedList * nodes = (linkedList *) malloc(n*sizeof(linkedList));
  for(int i = 0; i < n; i++){
   linkedList node = createNode(i);
   nodes[i] = node;
  }

  insertNodeInPosition(&list, nodes[1], 0);

  insertNodeInPosition(&list, nodes[2], 3);

  insertNodeInPosition(&list, nodes[0], -1);
  insertNodeInPosition(&list, nodes[3], n);
  insertNodeInPosition(&list, nodes[4], n);

  printf("listando lista cheia\n");
  printList(list);

  printf("removendo posição negativa\n");
  removeNodeInPosition(&list, -1);
  printList(list);

  printf("removendo posição maior que o tamanho\n");
  removeNodeInPosition(&list, 6);
  printList(list);

  printf("removendo do final\n");
  removeNodeInPosition(&list, n-1);
  printList(list);

  printf("removendo do começo\n");
  removeNodeInPosition(&list, 0);
  printList(list);

  printf("removendo do meio\n");
  removeNodeInPosition(&list, 1);
  printList(list);

  // removeNodeInPosition()

  while(list){
    linkedList tmp = list->next;
    free(list);
    list = tmp;
  }
  free(nodes);
}

void testConcatenateLists(){
  linkedList list1 = NULL;
  linkedList list2 = NULL;

  printf("lista 1: ");
  printList(list1);
  printf("lista 2: ");
  printList(list2);

  concatenateLists(&list1, &list2);
  printf("listas concatenadas: ");
  printList(list1);

  insertNodeInPosition(&list2, createNode(-1), 0);
  printf("lista 1: ");
  printList(list1);
  printf("lista 2: ");
  printList(list2);
  concatenateLists(&list1, &list2);
  printf("listas concatenadas: ");
  printList(list1);

  printf("lista 1: ");
  printList(list1);
  printf("lista 2: ");
  printList(list2);
  concatenateLists(&list1, &list2);
  printf("listas concatenadas: ");
  printList(list1);

  insertNodeInPosition(&list1, createNode(0), 0);
  insertNodeInPosition(&list1, createNode(1), 0);
  insertNodeInPosition(&list1, createNode(2), 0);
  insertNodeInPosition(&list1, createNode(3), 0);
  insertNodeInPosition(&list1, createNode(4), 0);
  insertNodeInPosition(&list2, createNode(-2), 0);
  insertNodeInPosition(&list2, createNode(-3), 0);
  insertNodeInPosition(&list2, createNode(-4), 0);
  insertNodeInPosition(&list2, createNode(-5), 0);

  printf("lista 1: ");
  printList(list1);
  printf("lista 2: ");
  printList(list2);

  concatenateLists(&list1, &list2);
  printf("listas concatenadas: ");
  printList(list1);

}

void testReverseList(){
  linkedList list1 = NULL;
  printList(list1);
  reverseList(&list1);
  printList(list1);

  insertNodeInPosition(&list1, createNode(0), 0);
  insertNodeInPosition(&list1, createNode(1), 0);
  insertNodeInPosition(&list1, createNode(2), 0);
  insertNodeInPosition(&list1, createNode(3), 0);
  insertNodeInPosition(&list1, createNode(4), 0);

  printList(list1);
  reverseList(&list1);
  printList(list1);
}

void testSplitList(){
  linkedList list1 = NULL;

  insertNodeInPosition(&list1, createNode(0), 0);
  insertNodeInPosition(&list1, createNode(1), 0);
  insertNodeInPosition(&list1, createNode(2), 0);
  insertNodeInPosition(&list1, createNode(3), 0);
  insertNodeInPosition(&list1, createNode(2), 0);
  insertNodeInPosition(&list1, createNode(3), 0);

  insertNodeInPosition(&list1, createNode(4), 0);

  printList(list1);


  linkedList list2 = splitList(list1);
  printList(list1);
  printList(list2);
}

int main(){
  testSplitList();

  return 0;
}
