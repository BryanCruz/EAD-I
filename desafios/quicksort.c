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

void printList(linkedNode list, linkedNode last){
	while(list != last){
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

linkedNode quickSort(linkedNode list, linkedNode last){
	linkedNode pivo 	= list;

	linkedNode menores 	= NULL;
	linkedNode menoresLast  = NULL;

	linkedNode maiores      = NULL;	
	linkedNode maioresLast  = NULL;

	linkedNode tmp 	   = pivo->next;

	while(tmp != last){
		if(tmp->value < pivo->value){
			if(!menores)	  menores = tmp;
			else	menoresLast->next = tmp;
			
			menoresLast = tmp;
		}else{
			if(!maiores)      maiores = tmp;
			else    maioresLast->next = tmp;

			maioresLast = tmp;
		}
		tmp = tmp->next;		
	}

	if(menores){
		menoresLast->next = pivo;
	}
	if(maiores){	
		pivo->next 	  = maiores;
		maioresLast->next = last;
	}else{
		pivo->next = last;
	}
	
	
	if(menores    != NULL) 	menores    = quickSort(menores, pivo);
	if(maiores    != NULL)	pivo->next = quickSort(maiores, last);
	
	return menores? menores : pivo;
}

int main(void){
	linkedNode list = NULL;
	linkedNode last = NULL;
	char op;
	int value;

	do{
		scanf(" %c", &op);
		if(op >= 'a' && op <= 'z') op += 'A' - 'a';
		printf("%c\n", op);

		switch(op){
			case 'I':
				scanf("%d", &value);
				insertNode(&list, &last, createNode(value));
			break;

			case 'Q':
				list = quickSort(list, NULL);
			break;

			case 'P':
				printList(list, NULL);
			break;
		}

	}while(op != 'S');

	deleteList(list);
	return 0;
}
