import math
import os

# definição da função que converte graus para radianos
def graus_para_radianos():
    while True:
        try:
            graus = float(input("Digite um ângulo em graus para conversão para radianos: \n"))
            radianos = round(math.radians(graus),2)
            while True:
                resposta = (input('Deseja exibir o valor em radianos? ')).lower()
                if resposta in {'s','S','sim','Sim','ss','Ss','SS'}: # testar if resposta in [s,sim.ss]
                    print(f'O valor de radianos de {graus} é: {radianos}')
                    return radianos
                elif resposta in ['n','ñ','não','nao','nn','N','Ñ','Não','NÂO','NAO']: # usando if, muito mais rápido e eficiente
                    print('OK!')
                    os.system('clear')
                    exit(1)
                else:
                    print('Digite um valor válido')
        except ValueError:
            print('Digite um valor válido para o ângulo.')

def radianos_para_graus():
    while True:
        try:
            entrada = input('Digite uma expressão como 2*pi, ou 3*pi/2 para calcular radianos: ').lower().strip()
            # entrada do tipo string, removida de espaços e forçada a ser toda minuscula
            expressao = entrada.replace('pi', 'math.pi')
            # converte a entrada do usuario de pi para math.pi
            radianos = eval(expressao, {'math': math})
            # mágica que faz o intepretador do python avaliar a string como função matemática
            #usando um dicionario que linka qualquer menção de math na string à biblioteca math
            #o dicionário faz com que a avaliação linke qualquer math ao módulo que eu exportei la em cima
            #fazendo com que seja possível usar a constante math.pi
            graus = round(math.degrees(radianos),2)
            # obtendo graus com a função math.degrees de radianos
            while True:
                resposta=input('Deseja receber o valor em radianos?')
                if resposta in ['s','S','ss','Ss','SS','sim','Sim','SIM']:
                    print(f'O valor de {entrada} em graus é: {graus}')
                    return graus
                elif resposta in ['n','ñ','não','nao','nn','N','Ñ','Não','NÂO','NAO']:
                    print('OK!')
                    os.system('clear')
                    exit(2)
                else:
                    print('Digite uma resposta válida')
        except (ValueError,ZeroDivisionError,SyntaxError,NameError):
            # NameError roda se o usuário escrever algo aleatório
            print('Digitar um valor válido para o ângulo')



# área global
print('Este programa exibe o valor aproximado de radianos de um ângulo em graus, com duas casas decimais,'
      'além de ler um ângulo em radianos, e retornar o valor em graus, também com duas casas decimais')
seletor = input('Digite 1 para converter de graus para radianos, ou 2 para converter de radianos para graus e'
                ' qualquer outro número para sair do código: ')
if seletor in {'1','Um','um','UM'}:
    angulo = graus_para_radianos()
elif seletor in {'2','Dois','dois','DOIS'}:
    angulo = radianos_para_graus()
else:
    print('OK!')
    exit(3)






