#include<stdlib.h>
#include<stdio.h>
/*
 *Escreva um programa para gerenciar uma agenda de contatos. Para cada contato deve-se
 *armazenar Nome , Telefone e Email . Seu programa deve dar as seguintes opções ao usuário:
 *Inserir um contato no nal da agenda, Buscar dados pelo Nome , Buscar dados pelo
 *Telefone , Mostrar Agenda e Sair
 */

typedef struct s_contato *contatos;

struct s_contato{
   char * nome;
   char * telefone;
   char * email;
   contatos prox;
};


contatos criarContato(char * nome, char * telefone, char * email){
  contatos novo = (contatos) malloc(sizeof(struct s_contato));
  if(novo){
    novo->nome = nome;
    novo->telefone = telefone;
    novo->email = email;
    novo->prox = NULL;
  }
  return novo;
}

void addContato(contatos * lista, contatos novo){
  if(*lista){
    contatos rodando;
    for(rodando = *lista; rodando->prox != NULL; rodando = rodando->prox);
    rodando->prox = novo;
  }else{
    *lista = novo;
  }
}

void exibirContato(contatos contato){
  printf("----------------------------------------\n");
  printf("nome: %s\n", contato->nome);
  printf("telefone: %s\n", contato->telefone);
  printf("email: %s\n", contato->email);
  printf("----------------------------------------\n");
}

void exibirLista(contatos lista){
  printf("========================================\n");
  if(lista){
    int i = 1;
    while(lista != NULL){
      printf("contato nº %d\n", i);
      exibirContato(lista);
      lista = lista->prox;
      i++;
    }
  }else{
    printf("AGENDA VAZIA\n");
  }
  printf("========================================\n\n");
}

int compararStrings(char * string1, char * string2){
  int result = 1;
  int i;
  for(i = 0; result && string1[i] != '\0'; i++){
    result = (string2[i] != '\0' && string1[i] == string2[i]);
  }
  result = result && string2[i] == '\0';

  return result;
}

void buscarContatoPorNome(contatos lista, char * nome){
  contatos result = NULL;
  int achou = 0;
  printf("BUSCANDO POR NOME: %s\n", nome);
  while(lista != NULL){
    if(compararStrings(lista->nome, nome)){
      printf("CONTATO ENCONTRADO:\n");
      exibirContato(lista);

      achou = 1;
    }

    lista = lista->prox;
  }

  if(!achou){
    printf("NENHUM CONTATO ENCONTRADO\n");
  }
}

void buscarContatoPorTelefone(contatos lista, char * telefone){
  contatos result = NULL;
  int achou = 0;
  printf("BUSCANDO POR TELEFONE: %s\n", telefone);
  while(lista != NULL){
    if(compararStrings(lista->telefone, telefone)){
      printf("CONTATO ENCONTRADO:\n");
      exibirContato(lista);

      achou = 1;
    }

    lista = lista->prox;
  }

  if(!achou){
    printf("NENHUM CONTATO ENCONTRADO\n");
  }
}

void excluirContato(contatos contato){
  free(contato->nome);
  free(contato->telefone);
  free(contato->email);

  free(contato);
}

void excluirLista(contatos lista){
  while(lista != NULL){
    contatos aux = lista->prox;
    excluirContato(lista);
    lista = aux;
  }
}

void sair(){
  exit(0);
}

int main(void){
  contatos agenda = NULL;

  do{
    printf("\nEscolha uma opção: \n");
    printf("1: Inserir um contato na agenda\n");
    printf("2: Buscar um contato pelo nome\n");
    printf("3: Buscar um contato pelo telefone\n");
    printf("4: Mostrar agenda \n");
    printf("5: Sair (atenção: sua agenda será DELETADA)\n");
    printf("Sua opção: ");
    char op;
    scanf(" %c", &op);

    printf("VOCÊ ESCOLHEU: %c\n", op);
    if(op == '1'){
      char * nome = (char*) malloc(50*sizeof(char));
      char * telefone = (char*) malloc(50*sizeof(char));
      char * email = (char*) malloc(50*sizeof(char));

      printf("Dados do novo contato:\n");
      printf("Nome: ");
      scanf("%s", nome);
      printf("Telefone: ");
      scanf("%s", telefone);
      printf("Email: ");
      scanf("%s", email);

      contatos novo = criarContato(nome, telefone, email);
      if(novo){
        addContato(&agenda, novo);
        printf("CONTATO INSERIDO COM SUCESSO\n");
      }else{
        printf("MEMÓRIA INSUFICIENTE PARA CRIAR NOVO CONTATO\n");
      }
    }else if(op == '2'){
      char * nome = (char*) malloc(50*sizeof(char));
      printf("Digite o nome a ser procurado: ");
      scanf("%s", nome);

      buscarContatoPorNome(agenda, nome);

      free(nome);
    }else if(op == '3'){
      char * numero = (char*) malloc(50*sizeof(char));
      printf("Digite o numero a ser procurado: ");
      scanf("%s", numero);

      buscarContatoPorTelefone(agenda, numero);

      free(numero);
    }else if(op == '4'){
      exibirLista(agenda);
    }else if(op == '5'){
      excluirLista(agenda);
      sair();
    }else{
      printf("\nOPÇÃO INVÁLIDA\n");
    }
  }while(1);

  return 0;
}
