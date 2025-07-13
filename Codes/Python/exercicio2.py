import time
import os


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


def limpar_tela():
    os.system('cls' if os.name == 'nt' else 'clear')


RESPOSTAS_POSITIVAS = {
    "sim", "s", "ss", "claro", "ok", "yes", "y",
    "affirmativo", "positivo", "beleza", "certamente"
}

RESPOSTAS_NEGATIVAS = {
    "não", "nao", "n", "nn", "no", "negativo", "nem", "nunca", "jamais"
}


def main():
    while True:
        limpar_tela()

        time.sleep(2)

        print('\n\n')

        print('Bem vindo à essa versão que busca reescrever o programa da calculadora usando a abordagem'
              ' orientada a objetos, utilizando-se métodos dentro da classe para execução dos cálculos')

        print('\n')

        calc = None  # inicializa para evitar erro

        while True:
            try:
                print('Por favor, insira dois números: \n')

                a = float(input('Digite o 1º número: '))
                b = float(input('Digite o 2º número: '))

                resposta_valida = False

                # loop de validação
                while not resposta_valida:
                    resposta = input(f'Deseja confirmar {a} e {b} como números escolhidos? ').strip().lower()

                    if resposta in RESPOSTAS_POSITIVAS:
                        print(f'Certo, {a} e {b} confirmados!')
                        calc = Calculadora(a, b)  # inicializa objeto
                        resposta_valida = True

                    elif resposta in RESPOSTAS_NEGATIVAS:
                        print('Certo, reiniciando entrada de dados...')
                        time.sleep(1)
                        limpar_tela()
                        resposta_valida = True
                    else:
                        print('Huh?... Resposta não reconhecida.')
                        time.sleep(2)
                        limpar_tela()

                if resposta_valida:
                    break
                else:
                    continue

            except ValueError:
                print('Por favor, digite novamente')
                time.sleep(1)
                limpar_tela()
                continue

        # Confirmação de que calc foi criado
        if calc is None:
            print("Erro: não foi possível inicializar a calculadora.")
            return

        # Menu de operações usando match/case
        while True:
            print('\nQual operação deseja realizar?')
            print('1) Soma')
            print('2) Subtração')
            print('3) Multiplicação')
            print('4) Divisão')
            print('5) Sair')

            opcao = input('Escolha uma opção (1-5): ').strip()

            match opcao:
                case '1':
                    print(f'Resultado da soma: {calc.soma()}')
                case '2':
                    print(f'Resultado da subtração: {calc.sub()}')
                case '3':
                    print(f'Resultado da multiplicação: {calc.mult()}')
                case '4':
                    print(f'Resultado da divisão: {calc.div()}')
                case '5':
                    print('Encerrando...')
                    del calc  # força destrutor, opcional
                    time.sleep(1)
                    return
                case _:
                    print('Opção inválida.')

            input('\nPressione Enter para continuar...')


if __name__ == "__main__":
    main()
