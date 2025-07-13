#include <iostream>
#include <string>
#include <chrono>
#include <thread>

/*fazendo hello world de uma forma diferente*/

class HelloWorld{

  private:
     std::string ola_mundo{"Hello world!"};

  public:

    //construtor
    HelloWorld(void){
      std::cout << "Inicializando objHelloWorld..." << std::endl;
      std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    //destrutor
    ~HelloWorld(void){
      std::cout << "Desligando objHelloWorld..." << std::endl;
      std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    //método que imprime ola_mundo
    void printfworld(void){
      std::cout << "Imprimindo..." << std::endl;
      std::this_thread::sleep_for(std::chrono::seconds(1));
      std::cout << ola_mundo << std::endl;
    }

}; 

int main ( void ){

  HelloWorld hello;

  hello.printfworld();

  return 0;
  
}
