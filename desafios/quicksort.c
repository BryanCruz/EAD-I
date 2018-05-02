#include<stdio.h>
#include<stdlib.h>

typedef struct linkedNode * linkedNode;
struct linkedNode{
	int value;
	linkedNode next;
};

linkedNode createNode(int value){
	linkedNode newNode = (linkedNode) malloc(sizeof(struct linkedNode));
	
	newNode->value = value;
	newNode->next  = NULL;

	return newNode;
}

linkedNode insertNode(linkedNode * list, linkedNode * last, linkedNode newNode){
	if(*last){
		(*last)->next = newNode;
		*last = newNode;
	}else{
		*list = newNode;
		*last = newNode;
	}

	return newNode;
}

void printList(linkedNode list){
	while(list){
		printf("%d ", list->value);
		list = list->next;	
	}
	printf("\n");
}

void deleteList(linkedNode list){
	if(!list) return;
	
	deleteList(list->next);
	free(list);
}

void quickSort(linkedNode * list, linkedNode * last){
	if(*list == *last) return;

	linkedNode pivo = *list;
	
	linkedNode menores = NULL;
	linkedNode menoresLast = NULL;

	linkedNode tmp 	   = pivo->next;
	linkedNode prev    = pivo;

	while(tmp != (*last)->next){
		if(tmp->value < pivo->value){
			if(!menores){
				menores = tmp;
			}else{
				menoresLast->next = tmp;
			}
			menoresLast = tmp;
			
			prev->next = tmp->next;
		}else{
			prev = tmp;
		}

		tmp = tmp->next;
	}
	
	if(menoresLast) pivo->next = menoresLast->next;
	if(menoresLast) menoresLast->next = pivo;
	*list = menores; //perdi o pivo
}

int main(void){
	linkedNode list = NULL;
	linkedNode last = NULL;
	char op;
	int value;

	do{
		scanf("%c", &op);
		if(op >= 'a' && op <= 'z') op += 'A' - 'a';
		printf("escolheu %c\n", op);

		switch(op){
			case 'I':
				scanf("%d", &value);
				insertNode(&list, &last, createNode(value));
			break;

	
			case 'Q':
				quickSort(&list, &last);
			break;	

			case 'P':
				printList(list);
			break;	
		}

	}while(op != 'S');

	deleteList(list);
	return 0;
}
