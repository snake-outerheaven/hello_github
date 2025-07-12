#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// escrever uma função recursiva para calcular a sequencia de Collatz



void SeqCollatz( int numero_do_usuario) {

	if ( numero_do_usuario == 1){
		 printf("\n%d",numero_do_usuario);
		 sleep(1);
		 printf("\n\nFim da sequencia!");
		 return;

		 
	}
	if ( numero_do_usuario != 1 ) {
		sleep (1);
		printf("\n%d\n", numero_do_usuario);

		SeqCollatz(numero_do_usuario % 2 == 0
				? numero_do_usuario /2 
				: numero_do_usuario * 3 + 1);
	}


} // fim da minha função aqui



int main (void){
	int numero_do_usuario;

	while(1){
		printf("\n\n");
		sleep(1);
		printf("Digite um número inteiro para calcular a sequencia de Collatz dele: ");
		while (scanf("%d",&numero_do_usuario) != 1|| numero_do_usuario < 0){
			sleep(1);
			printf("\nValor inválido detectado! Aguarde para digitar um novo número.");
			sleep(1);
			system("clear");
			printf("\nDigite o número novamente para executar o cálculo da "
				"sequencia de Collatz: ");
			getchar();
		}
		getchar();
		if ( numero_do_usuario == 0){
			sleep(1); 
			printf("\nEncerrando o código ...\n");
			sleep(1);
			system("clear");
			break;
		}
		printf("\n\n");
		SeqCollatz( numero_do_usuario);

		printf("\n\nPS: Digite 0 para encerrar o programa caso queira!");


	}
	return 0;
}
