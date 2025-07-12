#include "iostream" // header file que contém std::cin e std::cout ( objetos de entrada ( cin ) e saida (cout))
// using namespace std;  se eu usar isso, nao preciso escrever std::, usando apenas cout e cin 

int main ( void ){
  int x {}, y {}; // inicializando variável vazias, formato recomendado de C++
  std::cin >> x >> y ; // scanf, mas tipo lido depende da variável, sem especificação como no scanf de C  ( lê do teclado )
  // std::cin >> y; posso colocar separadamente ou deixar junto
  int z = x+y; // declaro variaveis onde eu quiser
  std::cout << "Este programa calcula a soma de " << x << " e "<< y << ", que é: "<< z << "."<< '\n';
  //std::endl;
  // o manual falou que std::endl deixa o código mais lento, sendo útil usar apenas \n, o que faz sentido
  return 0;
}
