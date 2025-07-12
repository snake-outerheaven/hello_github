// Implementar salvamento dos dados do cliente em um arquivo de texto na pasta
// /Codes
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


// Objetivo do código:
// Entender structs, e como vetorizar eles.
// Talvez seja interessante voltar naquele exemplo do banco,
// criar um registro de clientes, onde cada um vai ter um
// nome, número da conta, valor da conta corrente, ver se
// ele está em dívida com o banco se o valor da conta está
// abaixo de zero, perguntar se ele trabalha, e se sim,
// inserir a renda e colocar um rating dependendo da renda,
// além do nome da ocupação.
//
// Objetivo 2: buscar métodos de implementar a leitura do
// arquivo gerado, adicionar a adição de novos clientes
// colocar a função obtendo clientes como a função de
// reescrever o arquivo de texto: usando o struct
// cliente e o vetor de structs clientes(obtido com
// malloc) como ferramentas para a execução do objetivo

// Definindo o meu cliente como um struct.

typedef struct { // Essa forma de declarar structs é útil
                 // para eu usar cliente em qualquer lugar
                 // no código.
  char nome_cliente[100]; // 100 bits
  int numero_conta; // 1
  double conta_cliente; // 1 
  int status_divida; // bool bool1 = true
  int status_trabalho; // bool bool2 = false
  char ocupacao[100];
  double renda; //8
} cliente; // Meu cliente!

// Função para exibir o vetor de estruturas para o usuário, eu chamo ela no
// final da segunda função
void exibir_clientes(cliente *clientes,
                     int quantidade) { // int quantidade
                                       // vai receber
                                       // quantidade_clientes
                                       // a função usa como parâmetro clientes.
  printf("\n\n--- Clientes Cadastrados ---\n");
  for (int i = 0; i < quantidade; i++) {
    printf("\nCliente %d:\n", i + 1);
    printf("  Nome: %s\n", clientes[i].nome_cliente);
    printf("  Número da conta: %d\n", clientes[i].numero_conta);
    printf("  Saldo: %.2lf\n", clientes[i].conta_cliente);
    printf("  Em dívida: %s\n", clientes[i].status_divida
                                    ? "Sim"
                                    : "Não"); // estrutura lógica interessante
    printf("  Trabalha: %s\n", clientes[i].status_trabalho ? "Sim" : "Não");
    if (clientes[i].status_trabalho) {
      printf("  Renda: %.2lf\n", clientes[i].renda);
      printf("  Ocupação: %s\n", clientes[i].ocupacao);
    }
  }
} // Fim da função aqui

