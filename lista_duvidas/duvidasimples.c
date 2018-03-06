#include<stdio.h>
#include<stdlib.h>

typedef struct s_duvidas * duvidas;
struct s_duvidas{
	int ra;
	int codTopico;
	duvidas prox;
};

duvidas criarDuvida(int ra, int codTopico){
	duvidas duvida = (duvidas) malloc(sizeof(struct s_duvidas));
	if(duvida){
		duvida->ra 		  = ra;
		duvida->codTopico = codTopico;
		duvida->prox  	  = NULL;
	}
	return duvida;
}

duvidas inserirDuvida(duvidas * lista, int ra, int codTopico){
	duvidas duvida = criarDuvida(ra, codTopico);

	if(duvida){
		if(!*lista){ //verifica se a lista está vazia
			*lista = duvida; 
		}else{
			//acha o ultimo nó da lista
			duvidas tmp;
			for(tmp = *lista; tmp->prox; tmp=tmp->prox); 
			
			//insere o nó
			tmp->prox = duvida;
		}
	}

	return duvida;
}

void imprimirLista(duvidas lista){
	duvidas tmp = lista;

	while(tmp != NULL){
		//printf("ra: %d\ncodTopico: %d\n\n", tmp->ra, tmp->codTopico);
		printf("%d %d\n", tmp->ra, tmp->codTopico);
		tmp = tmp->prox;
	}
}

void excluirDuvida(duvidas duvida){
	free(duvida);
}

void excluirLista(duvidas lista){
	while(lista){
		duvidas tmp = lista->prox;

		excluirDuvida(lista);

		lista = tmp;
	}
}

int main(void){
	duvidas lista = NULL;

	int ra, codTopico;
	scanf("%d %d", &ra, &codTopico);
	do{
		inserirDuvida(&lista, ra, codTopico);
		
		//leitura do ra e do código do tópico
		scanf("%d %d", &ra, &codTopico);
	}while(ra != -1 || codTopico != -1);

	imprimirLista(lista);
	excluirLista(lista);

	return 0;
}