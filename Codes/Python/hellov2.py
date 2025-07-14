# fazendo a mesma coisa do hellov2.cpp, fazer um hello world com Orientação a Objetos


import time as tm

class HelloWorld:

    #construtor

    def __init__ (self):
        print('Inicializando o objeto que vai falar algo...')
        tm.sleep(2)

    #destrutor

    def __del__ (self):
        print('Destruindo o objeto :(')
        tm.sleep(2)


    def falar(self):
        print('\nHello World!\n')

def main():

    hello = HelloWorld # o objeto nasce aqui e aparece o __init__ 

    hello.falar() # roda o método

    del hello #destrutor roda aqui

if __name__ == "__main__":
    main()
