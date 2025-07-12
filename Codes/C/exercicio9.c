#include <stdio.h>
#include <stdlib.h> // vamos estudar alocação dinâmica de memória na terceira função.
#include <string.h>
#include <unistd.h>

// criar um programa que calcula a média das contas de luz pagas em um ano
// as contas estarão contidas em um vetor
// haverá validação de entrada de dados.
// vou precisar estudar malloc e free para fazer a terceira e última função.
// não é dificil, apenas seguir o formato para fazer o malloc, colocar um if
// encerrando o programa se não foi possível alocar a memória, e depois liberar
// ela dps do uso, para evitar vazamentos de memória.

void obtendo_listas(
    double lista_contas[12]) { // obtendo as listas, o vetor dentro da função
                               // principal receberá esta função
  char resp[10];
  for (int x = 0; x < 12; x++) {
    do {
      sleep(1);
      printf("\nDigite o valor da %dº conta: ", x + 1);
      while (scanf("%lf", &lista_contas[x]) != 1 || lista_contas[x] < 0) {
        if (scanf("%lf", &lista_contas[x]) != 1) {
          sleep(1);
          printf("\nPor favor, digite um número...");
          printf("\nDigite o valor da %dº conta: ", x + 1);
          getchar();
          continue;
        } else if (lista_contas[x] < 0) {
          sleep(1);
          printf("\nDigite um número válido para contas( conta deve ser maior "
                 "ou igual a 0 )");
          printf("\nDigite o valor da %dº conta: ", x + 1);
          getchar();
          continue;
        }
      }
      getchar();
      sleep(1);
      printf("%.2lf é o número digitado, isto procede? ", lista_contas[x]);
      fgets(resp, sizeof(resp), stdin);
      resp[strcspn(resp, "\n")] = '\0';
    } while (resp[0] == 'n' || resp[0] == 'N');
  }
} // fim da função aqui.

double
obtendo_media(double lista_contas[12]) { // tive que mudar o tipo de função pois
                                         // ela agora retorna um valor double
  double sum = 0;
  int quantidade = 12;
  for (int x = 0; x < quantidade; x++) {
    sum += lista_contas[x];
  }
  return sum / 12; // não foi muito difícil entender isso aqui, já que q estou
                   // obtendo uma variável double

} // fim da função aqui.

