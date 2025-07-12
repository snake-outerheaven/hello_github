#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> // biblioteca do padrão POSIX, que fornece acesso a diversas funções do sistema 
		    // operacional, em sistemas Unix/Linux. ela contem chamadas de sistema(syscalls)
		    // para manipular arquivos, processos, entrada/saída e outras operações
// Programa que calcula a área de um triângulo utilizando a fórmula de Heron
// e verifica se os lados formam um triângulo válido.

void obtendo_lados(double lados[3]) { // função que obtem lados
    char resp[10];

    for (int x = 0; x < 3; x++) {
        int bool = 0;
        
        while (!bool) {
            printf("\n\nDigite o %d° lado: ", x + 1);
            
            if (scanf("%lf", &lados[x]) != 1) { // scanf retorna 0 se o valor lido for inválido
						// para o tipo de dado a ser recebido. %lf recebe
						// valores double(long float), um tipo de float 
						// com mais precisão. Tratamento de erros fundamentais.
                printf("\nDigite um número jumento!\n");
                getchar(); // limpeza do buffer stdin(standard input)
                continue; // continuação do loop infinito.
            }
            getchar();

            if (lados[x] <= 0) {
                printf("\nO lado não pode ser negativo ou zero. Digite novamente.\n");
                sleep(1); // syscall para o kernel parar o meu programa por 1 segundo.
                continue; 
            }

            printf("\nLado digitado: %.2lf, isto está correto? (S/N): ", lados[x]);
            fgets(resp, sizeof(resp), stdin);
            resp[strcspn(resp, "\n")] = '\0'; // limpeza do buffer(remove \n) string lida pelo fgets.
					      // strcspn percorre resp até encontrar \n e retorna o
					      // índice onde está \n, e o sinal de atribuição = 
					      // associa o valor à \n

            if (resp[0] == 's' || resp[0] == 'S') {
                printf("\nOk! Lado confirmado!");
                bool = 1; // bool recebe 1 se o lado for confirmado, quebrando o laço while(!bool)
            } else {
                printf("\nDigite o lado novamente.");
            }
        }
    }

    // Verificação da desigualdade triangular
    double a = lados[0], b = lados[1], c = lados[2];

    if (a < b + c && b < a + c && c < a + b) { // aqui faltou &&, pois todos os lados devem obedecer
					       // à regra de existência de um triângulo retângulo.
        printf("\nO triângulo existe, pois cumpre a regra da desigualdade triangular.");
    } else {
        printf("\n\nO triângulo NÃO existe, pois quebra a regra da desigualdade triangular.");
        printf("\n\nDeseja inserir outros lados? (S/N): ");
        fgets(resp, sizeof(resp), stdin);
        resp[strcspn(resp, "\n")] = '\0';

        if (resp[0] == 's' || resp[0] == 'S') {
		printf("Limpando tela...");
		sleep(2);
             	system("clear"); // limpeza de tela.
            	obtendo_lados(lados);  // Chamada recursiva correta
        } else {
            	printf("\nOk, saindo do programa...");
            	exit(-1);
        }
    }
}

int main(void) {
    double lados[3];
    char resp[10];
    int bool = 0;

    printf("\nEste é um programa que calcula a área um triângulo utilizando a fórmula de Heron.");
    sleep(1);
    printf("\nDigite os lados do triângulo.\n");
    sleep(1);
    obtendo_lados(lados);  // Chamada correta da função

    while (!bool) {
        printf("\nAbaixo segue a lista dos lados digitados:");
        for (int x = 0; x < 3; x++) {
            printf("\n\n%d° lado: %.2lf unidades de comprimento.", x + 1, lados[x]);
        }

        printf("\n\n\nOs lados estão corretos? (S/N): ");
        fgets(resp, sizeof(resp), stdin);
        resp[strcspn(resp, "\n")] = '\0';

        if (resp[0] == 's' || resp[0] == 'S') {
            printf("\nLados confirmados!");
            bool = 1;
        } else if(resp[0] == 'n' || resp[0] == 'N') {
            printf("\nDeseja repetir o programa? ");
            fgets(resp, sizeof(resp), stdin);
	    resp[strcspn(resp, "\n")] = '\0';
	    if(resp[0] == 's' || resp[0] == 'S'){
		    printf("\nOk,aguarde.");
		    sleep(1);
		    system("clear");
		    return main(); // retorno da main kkkkkkkkkkkkkkkk
	    }else{
		    printf("\nOk, encerrando o programa por segurança.");
		    sleep(1);
		    return -1;
	    }
        } else{
		printf("\nDigite uma resposta válida!");
		continue;
	}
    } 
    double a = lados[0], b = lados[1], c = lados[2];
    bool = 0;
    while(!bool){ // laço while desnecessário...
	    printf("\nDeseja ver a área do triângulo? ");
	    fgets(resp,sizeof(resp),stdin);
	    resp[strcspn(resp, "\n")] = '\0';
	    if(resp[0] == 'S' || resp[0] == 's'){
		    printf("\nOk, calculando a área...");
		    sleep(2);
		    double perimetro = a+b+c, semiper = perimetro/2;
		    double heron = sqrt(semiper*(semiper-a)*(semiper-b)*(semiper-c));
		    printf("\nA área do triângulo é: %.2lf unidades de área",heron);
		    printf("\nEncerrando o programa.");
		    sleep(2);
		    bool = 1;
	    }else{
		    printf("Ok! encerrando o programa");
		    sleep (1);
		    bool = 1;
	    }
    }
    return 0;
}
