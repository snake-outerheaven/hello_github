import os
# definição da função que pega o nome do aluno, deu para fazer de forma quase autonoma, apenas esqueci o return
# aluno da linha 13
def confirmar_aluno():
    """
    Registra o nome do aluno e verifica se é válido
   returns:
      o nome do aluno se a resposta for sim e o nome válido
    """
    while True:
        nome = input('Digite o nome do aluno: ').strip()
        if not nome: #string vazia entra como falso, sendo reconhecido pelo not no código
            print("O nome não pode estar vazio.")
            continue # volta ao inicio do loop
        resposta = input(f'O nome digitado é {nome}, isto esta correto? (s/n)\n').upper() # variavel local da função, serve
                                                                                           # apenas quando ela e chamada
        if resposta == 'S' or resposta == 'SIM':
            return nome # retorna o imput de aluno, fim da declaração da função
        else:
            os.system('clear')
            print('Digite o nome novamente')
            continue # faz o programa continuar do inicio do while true, a fim de corrigir possíveis bugs
# função definidora de notas, a mais difícil
def registrar_notas_e_pesos():
    """
    Registra três notas e três pesos fornecidos pelo usuário, com verificação.

    Returns:
        tuple: Duas listas, uma com as notas e outra com os pesos, após confirmação.
    """
    while True:
        notas = []  # Cria uma lista vazia para armazenar as notas
        pesos = []  # Cria uma lista vazia para armazenar os pesos

        # Coleta as 3 notas e 3 pesos
        for i in range(3):
            # Leitura e validação da nota dado indice i, uma coisa interessante de python
            # é que o tamanho da lista não é fixo e depende apenas de range, com a variavel inteira
            # i sendo usada somente nessa parte do código, podendo ser reutilizada para a frente
            while True:
                try:
                    # ele tenta isso
                    nota = float(input(f"Digite a {i + 1}ª nota: "))
                    if nota < 0 or nota > 10:
                        print("A nota deve estar entre 0 e 10. Tente novamente.")
                        continue
                    break # quebra o loop infinito se a nota for valida(perceba como o break está dentro do try)
                except ValueError: # o valueerror serve se eu digitar vazio, apenas apertar enter
                                   # ou entrar um caracter
                    print("Por favor, digite um número válido para a nota.")
            notas.append(nota) # registra a nota no indice i na lista notas
            # abaixo segue a mesma lógica, apenas salvando o peso no indice i de pesos
            # Leitura e validação do peso
            while True:
                try:
                    peso = int(input(f"Digite o {i + 1}º peso: "))
                    if peso < 1 or peso >10:
                        print('O peso deve estar entre 1 e 10, Tente novamente')
                        continue
                    break
                except ValueError:
                    print("Por favor, digite um número válido para o peso.")
            pesos.append(peso)

        # Exibe os valores para confirmação
        print("\nValores registrados:")
        for i in range(3):
            print(f"{i + 1}ª nota: {notas[i]}")  # exibe a lista notas
        for i in range(3):
            print(f"{i + 1}° peso: {pesos[i]}") # exibe logo abaixo da notas a lista pesos

        # Pergunta se estão corretos
        resposta = input("Os valores estão corretos? (s/n):\n").upper()  #parte compreensivel
        if resposta == 'S' or resposta == 'SIM':
            return notas, pesos  # Retorna as listas se confirmadas
        else:
            os.system('clear')  # Limpa a tela (use 'cls' no Windows)
            print("Digite os valores novamente.\n")

# definição da média ponderada, estudar isso depois
def calcular_media_ponderada(notas, pesos):
    """
    Calcula a média ponderada do aluno com base nas notas e pesos fornecidos.

    Args:
        notas (list): Lista com as 3 notas do aluno. é usado como parâmetro as notas da função anterior
        pesos (list): Lista com os 3 pesos correspondentes às notas.

    Returns:
        float: A média ponderada arredondada para 2 casas decimais.
    """
    # Calcula a soma dos produtos (nota * peso)/ parte de cima da conta de média
    soma_ponderada = 0
    for i in range(3):
        soma_ponderada += notas[i] * pesos[i]

    # Calcula a soma dos pesos/ parte de baixo da conta de média
    soma_pesos = 0
    for i in range(3):
        soma_pesos += pesos[i]

    # Verifica se a soma dos pesos é diferente de zero para evitar divisão por zero
    if soma_pesos == 0:
        print("Erro: A soma dos pesos não pode ser zero.")
        return 0 # causa o fim do programa, se o usuário escrever 0 para todos os pesos

    # Calcula a média ponderada e arredonda para 2 casas decimais
    media = soma_ponderada / soma_pesos # ja assume um valor float automaticamente, interessante
    return round(media, 2) # a função retorna a média com duas casas decimais

# função main
z ='S'
print('Este é um programa que calcula a média ponderada de um aluno.')
while z == 'SIM' or z=='S':
    aluno = confirmar_aluno() # chamada da primeira função, salvando o que esta sendo retornado em nome
    print(f'Aluno confirmado: {aluno}')
    notas2, pesos2 = registrar_notas_e_pesos() # chamada da segunda função, salvando o que esta sendo retornado em
                                               # notas2,pesos2, que viram listas ao receberem os valores da função
    print(f'Notas de {aluno} confirmadas: {notas2}') # mostra os valores salvos das notas na lista notas2
    print(f'Pesos das notas de {aluno} confirmados: {pesos2}') # mostra os valores salvos na lista pesos2
    media2 = calcular_media_ponderada(notas2, pesos2) # chama a função de cálculo da média ponderada, utilizando os
                                                      # conteúdos salvos nas listas notas2 e pesos2
    print(f'A média de {aluno} é {media2}') # exibe a média do aluno
    z=input('Deseja repetir o código para outro aluno?\n').upper() # z é a variável que vai executar o loop da "função"
                                                                  # principal
    if z == 'SIM' or z =='S':
        os.system('clear') # limpa tela se o usuário confirmar o loop