void avaliando_contas(double lista_contas[12], double media) {
  int quantidade = 12;
  int quantidade_menor = 0, quantidade_maior = 0, quantidade_igual = 0;
  for (int x = 0; x < quantidade; x++) {
    if (lista_contas[x] < media) {
      quantidade_menor++;
    } else if (lista_contas[x] > media) {
      quantidade_maior++;
    } else {
      quantidade_igual++;
    }
  }
  // alocando memória para criar um vetor dinâmico.
  double *lista_menor = (double *)malloc(quantidade_menor * sizeof(double));
  double *lista_maior = (double *)malloc(quantidade_maior * sizeof(double));
  double *lista_igual = (double *)malloc(quantidade_igual * sizeof(double));

  // liberando memória e encerrando o programa caso não dê para alocar a
  // memória.
  if (lista_menor == NULL || lista_igual == NULL || lista_maior == NULL) {
    printf("\nErro ao alocar memória.");
    free(lista_maior), free(lista_igual), free(lista_menor);
    return;
  }
  // inserindo os valores nas listas criadas pelo malloc.
  int idx_menor = 0, idx_maior = 0,
      idx_igual = 0; // indices dos meu vetores dinâmicos.
  for (int x = 0; x < quantidade; x++) {
    if (lista_contas[x] < media) {
      lista_menor[idx_menor] = lista_contas[x];
      idx_menor++;
    } else if (lista_contas[x] > media) {
      lista_maior[idx_maior] = lista_contas[x];
      idx_maior++;
    } else {
      lista_igual[idx_igual] = lista_contas[x];
      idx_igual++;
    }
  }
  // inicio do fim, apresentar a média, a lista de contas e depois as listas dos
  // dados tratados.
  sleep(1);
  printf("\nA média das contas inseridas é: %.2lf\n\n", media);

  // apresentando as listas
  printf("Abaixo seguem as listas de contas, incluindo a avaliação das contas "
         "comparadas com a média.\n\n");
  sleep(1);
  printf("Lista das contas de luz:\n");
  for (int x = 0; x < quantidade; x++) {
    printf("|%.2lf|\n", lista_contas[x]);
  }
  printf("\n");
  sleep(1);
  printf("Lista de contas maiores que a média:\n");
  if (quantidade_maior == 0) {
    printf("Não há valores.\n\n");
  } else {
    for (int x = 0; x < quantidade_maior; x++) {
      printf("|%.2lf|\n", lista_maior[x]);
    }
    printf("\n");
  }
  sleep(1);
  printf("Lista de contas menores que a média:\n");
  if (quantidade_menor == 0) {
    printf("Não há valores.\n\n");
  } else {
    for (int x = 0; x < quantidade_menor; x++) {
      printf("|%.2lf|\n", lista_menor[x]);
    }
    printf("\n");
  }
  sleep(1);
  printf("Lista de contas iguais à média:\n");
  if (quantidade_igual == 0) {
    printf("Não há valores.\n\n");
  } else {
    for (int x = 0; x < quantidade_igual; x++) {
      printf("|%.2lf|\n", lista_igual[x]);
    }
    printf("\n");
  }
  // Seção para gerenciar a criação e escrita do arquivo de texto na pasta
  // ~/Codes

  // Declara um buffer de 256 caracteres para armazenar o caminho completo do
  // arquivo. Esse tamanho é suficiente para a maioria dos caminhos de arquivo
  // em sistemas Unix.
  char caminho[256];

  // Obtém o valor da variável de ambiente HOME, que contém o diretório home do
  // usuário (ex.: /home/usuario). A função getenv retorna uma string ou NULL se
  // falhar.
  const char *home = getenv("HOME");

  // Verifica se o diretório home foi obtido com sucesso. Se home for NULL,
  // significa que a variável HOME não está definida (algo raro), e um erro é
  // exibido.
  if (home == NULL) {
    printf("\nErro: Não foi possível obter o diretório home.\n");
  } else {
    // Constrói o caminho completo do arquivo combinando o diretório home com
    // /Codes/contas_luz.txt. A função snprintf formata a string de forma
    // segura, evitando estouros de buffer, e usa o tamanho máximo de caminho
    // (256).
    snprintf(caminho, sizeof(caminho), "%s/Codes/contas_luz.txt", home);

    // Tenta abrir o arquivo no modo "w" (escrita). Isso cria um novo arquivo ou
    // sobrescreve o existente no caminho especificado. A função fopen retorna
    // um ponteiro FILE* se bem-sucedida ou NULL se falhar (ex.: pasta
    // inexistente).
    FILE *arquivo = fopen(caminho, "w");

    // Verifica se a abertura do arquivo falhou. Se arquivo for NULL, exibe uma
    // mensagem de erro com o caminho completo, sugerindo que o usuário
    // verifique se a pasta ~/Codes existe (deve ser criada manualmente com
    // mkdir ~/Codes).
    if (arquivo == NULL) {
      printf("\nErro ao criar o arquivo %s. Verifique se a pasta ~/Codes "
             "existe.\n",
             caminho);
    } else {
      // Se o arquivo foi aberto com sucesso, começa a escrever os dados.

      // Escreve a média das contas no arquivo, formatada com duas casas
      // decimais, seguida de duas quebras de linha para separar do próximo
      // conteúdo.
      fprintf(arquivo, "A média das contas inseridas é: %.2lf\n\n", media);

      // Adiciona um texto descritivo para introduzir as listas, com duas
      // quebras de linha para melhorar a formatação no arquivo.
      fprintf(arquivo, "Abaixo seguem as listas de contas, incluindo a "
                       "avaliação das contas comparadas com a média.\n\n");

      // Escreve o título da lista de todas as contas de luz, seguido de uma
      // quebra de linha.
      fprintf(arquivo, "Lista das contas de luz:\n");

      // Loop para escrever cada valor do array lista_contas no arquivo.
      // Usa |%.2lf| para formatar cada valor com duas casas decimais e adiciona
      // uma quebra de linha após cada um.
      for (int x = 0; x < quantidade; x++) {
        fprintf(arquivo, "|%.2lf|\n", lista_contas[x]);
      }

      // Adiciona uma quebra de linha extra para separar esta seção da próxima.
      fprintf(arquivo, "\n");

      // Escreve o título da lista de contas maiores que a média.
      fprintf(arquivo, "Lista de contas maiores que a média:\n");

      // Verifica se não há valores na lista_maior. Se quantidade_maior for 0,
      // escreve "Não há valores" com duas quebras de linha.
      if (quantidade_maior == 0) {
        fprintf(arquivo, "Não há valores.\n\n");
      } else {
        // Se houver valores, percorre o array lista_maior e escreve cada um.
        for (int x = 0; x < quantidade_maior; x++) {
          fprintf(arquivo, "|%.2lf|\n", lista_maior[x]);
        }
        // Adiciona uma quebra de linha extra após a lista.
        fprintf(arquivo, "\n");
      }

      // Repete o processo para a lista de contas menores que a média.
      fprintf(arquivo, "Lista de contas menores que a média:\n");
      if (quantidade_menor == 0) {
        fprintf(arquivo, "Não há valores.\n\n");
      } else {
        for (int x = 0; x < quantidade_menor; x++) {
          fprintf(arquivo, "|%.2lf|\n", lista_menor[x]);
        }
        fprintf(arquivo, "\n");
      }

      // Repete o processo para a lista de contas iguais à média.
      fprintf(arquivo, "Lista de contas iguais à média:\n");
      if (quantidade_igual == 0) {
        fprintf(arquivo, "Não há valores.\n\n");
      } else {
        for (int x = 0; x < quantidade_igual; x++) {
          fprintf(arquivo, "|%.2lf|\n", lista_igual[x]);
        }
        fprintf(arquivo, "\n");
      }

      // Fecha o arquivo, garantindo que todos os dados sejam salvos no disco
      // e liberando os recursos do sistema operacional.
      fclose(arquivo);

      // Exibe uma mensagem na tela confirmando que o salvamento foi
      // bem-sucedido, incluindo o caminho completo do arquivo para referência
      // do usuário.
      printf("\nResultados salvos em %s com sucesso!\n", caminho);
    }
  }

  // Liberando a memória alocada, obrigado heap!
  free(lista_menor);
  free(lista_maior);
  free(lista_igual);
} // função acaba aqui.

// agora sim, vamos executar o programa na função main.
int main(void) {
  double lista_contas[12];
  double media;

  printf("Bem-vindo ao programa de cálculo de média de contas de luz!\n");
  sleep(1);
  obtendo_listas(lista_contas);
  media = obtendo_media(lista_contas);
  avaliando_contas(lista_contas, media);

  return 0;
}