// Aqui vai vir a função que vai salvar os dados em um arquivo de texto.
void salvando_clientes(cliente *clientes, int quantidade) {
  char caminho[256]; // Abrindo o vetor que vai armazenar o caminho do meu
                     // arquivo.

  sleep(1);

  printf(
      "Imprimindo um arquivo de texto na pasta Codes do diretório home...\n");
  sleep(1);

  const char *home =
      getenv("HOME"); // ponteiro home recebe $HOME => (/home/user)

  if (home == NULL) {
    printf("Não foi possível adquirir o diretório home do seu usuário, "
           "por algum motivo...\n");
    sleep(1);
    printf("Encerrando a função de salvamento dos dados...\n");
    sleep(2);
    return;
  } else {
    snprintf(caminho, sizeof caminho, "%s/Codes/C/registroclientes.txt", home);
    // snprintf preenche caminho de forma especial, considerando o tamanho todo do buffer
    // Abrindo stream de dados para o arquivo que contem o caminho, lembrar de
    // fechar o arquivo depois de acabar.
    FILE *arquivo = fopen(caminho, "w"); // aqui, fopen abre o arquivo no modo de escrita(write)
					 // reescrevendo ou criando o arquivo toda a vez que for
					 // executado.

    if (arquivo == NULL) {
      sleep(1);
      printf(
          "\nNão foi possível criar o arquivo, veja se a pasta Codes existe.");
      return;
    }

    fprintf(arquivo, "Registro de clientes do banco.\n\n\n\n");

    for (int i = 0; i < quantidade; i++) {
      fprintf(arquivo, "Cliente %d\n\n", i + 1);
      fprintf(arquivo, "Nome: %s\n", clientes[i].nome_cliente);
      fprintf(arquivo, "Número da conta de %s: %d\n", clientes[i].nome_cliente,
              clientes[i].numero_conta);
      fprintf(arquivo, "Saldo de %s: %.2lf\n", clientes[i].nome_cliente,
              clientes[i].conta_cliente);
      fprintf(arquivo, "Em dívida: %s\n",
              clientes[i].status_divida ? "Sim" : "Não");
      fprintf(arquivo, "Trabalha: %s\n",
              clientes[i].status_trabalho ? "Sim" : "Não");
      if (clientes[i].status_trabalho) {
        fprintf(arquivo, "Renda de %s: %.2lf\n", clientes[i].nome_cliente,
                clientes[i].renda);
        fprintf(arquivo, "Ocupação de %s: %s\n", clientes[i].nome_cliente,
                clientes[i].ocupacao);
      }
      fprintf(arquivo,
              "\n\n\n\n"); // Abrindo espaço entre o registro de clientes.
    } // Fim do meu for de entrada de dados

    fclose(arquivo);

    printf("Dados salvos com sucesso em ~/Codes/C/registroclientes.txt\n");
  } // Fim do meu else de entrada de dados
} // Fim da minha função aqui

// aqui entra a função que mostra os clientes colocados no arquivo de texto.
//

void lendo_clientes_salvos(void) {
  printf("\nAguarde para poder ler o arquivo...");
  sleep(2);
  printf("\n\n\n");

  const char *home = getenv("HOME");
  const char *user = getenv("USER");

  if (home == NULL) {
    printf("Não foi possível obter o diretório home do usuário %s...", user);
    sleep(1);
    return;

  } else {
    char caminho[256]; // buffer do caminho do meu arquivo
    snprintf(caminho, sizeof caminho, "%s/Codes/C/registroclientes.txt", home);

    FILE *arquivo = fopen(caminho, "r"); // abro uma stream do tipo file, cujo endereço de memoria(ponteiro) é nomeado de arquivo
					 // para ficar mais facil o resto do código, o "r" abre o arquivo no modo de leitura(read)

    if (arquivo == NULL) {
      printf("Não foi possível ver o arquivo, veja se ele existe.");
      sleep(1);
      return;

    } else {
      // Lê e exibe o conteúdo do arquivo linha por linha
      char linha[256];
      printf("Conteúdo do arquivo %s:\n\n", caminho);
      while (fgets(linha, sizeof(linha), arquivo) != NULL) { // aqui fgets faz algo muito interessante,
							     // ele esta preenchendo a string linha, com o 
							     // tamanho de linha, da stream do tipo FILE arquivo
							     // parseia meu arquivo
        printf("%s", linha); 
	// mostra em tela os valores varridos por fgets
      } 
    }
    // de todo o jeito, um fopen sempre precisa de um fclose , melhor deixar ele fora caso de certo em ambos os códigos
    fclose(arquivo);
  } // fim do else quando é possível obter o usuário

} // fim da função aqui

