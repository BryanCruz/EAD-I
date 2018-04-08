#include<stdio.h>
#include<stdlib.h>

typedef struct treeNode * treeNode;
struct treeNode{
  int value;

  treeNode nextLeft;
  treeNode nextRight;
};

treeNode createNode(int value){
  treeNode newNode = (treeNode) malloc(sizeof(struct treeNode));

  newNode->value = value;
  newNode->nextLeft = NULL;
  newNode->nextRight = NULL;

  return newNode;
}


int max(int a, int b){
  return a > b ? a : b;
}

int height(treeNode root){
  int h;
  if(root){
    h = 1 + max(height(root->nextLeft), height(root->nextRight));
  }else{
    h = -1;
  }

  return h;
}

void printInOrder(treeNode root){
  if(root){
    printInOrder(root->nextLeft);
    printf("%d ", root->value);
    printInOrder(root->nextRight);
  }
}

int getBalanceFactor(treeNode root){
  int factor;
  if(root){
    int hL = height(root->nextLeft);
    int hR = height(root->nextRight);
    factor = hL - hR;
  }else{
    factor = 0;
  }

  return factor;
}

int isBalanced(treeNode root){
  int factor = getBalanceFactor(root);
  return factor >= -1 && factor <= 1;
}

void checkBalance(treeNode root){
    if(isBalanced(root)){
      printf("IS BALANCED\n");
    }else{
      printf("IS NOT BALANCED\n");
    }
}

void rotateLL(treeNode * root){
  treeNode pivot = (*root)->nextLeft;

  (*root)->nextLeft = pivot->nextRight;
  pivot->nextRight = (*root);

  *root = pivot;
}

void rotateRR(treeNode * root){
  treeNode pivot = (*root)->nextRight;

  (*root)->nextRight = pivot->nextLeft;
  pivot->nextLeft = (*root);

  *root = pivot;
}

void rotateLR(treeNode * root){
  treeNode aux = (*root)->nextLeft;
  treeNode pivot = aux->nextRight;

  rotateRR(&((*root)->nextLeft));
  rotateLL(root);
}

void rotateRL(treeNode * root){
  treeNode aux = (*root)->nextRight;
  treeNode pivot = aux->nextLeft;

  rotateLL(&((*root)->nextRight));
  rotateRR(root);
}

void rotate(treeNode * root){
  if(*root){
    int balanceFactor = getBalanceFactor(*root);
    int childBalanceFactor;
    if(balanceFactor >= 0){
      if((*root)->nextLeft){
        childBalanceFactor = getBalanceFactor((*root)->nextLeft);
        if(childBalanceFactor >= 0){
          rotateLL(root);
        }else{
          rotateLR(root);
        }
      }
    }else{
      if((*root)->nextRight){
        childBalanceFactor = getBalanceFactor((*root)->nextRight);
        if(childBalanceFactor <= 0){
          rotateRR(root);
        }else{
          rotateRL(root);
        }
      }
    }
  }
}

void balance(treeNode * root){
  if(*root){
    balance(&((*root)->nextLeft));
    balance(&((*root)->nextRight));

    if(!isBalanced(*root)){
      rotate(root);
    }
  }
}

treeNode insertNode(treeNode * root, int value){
  treeNode newNode = createNode(value);

  if(*root){
    treeNode prev = NULL;
    treeNode tmp = *root;

    while(tmp){
      prev = tmp;
      if(value < tmp->value){
        tmp = tmp->nextLeft;
      }else if(value > tmp->value){
        tmp = tmp->nextRight;
      }else{
        break;
      }
    }

    //insert only if (tmp is null <=> value doesn't exists in the tree)
    if(!tmp){
      if(value < prev->value){
        prev->nextLeft = newNode;
      }else{
        prev->nextRight = newNode;
      }

      balance(root);
    }
  }else{
    *root = newNode;
  }

  return newNode;
}

void deleteNode(treeNode * root, int value){
  treeNode prev = NULL;
  treeNode tmp = *root;

  while(tmp && tmp->value != value){
    prev = tmp;
    if(value < tmp->value){
      tmp = tmp->nextLeft;
    }else{
      tmp = tmp->nextRight;
    }
  }

  //if tmp <=> there's a key with this value
  if(tmp){
    if(tmp->nextLeft && tmp->nextRight){
      treeNode tmp2 = tmp->nextRight;
      while(tmp2->nextLeft){
        tmp2 = tmp2->nextLeft;
      }

      tmp->value = tmp2->value;
      deleteNode(&(tmp->nextRight), tmp->value);
    }else{
      treeNode tmp2;
      if(tmp->nextLeft){
        tmp2 = tmp->nextLeft;
      }else{
        tmp2 = tmp->nextRight;
      }

      if(prev){
        if(value < prev->value){
          prev->nextLeft  = tmp2;
        }else{
          prev->nextRight = tmp2;
        }
      }else{
        *root = tmp2;
      }

      free(tmp);
    }
    balance(root);
  }
}

void turnIntoRoot(treeNode * root, int value){
  insertNode(root, value);

  while((*root)->value != value){
    treeNode * tmp = root;
    treeNode * prev=  NULL;
    //find the node which value is
    while(value != (*tmp)->value){
      prev = tmp;
      if(value < (*tmp)->value){
        tmp = &((*tmp)->nextLeft);
      }else{
        tmp = &((*tmp)->nextRight);
      }
    }

    if(value < (*prev)->value){
      rotateLL(prev);
    }else{
      rotateRR(prev);
    }
  }
  return;
}
void printTopDownAux(treeNode root, int h){
  if(h == 0){
    if(root){
      printf("%d ", root->value);
    }else{
      printf("- ");
    }
  }else{
    if(root){
      printTopDownAux(root->nextLeft,  h-1);
      printTopDownAux(root->nextRight, h-1);
    }else{
      printTopDownAux(NULL, h-1);
      printTopDownAux(NULL, h-1);
    }
  }
}

void printTopDown(treeNode root){
  int h = height(root);
  for(int i = 0; i <= h; i++){
    for(int j = 0; j < h-i; j++){
      printf(" ");
    }
    printTopDownAux(root, i);
    printf("\n");
  }
}

int main(void){
  treeNode root = NULL;

  char c;
  int value;

  scanf("%c", &c);
  while(1){
    if(c >= 'a' && c <= 'z') c += 'A'-'a';
    switch(c){
      case 'I':
        scanf("%d", &value);
        insertNode(&root, value);
        break;
      case 'D':
        scanf("%d", &value);
        deleteNode(&root, value);
        break;
      case 'P':
        printTopDown(root);
        break;
      case 'C':
        checkBalance(root);
        break;
      case 'R':
        scanf("%d", &value);
        turnIntoRoot(&root, value);
        break;
      case 'B':
        balance(&root);
        break;
      case 'E':
        exit(0);
        break;
    }
    printTopDown(root);
    checkBalance(root);
    printf("\n");
    scanf("\n%c", &c);
  }

  return 0;
}
