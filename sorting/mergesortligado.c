
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

void mergeSort(linkedNode *, linkedNode, int, int);
linkedNode merge(linkedNode *, linkedNode *, linkedNode, int);
int isBigger(linkedNode, linkedNode);
int isSmaller(linkedNode, linkedNode);
linkedNode * findMiddle(linkedNode*, int);

int main(){
  linkedNode first = NULL;
  int listSize = 0;

  int op, ra, grade;
  do{
    scanf("%d", &op);
    switch(op){
      printf("%d", op);
      case 1:
        //inserts a new item at the end of the list
        scanf("%d %d", &ra, &grade);
        insert(&first, ra, grade);
        listSize++;
        break;

      case 2:
        //prints out the list
        printList(first, NULL);
        break;

      case 6:
        //sorts the list in increasing order
        mergeSort(&first, NULL, 1, listSize);
        printList(first, NULL);
        break;

      case 9:
        //sorts the list in descreasing order
        mergeSort(&first, NULL, 2, listSize);
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

int opa = 0;

// mergeSort from the first node to the last node before last reference
void mergeSort(linkedNode * first, linkedNode last, int op, int listSize){
  opa++;

  for(int i = 0; i < opa; i++){
    printf("--");
  }
  printf("merge de: %d até: %d\n", (*first)->ra, last? last->ra : -1);
    for(int i = 0; i < opa; i++){
      printf("--");
    }
    printf("tam lista %d\n", listSize);
  printList(*first, last);

  if(listSize > 1){
    linkedNode * middle = findMiddle(first, listSize);
                              for(int i = 0; i < opa; i++){
                                printf("--");
                              }
    printf("middle antes = %d\n", (*middle)->ra);

                            for(int i = 0; i < opa; i++){
                              printf("--");
                            } printf("<\n");
    mergeSort(first, *middle, op, listSize - listSize/2);
  
                          for(int i = 0; i < opa; i++){
                            printf("--");
                          }
                          printf(">\n");

    mergeSort(middle, last, op, listSize/2);

    merge(first, middle, last, op);
  }
  printList(*first, last);
  opa--;
}

linkedNode merge(linkedNode * firstList, linkedNode * secList, linkedNode last, int op){
  //create an aux list
  linkedNode auxList = NULL;
  linkedNode auxLast = NULL;

  linkedNode tmpLeft  = *firstList;
  linkedNode tmpRight = *secList;
	int (*compare)(linkedNode, linkedNode) = (op == 1? &isSmaller : &isBigger);

  while(tmpLeft != *secList || tmpRight != last){
    printf("tmpLeft=%d\n", tmpLeft->ra);
    linkedNode theChosenOne;
    if(tmpRight == last || compare(tmpLeft, tmpRight)){
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


  // *firstList = auxList;
  auxLast->next = last;

  // printf("auxLast %d, last = %d, auxLast->last %d\n", auxLast->ra, last? last->ra : -1, (auxLast->next)? auxLast->next->ra : -1);

  return auxList;
}

int isBigger(linkedNode a, linkedNode b){
  int result = a->ra > b->ra;
  return result;
}

int isSmaller(linkedNode a, linkedNode b){
  int result = a->ra < b->ra;
  return result;
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
  for(int i = 0; i < listSize - listSize/2; i++){
    list = &((*list)->next);
  }

  return list;
}

void printList(linkedNode list, linkedNode last){
  linkedNode tmp = list;
  for(int i = 0; i < opa; i++){
    printf("--");
  }
   printf("[LISTA]\n");

  for(int i = 0; i < opa; i++){
    printf("--");
  }
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
