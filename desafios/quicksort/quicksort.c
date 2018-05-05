#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct discoVoador{
	char * modelo;
	int    velocidade, capacidade, prazoDeEntrega;
	double eficiencia;
};

typedef struct linkedNode * linkedNode;
struct linkedNode{
	struct discoVoador valor;
	linkedNode prox;
};

linkedNode criarNode(char * modelo, int velocidade, double eficiencia, int capacidade, int prazoDeEntrega){
	linkedNode novoNode = (linkedNode) malloc(sizeof(struct linkedNode));

	novoNode->valor.modelo 		     = modelo;
	novoNode->valor.velocidade     = velocidade;
	novoNode->valor.capacidade     = capacidade;
	novoNode->valor.prazoDeEntrega = prazoDeEntrega;
	novoNode->valor.eficiencia     = eficiencia;

	novoNode->prox  							 = NULL;

	return novoNode;
}

linkedNode inserirNode(linkedNode lista, linkedNode novoNode){
	if(lista){
		while(lista->prox) lista = lista->prox;
		lista->prox 					   = novoNode;
	}

	return novoNode;
}

void exibirLista(linkedNode lista){
	while(lista != NULL){
		struct discoVoador atual = lista->valor;

		printf("[");
		printf("M=%s V=%d KM-L=%.2lf C=%d E=%d", atual.modelo, atual.velocidade, atual.eficiencia, atual.capacidade, atual.prazoDeEntrega);
		printf("]\n");

		lista = lista->prox;
	}
}

void deletarLista(linkedNode lista){
	if(!lista) return;

	deletarLista(lista->prox);
	free(lista->valor.modelo);
	free(lista);
}

int compararInt(int a, int b){
	int result;
	if(a < b){
		result = -1;
	}else if(a == b){
		result = 0;
	}else{
		result = 1;
	}

	return result;
}

int compararDouble(double a, double b){
	int result;
	if(a < b){
		result = -1;
	}else if(a == b){
		result = 0;
	}else{
		result = 1;
	}

	return result;
}

int compararString(char * a, char * b){
	int result = strcmp(a, b);

	return result;
}

int comparar(struct discoVoador a, struct discoVoador b, int modoDeComparacao){
	int campo = modoDeComparacao/10;
	int ordemDecrescente = modoDeComparacao%10;

	int result = 0;
	switch(campo){
		case 1:
			result = compararString(a.modelo, b.modelo);
		break;

		case 2:
			result = compararInt(a.capacidade, b.capacidade);
		break;

		case 5:
			result = compararInt(a.velocidade, b.velocidade);
			if(result){
				ordemDecrescente = 1;
			}else{
				result = compararDouble(a.eficiencia, b.eficiencia);
				ordemDecrescente = !ordemDecrescente;
			}
		break;

		case 6:
			result = compararInt(a.prazoDeEntrega, b.prazoDeEntrega);
		break;
	}

	if(ordemDecrescente) result *= -1;
	return result;
}


linkedNode quickSort(linkedNode lista, linkedNode limite, int modoDeComparacao){
	linkedNode pivo 				    = lista;

	linkedNode listaAEsquerda 	= NULL;
	linkedNode ultimoDaEsquerda = NULL;

	linkedNode listaADireita    = NULL;
	linkedNode ultimoDaDireita  = NULL;

	linkedNode rodando 	   		  = pivo->prox;

	while(rodando != limite){
		// if(rodando->valor < pivo->valor){
		if(comparar(pivo->valor, rodando->valor, modoDeComparacao) > 0){
			if(!listaAEsquerda) listaAEsquerda = rodando;
			else 				ultimoDaEsquerda->prox = rodando;

			ultimoDaEsquerda = rodando;
		}else{
			if(!listaADireita) listaADireita = rodando;
			else      ultimoDaDireita->prox  = rodando;

			ultimoDaDireita = rodando;
		}
		rodando = rodando->prox;
	}

	if(listaAEsquerda != NULL){
		ultimoDaEsquerda->prox = pivo;
		listaAEsquerda = quickSort(listaAEsquerda, pivo, modoDeComparacao);
	}else{
		listaAEsquerda = pivo;
	}

	if(listaADireita != NULL){
		ultimoDaDireita->prox = limite;
		pivo->prox = quickSort(listaADireita, limite, modoDeComparacao);
	}else{
		pivo->prox = limite;
	}

	return listaAEsquerda;
}

int main(void){
	linkedNode lista  					= NULL;
	linkedNode ultimoNodeInserido = NULL;

	char * modelo;
	int velocidade, capacidade, prazoDeEntrega;
	double eficiencia;

	int modoDeComparacao;

	int opcao	;
	do{
		scanf("%d", &opcao);
		switch(opcao){
			case 1:
			modelo = (char*) malloc(50*sizeof(char));
				//insere um novo item no final da lista e salva a referencia para ele,
				//agilizando a inserção de novos itens
				scanf("%s %d %lf %d %d", modelo, &velocidade, &eficiencia, &capacidade, &prazoDeEntrega);
				ultimoNodeInserido = inserirNode(ultimoNodeInserido, criarNode(modelo, velocidade, eficiencia, capacidade, prazoDeEntrega));

				//inicia a lista se ela estiver vazia
				if(lista == NULL) lista = ultimoNodeInserido;
			break;

			case 8:
				//ordena utilizando o quick sort e um determinado modoDeComparacao de comparacao
				scanf("%d", &modoDeComparacao);
				lista = quickSort(lista, NULL, modoDeComparacao);

				//imprime a lista
				printf("[O=%d]\n", modoDeComparacao);
				exibirLista(lista);
			break;

			case 2:
				//imprime a lista
				printf("[DISCOS]\n");
				exibirLista(lista);
			break;

		}

	}while(opcao != 0);

	deletarLista(lista);
	return 0;
}
