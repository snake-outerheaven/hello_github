#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// fazer um programa que peça para o usuário insira valores para uma tabelaa
// 3x3, calcular a média aritmética, e então separar em 2 listas os valores 
// acima e abaixo da média.

int main (void){
	int tabela[3][3]; // tabela 3 linhas e 3 colunas, usar 2 for com x e y
			  // para inserir e ler dados dela.
	int lista1[9],lista2[9];
	int bool; //variável para bool
	char resp[10]; // string de resposta ao usuário
	int x,y,z; //valores para o for que irão percorrer os vetores
		   //z vai receber o somatório de y, que aqui vai dar = 9
		   //pois vai receber 0+1+2 3 vezes, q vai dar 9
	float media,somatorio=0;
	//área ativa do programa.
	
	printf("Digite números para uma tabela 3x3\n");
	do{
		bool = 0;
		z = 1;
		for (x = 0; x < 3; x++){
			for(y = 0; y < 3; y++){
				printf("\nDigite o %d número: ",z);
				scanf("%d",&tabela[x][y]);
				getchar();
				z++;
			}
		}
		z = 1;
		printf("\nAbaixo segue a tabela: \n\n");
		for (x = 0; x < 3; x++){
			printf("\n");
			for(y = 0; y < 3; y++){
				printf("\t%2dº elemento -> |%2d|\t", z, tabela[x][y]);
				// \t faz a formatação tabelada(faz um tab automaticamente)
				// %2d faz o número inteiro(d) ser formatado com 2 espaços
				// para exibi-los corretamente.
				z++;
			}
			printf("\n");
		}
		printf("\n\nA tabela está correta? ");
		fgets(resp,sizeof(resp),stdin);
		resp[strcspn(resp,"\n")] = '\0';
		if(resp[0] == 's' || resp[0] == 'S'){
			bool = 1;
			printf("\nContinuando o programa...");
		}else{
			system("clear");
			printf("\nDigite novamente.\n\n");
		}
	}while(!bool);
	printf("\n\nTabela confirmada!");
	for(x = 0; x < 3; x++){
		for(y = 0; y < 3; y++){
			somatorio += tabela[x][y];
		}
	}
	media = somatorio/9;
	int acima=0,abaixo=0; //define o indice do elemento nas listas
	for(x=0;x<3;x++){
		for(y=0;y<3;y++){
			if(tabela[x][y]<media){
				lista1[acima++] = tabela[x][y];
			}else{
				lista2[abaixo++] = tabela[x][y];
			}
		}
	}
	printf("\nA média dos valores da tabela é: %.2f.\n\n",media);
	printf("Abaixo seguem listas com valores da tabela acima e abaixo da média. ");
	printf("A primeira lista mostra os valores acima da média, enquanto a de baixo ");
	printf("mostra os valores abaixo da média.\n\n");
	for(z=0;z<acima;z++){
		printf("\n|%.2d|",lista1[z]);
	}
	printf("\n\n");
	for(z=0;z<abaixo;z++){
		printf("\n|%.2d|",lista2[z]);
	}
	return 0;
}
