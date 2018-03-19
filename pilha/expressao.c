#include <stdio.h>
#include <stdlib.h>

typedef struct valores * valores;
struct valores{
	double valor;
	valores prox;
};

typedef struct pilhaDeValores pilhaDeValores;
struct pilhaDeValores{
	valores topo;
	int tam;
};


//manipulacao dos valores
	//criacao dos valores
valores criarValor(double n){
	valores valor = malloc(sizeof(struct valores));
	valor->valor = n;
	valor->prox = NULL;

	return valor;
}

	//liberacao de memoria
void removerValor(valores valor){
	free(valor);
}

//manipulacao da pilha
	//inserir elemento no topo
void push(double n, pilhaDeValores * pilha){
	valores valor = criarValor(n);

	valor->prox = pilha->topo;	
	pilha->topo = valor;
}
	//remover elemento do topo
valores pop(pilhaDeValores * pilha){
	valores valor = pilha->topo;
	pilha->topo = (pilha->topo)->prox;


	valor->prox = NULL;
	return valor;
}

	//exibir os valores da pilha
void exibirPilha(pilhaDeValores pilha){
	valores tmp = pilha.topo;
	while(tmp){
		printf("%.2lf ", tmp->valor);
		tmp = tmp->prox;
	}
	printf("\n");
}

	//retirar valores da pilha
double getValor(pilhaDeValores * pilha){
	valores strucValor = pop(pilha);
	double valor = strucValor->valor;
	
	free(strucValor);

	return valor;
}

//funcoes a serem realizadas
double funcaoH(double a){
	return a*3;
}

double somar(double a, double b){
	return a+b;
}

double subtrair(double a, double b){
	return a-b;
}

double funcaoF(double a, double b, double c){
	return (a*a) - (b/2) + c;
}

double funcaoG(double a, double b, double c){
	return (a*b) + c;
}

void entradaInvalida(){
	printf("ERRO\n");
	exit(0);
}

int main(){
	char c;
	pilhaDeValores pilha = {NULL, 0};

	while(scanf("%c", &c) && c != '\n'){
		if(c >= '0' && c <= '9'){
			//insere o elemento lido na pilha
			push((c-'0'), &pilha);

			//atualiza o tamanho da pilha
			pilha.tam++;
		}else{
			//realiza a operacao nos elementos anteriores da pilha
			//adiciona o valor calculado à pilha
			//atualiza o tamanho da pilha
			double n1, n2, n3;
			if(c == 'h'){
				if (pilha.tam < 1) entradaInvalida();

				n1 = getValor(&pilha);
				push(funcaoH(n1), &pilha);
			}else if(c == '+'){
				if (pilha.tam < 2) entradaInvalida();

				n2 = getValor(&pilha);
				n1 = getValor(&pilha);

				push(somar(n1, n2), &pilha);

				pilha.tam--;
			}else if(c == '-'){
				if (pilha.tam < 2) entradaInvalida();

				n2 = getValor(&pilha);
				n1 = getValor(&pilha);

				push(subtrair(n1, n2), &pilha);

				pilha.tam--;
			}else if(c == 'f'){
				if (pilha.tam < 3) entradaInvalida();

				n3 = getValor(&pilha);
				n2 = getValor(&pilha);
				n1 = getValor(&pilha);

				push(funcaoF(n1, n2, n3), &pilha);

				pilha.tam-=2;
			}else{// c == 'g'
				if (pilha.tam < 3) entradaInvalida();

				n3 = getValor(&pilha);
				n2 = getValor(&pilha);
				n1 = getValor(&pilha);

				push(funcaoG(n1, n2, n3), &pilha);

				pilha.tam-=2;
			}
		}

	}

	if(pilha.tam == 1){
		exibirPilha(pilha);
	}else{
		entradaInvalida();
	}
	return 0;
}

