#include <iostream>
#include <stdio.h>
#include<stdlib.h>
#include <string>
#include  <unistd.h> // biblioteca de C que eu puxo em C++ para usar delay de forma simplificada, sem thread e chrono, em sistemas baseados
                     // em UNIX ( manipulo syscalls com ela )
using namespace std;

#define MAX_IGNORE_SIZE 1024

int main ( void ){
  system("clear");
  int inteiro{};
  string palavra{};
  char letra{};
  bool entrada_valida = false;
  //const char* palavra1 = palavra.c_str(); // crio um ponteiro constante que passa a conversão do tipo string de C++
                                          // para C
  cout << "\n\n";
  sleep(1);
  cout << "Este é um programa que recebe e imprime três variáveis, uma string, um char (ASCII) e um inteiro, respectivamente.";
  cout << "\n\n";
 sleep(1);
  cout << "Digite os valores abaixo" << endl;
  cout << "Digite uma string qualquer ( não pode ser vazia )" << endl;
  do {
    getline(cin,palavra);
    entrada_valida = !(palavra.empty());
    if(!entrada_valida){
      cout << "Entrada vazia detectada, digite novamente: ";
    }
  }while (!entrada_valida);
  do {
    if(cin >> letra >> inteiro){
      entrada_valida = true;
    }else{
      cout << "UM dos valores digitados não procede, favor digitar novamente: ";
      cin.clear();
      cin.ignore(MAX_IGNORE_SIZE,'\n');
    }
  }while (!entrada_valida);
  cout << "Você digitou: " << palavra<< ", " << letra << ", " <<  inteiro << "." << endl;
  printf("\n\n");
  printf("Usando printf: %s, %c , %d", palavra.c_str(), letra, inteiro);
  printf("\n\n");
  return 0;
}
