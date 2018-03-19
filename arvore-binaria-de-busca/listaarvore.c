#include<stdio.h>
#include<stdlib.h>

typedef struct linkedNode * linkedNode;
struct linkedNode{
	int ra;
	linkedNode next;
};

typedef struct treeNode * treeNode;
struct treeNode{
	int ra;
	treeNode nextLeft, nextRight;
};


//search the value and count the iterations
int linkedSearch(linkedNode list, int value){
	linkedNode tmp = list;
	int numIterations = 0;

	while(tmp && ++numIterations && tmp->ra < value){
		tmp = tmp->next;
	}

	return numIterations;
}

//search the value and count the iterations
int treeSearch(treeNode list, int value){
	int numIterations = 0;

	treeNode tmp = list;
	while(tmp){
		numIterations++;
		//find which direction to go
		if(value < tmp->ra){
			//go left
			tmp = tmp->nextLeft;
		}else if(value > tmp->ra){
			//go right
			tmp = tmp->nextRight;
		}else{
			//achou o valor
			tmp = NULL;
		}
	}

	return numIterations;
}

linkedNode createLinkedNode(int value){
	linkedNode newNode = (linkedNode) malloc(sizeof(struct linkedNode));
	newNode->ra        = value;
	newNode->next      = NULL;

	return newNode;
}

treeNode createTreeNode(int value){
	treeNode newNode   = (treeNode) malloc(sizeof(struct treeNode));
	newNode->ra        = value;
	newNode->nextLeft  = NULL;
	newNode->nextRight = NULL;

	return newNode;
}

linkedNode insertLinkedNode(linkedNode * list, int value){
	//create the node
	linkedNode newNode = createLinkedNode(value);
	
	//find where to insert the new node
	linkedNode tmp  = *list;
	linkedNode prev = NULL;
	while(tmp && tmp->ra < newNode->ra){
		prev = tmp;
		tmp  = tmp->next;
	}

	//prev is the last  node minor   than the new node
	//tmp  is the first node greater than the new node
	if(prev){
		prev->next = newNode;
		newNode->next = tmp;
	}else{  
		newNode->next = *list;
		*list = newNode;
	}

	return newNode;
}

treeNode insertTreeNode(treeNode * list, int value){
	//create the node
	treeNode newNode = createTreeNode(value);

	//find where to insert the new node
	treeNode tmp = *list;

	if(tmp){
		treeNode prev = NULL;
		while(tmp){
			prev = tmp;
			//find which direction to go
			if(newNode->ra < tmp->ra){
				//go left
				tmp = tmp->nextLeft;
			}else{
				//go right
				tmp = tmp->nextRight;
			}
		}

		//when tmp is null, it means the new element should go where it is right now
		if(newNode->ra < prev->ra){
			prev->nextLeft  = newNode;
		}else{
			prev->nextRight = newNode;
		}
	}else{
		*list = newNode;
	}

	return newNode;
}


void testSearching(linkedNode linkedList, treeNode treeList, int value){
	int linkedIterations = linkedSearch(linkedList, value);
	int treeIterations   = treeSearch(treeList, value);

	printf("L=%d A=%d\n", linkedIterations, treeIterations);
}

void printLinkedList(linkedNode list){
	while(list){
		printf("%d ", list->ra);
		list = list->next;
	}
	printf("\n");
}

int main(void){
	char op;
	int value;

	linkedNode linkedHead = NULL;
	treeNode     treeHead = NULL;

	while(scanf("%c %d", &op, &value) && (op != 'P' || value != 0)){
		if(op == 'B'){  		//search value
			testSearching(linkedHead, treeHead, value);
		}else if(op == 'I'){    //insert value
			insertLinkedNode(&linkedHead, value);
			insertTreeNode(&treeHead, value);
		} 						//else: invalid option
	}
	return 0;
}