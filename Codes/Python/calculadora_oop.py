import time
import os


class Calculadora:

    #construtor, método que roda quando a classe é inicializada
    def __init__(self, a=0, b=0):
        # esqueci da inicialização dos atributos a e b, que vem do código para a classe
        # self significa os atributo próprios do objeto, podendo ser feitas várias instancias de classe
        # com a e b de valores diferentes
        self.a = a
        self.b = b
        time.sleep(1)
        print(f'Calculadora inicializada com {a} e {b}!')

    #destrutor, método que roda quando o objeto inicializado com essa classe
    # é destruído.
    def __del__(self):
        time.sleep(1)
        print('Calculadora destruída!')

    #métodos simples para as operações da calculadora

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


#função que tenta limpar o terminal de forma portátil, usando cls ( comando usado para limpar terminal em windows
# [nt vem de Windows NT] ) e clear para sistemas Unix-like, como distros Linux ( Ex: Ubuntu, Debian, Fedora, Arch
# [ a que uso agora ], e também Unix originais como AIX, Solaris, IRIX e etc...)
def limpar_tela():
    os.system('cls' if os.name == 'nt' else 'clear')



# ainda não usei dicionários de jeitos mas complexos, mas eles são perfeitos para agrupar o máximo possível das
# repostas que um usuário pode dar ao 
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

        # captura de números para inicializar o objeto calc, que é uma instância da classe Calculadora
        while True:
            try:
                print('Por favor, insira dois números: \n')

                a = float(input('Digite o 1º número: '))
                b = float(input('Digite o 2º número: '))

                resposta_valida = False

                # loop de validação
                while not resposta_valida: # resposta_valida == False
                    resposta = input(f'Deseja confirmar {a} e {b} como números escolhidos? ').strip().lower()

                    if resposta in RESPOSTAS_POSITIVAS:
                        print(f'Certo, {a} e {b} confirmados!')
                        calc = Calculadora(a, b)  # inicializa calc como uma instância de Calculadora com a e b
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

                #truquezinho, usando um bool para capturar respostas válidas e quebrar o loop de validação
                if resposta_valida: # if resposta_valida == true
                    break
                else:
                    continue

            except ValueError:
                print('Por favor, digite novamente')
                time.sleep(1)
                limpar_tela()
                continue

        # Confirmação de que calc foi criado ( o que é improvável )
        if calc is None:
            print("Erro: não foi possível inicializar a calculadora.")
            return

        # Menu de operações usando match/case
        # Aprendi isso com Rust, mas só agora
        # havia percebido que é capaz de ser
        # usado em Python, usando para fazer
        # um switch case de C só que mais
        # idiomático de Python
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
                    del calc  # deleta o objeto, chamando o destrutor
                    time.sleep(1)
                    return
                case _:
                    print('Opção inválida.')

            input('\nPressione Enter para continuar...')

# Este bloco garante que o código dentro de main()
# só será executado se este arquivo for rodado diretamente
# pelo interpretador Python.
# Se este arquivo for importado como módulo em outro script,
# o conteúdo dentro de main() não roda automaticamente.
if __name__ == "__main__":
    main()
