#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int data;
  struct Node *next;
} Node;

// estrutura do elo da linked list

Node *new_list(int value) {
  Node *node = malloc(sizeof(Node));
  if (node == NULL) {
    perror("Falha na alocação dinâmica de memória");
    return NULL; // retorna ponteiro inválido! ou exit(EXIT_FAILURE) em código
                 // voltado para produção
  }
  node->data = value; // pode ser traduzido
  node->next = NULL;  // node da lista aponta para outro valor.
  printf("Nó inicial da linked list em %p.\n", (void *)node);
  return node; // retorno um node
}

void insert_node(Node **head, int value) {
  Node *new = malloc(sizeof(Node));
  if (new == NULL) {
    perror("Deu zebra, como você viu, essa função irá retornar nada.");
    free(new);
    return;
  }
  new->data = value;
  new->next = *head;
  *head = new;
  printf("Novo nó inserido na lista! Endereço de memória é %p\n", (void *)new);
}

void free_list(Node *head) {
  Node *current = head;
  Node *next; // preciso representar o outro nó, porque eu estaria liberando a
              // memória que segura o endereço de memória
  while (current != NULL) {
    next = current->next;
    printf("Endereço de memória do nó a ser limpo: %p\n", (void *)current);
    free(current);
    current = next;
  }
}

void print_list(Node *head) {
  Node *current = head;

  while (current != NULL) {
    printf("%d\n", current->data);
    printf("Endereço de memória do nó atual da lista: %p.\n", (void *)current);
    current = current->next;
  }
}

int main(void) {
  Node *link = new_list(10);
  insert_node(&link, 99);
  insert_node(&link, 88);
  insert_node(&link, 77);
  print_list(link);
  free_list(link);
  return 0;
}
