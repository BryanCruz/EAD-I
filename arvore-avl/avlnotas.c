#include<stdio.h>
#include<stdlib.h>

typedef struct treeNode * treeNode;
struct treeNode{
  int ra;
  int grade;

  treeNode nextLeft;
  treeNode nextRight;
};

treeNode createNode(int ra, int grade){
  treeNode newNode = (treeNode) malloc(sizeof(struct treeNode));

  newNode->ra    = ra;
  newNode->grade = grade;
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
    printf("%d ", root->ra);
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
	char c1, c2 ;
	int x, y, z;

	int balanceFactor = getBalanceFactor(*root);
	int childBalanceFactor;
	if(balanceFactor >= 0){
	  	c2 = 'D';
	    childBalanceFactor = getBalanceFactor((*root)->nextLeft);
	    if(childBalanceFactor >= 0){
	      c1 = 'S';
	      rotateLL(root);
	    }else{
	      c1 = 'D';
	      rotateLR(root);
	    }

	}else{
	    c2 = 'E';
	    childBalanceFactor = getBalanceFactor((*root)->nextRight);
	    if(childBalanceFactor <= 0){
	      c1 = 'S';
	      rotateRR(root);
	    }else{
	      c1 = 'D';
	      rotateRL(root);
	    }
	}

	y = (*root)->ra;
	x = (*root)->nextLeft->ra;
	z = (*root)->nextRight->ra;
	printf("[Rotacao: %c%c]\n", c1, c2);
	printf("[x=%d y=%d z=%d]\n", x, y, z);
}

int balance(treeNode * root){
  int balanced = 1;
  if(*root){
    balanced = balance(&((*root)->nextLeft));
    balanced = balanced && balance(&((*root)->nextRight));

    if(!isBalanced(*root)){
      printf("[No desbalanceado: %d]\n", (*root)->ra);
      rotate(root);

      balanced = 0;
    }
  }

  return balanced;
}

int checkBalance(treeNode * root){
	int balanced = balance(root);
    if(balanced){
      printf("[Ja esta balanceado]\n");
    }
}

void insertNode(treeNode * root, int ra, int grade){
  treeNode newNode = createNode(ra, grade);

  if(*root){
    treeNode prev = NULL;
    treeNode tmp = *root;

    while(tmp){
      prev = tmp;
      if(ra < tmp->ra){
        tmp = tmp->nextLeft;
      }else if(ra > tmp->ra){
        tmp = tmp->nextRight;
      }else{
        break;
      }
    }

    //insert only if (tmp is null <=> ra doesn't exists in the tree)
    if(!tmp){
      if(ra < prev->ra){
        prev->nextLeft = newNode;
      }else{
        prev->nextRight = newNode;
      }
    }else{
    	tmp->grade = grade;
    	free(newNode);
    }
  }else{
    *root = newNode;
  }
}

void insertRa(treeNode * root, int ra, int grade){
  insertNode(root, ra, grade);
  checkBalance(root);
}

void deleteNode(treeNode * root, int ra){
  treeNode prev = NULL;
  treeNode tmp = *root;

  while(tmp && tmp->ra != ra){
    prev = tmp;
    if(ra < tmp->ra){
      tmp = tmp->nextLeft;
    }else{
      tmp = tmp->nextRight;
    }
  }

  //if tmp <=> there's a key with this ra
  if(tmp){
    if(tmp->nextLeft && tmp->nextRight){
      treeNode tmp2 = tmp->nextRight;
      while(tmp2->nextLeft){
        tmp2 = tmp2->nextLeft;
      }

      tmp->ra = tmp2->ra;
      tmp->grade = tmp2->grade;
      deleteNode(&(tmp->nextRight), tmp->ra);
    }else{
      treeNode tmp2;
      if(tmp->nextLeft){
        tmp2 = tmp->nextLeft;
      }else{
        tmp2 = tmp->nextRight;
      }

      if(prev){
        if(ra < prev->ra){
          prev->nextLeft  = tmp2;
        }else{
          prev->nextRight = tmp2;
        }
      }else{
        *root = tmp2;
      }

      free(tmp);
    }
  }
}

void deleteRa(treeNode * root, int ra){
	deleteNode(root, ra);
	checkBalance(root);
}

void clearTree(treeNode * root){
	if(*root){
		clearTree(&(*root)->nextLeft);
		clearTree(&(*root)->nextRight);

		free(*root);
	}

	*root = NULL;
}

void printTreeHeight(treeNode root){
	int h = height(root);
	printf("A=%d\n", h);
}

void posOrderRecursion(treeNode root){
	if(root){
		posOrderRecursion(root->nextLeft);
		posOrderRecursion(root->nextRight);
		printf("%d ", root->ra);
	}
}

void printPosOrder(treeNode root){
	printf("[");
	posOrderRecursion(root);
	printf("]\n");
}

// void printTopDownAux(treeNode root, int h){
//   if(h == 0){
//     if(root){
//       printf("%d(%d) ", root->ra, root->grade);
//     }else{
//       printf("- ");
//     }
//   }else{
//     if(root){
//       printTopDownAux(root->nextLeft,  h-1);
//       printTopDownAux(root->nextRight, h-1);
//     }else{
//       printTopDownAux(NULL, h-1);
//       printTopDownAux(NULL, h-1);
//     }
//   }
// }
//
// void printTopDown(treeNode root){
//   int h = height(root);
//   for(int i = 0; i <= h; i++){
//     for(int j = 0; j < h-i; j++){
//       printf(" ");
//     }
//     printTopDownAux(root, i);
//     printf("\n");
//   }
// }

void printGrade(treeNode root, int ra){
	int i = 0;

	//search grade
	treeNode tmp = root;
	while(tmp){
		i++;
		if(ra < tmp->ra){
			tmp = tmp->nextLeft;
		}else if(ra > tmp->ra){
			tmp = tmp->nextRight;
		}else{
			//found it
			break;
		}
	}

	printf("C=%d Nota=%d\n", i, tmp? tmp->grade : -1);
}

int main(void){
  treeNode root = NULL;

  char c;
  int ra, grade;

  scanf("%c", &c);
  while(1){
    if(c >= 'a' && c <= 'z') c += 'A'-'a';
    switch(c){
      case 'I':
        scanf("%d %d", &ra, &grade);
        insertRa(&root, ra, grade);
        break;
      case 'R':
        scanf("%d", &ra);
        deleteRa(&root, ra);
        break;
      case 'B':
      	scanf("%d", &ra);
      	printGrade(root, ra);
      	break;
      case 'A':
      	printTreeHeight(root);
      	break;
      case 'P':
        printPosOrder(root);
		    clearTree(&root);
        exit(0);
        break;
      // case 'T':
      // 	printTopDown(root);
      // 	break;
    }
    scanf("\n%c", &c);
  }
  return 0;
}
