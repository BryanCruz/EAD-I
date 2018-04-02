#include<stdio.h>
#include<stdlib.h>

typedef struct linkedTree * linkedTree;
struct linkedTree{
	int ra;
	int nota;

	linkedTree proxMenor;
	linkedTree proxMaior;
};

linkedTree criarRa(int ra){
	linkedTree novoRa = (linkedTree) malloc(sizeof(struct linkedTree));
	
	if(novoRa){
		novoRa->ra   = ra;
		novoRa->nota = -1;
		novoRa->proxMenor = NULL;
		novoRa->proxMaior = NULL;
	}

	return novoRa; 
}

void inserirNota(int ra, int nota, linkedTree * raiz){
	//busca onde inserir
	linkedTree tmp  = *raiz;
	linkedTree prev = NULL;
	while(tmp && ra != tmp->ra){
		prev = tmp;
		if(ra < tmp->ra){
			tmp = tmp->proxMenor;
		}else{
			tmp = tmp->proxMaior;
		}
	}

	//se o nó não existir, cria um
	linkedTree novo = NULL;
	if(!tmp){
		novo = criarRa(ra);
	}

	//insere a nota
	if(tmp){ //caso o ra já exista na lista
		tmp->nota  = nota;

	}else{	  //caso o ra não exista na lista
		novo->nota = nota;

		if(prev){
			if(ra < prev->ra){
				prev->proxMenor = novo;
			}else{
				prev->proxMaior = novo;
			}
		}else{
			*raiz = novo;
		}
	}
}

int numIteracoes;
linkedTree buscarNotaPorRa(int ra, linkedTree raiz){
	numIteracoes = 0;
	linkedTree tmp = raiz;
	while(tmp){
		numIteracoes++;

		if(ra < tmp->ra){
			tmp = tmp->proxMenor;

		}else if(ra > tmp->ra){
			tmp = tmp->proxMaior;
		}else{ //achou o valor
			break;
		}
	}

	return tmp;
}

void removerRa(int ra, linkedTree *raiz){
	linkedTree prev = NULL;
	linkedTree tmp  = *raiz;

	while(tmp && ra != tmp->ra){
		prev = tmp;
		if(ra < tmp->ra){
			tmp = tmp->proxMenor;
		}else{
			tmp = tmp->proxMaior;
		}
	}

	if(tmp){ //o nó a ser removido existe na lista
		if(tmp->proxMenor && tmp->proxMaior){
			//busca o menor valor a direita do no em questao
			linkedTree menorADireita = tmp->proxMaior;
			while(menorADireita->proxMenor){
				menorADireita = menorADireita->proxMenor;
			}

			tmp->ra   = menorADireita->ra;
			tmp->nota = menorADireita->nota;

			removerRa(menorADireita->ra, &(tmp->proxMaior));
		}else{ //tem no max 1 nó filho
			linkedTree noFilho = NULL;
			
			if(tmp->proxMenor){
				noFilho = tmp->proxMenor;
			}else{
				noFilho = tmp->proxMaior;
			}

			if(prev){
				if(tmp->ra < prev->ra){
					prev->proxMenor = noFilho;
				}else{
					prev->proxMaior = noFilho;
				}
			}else{
				*raiz = noFilho;
			}

			free(tmp);
		}
	}
}

int maximo(int a, int b){
	return a > b? a : b;
}

int alturaDaArvore(linkedTree raiz){
	int h;

	if(raiz){
		h = 1 + maximo(alturaDaArvore(raiz->proxMenor), alturaDaArvore(raiz->proxMaior));	
	}else{
		h = -1;
	}

	return h;
}

void imprimirArvore(linkedTree raiz){
	if(raiz){
		imprimirArvore(raiz->proxMenor);
		printf("%d %d\n", raiz->ra, raiz->nota);
		imprimirArvore(raiz->proxMaior);
	}
}

void excluirArvore(linkedTree raiz){
	if(raiz){
		excluirArvore(raiz->proxMenor);
		excluirArvore(raiz->proxMaior);

		free(raiz);
	}
}

int main(void){
	linkedTree raiz = NULL;

	char c;
	int ra, nota, h;
	linkedTree tmp = NULL;

	scanf("%c", &c);
	while(1){
		switch(c){
			case 'i':
			case 'I':
				scanf("%d %d", &ra, &nota);
				inserirNota(ra, nota, &raiz);
				//imprimirArvore(raiz);
				break;

			case 'r':
			case 'R':
				scanf("%d", &ra);
				removerRa(ra, &raiz);
				break;

			case 'b':
			case 'B':
				scanf("%d", &ra);
				tmp = buscarNotaPorRa(ra, raiz);
				printf("C=%d Nota=%d\n", numIteracoes, tmp? tmp->nota : -1);
				tmp = NULL;
				break;

			case 'a':
			case 'A':
				h = alturaDaArvore(raiz);
				printf("A=%d\n", h);
				break;

			case 'p':
			case 'P':
				excluirArvore(raiz);
				exit(0);
				break;
		}
		scanf("\n%c", &c);
	}

	return 0;
}