def fatorial(x):
    # Converte x para inteiro e verifica se é não-negativo
    x = int(x) # converte x para inteiro
    if x < 0: # se x for negativo, a função retorna a string
        return "Fatorial não definido para números negativos"
    if x == 0 or x == 1: # se x for igual a zero ou 1, retorna 1, caso base
        return 1
    else: # se x for igual a qualquer coisa, usar a função para calcular ela mesma, convergindo
          #para o caso base
        return x * fatorial(x-1)

try: # tratamento de erros, recomendado usar em loop ( while True ), que sera quebrado somente
     # ao ter entrada valida
    numero = int(input('Digite um número para determinar o seu fatorial: ')) 
    resultado = fatorial(numero) # o interpretador já supoe que a função é do tipo inteiro, fazendo
                                 # a designação de tipos das variaveis automaticamente.
    print(f'O fatorial de {numero} é: {resultado}') # fstring para mostrar variaveis
except ValueError: # value error para capturar valores que nao corresponde ao tipo da variavel a qual
                   # estao sendo atribuidos
    print('Por favor, digite um número inteiro válido')
