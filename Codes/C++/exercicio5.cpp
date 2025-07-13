#include <cmath>
// biblioteca para matemática

#include <iostream>
#include <iomanip>
// biblioteca para entrada e saída (I/O)

#include <string>
// biblioteca de tipos e métodos para manipulação de strings

#include <thread>
// isso aqui consigo manipular diretamente com o processo do executável

#include <chrono>
// puxo para pegar um tipo de tempo

#include <cstdlib>
// puxo para usar std::system

#include <algorithm> 
#include <cctype>
// ambos para normalizar string em método descrito na função principal para tornar todo o conteúdo da resposta minúsculo

/*Classe simples para começar a molhar os pés em OOP*/

class Calculadora {

  private:
    // métodos escondidos (só a classe usa)
    // na prática apenas inicializando variáveis privadas, que só servem para a classe
    double a_;
    double b_;
    //std::string erro_; removi, pois acho desnecessário e acho que pode passar para a main

  public:
    // métodos públicos pelos quais o código geral pode interagir com a classe 

    // construtor: método que ocorre ao se inicializar uma classe
    // parece ser uma função que executa inicializando tudo, e imprimir que está tudo certo
    Calculadora(double a = 0, double b = 0){
      a_ = a; // ao inicializar o objeto, os valores com os quais ele receber do código geral, passam 
      b_ = b; // para a parte privada
      std::cout << "Calculadora pronta! a = " << a_ << ", b = " << b_ << "\n";
    }

    ~Calculadora(){
      //Destrutor: chamado quando a Calculadora é destruída
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
      if(b_ == 0){
        return NAN;
      }
      return a_ / b_; // lembrar de cuidar da divisão por zero na função principal
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

int main ( void ) {
  while(true) {
    // inicializo variáveis vazias para não dar problemas 
    double a{} , b{};
    bool entrada_valida = false;
    std::string resposta; // puxando a resposta

    limpar_tela();
    
    std::this_thread::sleep_for(std::chrono::seconds(2)); // manipulação de tempo em C++, revisar se está correto
    
    std::cout << "Este é um programa que executa cálculos simples ao receber dois números do usuário,\n"
      << " estes cálculos incluem soma, subtração, multiplicação e divisão, e visa \n"
      << " demonstrar de forma inicial o uso de classes e POO (Programação Orientada a Objetos)\n"
      << " de C++.";

    std::cout << "\n\n";

    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::cout << "Digite os valores de a e b para realizar os cálculos entre eles: ";

    do {
      if (std::cin >> a >> b){
        entrada_valida = true;
      }else{
        std::cout << "Um dos valores digitados não procede, favor digitar novamente: ";
        std::cin.clear();
        std::cin.ignore(1024,'\n');  // limpa até 1024 caracteres ou até o '\n'
      }
    }while(!entrada_valida);

    std::cin.ignore(1024, '\n'); // limpa o buffer antes de pegar a resposta completa com getline

    std::cout << a << " e " << b << " estão corretos? ";

    do{
      std::getline(std::cin, resposta);
    }while(resposta.empty());

    std::transform(resposta.begin(), resposta.end(), resposta.begin(),
      [](unsigned char c){return std::tolower(c);});

    // Aplica uma transformação em cada caractere da string 'resposta':
    // 1. Percorre a string do começo (resposta.begin()) até o fim (resposta.end()).
    // 2. Para cada caractere, chama a função definida aqui, que é um "lambda" —
    //    uma função sem nome, criada diretamente dentro do código para facilitar.
    // 3. Esse lambda recebe um caractere 'c' (como unsigned char para evitar erros)
    //    e usa a função std::tolower para transformar 'c' em letra minúscula.
    // 4. O resultado substitui o caractere original na mesma posição da string,
    //    então a string 'resposta' é modificada diretamente (in-place).
    // Resumindo: converte todas as letras da string para minúsculas sem criar outra string.

    if ( resposta == "sim" || resposta == "s" || resposta == "ss"){
      std::this_thread::sleep_for(std::chrono::seconds(1));

      Calculadora calc(a,b); // inicializo o meu objeto aqui, isso deve chamar o construtor

      std::this_thread::sleep_for(std::chrono::seconds(1));

      std::cout << std::fixed << std::setprecision(2); // aqui eu seto a precisão de cout para 2 casas decimais

      std::cout << "Resultados saindo:\n" << "Soma = " << calc.soma() << "\nSubtração = " << calc.sub()
                << "\nMultiplicação: " << calc.mult() << "\nDivisão = " << calc.div() << std::endl;

      break; // Sai do loop infinito e termina o programa

    } else {
      std::this_thread::sleep_for(std::chrono::seconds(1));
      std::cout << "Vamos tentar novamente.\n\n";
      // Continua o loop para repetir o processo
    }
  }
  return 0;
}
