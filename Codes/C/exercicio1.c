#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
// vamos começar a reescrita deste código, implementando modularização estilo UNIX, ou seja, faça uma coisa bem
// na pratica isso significa que, vou estar criando funções simples que podem ser reutilizadas uma dentro da 
// outra permitindo escalabilidade de forma bastante facilitada

void limpar_tela (void) {

// função que busca limpar a tela de forma portátil
// me utilizei de macros que me permitem configurar
// como o programa é executado

#ifdef _WIN32
    system("cls");

#else
    system("clear");

#endif

}


void trim (char *entrada) {
    

    // função que busca remover todo os tipos de whitespace de uma string recebida do usuário
    

    int len = strlen(str); // inicializo uma variável que recebe o valor do tamanho da str
    while(len > 0 && str[len - 1] == ' ' || str[len - 1] == '\n'|| str[len - 1] == '\r'|| str[len - 1] == '\t') 
        // enquanto len for maior que zero e o caracter em len - 1 for algum desses:
    {
                
                str[len - 1] = '\0'; 
                // coloco o caracter que determina o fim da string.
                // por que isso? uma string em C pode ser imaginada como
                // um conjunto de caracteres cercado por infinitos \0
                // acho que faz sentido imaginar isso.
                
                len--; // diminui o tamanho de len até zero
    }
} // fim da minha função aqui
    

/* Programa que converte graus Celsius para Fahrenheit ( V Inicial, de meses atrás )
int main() {
    float celsius, fahrenheit;
    char resp[4];

    do {
        // Solicita o valor em Celsius
        printf("\nDigite um valor em Celsius para conversao em Fahrenheit: ");
        scanf("%f", &celsius);
        getchar(); // limpa o buffer de entrada
        // Calcula Fahrenheit: F = (C * 9/5) + 32
        fahrenheit = (celsius * 9.0 / 5.0) + 32;

        // Exibe o resultado
        printf("%.2f graus Celsius equivalem a %.2f graus Fahrenheit.\n", celsius, fahrenheit);
        // Pergunta se o usuário deseja continuar
        printf("Deseja converter outro valor? (sim/nao): ");
	fgets(resp, sizeof(resp), stdin);
	resp[strcspn(resp, "\n")] = '\0';
        if (strcmp(resp,"sim") == 0 || strcmp(resp,"s") == 0 || strcmp(resp,"Sim") == 0 || strcmp(resp,"S") == 0){
		system("clear");

                }
      }while (strcmp(resp,"sim") == 0 || strcmp(resp,"s") == 0 || strcmp(resp,"Sim") == 0 || strcmp(resp,"S") == 0);
    return 0;
}

*/
