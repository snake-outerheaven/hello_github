#include <iostream> // biblioteca para entrada e saída (I/O)
#include <string> // biblioteca de tipos e métodos para manipulação de strings
#include <thread> // isso aqui consigo manipular diretamente com o processo do executável
#include <chrono> // puxo para pegar um tipo de tempo
#include <cstdlib> // puxo para usar std::command
/*Classe simples para começar a molhar os pés em */

class Calculadora {

  private:
    //metodos escondidos ( só a classe usa)
    // na prática apenas inicializando variáveis privadas, que só servem para a classe
    double a_;
    double b_;
    //std::string erro_; removi, pois acho desnecessário e acho que pode passar para a main

  public:
    // metodos publicos pelos quais o código geral pode interagir com a classe 

    
    // construtor: chamado quando se cria um objeto com a classe Calculadora
    // parece ser uma função que executa inicializando tudo, e imprimir que está tudo certo
    Calculadora(double a = 0, double b = 0){
      a_ = a;
      b_ = b;
      std::cout << "Calculadora pronta! a = " << a_ << ", b = " << b_ << "\n";
    }

    ~Calculadora(){
      //Destrutor: chamado quando a Calculadora é destruida
      std::cout << "Calculadora desligada!" << std::endl;
    }

    double soma(){
      // método de soma 
      return a_ + b_;
    }

    double sub(){
      //método da subtração
      return a_ - b_;
    }

    double mult(){
      //método da multiplicação
      return a_ * b_ ;
    }

    double div(){
      //método da divisão
      return a_ / b_; // lembrar de cuidadr da divisão por zero na função principal
    }
};

/*Função portátil e facilmente reutilizável para limpeza de telas em C++
  (depois ver algo parecido em C)
*/
void limpar_tela( void ){ 
  #ifdef _WIN32
    std::system("cls");
  #else
    std::system("clear");
  #endif
}

// eu poderia escrever uma função bool, mas eu teria que ver os artifícios de C++ para comprovar todos os tipos de leitura de forma genérica, investigar depois...
