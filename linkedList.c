/*******************************************************************************
*
*                      Implementação linked list
*                       Autor: Gabriel Matheus
*                          github.com/gmsj
*
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

typedef struct node { // Estrutura do nó
  int val;
  struct node *next;
} node;

typedef struct list { // Estrutura para lista de nós
  int valor;
  struct list *next;
  struct node *head;
} list;

node *listDelete (node *cur, node *head) { // Deleta o valor apontador por cur e retorna um ponteiro para a posição anterior
  if (cur == head) {
    printf("Não pode remover o head!!!!\n");
    return cur;
  }
  node *temp = head;
  while (temp->next != cur) {
    temp = temp->next;
  }
  temp->next = cur->next;
  (cur->next) = (temp->next);
  cur = NULL;
  free(cur);
  if (temp == head && temp->next != NULL) {
    return temp->next;
  }
  printf("Valor deletado!!!\n");
  return temp;
}

node *listValue (node *head, int val) { // Retorna a referencia ao ponteiro com o valor buscado
  node *cur = head;
  while ((cur->next) != NULL && cur->val != val) {
    cur = (cur->next);
  }
  if (cur->next == NULL && cur->val != val) {
    printf("Valor nao encontrado! cur setado para a ultima posicao!\n");
  }
  return cur;
}

node *listPos (node *head, int pos) {
  node *cur = head;
  int i;
  for (i = 0; i < pos; i++) {
    if (cur->next == NULL && i != pos-1) {
      printf("Posicao excedeu o numero de elementos...\n");
      return cur;
    }
    else {
      cur = (cur->next);
    }
  }
  printf("O valor na posicao desejada eh %d\n", cur->val);
  return cur;
}

node *listInsert (node *cur, int val) {
  node *new; // Crio novo nó em algum lugar da memoria
  new = (node*) malloc (sizeof(node));
  new->val = val; // Seto o valor
  new->next = cur->next; // Seto o next com o valor NULL do head
  cur->next = new; // Seto o next do anterior com o endereco do novo
  cur = new; // Seto o cursor para o corrente
  return cur;
}

node *enqueue (node *head, int val) {
  node *cur = head;
  while (cur->next != NULL) {
    cur = cur->next;
  }
  cur = listInsert(cur, val);
  return cur;
}

node *dequeue (node *head) {
  if (head->next == NULL) {
    printf("Não pode remover o head!!!!\n");
    return head;
  }
  node *cur = head->next;
  printf("Valor a ser removido da fila [%d]\n", cur->val);
  cur = listDelete(cur, head);
  return cur;
}

void printCur (node *cur) {
  putchar('\n');
  if (cur == NULL) {
    printf("Valor apontado por cur: [NULL]\n");
  }
  else {
    printf("Valor apontado por cur: [%d]\n", cur->val);
  }
}

void menu () {
  putchar('\n');
  printf("1 ....................................... Adicionar valor\n");
  printf("2 .................................. Valor na posicao [X]\n");
  printf("3 ............... Mover cursor para posicao com valor [X]\n");
  printf("4 ........................ Deletar valor na posicao [cur]\n");
  printf("5 ............................... Listar todos os valores\n");
  printf("6 ................................... Valor posicao [cur]\n");
  printf("7 ....................................... Colocar da fila\n");
  printf("8 ....................................... Remover da fila\n");
  printf("0 .................................................. Sair\n");
  printf("Opcao: ");
}

void printAll (node *head) {
  int pos = 1;
  putchar('\n');
  node *cur = head->next;
  if (cur == NULL) {
    printf("Nao ha valores a serem exibidos!!!\n");
    return;
  }
  printf("Todos os valores sao: \n");
  while (cur != NULL) {
    printf("Valor na pos [%d] eh: [%d]\n", pos, cur->val);
    cur = cur->next;
    pos++;
  }
}

int main () {
  int i, val, pos, opcao = 1;
  node *head; // Criando head
  node *cur; // Criando cursor
  head = (node*) malloc (sizeof(node)); // Alocando espaço na memória
  if (head == NULL) { // Teste para ver se o espaço estava disponivel (dificilmente teremos esse problema)
    printf("Problem in head [error: 01]\n");
    exit(1);
  }
  head->next = NULL;
  cur = head;
  // Criando a lista de nós
  list *lista1;
  lista1 = (list*) malloc (sizeof(list));
  lista1->next = NULL;
  lista1->head = head;
  lista1->valor = 1;

  while (opcao != 0) {
    menu();
    scanf("%d", &opcao);
    switch (opcao) {
      case 1: // Adicionar valor
        printf("Digite o valor: ");
        scanf("%d", &val);
        cur = listInsert(cur, val);
        break;
      case 2 : // Valor pos
        printf("Digite a posicao: ");
        scanf("%d", &pos);
        cur = listPos(head, pos);
        break;
      case 3 : // Mover cur para pos
        printf("Digite o valor: ");
        scanf("%d", &val);
        cur = listValue(head, val);
        printf("Feito...\n");
        break;
      case 4 : // Deletar
        cur = listDelete(cur, head);
        break;
      case 5 : // Listar todos
        printAll(head);
        break;
      case 6 : // Valor cur
        printCur(cur);
        break;
      case 7 :
        printf("Digite o valor: ");
        scanf("%d", &val);
        cur = enqueue(head, val);
        break;
      case 8 :
        cur = dequeue(head);
        break;
      case 0 : // Sair
        printf("Vlwss, Flwss!!!\n");
        break;
      default :
        printf("Opcao invalida, tente novamente!\n");
    }
  }
  return 0;
}
