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

// ############################################################
// # 🔍 O QUE É UM VALOR BOOLEANO E COMO FOI USADO NO CÓDIGO? #
// ############################################################
//
// Um **valor booleano** é um tipo de variável que representa **verdadeiro ou falso**.
// Em C, não existe um tipo `bool` nativo (como em outras linguagens como Python ou Java), 
// mas podemos usar `int` para representar estados lógicos:
//
// - `0` → Representa **falso** (false).
// - Qualquer outro valor diferente de `0` → Representa **verdadeiro** (true).
//
// 💡 **Uso no código:**
// O código usa a variável `int confirmado = 0;` para controlar o fluxo da confirmação do nome:
// - Se o usuário digita `"S"` para confirmar, `confirmado = 1;`, encerrando o loop.
// - Se ele digita `"N"`, `system("clear")` é chamado e o loop continua.
// - Se a resposta for inválida, ele avisa e pede para tentar novamente.
//
// ✅ **Vantagens de usar um controle lógico ao invés de `goto`**
// - O código fica mais **organizado e intuitivo**.
// - Evita **saltos inesperados** no fluxo do programa.
// - Facilita a **manutenção e depuração**, sem precisar rastrear labels.
//
// Agora o código está **mais legível, seguro e eficiente**! 🚀✨

// ###############################################################
// # 🔍 POR QUE USAMOS `while(getchar() != '\n' && getchar() != EOF);`? #
// ###############################################################
//
// 🚀 **O problema do `scanf` e o buffer de entrada**
// - Quando usamos `scanf("%d", &num);`, o usuário digita um número e pressiona **Enter**.
// - O `scanf` lê o número, mas **deixa o `\n` (nova linha) no buffer**.
// - Se depois usamos `fgets()`, ele pode capturar esse `\n`, causando erros na leitura.
//
// 🔥 **Por que `getchar();` sozinho não resolve?**
// - `getchar();` lê **apenas um caractere**.
// - Se houver **mais de um caractere sobrando no buffer**, ele **não limpa completamente**.
// - Isso pode causar problemas em futuras entradas do usuário.
//
// ✅ **A solução completa: `while(getchar() != '\n' && getchar() != EOF);`**
// - Este loop **remove tudo** que estiver no buffer **até encontrar o '\n'**.
// - Se o usuário digitou `"123abc"`, ele **consome todos os caracteres restantes**.
// - Funciona bem **antes de `fgets()`**, garantindo que ele capture corretamente a próxima entrada.
//
// 🎯 **Exemplo Prático**
// ```c
// int idade;
// char nome[50];
//
// printf("Digite sua idade: ");
// scanf("%d", &idade);
//
// // Limpa o buffer após scanf
// while(getchar() != '\n' && getchar() != EOF);
//
// printf("Digite seu nome: ");
// fgets(nome, sizeof(nome), stdin);
// nome[strcspn(nome, "\n")] = '\0';
//
// printf("\nNome: %s\nIdade: %d\n", nome, idade);
// ```
//
// ✅ **Aqui garantimos que a leitura do nome ocorra corretamente, sem interferências do `scanf` anterior**.
//
// 🏆 **Resumo**
// - `getchar();` **não limpa completamente o buffer**.
// - `while(getchar() != '\n' && getchar() != EOF);` **remove resíduos deixados pelo `scanf`**.
// - Isso é **essencial** quando usamos `fgets` após `scanf`.
// - Com essa técnica, o programa **funciona corretamente sem erros de entrada**! 🚀✨
// ###############################################################
// # 🔍 POR QUE USAMOS `while(getchar() != '\n' && getchar() != EOF);` COM `scanf`? #
// ###############################################################
//
// 🚀 **O problema do `scanf` e o buffer de entrada**
// - Quando usamos `scanf("%d", &num);`, o usuário digita um número e pressiona **Enter**.
// - O `scanf` lê o número corretamente, MAS deixa **o caractere '\n' (nova linha) no buffer**.
// - Se depois chamarmos `fgets()`, ele pode capturar esse `\n` e acabar ignorando uma entrada do usuário.
//
// 🔥 **Por que `getchar();` sozinho não resolve?**
// - `getchar();` lê **apenas um caractere** e pode não limpar completamente o buffer.
// - Se houver mais de um caractere sobrando (exemplo: `"123abc"`), `getchar();` só removerá **um deles**, deixando resíduos.
//
// ✅ **A solução correta: `while(getchar() != '\n' && getchar() != EOF);`**
// - Esse loop consome **todos os caracteres restantes** até encontrar a **nova linha (`\n`)**.
// - Se o usuário digitou `"123abc"`, ele irá **remover os caracteres não lidos corretamente**.
// - Isso **garante que `fgets()` leia apenas a entrada correta**, sem interferências.
//
// 🎯 **Exemplo prático**
// ```c
// int idade;
// char nome[50];
//
// printf("Digite sua idade: ");
// scanf("%d", &idade);
//
// // Limpa o buffer após scanf
// while(getchar() != '\n' && getchar() != EOF);
//
// printf("Digite seu nome: ");
// fgets(nome, sizeof(nome), stdin);
// nome[strcspn(nome, "\n")] = '\0';
//
// printf("\nNome: %s\nIdade: %d\n", nome, idade);
// ```
//
// ✅ **Aqui garantimos que a leitura do nome ocorra corretamente, sem interferências do `scanf` anterior**.
//
// 🏆 **Resumo**
// - `getchar();` **não limpa completamente o buffer**.
// - `while(getchar() != '\n' && getchar() != EOF);` **remove resíduos deixados pelo `scanf`**.
// - Isso é **essencial** quando usamos `fgets` após `scanf`, evitando capturas indesejadas de `\n`.
// - Com essa técnica, seu código **funcionará corretamente sem problemas de entrada**! 🚀✨
