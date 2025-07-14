import time
import os
import math


class Calculadora:

    def __init__(self, a=0, b=0):
        self.a = a
        self.b = b
        time.sleep(1)
        print(f'Calculadora inicializada com {a} e {b}!')

    def __del__(self):
        time.sleep(1)
        print('Calculadora destruída!')

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

    def potencia(self):
        return self.a ** self.b

    def raiz_quadrada(self):
        # trata raiz de número negativo
        if self.a < 0:
            return 'Lamento, mas não dá para calcular raiz quadrada de número negativo.'
        else:
            # calcula raiz normalmente e formata o resultado para 4 casas decimais
            return f'{math.sqrt(self.a):.4f}'

    def logaritmo(self, base=10):
        if self.a <= 0:
            return 'Lamento, mas logaritmo só é definido para números positivos.'
        else:
            return f'{math.log(self.a, base):.4f}'

    def seno(self):
        # calcula seno de a em graus convertendo para radianos
        return f'{math.sin(math.radians(self.a)):.4f}'

    def cosseno(self):
        # calcula cosseno de a em graus convertendo para radianos
        return f'{math.cos(math.radians(self.a)):.4f}'

    def tangente(self):
        # verifica se tangente está perto de ser indefinida (90 + k*180 graus)
        angulo_mod = self.a % 180
        if abs(angulo_mod - 90) < 1e-10:  # aproximação
            return 'Lamento, tangente indefinida para esse ângulo.'
        else:
            return f'{math.tan(math.radians(self.a)):.4f}'

    def avaliar_expressao(self, expressao: str):
        ambiente = {
            "math": math,
            "a": self.a,
            "b": self.b,
            "__builtins__": {}
        }
        try:
            resultado = eval(expressao, ambiente)
            if isinstance(resultado, float):
                return f'{resultado:.4f}'
            else:
                return resultado
        except Exception as e:
            return f'Opa, deu erro aqui: {e}'

    def graus_para_radianos(self):
        radianos = round(math.radians(self.a), 4)
        print(f'O valor de {self.a} graus em radianos é: {radianos}')
        return radianos

    def radianos_para_graus(self):
        graus = round(math.degrees(self.a), 4)
        print(f'O valor de {self.a} radianos em graus é: {graus}')
        return graus


def limpar_tela():
    os.system('cls' if os.name == 'nt' else 'clear')


RESPOSTAS_POSITIVAS = {
    "sim", "s", "ss", "claro", "ok", "yes", "y",
    "affirmativo", "positivo", "beleza", "certamente"
}

RESPOSTAS_NEGATIVAS = {
    "não", "nao", "n", "nn", "no", "negativo", "nem", "nunca", "jamais"
}


def obter_numeros():
    while True:
        try:
            print('Por favor, digite dois números:\n')
            a = float(input('Digite o 1º número (para funções que usam só um número, digite aqui): '))
            b = float(input('Digite o 2º número (para funções que usam só um número, pode deixar zero): '))

            resposta_valida = False

            while not resposta_valida:
                resposta = input(f'Deseja confirmar {a} e {b} como números escolhidos? ').strip().lower()
                if resposta in RESPOSTAS_POSITIVAS:
                    print(f'Certo, {a} e {b} confirmados!')
                    resposta_valida = True
                elif resposta in RESPOSTAS_NEGATIVAS:
                    print('Beleza, vamos tentar de novo...')
                    time.sleep(1)
                    limpar_tela()
                    resposta_valida = True
                else:
                    print('Huh?... não entendi sua resposta.')
                    time.sleep(1)
                    limpar_tela()

            if resposta_valida and resposta in RESPOSTAS_POSITIVAS:
                return a, b

        except ValueError:
            print('Ei, só números válidos, por favor!')
            time.sleep(1)
            limpar_tela()


def menu_calculadora(calc):
    while True:
        print('\nQual operação você quer fazer?')
        print('1) Soma (usa a e b)')
        print('2) Subtração (usa a e b)')
        print('3) Multiplicação (usa a e b)')
        print('4) Divisão (usa a e b)')
        print('5) Potência (a elevado a b)')
        print('6) Raiz quadrada (de a)')
        print('7) Logaritmo base 10 (de a)')
        print('8) Seno (de a graus)')
        print('9) Cosseno (de a graus)')
        print('10) Tangente (de a graus)')
        print('11) Avaliar expressão matemática (use math, a e b)')
        print('12) Converter graus para radianos (de a)')
        print('13) Converter radianos para graus (de a)')
        print('14) Atualizar valores de a e b')
        print('15) Sair')

        opcao = input('Escolha uma opção (1-15): ').strip()

        match opcao:
            case '1':
                print(f'O resultado da soma é: {calc.soma():.4f}')
            case '2':
                print(f'O resultado da subtração é: {calc.sub():.4f}')
            case '3':
                print(f'O resultado da multiplicação é: {calc.mult():.4f}')
            case '4':
                resultado = calc.div()
                if isinstance(resultado, float):
                    print(f'O resultado da divisão é: {resultado:.4f}')
                else:
                    print(resultado)
            case '5':
                print(f'O resultado da potência é: {calc.potencia():.4f}')
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
                print('Vamos atualizar os valores de a e b...')
                a, b = obter_numeros()
                calc.a = a
                calc.b = b
                print(f'Valores atualizados para a = {a} e b = {b}')
            case '15':
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

