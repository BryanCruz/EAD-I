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
		duvida->ra 		    = ra;
		duvida->codTopico = codTopico;
		duvida->prox  	  = NULL;
	}
	return duvida;
}

int acharIndex(duvidas lista, int ra){
	duvidas tmp;

	int achou = 0, index = 0;
	for(tmp = lista; !achou && tmp; tmp = tmp->prox, index++){
		if(tmp->ra == ra){
			achou = 1;

			while(tmp->prox && (tmp->prox)->ra == ra){
				index++;
				tmp = tmp->prox;
			}
			index--; //correcao do for
		}
	}
	return index;
}

duvidas inserirDuvida(duvidas * lista, int ra, int codTopico){
	int index = acharIndex(*lista, ra);
	duvidas duvida = criarDuvida(ra, codTopico);

	if(duvida){	//verifica se o nó foi criado
		if(!*lista){ //verifica se a lista está vazia
			*lista = duvida;
		}else{
			//acha o nó a ser inserido
			duvidas tmp = *lista;
			int i = 0;
			while(tmp->prox && i < index){
				i++;
				tmp = tmp->prox;
			}
			//for(tmp = *lista, i = 0; tmp->prox && i < index; tmp=tmp->prox, i++);
			//insere o nó
			duvida->prox = tmp->prox;
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
	while(ra != -1 || codTopico != -1){
		inserirDuvida(&lista, ra, codTopico);
		//leitura do ra e do código do tópico
		scanf("%d %d", &ra, &codTopico);
	}

	imprimirLista(lista);
	excluirLista(lista);

	return 0;
}
