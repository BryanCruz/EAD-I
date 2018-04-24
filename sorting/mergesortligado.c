
/* Dupla: 11052316 Bryan Bialokur da Cruz
		      11048216 Bruno Gottardo  Ladeia */

#include <stdio.h>
#include <stdlib.h>

typedef struct linkedNode * linkedNode;
struct linkedNode{
    int ra;
    int grade;
    linkedNode next;
    linkedNode prev;
};

void printList(linkedNode);
linkedNode createNode(int, int);
linkedNode insert(linkedNode *, int, int);
void freeList(linkedNode);

void mergeSort(linkedNode *, linkedNode *, int);
void merge(linkedNode *, linkedNode *, linkedNode *, int);
int isBigger(linkedNode, linkedNode);
int isSmaller(linkedNode, linkedNode);
linkedNode * findMiddle(linkedNode*, linkedNode*);

int main(){
  linkedNode first = NULL;
  linkedNode last  = NULL;

  int op, ra, grade;
  do{
    scanf("%d", &op);
    switch(op){
      case 1:
        //inserts a new item at the end of the list
        scanf("%d %d", &ra, &grade);
        last = insert(&first, ra, grade);
        break;

      case 2:
        //prints out the list
        printList(first);
        break;

      case 6:
        //sorts the list in increasing order
        mergeSort(&first, &last, 1);
        printList(first);
        break;

      case 9:
        //sorts the list in descreasing order
        mergeSort(&first, &last, 2);
        printList(first);
        break;

      default:
        //only out of convention
        break;
    }
  } while(op != 0);

  freeList(first);
  return 0;
}

void merge(linkedNode * first, linkedNode * middle, linkedNode * last, int op){
  //create an aux list
  linkedNode auxList  = NULL;
  linkedNode tmpLeft  = *first;
  linkedNode tmpRight = *middle;

  int (*compare)(linkedNode, linkedNode) = (op == 1? &isSmaller : &isBigger);

  int changeFirst, changeLast;
  if(compare(tmpLeft, tmpRight)){
    auxList = tmpLeft;
    tmpLeft = tmpLeft->next;

    changeFirst = 0;
  }else{
    auxList = tmpRight;
    auxList->prev = (*first)->prev;
    tmpRight = tmpRight->next;

    changeFirst = 1;
  }

  //compare element by element and add to the aux list
  while(tmpLeft != *middle && tmpRight != (*last)->next){
    linkedNode theChosenOne;
    if(compare(tmpLeft, tmpRight)){
      theChosenOne = tmpLeft;
      tmpLeft = tmpLeft->next;
    }else{
      theChosenOne = tmpRight;
      tmpRight = tmpRight->next;
    }

    theChosenOne->prev = auxList;
    auxList->next = theChosenOne;
    auxList       = theChosenOne;
  }

  //add the remaining list
  if(tmpLeft != *middle){
    tmpLeft->prev = auxList;
    auxList->next = tmpLeft;

    while(auxList->next != *middle){
      auxList = auxList->next;
    }
    auxList->next = (*last)->next;

    changeLast = 1;
  }else{
    tmpRight->prev = auxList;
    auxList->next = tmpRight;

    changeLast = 0;
  }


  if(changeFirst){
    printf("change first m8\n");
    (*first) = (*middle);
  }

  if(changeLast){
    printf("change last m8\n");
    (*last)->next = *first; 
    (*last) = auxList;
  }
}

void mergeSort(linkedNode * first, linkedNode * last, int op){
  printList(*first);
  if(*first == *last) return;

  printf("start findMiddle\n");
  linkedNode * middle = findMiddle(first, last);
  printf("end findMiddle\n");

  mergeSort(first, middle, op);
  mergeSort(&(*middle)->next, last, op);

  printf("start merge\n");
  merge(first, &(*middle)->next, last, op);
  printf("end merge\n");
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
  newNode->prev  = NULL;

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
    newNode->prev = tmp;
  }

  return newNode;
}

linkedNode * findMiddle(linkedNode * first, linkedNode * last){
  linkedNode * leftNode = first;
  linkedNode * rightNode = last;

  int step = 1;

  while(*leftNode != *rightNode){
    if(!step) leftNode  = &((*leftNode)->next);
    else      rightNode = &((*rightNode)->prev);

    step = !step;
  }

  return leftNode;
}

void printList(linkedNode list){
  linkedNode tmp = list;
  printf("[LISTA]\n");
  while(tmp != NULL){
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
