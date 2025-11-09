#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

/*
 * Macros úteis ao sistema
 */
#define MAX_CLIENT_NUMBER 10
#define LIM_MONEY 700.0F
/*
 * Enums úteis ao sistema
 */

/*
 * Estado do cliente no sistema
 */
typedef enum estado {
  ATIVO,
  OCIOSO,
  DESCONECTADO,
} Estado;

/*
 * Estruturas úteis ao sistema
 */

/*
 * Estrutura de dados que representa o cliente do banco
 */
typedef struct cliente {
  unsigned long long id;
  char nome_cliente[50];
  uint8_t numero_conta;
  Estado status;
  float saldo;
  bool status_divida;
  bool status_trabalho;
  char ocupacao[50];
  float renda;
} Cliente;

/*
 * Protótipo de funções utilitárias do sistema
 */

bool trim(char *str);
unsigned long long criarRand(void);
/*
 * Protótipo de funções essenciais
 */
 Cliente* criarCliente(void){

 }
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

unsigned long long criarRand(void) {
  unsigned long long r = 0;
  static int seed = 0;
  if (!seed) {
    srand((unsigned int)time(NULL));
    seed = 1;
  }
  r |= (unsigned long long)(rand() & 0XFFFF) << 0;
  r |= (unsigned long long)(rand() & 0XFFFF) << 16;
  r |= (unsigned long long)(rand() & 0XFFFF) << 32;
  r |= (unsigned long long)(rand() & 0XFFFF) << 48;
  return r;
}

/*
 * Implementação das funções do sistema
 */
