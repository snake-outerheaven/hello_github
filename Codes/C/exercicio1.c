#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
// vamos começar a reescrita deste código, implementando modularização estilo UNIX, ou seja, faça uma coisa bem

// na pratica isso significa que, vou estar criando funções simples que podem ser reutilizadas uma dentro da 
// outra permitindo escalabilidade de forma bastante facilitada

void limpar_tela (void) 
{
// função que busca limpar a tela de forma portátil
// me utilizei de macros que me permitem configurar
// como o programa é executado

#ifdef _WIN32
    system("cls");

#else
    system("clear");

#endif
}

void trim (char *str) 
{
    // Função que remove espaços em branco (whitespace) do início e do fim de uma string.

    int fim = strlen(str);  // Obtém o tamanho atual da string

    // Remover espaços em branco do fim da string
    // Enquanto o tamanho for maior que zero e o último caractere for um espaço (ou outro whitespace)
    while(fim > 0 && isspace((unsigned char) str[fim - 1])) 
    {
        str[fim - 1] = '\0';  // Substitui o último caractere por '\0', encurtando a string
        fim--;                // Decrementa o tamanho da string
    }

    // Remover espaços em branco do início da string
    int start = 0;
    // Enquanto o caractere na posição start existir e for whitespace
    while(str[start] && isspace((unsigned char) str[start]))
        start++;  // Avança para o próximo caractere

    // Se houver espaços no início, desloca a string para a esquerda para remover esses espaços
    if (start > 0) {
        int i = 0;
        // Copia os caracteres da posição 'start' até o fim da string
        while(str[start + i]) {
            str[i] = str[start + i];
            i++;
        }
        str[i] = '\0';  // Finaliza a string corretamente
    }
}

// agora é criar uma função que recebe um prompt em string e imprime em qualquer FILE, seja stdout
// para mostrar em tela stderr, ou uma stream de dados qualquer (de forma mais elementar sendo um 
// arquivo de texto que vai ser criado la na frente.

void imprimir (FILE *arquivo, const char *prompt)
{
    fprintf(arquivo,"%s\n",prompt);
}


int escrever (FILE *stream, size_t tamanho, char *saida)
{
   // todas as operações de entrada e saída se dão em buffers, a mesma lógica de ler uma arquivo de texto
   // se dá em ler entrada do teclado, só que a stream de dados vem de /dev/stdin, pelo menos em sistemas Unix
   
   char buffer[tamanho]; // buffer de operações

   if (fgets(buffer,tamanho,stream) == NULL)
   {
       imprimir(stderr,"Leitura de entrada falhou.");
       return 0; // função retorna 0, depois só verificar com if ( escrever(parametros) == 0 ) 
       // { tratamento da falha }
   }

   // fgets obtém uma string com \n, então vou usar a função trim para limpar o buffer

   trim(buffer);
   
   if (buffer[0] == '\0')
   {
       imprimir(stderr,"String vazia detectada.");
       limpar_tela();
       imprimir(stderr,"Digite novamente:");
       return escrever (stream, tamanho, saida);
   }
   strncpy(saida,buffer,tamanho);
   saida[tamanho-1] = '\0';
   return 1; // sucesso
}

// reimplementar as funções abaixo de forma recursiva igual feito acima, e mudar o uso de escrever, ja que
// a função foi reescrita.

int obter_int(char *entrada, long *saida)
{
    imprimir(stdout, "Por favor, digite um número inteiro. (Máximo de 4 caracteres.)"); 
    if (escrever(stdin,5, entrada) == 0) // 4 + caracter finalizador de string '\0'
    {
        imprimir(stderr,"Erro ao obter entrada do usuário");
        return -1; // crash total, tentativa de obter entrada do usuário não funcionou
    }
    
    char *ptr;
    long val = strtol(entrada,&ptr,10); // 10 indica a base numérica, no caso, sistema decimal normal
    
    if(*ptr == '\0' && entrada[0] != '\0') // se o ptr apontar para o final da string, quer dizer que 
                                           // houve conversão completa, e se a entrada do usuário for válida
    {
        *saida = val;
        return 1; // função deu certo, yay!
    }
    else
    {
        return 0; // função deu errado, uhhh.
    }
}

int obter_double(char *entrada, double *saida)
{
    imprimir(stdout,"Por favor, digite um número decimal ( use ponto no lugar da vírgula."
                    " máximo de 6 caracteres, incluindo a vírgula");
    if (escrever(stdin,7, entrada ) == 0) 
    {
        imprimir(stderr,"Falha ao receber entrada.");
        return -1; // crash total, tentativa de usuário
    }

    char *ptr; // este ponteiro recebe a parte não convertida
    double val = strtod(entrada,&ptr);


    if(*ptr == '\0' && entrada[0] != '\0') // se o ponteiro for uma string nula, conversão deu bom.
    {
        *saida = val;
        return 1;
    }
    else
    {
        return 0;
    }
}

// a partir daqui vem de fato o desenvolvimento do programa de conversão



// funções elementares que fazem a conversão entre as temperaturas

double fahrenheit(double *entrada)
{
	double fah = (*entrada * (9.0/5.0)) + 32.0; // ponteiro duplo
	return fah;
}

double celsius(double *entrada)
{
	double cels = (5.0/9.0)*(*entrada - 32.0);
	return cels;
}

// vamos começar a estruturar as funções bases do programa.

// agora é criar uma função que faz o primeiro bloco do código, obtém o nome do usuário
// ela pode funcionar de forma parecida com as anteriores, retornano 0 ou 1 dependendo do status

int obtendo_nome(char *entrada, char *saida)
{
	// lógica à ser implementada...
}

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
