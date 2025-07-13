#include <iostream>
#include <string>

class Calculadora {

  private:
    //metodos escondidos ( só a classe usa)
    // na prática apenas inicializando variáveis privadas, que só servem para a classe
    double a_;
    double b_;
    std::string erro_;

  public:
    // metodos publicos pelos quais o código geral pode interagir com a classe 

    
    // construtor: chamado quando se cria um objeto com a classe Calculadora
    // parece ser uma função que executa inicializando tudo, e imprimir que está tudo certo
    Calculadora(double a = 0, double b = 0){
      a_ = a;
      b_ = b;
      erro_ = "Erro";
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
      return a_ / b_;
    }
};
