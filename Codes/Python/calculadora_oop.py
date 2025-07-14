import time
import os
import math


class Calculadora:

    # construtor, método que roda quando a classe é inicializada
    def __init__(self, a=0, b=0):
        # self significa os atributos próprios do objeto, podendo ser feitas várias instâncias de classe
        # com a e b de valores diferentes
        self.a = a
        self.b = b
        time.sleep(1)  # só pra dar uma pausa e dar efeito na inicialização
        print(f'Calculadora inicializada com {a} e {b}!')

    # destrutor, método que roda quando o objeto inicializado com essa classe
    # é destruído.
    def __del__(self):
        time.sleep(1)  # pausa para dar efeito dramático :)
        print('Calculadora destruída!')

    # métodos simples para as operações da calculadora

    def soma(self):
        return self.a + self.b

    def sub(self):
        return self.a - self.b

    def mult(self):
        return self.a * self.b

    def div(self):
        if self.b == 0:
            return f'Lamento, mas b não pode ser {self.b}'
        else:
            return self.a / self.b

    # operações trigonométricas e matemáticas avançadas

    def seno(self):
        # calcula seno de self.a, que está em graus, mas math.sin precisa de radianos
        # então convertemos graus para radianos com math.radians antes de passar para math.sin
        return math.sin(math.radians(self.a))

    def cosseno(self):
        # calcula cosseno de self.a (em graus), convertendo para radianos
        return math.cos(math.radians(self.a))

    def tangente(self):
        # calcula tangente de self.a (em graus), convertendo para radianos
        return math.tan(math.radians(self.a))

    def potencia(self):
        # calcula self.a elevado a self.b usando operador **
        return self.a ** self.b

    def raiz_quadrada(self):
        # verifica se self.a é negativo, pois raiz quadrada de número negativo não é real
        if self.a < 0:
            # avisa que não é possível calcular raiz quadrada de número negativo
            return 'Lamento, mas não dá para calcular raiz quadrada de número negativo.'
        else:
            # calcula raiz quadrada normalmente usando math.sqrt
            return math.sqrt(self.a)

    def logaritmo(self, base=10):
        # verifica se self.a é positivo, porque logaritmo só é definido para números > 0
        if self.a <= 0:
            return 'Lamento, mas logaritmo só é definido para números positivos.'
        else:
            # calcula logaritmo de self.a na base passada (padrão base 10)
            return math.log(self.a, base)

    # método para avaliar uma expressão matemática usando eval com sandbox
    def avaliar_expressao(self, expressao: str):
        # prepara um "ambiente seguro" para avaliar a expressão que o usuário passar
        # nesse ambiente, só permitimos acesso a: módulo math, atributos a e b,
        # e bloqueamos o acesso a built-ins do Python para evitar código malicioso
        ambiente = {
            "math": math,
            "a": self.a,
            "b": self.b,
            "__builtins__": {}  # remove built-ins para segurança
        }
        try:
            # avalia a expressão matemática no ambiente controlado
            resultado = eval(expressao, ambiente)
            return resultado
        except Exception as e:
            # se der erro (ex: sintaxe errada, divisão por zero, nome inválido),
            # retorna uma mensagem amigável para o usuário
            return f'Opa, deu erro aqui: {e}'

    # métodos para conversão graus <-> radianos

    def graus_para_radianos(self):
        # converte o atributo 'a' que está em graus para radianos e retorna arredondado
        radianos = round(math.radians(self.a), 4)
        print(f'O valor de {self.a} graus em radianos é: {radianos}')
        return radianos

    def radianos_para_graus(self):
        # converte o atributo 'a' que está em radianos para graus e retorna arredondado
        graus = round(math.degrees(self.a), 4)
        print(f'O valor de {self.a} radianos em graus é: {graus}')
        return graus


# Função para limpar a tela do terminal de forma portátil entre Windows e Linux/Mac
def limpar_tela():
    os.system('cls' if os.name == 'nt' else 'clear')


# Conjuntos de respostas aceitas para confirmação positiva
RESPOSTAS_POSITIVAS = {
    "sim", "s", "ss", "claro", "ok", "yes", "y",
    "affirmativo", "positivo", "beleza", "certamente"
}

# Conjuntos de respostas aceitas para confirmação negativa
RESPOSTAS_NEGATIVAS = {
    "não", "nao", "n", "nn", "no", "negativo", "nem", "nunca", "jamais"
}


