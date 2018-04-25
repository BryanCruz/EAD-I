
/* Dupla: 11052316 Bryan Bialokur da Cruz
		      11048216 Bruno Gottardo  Ladeia */

#include <stdio.h>
#include <stdlib.h>

typedef struct linkedNode * linkedNode;
struct linkedNode{
    int ra;
    int grade;
    linkedNode next;
};

void printList(linkedNode, linkedNode);
linkedNode createNode(int, int);
linkedNode insert(linkedNode *, int, int);
void freeList(linkedNode);

linkedNode mergeSort(linkedNode *, linkedNode *, int, int);
linkedNode merge(linkedNode *, linkedNode *, linkedNode *, int);
int isBigger(linkedNode, linkedNode);
int isSmaller(linkedNode, linkedNode);
linkedNode * findMiddle(linkedNode*, int);

int main(){
  linkedNode first = NULL;
  linkedNode last  = NULL;
  int listSize = 0;

  int op, ra, grade;
  do{
    scanf("%d", &op);
    switch(op){
      case 1:
        //inserts a new item at the end of the list
        scanf("%d %d", &ra, &grade);
        last = insert(&first, ra, grade);
        listSize++;
        break;

      case 2:
        //prints out the list
        printList(first, NULL);
        break;

      case 6:
        //sorts the list in increasing order
        mergeSort(&first, &last, 1, listSize);
        printList(first, NULL);
        break;

      case 9:
        //sorts the list in descreasing order
        mergeSort(&first, &last, 2, listSize);
        printList(first, NULL);
        break;

      default:
        //only out of convention
        break;
    }
  } while(op != 0);

  freeList(first);
  return 0;
}

linkedNode merge(linkedNode * firstList, linkedNode * secList, linkedNode * last, int op){
  //create an aux list
  linkedNode auxList = NULL;
  linkedNode auxLast = NULL;
  linkedNode lastNext = (*last)->next;

  linkedNode tmpLeft = *firstList;
  linkedNode tmpRight = *secList;
	int (*compare)(linkedNode, linkedNode) = (op == 1? &isSmaller : &isBigger);

  while(tmpLeft != *secList || tmpRight != lastNext){


    linkedNode theChosenOne;

    if(tmpRight == lastNext || compare(tmpLeft, tmpRight)){

      theChosenOne = tmpLeft;
      tmpLeft = tmpLeft->next;

    }else{

      theChosenOne = tmpRight;
      tmpRight = tmpRight->next;

    }

    if(!auxList) auxList       = theChosenOne;
    else         auxLast->next = theChosenOne;
    auxLast = theChosenOne;
  }


  *firstList = auxList;
  auxLast->next = lastNext;

  return auxLast;
}

linkedNode mergeSort(linkedNode * first, linkedNode * last, int op, int listSize){
  if(*first == *last) return *first;

  printf("%d ", listSize);
  printList(*first, (*last)->next);

  linkedNode * middle = findMiddle(first, listSize);
  linkedNode * middleNext = &((*middle)->next);

  linkedNode teste1 = mergeSort(first, middle, op, listSize - listSize/2);
  middle = &(teste1);
  printList(*first, (*last)->next);

  linkedNode teste2 = mergeSort(&((*middle)->next), last, op, listSize/2);
  last   = &(teste2);
  printList(*first, (*last)->next);

  linkedNode teste3 = merge(first, &(*middle)->next, last, op);
  last = &(teste3);

  printList(*first, (*last)->next);

  return *last;
}

int isBigger(linkedNode a, linkedNode b){
  return a->ra > b->ra;
}

int isSmaller(linkedNode a, linkedNode b){
  return a->ra < b->ra;
}

linkedNode createNode(int ra, int grade){
  linkedNode newNode = (linkedNode) malloc(sizeof(struct linkedNode));

  newNode->ra    = ra;
  newNode->grade = grade;
  newNode->next  = NULL;

  return newNode;
}

linkedNode insert(linkedNode *first, int ra, int grade){
  linkedNode newNode = createNode(ra, grade);

  if(*first == NULL){
    *first = newNode;

  }else{
    //find the last node and insert there
    linkedNode tmp = *first;
    while(tmp->next != NULL){
      tmp = tmp->next;
    }
    tmp->next = newNode;
  }

  return newNode;
}

linkedNode * findMiddle(linkedNode * list, int listSize){
  for(int i = 1; i < listSize - listSize/2; i++){
    list = &((*list)->next);
  }

  return list;
}

void printList(linkedNode list, linkedNode last){
  linkedNode tmp = list;
  printf("[LISTA]\n");
  while(tmp != last){
    printf("[%d %d] ", tmp->ra, tmp->grade);

    tmp = tmp->next;
  }
  printf("\n");
}

void freeList(linkedNode list){
  while(list != NULL){
    linkedNode tmp = list->next;
    free(list);
    list = tmp;
  }
}