// função que obtem clientes
void obtendo_clientes(void) {
  int quantidade_clientes;
  char resposta[10];

  // Saudações
  printf("\nFunção de registro iniciada.");
  sleep(5);

  // Loop até confirmação da quantidade de clientes
  do {
    printf(
        "\n\nPor favor, digite o número de clientes que serão registrados: ");
    while (scanf("%d", &quantidade_clientes) != 1 || quantidade_clientes <= 0) {
      sleep(1);
      printf("\nLetra ou número inválido detectado!\n");
      sleep(1);
      printf("Por favor, digite um número válido: ");
      getchar();
    }
    getchar();

    printf("\n%d é a quantidade de clientes certa? ", quantidade_clientes);
    fgets(resposta, sizeof(resposta), stdin);
    resposta[strcspn(resposta, "\n")] = '\0';
    if (resposta[0] == 'N' || resposta[0] == 'n') {
      printf("\nOk! Aguarde para reinserir a quantidade de clientes.\n");
      sleep(1);
    }
  } while (resposta[0] == 'N' || resposta[0] == 'n');

  // Alocação dinâmica do vetor da estrutura clientes.
  cliente *clientes = malloc(quantidade_clientes *
                             sizeof(*clientes)); // n precisa do header em C

  // Fazendo um teste para caso não tenha como alocar, encerrar o programa.
  if (clientes == NULL) {
    sleep(1);
    printf("\n\nAlocação da memória do computador para registro de dados"
           " dos clientes não foi possível"); 
    free(clientes); // liberando memória 
    return;
  }

  // Preenchimento de dados de cada cliente
  for (int i = 0; i < quantidade_clientes; i++) {
    do {
      // Coletando nome
      printf("\nDigite o nome do %dº cliente: ", i + 1);
      fgets(clientes[i].nome_cliente, sizeof(clientes[i].nome_cliente), stdin);
      clientes[i].nome_cliente[strcspn(clientes[i].nome_cliente, "\n")] = '\0';

      // Validação de nome não vazio
      while (clientes[i].nome_cliente[0] == '\0') {
        sleep(1);
        printf("\n\nNome vazio detectado! Digite novamente: ");
        fgets(clientes[i].nome_cliente, sizeof(clientes[i].nome_cliente),
              stdin);
        clientes[i].nome_cliente[strcspn(clientes[i].nome_cliente, "\n")] =
            '\0';
      }

      // Coletando número da conta
      printf("Digite o número da conta de %s: ", clientes[i].nome_cliente);
      while (scanf("%d", &clientes[i].numero_conta) != 1 ||
             clientes[i].numero_conta <= 0) {
        sleep(1);
        printf("Entrada inválida! Digite um número maior que 0: ");
        getchar();
      }
      getchar();

      // Coletando saldo
      printf("Digite o saldo da conta de %s: ", clientes[i].nome_cliente);
      while (scanf("%lf", &clientes[i].conta_cliente) != 1) {
        sleep(1);
        printf("Entrada inválida! Digite um valor numérico: ");
        getchar();
      }
      getchar();
      clientes[i].status_divida = (clientes[i].conta_cliente < 0);

      // Coletando status de trabalho
      printf("O cliente %s trabalha? (0 para não, 1 para sim): ",
             clientes[i].nome_cliente);
      while (scanf("%d", &clientes[i].status_trabalho) != 1 ||
             (clientes[i].status_trabalho != 0 &&
              clientes[i].status_trabalho != 1)) {
        sleep(1);
        printf("Entrada inválida! Digite 0 ou 1: ");
        getchar();
      }
      getchar();

      // Se trabalha, coleta renda e ocupação
      if (clientes[i].status_trabalho == 1) {
        printf("Digite a renda mensal de %s: ", clientes[i].nome_cliente);
        while (scanf("%lf", &clientes[i].renda) != 1 || clientes[i].renda < 0) {
          sleep(1);
          printf("Valor inválido! Digite um valor não-negativo: ");
          getchar();
        }
        getchar();

        printf("Digite a ocupação de %s: ", clientes[i].nome_cliente);
        fgets(clientes[i].ocupacao, sizeof(clientes[i].ocupacao), stdin);
        clientes[i].ocupacao[strcspn(clientes[i].ocupacao, "\n")] = '\0';
      } else {
        // Caso não trabalhe, zera renda e ocupação
        clientes[i].renda = 0.0;
        clientes[i].ocupacao[0] = '\0';
      }

      // Exibe resumo e pede confirmação dos dados
      printf("\nResumo do %d° cliente:\n", i + 1);
      printf("Nome: %s\n", clientes[i].nome_cliente);
      printf("Número da conta: %d\n", clientes[i].numero_conta);
      printf("Saldo: %.2lf\n", clientes[i].conta_cliente);
      printf("Em dívida: %s\n", clientes[i].status_divida ? "Sim" : "Não");
      printf("Trabalha: %s\n", clientes[i].status_trabalho ? "Sim" : "Não");
      if (clientes[i].status_trabalho) {
        printf("Renda: %.2lf\n", clientes[i].renda);
        printf("Ocupação: %s\n", clientes[i].ocupacao);
      }
      printf("Os dados estão corretos? (s/n): ");
      fgets(resposta, sizeof(resposta), stdin);
      resposta[strcspn(resposta, "\n")] = '\0';
    } while (resposta[0] == 'n' || resposta[0] == 'N');
    sleep(1);
  } // Fim do meu loop for!

  // Exibe todos os clientes cadastrados
  exibir_clientes(clientes, quantidade_clientes);

  // Salvando os dados dos clientes.
  salvando_clientes(clientes, quantidade_clientes);

  free(clientes); // Obrigado memória RAM!
} // Fim da minha função aqui.

