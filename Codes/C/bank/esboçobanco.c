#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
 * Macros úteis ao sistema
 */

typedef struct cliente {
  uint8_t id;
  char nome_cliente[50];
  uint8_t numero_conta;
  float saldo;
  bool status_divida;
  bool status_trabalho;
  char ocupacao[50];
  float renda;
} Cliente;

/*
 * Funções utilitárias
 */

bool trim(char *str);
/*
 * Funções do sistema
 */

/*
 * Função principal
 */
int main(void) {}

/*
 * Implementação das funções utilitárias
 */
bool trim(char *str) {
  size_t end = strlen(str);
  if (end == 0)
    return false;
  end--;
  size_t start = 0;
  size_t len;

  while (end >= start && isspace((unsigned char)str[start]))
    start++;
  while (start <= end && isspace((unsigned char)str[end]))
    end--;

  len = end - start + 1;
  memmove(str, str + start, len);
  str[len] = '\0';
  return true;
}

/*
 * Implementação das funções do sistema
 */