# Função que pede os números ao usuário e valida a confirmação
def obter_numeros():
    while True:
        try:
            print('Por favor, digite dois números:\n')

            # Entrada dos dois números, um por vez
            a = float(input('Digite o 1º número (para funções que usam só um número, digite aqui): '))
            b = float(input('Digite o 2º número (para funções que usam só um número, pode deixar zero): '))

            resposta_valida = False

            # Loop para validar a confirmação do usuário sobre os números digitados
            while not resposta_valida:
                resposta = input(f'Deseja confirmar {a} e {b} como números escolhidos? ').strip().lower()
                if resposta in RESPOSTAS_POSITIVAS:
                    # se positivo, confirma os números e sai do loop para retornar
                    print(f'Certo, {a} e {b} confirmados!')
                    resposta_valida = True
                elif resposta in RESPOSTAS_NEGATIVAS:
                    # se negativo, limpa a tela e reinicia o processo de entrada dos números
                    print('Beleza, vamos tentar de novo...')
                    time.sleep(1)
                    limpar_tela()
                    resposta_valida = True  # sai do loop interno, mas não retorna os números
                else:
                    # se resposta inválida, pede para digitar algo válido
                    print('Huh?... não entendi sua resposta.')
                    time.sleep(1)
                    limpar_tela()

            # só retorna os números se o usuário confirmou (resposta positiva)
            if resposta_valida and resposta in RESPOSTAS_POSITIVAS:
                return a, b  # retorna os números confirmados para o programa continuar

        except ValueError:
            # caso o usuário digite algo que não seja número, avisa e repete o loop
            print('Ei, só números válidos, por favor!')
            time.sleep(1)
            limpar_tela()


# Função que exibe o menu com as opções e trata a escolha do usuário
def menu_calculadora(calc):
    while True:
        print('\nQual operação você quer fazer?')
        print('1) Soma')
        print('2) Subtração')
        print('3) Multiplicação')
        print('4) Divisão')
        print('5) Potência (a elevado a b)')
        print('6) Raiz quadrada (de a)')
        print('7) Logaritmo base 10 (de a)')
        print('8) Seno (de a graus)')
        print('9) Cosseno (de a graus)')
        print('10) Tangente (de a graus)')
        print('11) Avaliar expressão matemática (use math, a e b)')
        print('12) Converter graus para radianos (de a)')
        print('13) Converter radianos para graus (de a)')
        print('14) Sair')

        opcao = input('Escolha uma opção (1-14): ').strip()

        match opcao:
            case '1':
                print(f'O resultado da soma é: {calc.soma()}')
            case '2':
                print(f'O resultado da subtração é: {calc.sub()}')
            case '3':
                print(f'O resultado da multiplicação é: {calc.mult()}')
            case '4':
                print(f'O resultado da divisão é: {calc.div()}')
            case '5':
                print(f'O resultado da potência é: {calc.potencia()}')
            case '6':
                print(f'A raiz quadrada de {calc.a} é: {calc.raiz_quadrada()}')
            case '7':
                print(f'O logaritmo base 10 de {calc.a} é: {calc.logaritmo()}')
            case '8':
                print(f'O seno de {calc.a} graus é: {calc.seno()}')
            case '9':
                print(f'O cosseno de {calc.a} graus é: {calc.cosseno()}')
            case '10':
                print(f'A tangente de {calc.a} graus é: {calc.tangente()}')
            case '11':
                expr = input('Digite a expressão matemática (ex: math.sin(math.radians(a)) + b): ')
                resultado = calc.avaliar_expressao(expr)
                print(f'O resultado da expressão é: {resultado}')
            case '12':
                calc.graus_para_radianos()
            case '13':
                calc.radianos_para_graus()
            case '14':
                print('Ok, encerrando a calculadora...')
                del calc
                time.sleep(1)
                break
            case _:
                print('Opção inválida, tenta de novo aí.')

        input('\nPressione Enter para continuar...')
        limpar_tela()


def main():
    limpar_tela()
    time.sleep(1)

    print('\nBem vindo à versão avançada da calculadora orientada a objetos!\n')

    a, b = obter_numeros()
    calc = Calculadora(a, b)

    menu_calculadora(calc)


if __name__ == "__main__":
    main()

