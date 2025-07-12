
#include <math.h>    // Biblioteca de funções matemáticas (M_PI não funciona, por isso usamos 3.14)
#include <stdio.h>
#include <string.h>
#include <unistd.h>  // Para a função sleep (Linux)

void area_circulo(double raio) { 
    const double pi = 3.14;
    double area = pi * pow(raio, 2);
    printf("\nA área do círculo é: %.2f", area);
}

void circunferencia(double raio) {
    const double pi = 3.14;
    double circ = 2 * pi * raio;
    printf("\nA circunferência do círculo é: %.2f", circ);
}

int main(void) {
    double raio;
    char resp[10];
    int bool = 1; // Variável de controle para garantir entrada válida(estudar booleanos mais tarde)

    printf("Este é um programa que calcula a área de um círculo e sua circunferência.\n\n");

    do {
        sleep(2);

        // Loop para garantir que o usuário insira um raio válido (maior que zero)
        while (bool == 1) {
            printf("\nDigite um raio válido (maior que zero): ");
            if (scanf("%lf", &raio) != 1 ) {  // Verifica se a entrada é numérica(scanf retorna 0 se ler um valor inválido)
		sleep(2);
                printf("\nEntrada inválida! Digite apenas números.\n");
                getchar();  // Limpa o buffer
                continue;   // Solicita nova entrada , repetindo o loop principal
            }
            getchar(); // Limpa qualquer resíduo no buffer

            if (raio > 0) {
                bool = 0; // Saímos do loop ao obter um valor válido
            } else {
                printf("\nO raio deve ser maior que zero!\n");
            }
        }

        sleep(1);
        printf("\n\nDeseja ver a área e a circunferência do círculo de raio %.2f? (S/N): ", raio);
        fgets(resp, sizeof(resp), stdin);
        resp[strcspn(resp, "\n")] = '\0';
        bool = 1;  // Reinicia a variável de controle para a próxima iteração

        if (resp[0] == 's' || resp[0] == 'S') {
            printf("\n\nCalculando a área e a circunferência do círculo...");
            sleep(2);
            area_circulo(raio);
            circunferencia(raio);
	    bool = 0;
        } else if (resp[0] == 'n' || resp[0] == 'N') {
            printf("\nOk, encerrando o programa.\n");
            return 0;
        } else {
            printf("\npipipopo!\n");
            return 3;
        }

    } while (bool == 1);

    return 0;
}

/* 
Sessão comentada:

Neste código, as funções 'area_circulo' e 'circunferencia' foram definidas com o tipo void, o que significa que elas
não retornam nenhum valor. Em vez disso, cada função realiza seu cálculo (área ou circunferência do círculo) e 
imprime o resultado diretamente com printf(). Esse uso de void é útil quando não se precisa que a função devolva um 
valor para o main, mas apenas exiba um resultado ou execute uma ação.

Outros pontos importantes:
- O loop de validação (while com a variável "bool") garante que o usuário insira um valor numérico válido e maior que zero.
  Se o usuário digitar uma entrada inválida (por exemplo, letras ou palavras), scanf() falhará (retornará 0) e o programa 
  exibirá uma mensagem de erro, solicitando nova entrada.
- Após a validação do raio, o programa pergunta se o usuário deseja ver os resultados. Se a resposta for "S", as funções
  void são chamadas para calcular e imprimir a área e a circunferência; se for "N", o programa encerra. Qualquer outra 
  entrada resulta na mensagem "pipipopo!" e termina o programa com código 3.
*/
