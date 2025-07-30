#include <string.h>
#include <stdio.h>
#include <stdlib.h>
// checar final do código para a sessão comentada de explicações.
// Pedir o nome de um aluno e dar a média ponderada considerando pesos dados pelo usuário
int main(void) {
    char aluno[100], resp[10];
    float nota[5], peso[5], media, somaponderada = 0, somapesos = 0;
    int num_notas, i;
    int confirmado = 0; // Variável de controle lógico (booleano)

    do {
        printf("\nDigite o nome do aluno do qual voce calculara as medias: ");
        fgets(aluno, sizeof(aluno), stdin);
        aluno[strcspn(aluno, "\n")] = '\0'; // procura na string o new line e substitui
					    // por '\0', que indica o fim de uma string.
        printf("\n%s eh o nome do aluno digitado. Isto esta correto? (S/N): ", aluno);
        fgets(resp, sizeof(resp), stdin);
        resp[strcspn(resp, "\n")] = '\0'; 

        if (resp[0] == 'S' || resp[0] == 's') {
            confirmado = 1; // Define que o nome foi confirmado, encerrando o loop
        } else if (resp[0] == 'N' || resp[0] == 'n') {
            system("clear"); // Limpa a tela para permitir nova entrada
        } else {
            printf("\nResposta inválida! Digite 'S' para confirmar ou 'N' para mudar.\n");
        }

    } while (!confirmado); // Mantém o loop ativo enquanto confirmado for 0 (falso)

    printf("\nNome confirmado: %s\n", aluno);

    // Solicita ao usuário quantas notas deseja inserir
    printf("\nQuantas notas deseja inserir (máximo 5)? ");
    scanf("%d", &num_notas);

    // Limpa o buffer após scanf para evitar problemas com fgets
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    // Entrada de notas e pesos
    for (i = 0; i < num_notas; i++) {
        printf("\nDigite a %dª nota: ", i + 1);
        scanf("%f", &nota[i]);

        printf("Digite o peso da %dª nota: ", i + 1);
        scanf("%f", &peso[i]);

        somaponderada += nota[i] * peso[i]; // Multiplica a nota pelo peso e soma
        somapesos += peso[i]; // Soma os pesos para calcular a média posteriormente
    }

    // Cálculo da média ponderada
    if (somapesos > 0) {
        media = somaponderada / somapesos;
        printf("\nA média ponderada de %s é: %.2f\n", aluno, media);
    } else {
        printf("\nErro: Os pesos devem ser maiores que zero.\n");
    }

    return 0;
}
