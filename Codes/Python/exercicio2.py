import time
import os

# notas importantes:
# Em Python, as variáveis são dinamicamente tipadas
class Calculadora:

    # aqui vem o construtor, é bem diferente de C++
    # sendo definido por __init__
    # cada valor dentro de um construtor é unico
    # a cada instância da classe

    def __init__ (self, a = 0 , b = 0):
        time.sleep(1)
        print(f'Calculadora inicializada com {a} e {b}!')

    #destrutor é definido com __del__
    # e serve como um método especial
    # que aparece toda a vez que um
    # objeto é deletado com delete
    # ou sai do escopo ( removido
    # pelo garbage collector )
    
    def __del__  (self):
        time.sleep(1)
        print('Calculadora destruída!')

    # abaixo vem métodos simples
    # para a calculadora funcionar
    # do jeito desejado

    def soma(self):
        return self.a + self.b

    def sub(self):
        return self.a + self.b

    def mult(self):
        return self.a * self.b

    def div(self):
        if self.b ==  0:
            return f'Lamento, mas b não pode ser {self.b}'
        else:
            return self.a / self.b

