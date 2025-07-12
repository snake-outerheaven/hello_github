#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Dado um vetor de inteiros nums e um inteiro target,
// target define quantos elementos de nums serão somados (pela posição)
// e depois exibe o valor resultante da soma dos elementos de nums.
int main() {
    int nums[5] = {2, 3, 12, 20, 30};
    int tamanho = sizeof(nums) / sizeof(nums[0]); // fórmula que vale investigação depois.
						  // tomando gap da matemática básica kkk
    int target, x, soma;
    char resp[10];

    do {
        // Exibe a lista de números com seus índices
        printf("\nAbaixo segue uma lista de números:\n");
        for (x = 0; x < tamanho; x++){
            printf("--\n");
            printf("|%d| --> %d", nums[x], x + 1);
            printf("\n--");
        }

        int bool = 0; //bool inicizalado para 
        do {
            soma = 0; // Reinicia a soma para cada nova tentativa
            printf("\nDigite um valor para determinar quantos elementos da lista serão somados: ");
            scanf("%d", &target);
            getchar();  // Mantido conforme implementação original

            // Validação: target deve ser maior que 0 e menor ou igual ao número de elementos do array.
            if (target > 0 && target <= tamanho) {  
                bool = 1;
            } else {
                printf("\nDigite um valor válido!\n");
            }
        } while (!bool);

        // Soma os 'target' primeiros elementos do array
        for (x = 0; x < target; x++){
            soma += nums[x];
        }
        printf("\nA soma dos números da lista até o índice %d (soma dos %d primeiros elementos) é %d!\n", target, target, soma);

        // Lê a resposta para determinar se o usuário deseja repetir o processo
        printf("\nDeseja tentar outro valor? (S/N): ");
        fgets(resp, sizeof(resp), stdin);
        resp[strcspn(resp, "\n")] = '\0';

        // Se a resposta for 'S' ou 's', limpa a tela antes de reiniciar o loop
        if (resp[0] == 'S' || resp[0] == 's') {
            system("clear");  // Utilizar "cls" no Windows
        }
    } while (resp[0] == 'S' || resp[0] == 's');

    return 0;
}

// ###############################################################
// Resumo do aprendizado durante o desenvolvimento do código:
//
// 1. Utilizou-se um array para armazenar números, e o tamanho do array foi calculado
//    com a expressão sizeof(nums) / sizeof(nums[0]).
//
// 2. A lista de números é exibida com seus respectivos índices para facilitar a seleção de um valor,
//    que define quantos elementos serão somados.
//
// 3. Foi implementado um loop do-while para validar a entrada, garantindo que o valor informado (target)
//    seja maior que 0 e menor ou igual ao total de elementos do array.
//
// 4. Um loop for foi empregado para somar os primeiros "target" elementos do array, utilizando o operador (+=)
//    para acumular o resultado.
//
// 5. A função scanf foi utilizada para ler valores numéricos e fgets para capturar respostas (strings) do usuário,
//    mantendo o uso do getchar() conforme a implementação original para parte da limpeza do buffer.
//
// 6. Um segundo loop do-while permite que a operação seja repetida, e o comando system("clear") é usado para
//    limpar a tela (observando que, no Windows, "cls" deve ser utilizado).
// ###############################################################
