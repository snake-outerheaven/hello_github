//#include <math.h> // bibliotec para funções matemáticas ( sin, cos, tan ( outras trigonométricas ) pow,sqrt etc etc
#include <stdio.h> // biblioteca padrão (std) de saída e entrada de dados ( io )
#include <stdlib.h> // biblioteca padrão que contem funções muito uteis, como free
#include <string.h> //bibliotec padrao (std) com funções para manipular strings ( strcpy , strlen, strcmp, strcspn, strcat, etc,etc)
#include <unistd.h> // biblioteca do padrão POSIX ( para sistemas que cumprem esse modelo de uniformização de sistemas baseados em UNIX )

/* refazer programa de notas */

// função que retorna o nome do aluno

char* obtendo_aluno(void) {
  char* nome = malloc(100 * sizeof(char)); // ponteiro da minha string ( devo
                                           // usar uma referencia de tipo char )

  char resposta[5]; // declaro um array de 10 caracteres para armazenar a
                    // confirmação do usuário

  if (nome == NULL) { // se houve falha de alocação de memória, limpo tudo e
                      // encerro o código
    sleep(1);
    printf("\n\n");
    printf("Não foi possível registrar o nome do aluno! Falha de alocação de "
           "memória!");
    free(nome);
    exit(1);
  } else {
    sleep(1); // apenas espero o tempo passar em segundos

    printf("Digite o nome do aluno: "); // printf normal para pedir o nome do aluno

    fgets(nome, 100 * sizeof(char),
          stdin); // lê nome, o nome de nome, do stdin ( buffer padrão de
                  // entrada de dados, para onde o meu teclado envia os dados )

    nome[strcspn(nome, "\n")] =
        '\0'; // strcspn, caça newline na string, retorna o index ( já que a
              // minha string é um vetor de caracteres )

    printf("\n\n"); // pulando linhas
    
    sleep(1);

    printf("Por favor, confirme se %s está correto (s/n): ", nome);

    fgets(resposta, sizeof(resposta), stdin);

    resposta[strcspn(resposta, "\n")] = '\0';

    if (strcmp(resposta, "s") == 0) {
      printf("\n\n");
      sleep(1);
      printf("Certo, nome %s confirmado!", nome);
      return nome; // retorna o ponteiro que aponta para a minha string
    } else if (strcmp(resposta, "n") == 0) {
      printf("\n\n");
      sleep(1);
      printf("Certo! Limpando tela e reiniciando função de inserir nome...");
      free(nome);
      sleep(1);
      system("clear");
      printf("\n\n");
      return obtendo_aluno(); // recursividade
    } else {
      printf("\n\n");
      sleep(1);
      printf("Resposta inválida detectada!");
      printf("\n");
      printf("Encerrando o código por segurança.");
      sleep(1);
      free(nome);
      exit(1);
    }
  }
}

/*recebe o ponteiro de memória referente ào nome do aluno*/

double* obtendo_notas(char* nome){
  double* notas = malloc(3 * sizeof(double));
  // aloco 3x o tamanho de um double na heap
  // para retornar um endereço de memória que contem as notas
  char resposta[5];

  if(notas == NULL){
    sleep(1);
    printf("\n\n");
    printf("Não foi possível criar espaço de registro das notas na memória do computador");
    free(notas);
    exit(1);
  }else{
    printf("\n\n");
    printf("Inicializando registro...");
    sleep(2);
    printf("\n\n");

    for(int x = 0; x < 3; x++){
	    printf("");
    }
  } // fim do else aqui
} // fim da função aqui

int main ( void ) {
	char* aluno = obtendo_aluno();
	// a unica variavel para uma função que retorna um ponteiro char é um ponteiro char
	printf("\n%s\n",aluno);
	free(aluno); // liberando a memória usada por aluno
	return 0;
}
