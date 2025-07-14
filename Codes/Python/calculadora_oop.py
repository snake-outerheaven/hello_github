import time
import os
import math


class Calculadora:

    # Inicializa a calculadora com os valores a e b
    def __init__(self, a=0, b=0):
        self.a = a
        self.b = b
        time.sleep(1)
        print(f'Calculadora inicializada com {a} e {b}.')

    # Informa quando o objeto é destruído
    def __del__(self):
        time.sleep(1)
        print('Calculadora encerrada.')

    # Soma de a e b
    def soma(self):
        return f'{self.a + self.b:.4f}'

    # Subtração de a menos b
    def sub(self):
        return f'{self.a - self.b:.4f}'

    # Multiplicação de a por b
    def mult(self):
        return f'{self.a * self.b:.4f}'

    # Divisão de a por b, com proteção contra divisão por zero
    def div(self):
        if self.b == 0:
            return 'Erro: divisão por zero não permitida.'
        else:
            return f'{self.a / self.b:.4f}'

    # Potência: a elevado a b
    def potencia(self):
        return f'{self.a ** self.b:.4f}'

    # Raiz quadrada de a, com verificação para números negativos
    def raiz_quadrada(self):
        if self.a < 0:
            return 'Erro: raiz quadrada de número negativo não definida.'
        else:
            return f'{math.sqrt(self.a):.4f}'

    # Logaritmo base 10 de a, com validação para números positivos
    def logaritmo(self, base=10):
        if self.a <= 0:
            return 'Erro: logaritmo definido apenas para números positivos.'
        else:
            return f'{math.log(self.a, base):.4f}'

    # Seno de a em graus
    def seno(self):
        return f'{math.sin(math.radians(self.a)):.4f}'

    # Cosseno de a em graus
    def cosseno(self):
        return f'{math.cos(math.radians(self.a)):.4f}'

    # Tangente de a em graus, tratando pontos onde tangente é indefinida
    def tangente(self):
        angulo_mod = self.a % 180
        if abs(angulo_mod - 90) < 1e-10:
            return 'Erro: tangente indefinida para este ângulo.'
        else:
            return f'{math.tan(math.radians(self.a)):.4f}'

    # Avalia expressão matemática usando eval em ambiente restrito
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
            return f'Erro na avaliação da expressão: {e}'

    # Converte graus para radianos e exibe o resultado
    def graus_para_radianos(self):
        radianos = round(math.radians(self.a), 4)
        print(f'{self.a} graus equivalem a {radianos} radianos.')
        return radianos

    # Converte radianos para graus e exibe o resultado
    def radianos_para_graus(self):
        graus = round(math.degrees(self.a), 4)
        print(f'{self.a} radianos equivalem a {graus} graus.')
        return graus


# Função para limpar a tela de forma portátil (Windows e Unix)
def limpar_tela():
    os.system('cls' if os.name == 'nt' else 'clear')


# Respostas reconhecidas como positivas
RESPOSTAS_POSITIVAS = {
    "sim", "s", "ss", "claro", "ok", "yes", "y",
    "affirmativo", "positivo", "beleza", "certamente"
}

# Respostas reconhecidas como negativas
RESPOSTAS_NEGATIVAS = {
    "não", "nao", "n", "nn", "no", "negativo", "nem", "nunca", "jamais"
}


# Função para obter e confirmar dois números do usuário
def obter_numeros():
    while True:
        try:
            print('Digite dois números:\n')
            a = float(input('Digite o 1º número (para funções que usam só um número, digite aqui): '))
            b = float(input('Digite o 2º número (para funções que usam só um número, pode deixar zero): '))

            resposta_valida = False

            while not resposta_valida:
                resposta = input(f'Deseja confirmar {a} e {b}? ').strip().lower()
                if resposta in RESPOSTAS_POSITIVAS:
                    print('Números confirmados.')
                    resposta_valida = True
                elif resposta in RESPOSTAS_NEGATIVAS:
                    print('Vamos tentar novamente.')
                    time.sleep(1)
                    limpar_tela()
                    resposta_valida = True
                else:
                    print('Resposta não reconhecida. Por favor, responda sim ou não.')
                    time.sleep(1)
                    limpar_tela()

            if resposta_valida and resposta in RESPOSTAS_POSITIVAS:
                return a, b

        except ValueError:
            print('Entrada inválida. Por favor, digite números válidos.')
            time.sleep(1)
            limpar_tela()


# Menu para escolher operação
def menu_calculadora(calc):
    while True:
        print('\nEscolha a operação desejada:')
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
        print('15) Exibit a e b')
        print('16) Sair')

        opcao = input('Escolha uma opção (1-15): ').strip()

        match opcao:
            case '1':
                print(f'Resultado da soma: {calc.soma()}')
            case '2':
                print(f'Resultado da subtração: {calc.sub()}')
            case '3':
                print(f'Resultado da multiplicação: {calc.mult()}')
            case '4':
                resultado = calc.div()
                print(resultado)
            case '5':
                print(f'Resultado da potência: {calc.potencia()}')
            case '6':
                print(f'Raiz quadrada de {calc.a}: {calc.raiz_quadrada()}')
            case '7':
                print(f'Logaritmo base 10 de {calc.a}: {calc.logaritmo()}')
            case '8':
                print(f'Seno de {calc.a} graus: {calc.seno()}')
            case '9':
                print(f'Cosseno de {calc.a} graus: {calc.cosseno()}')
            case '10':
                print(f'Tangente de {calc.a} graus: {calc.tangente()}')
            case '11':
                expr = input('Digite a expressão matemática (ex: math.sin(math.radians(a)) + b): ')
                resultado = calc.avaliar_expressao(expr)
                print(f'Resultado da expressão: {resultado}')
            case '12':
                calc.graus_para_radianos()
            case '13':
                calc.radianos_para_graus()
            case '14':
                print('Atualizando valores de a e b...')
                a, b = obter_numeros()
                calc.a = a
                calc.b = b
                print(f'Valores atualizados: a = {a}, b = {b}')
            case '15':
                print(f'Os valores registrados são {calc.a} e {calc.b}')
            case '16':
                print('Encerrando o programa.')
                del calc
                time.sleep(1)
                break
            case _:
                print('Opção inválida. Tente novamente.')

        input('\nPressione Enter para continuar...')
        limpar_tela()


# Função principal
def main():
    limpar_tela()
    time.sleep(1)

    print('\nBem-vindo ao programa de calculadora OOP.\n')

    a, b = obter_numeros()
    calc = Calculadora(a, b)

    menu_calculadora(calc)


if __name__ == "__main__":
    main()
