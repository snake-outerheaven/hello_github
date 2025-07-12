#include <stdio.h>
#include <string.h>
// objetivo do código: coletar 19 idades em um array e depois e calcule a média aritimética das idades
int main(void){
	// declaração de variáveis
	int x, idades[20], quantidade, tamanho = sizeof(idades)/sizeof(idades[0]);
	float media, soma_idades = 0;
	char nomes[20][100],verif[10];
	int bool; //bool de confirmação
	printf("\nEste eh um programa que calcula a media das idades de ate 20 pessoas.\n");
	do {
		bool = 0;
		printf("\nDigite a quantidade de idades que serao calculadas: ");
		scanf("%d",&quantidade);
		getchar();
		if (quantidade > tamanho || quantidade <= 0) {
			printf("\nQuantidade invalida, digite novamente: ");
			scanf("%d",&quantidade);
			getchar();
		}
		printf("\nVoce deseja inserir %d idades? (S/N)\n\nResposta: ",quantidade);
		fgets(verif,sizeof(verif),stdin);
		verif[strcspn(verif,"\n")] = '\0';
		if (verif[0] == 's' || verif [0] == 'S') {
			bool = 1;
			printf("\nNumero de idades confirmados: %d\n",quantidade);
		}else{
			printf("\nOk! Digite novamente!\n");
		}
	}while (!bool);
	// acima, tem a parte do código responsável por obter o número de idades
	// abaixo, a parte do código que captura os nomes e as idades, e as coloca
	// nos em seus respectivos vetores.
	printf("\nDigite o nome e a idade de %d pessoas\n",quantidade);
	for(x = 0; x < quantidade; x++){
		do {
			bool = 0;
			printf("\nDigite o nome da %d pessoa: ",x+1); 
			fgets(nomes[x], sizeof(nomes[x]), stdin);
			nomes[x][strcspn(nomes[x],"\n")] = '\0';
			while(strcmp(nomes[x],"") == 0){
				printf("Nome inválido, digite o nome novamente: ");
				fgets(nomes[x],sizeof(nomes[x]),stdin);
				nomes[x][strcspn(nomes[x], "\n")] = '\0';
			}
			printf("\nDigite a idade de %s: ",nomes[x]);
			scanf("%d",&idades[x]);
			getchar();
			while(idades[x] <= 0){
				printf("\nDigite novamente a idade de %s: ",nomes[x]);
				scanf("%d",&idades[x]);
				getchar();
			}
			printf("\nNome digitado: %s\n\nIdade digitada: %d\n\n\nIsto esta correto? ",nomes[x],idades[x]);
			fgets(verif,sizeof(verif),stdin);
			verif[strcspn(verif, "\n")] = '\0';
			if(verif[0] == 's' || verif[0] == 'S'){
				bool = 1;
				printf("\nContinuando o programa!\n");
			}else{
				printf("Digite os dados novamente.");
			}
		}while (!bool);
	} // } do for, usar um for para exibir os nomes e idades das pessoas
	for (x = 0; x < quantidade; x++){
		printf("\ndados da %d pessoa:\n\nNome: %s\nIdade: %d\n\n\n\n",x+1,nomes[x],idades[x]);
	}
	for (x = 0; x < quantidade; x++){ // laço for para armazenar a soma das idades do vetor em uma unica variável.
		soma_idades += idades[x];
	}
	media = soma_idades/quantidade;
	printf("A media aritmética das idades é: %.2f",media);


	return 0;
}