// Função principal!
int main(void) {
  int opcao;
  system("clear");

  while (1) {
    printf("\n--- Menu do Sistema Bancário ---\n");
    printf("1. Registrar novos clientes (Também sobrescreve um registro já existente)\n");
    printf("2. Ler clientes salvos do arquivo\n");
    printf("3. Sair\n");
    printf("Escolha uma opção (1-3): ");

    if (scanf("%d", &opcao) != 1) {
      printf("Entrada inválida! Por favor, digite um número.\n");
      sleep(1);
      getchar();
      system("clear");
      continue;
    }

    getchar(); // Consome o '\n' deixado pelo scanf

    switch (opcao) {
    case 1:
      obtendo_clientes();
      break;
    case 2:
      lendo_clientes_salvos();
      break;
    case 3:
      printf("\nEncerrando o programa. Até mais!");
      printf("\n");
      sleep(2);
      return 0;
    default:
      printf("Opção inválida! Escolha entre 1 e 3.\n");
      sleep(1);
      system("clear");
    }

    sleep(1); // Espera um pouco antes de mostrar o menu novamente
  }
}

/*
Notas de funcionamento:

1. typedef struct cliente { ... };
   // Define o tipo 'cliente' com todos os campos necessários: nome, número da
conta,
   // saldo, status de dívida, status de trabalho, ocupação e renda.

2. void exibir_clientes(cliente *clientes, int quantidade);
   // Itera sobre o vetor de clientes e imprime cada campo formatado na tela
para o usuário.

3. void salvando_clientes(cliente *clientes, int quantidade);
   // Salva os dados dos clientes em um arquivo de texto em
~/Codes/registroclientes.txt.
   // - Constrói o caminho usando getenv("HOME") e snprintf.
   // - Abre o arquivo com fopen e verifica erros.
   // - Escreve os dados de cada cliente com fprintf em formato legível.
   // - Fecha o arquivo com fclose e exibe mensagem de sucesso.

4. void obtendo_clientes(void);
   // - Exibe uma saudação ao usuário e pausa com sleep.
   // - Solicita e valida a quantidade de clientes a serem registrados.
   // - Aloca dinamicamente um vetor de 'cliente' com malloc e verifica
falhas.
   // - Para cada cliente no vetor:
   //     * Lê e valida o nome (não vazio).
   //     * Lê e valida o número da conta (inteiro > 0).
   //     * Lê e valida o saldo (double).
   //     * Determina automaticamente se está em dívida (saldo < 0).
   //     * Lê o status de trabalho (0 ou 1).
   //     * Se trabalha, lê renda (double >= 0) e ocupação (string).
   //     * Exibe um resumo dos dados e pede confirmação; repete se resposta
for 'n'.
   // - Após preencher todos os clientes, chama exibir_clientes para exibir os
dados.
   // - Chama salvando_clientes para salvar os dados em um arquivo.
   // - Libera a memória alocada com free.

5. int main(void);
   // Função principal que chama obtendo_clientes() e encerra o programa.
*/
