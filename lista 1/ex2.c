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
  int i = 1;
  while(lista != NULL){
    printf("contato nº %d\n", i);
    exibirContato(lista);
    lista = lista->prox;
    i++;
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
  printf("buscando por nome: %s\n", nome);
  while(lista != NULL){
    if(compararStrings(lista->nome, nome)){
      printf("contato encontrado:\n");
      exibirContato(lista);

      achou = 1;
    }

    lista = lista->prox;
  }

  if(!achou){
    printf("nenhum contato encontrado\n");
  }
}

void buscarContatoPorTelefone(contatos lista, char * telefone){
  contatos result = NULL;
  int achou = 0;
  printf("buscando por telefone: %s\n", telefone);
  while(lista != NULL){
    if(compararStrings(lista->telefone, telefone)){
      printf("contato encontrado:\n");
      exibirContato(lista);

      achou = 1;
    }

    lista = lista->prox;
  }

  if(!achou){
    printf("nenhum contato encontrado\n");
  }
}

void sair(){
  exit(0);
}

int main(void){
  // contatos agenda = NULL;
  //
  // do{
  //   printf("\nEscolha uma opção: \n");
  //   printf("1: Inserir um contato na agenda\n");
  //   printf("2: Buscar um contato pelo nome\n");
  //   printf("3: Buscar um contato pelo telefone\n");
  //   printf("4: Mostrar agenda \n");
  //   printf("5: Sair (atenção: sua agenda será DELETADA)\n");
  //   printf("Sua opção: ");
  //   char op;
  //   scanf(" %c", &op);
  //
  //   printf("voce escolheu %c\n", op);
  //   if(op == '1'){
  //     char nome[50];
  //     char telefone[50];
  //     char email[50];
  //
  //     printf("Dados do novo contato:\n");
  //     printf("Nome: ");
  //     scanf("%s", nome);
  //     printf("Telefone: ");
  //     scanf("%s", telefone);
  //     printf("Email: ");
  //     scanf("%s", email);
  //
  //     contatos novo = criarContato(nome, telefone, email);
  //     if(novo){
  //       addContato(&agenda, novo);
  //       printf("contato inserido com sucesso\n");
  //     }else{
  //       printf("memória insuficiente para criar novo contato\n");
  //     }
  //   }else if(op == '2'){
  //     char nome[50];
  //     printf("Digite o nome a ser procurado: ");
  //     scanf("%s", nome);
  //
  //     buscarContatoPorNome(agenda, nome);
  //   }else if(op == '3'){
  //     char numero[50];
  //     printf("Digite o numero a ser procurado: ");
  //     scanf("%s", numero);
  //
  //     buscarContatoPorNome(agenda, numero);
  //   }else if(op == '4'){
  //     exibirLista(agenda);
  //   }
  //
  // }while(1);

  // printf("%s\n", compararStrings("abcd", "gdea")? "errado" : "certo");
  // printf("%s\n", compararStrings("abcd", "abcd")? "certo" : "errado");
  // printf("%s\n", compararStrings("abcd", "abcde")? "errado" : "certo");
  // printf("%s\n", compararStrings("abcde", "abcd")? "errado" : "certo");
  // printf("%s\n", compararStrings("abcde", "abcdf")? "errado" : "certo");


  contatos lista = NULL;
  contatos teste2 = criarContato("joao", "555", "hidromel");
  contatos teste = criarContato("maria", "333", "eita");
  contatos teste3 = criarContato("jenosvaldo", "111", "lol");
  contatos teste4 = criarContato("maria", "113", "abc");
  addContato(&lista, teste);

  exibirLista(lista);

  addContato(&lista, teste2);
  exibirLista(lista);

  addContato(&lista, teste3);
  addContato(&lista, teste4);
  exibirLista(lista);

  //buscarContatoPorNome(lista, "maria");
//  buscarContatoPorNome(lista, "joao");
//  buscarContatoPorNome(lista, "abcd");

  return 0;
}
