#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif
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

void dormir(int tempo)
{
    #ifdef _WIN32
        Sleep(tempo * 1000); // função de sleep no windows é em milisegundos
    #else
        sleep(tempo);
    #endif
    return;
}

void trim (char *str) 
{
    // Função que remove espaços em branco (whitespace) do início e do fim de uma string.

    int fim = strlen(str);  // Obtém o tamanho atual da string

    // Remover espaços em branco do fim da string
    // Enquanto o tamanho for maior que zero e o último caractere for um espaço (ou outro whitespace):
    while(fim > 0 && isspace((unsigned char) str[fim - 1])) 
    {
        str[fim - 1] = '\0';  //  1º -> Substitui o último caractere por '\0', encurtando a string
        fim--;                //  2º -> Decrementa o tamanho da string
    }

    // Remover espaços em branco do início da string
    int start = 0;
    // Enquanto o caractere na posição start existir e for whitespace
    while(str[start] && isspace(str[start]))
    { 

   /* 
   		Retirado de man isspace ( para maior contexto da função )
   ---------------------------------------------------------------------------------------------
   The standards require that the argument c for these functions is either EOF or a value that
    is  representable  in the type unsigned char; otherwise, the behavior is undefined.  If the
    argument c is of type char, it must be cast to unsigned char, as in the following example:

        char c;
        ...
        res = toupper((unsigned char) c);
   ---------------------------------------------------------------------------------------------
   */
        start++;  // Avança para o próximo caractere
	}
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
    return;
}

// acho que depois daqui, na versão anterior, o código desandou, é possível deixar ele mais seco. e é isso que vou fazer 
// até entregar um resultado sensato.
