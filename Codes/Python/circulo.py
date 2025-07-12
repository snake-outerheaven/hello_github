import math
import os
# definição da função que calcula a área do circulo
def area_circulo(raio):
    if raio < 0:
        return 'Impossível calcular a área com raio negativo' #condicionais importantes
    if raio == 0:
        return 'A área é zero'
    area = math.pi * pow(raio,2) #math.pi, chama pi, pow chama a função exponencial com base raio, e expoente 2
    return round(area,2) #round(variavel,numero) está retornando o valor do calculo da área do círculo
                         # com duas casas decimais
# definição
def circunferencia(raio):
    if raio < 0:
        return 'Impossível calcular a circunferência com raio negativo' #condicionais importantes
    if raio == 0:
        return 'A circunferência é zero'
    perimetro = 2 * math.pi * raio
    return round(perimetro,2)
# função main XD
z='SIM'
while z == 'SIM' or z== 'S':
    print("\nEste é um programa que calcula a área de um circulo utilizando a formula pi vezes raio ao quadrado e "
          "sua circunferencia usando a formula 2 vezes pi vezes raio \n")
    raio2 = float(input('\nDigite um raio válido: '))
    if raio2 < 0:
        print(area_circulo(raio2))
        print(circunferencia(raio2))
    elif raio2 == 0:
        print(area_circulo(raio2))
        print(circunferencia(raio2))
    else:
        print(f'A área do círculo é {area_circulo(raio2)}')
        print(f'A circumferência do círculo é {circunferencia(raio2)}')

    z=(input('Deseja repetir o código?\n')).upper()
    if z == 'SIM' or z=='S':
        os.system('clear')

# A biblioteca math oferece funções matemáticas e constantes úteis para cálculos diversos:
# Constantes:
# - math.pi: Valor de π (3.141592653589793), usado em cálculos trigonométricos e geométricos.
# - math.e: Base dos logaritmos naturais (2.718281828459045), usada em funções exponenciais.
# - math.tau: Valor de τ (2π, 6.283185307179586), útil para cálculos de ângulos completos.
# - math.inf: Representa infinito positivo (ex.: float('inf')).
# - math.nan: Representa "Not a Number" (ex.: float('nan')).
#
# sqrt(variavel) retorna a raiz quadrada de um número
# Funções principais:
# - Trigonométricas (em radianos): sin(x), cos(x), tan(x), asin(x), acos(x), atan(x), atan2(y, x) (arcotangente de y/x),
#   sinh(x), cosh(x), tanh(x) (hiperbólicas), asinh(x), acosh(x), atanh(x) (inversas hiperbólicas).
# - Exponenciais e logarítmicas: exp(x), expm1(x) (exp(x)-1 com maior precisão para x pequeno), log(x), log1p(x) (log(1+x) com maior precisão),
#   log2(x), log10(x), log(x, base) (logaritmo com base especificada).
# - Potência e raiz: sqrt(x), pow(x, y), hypot(x, y) (hipotenusa: √(x² + y²)), dist(p, q) (distância euclidiana entre pontos p e q).
# - Arredondamento: ceil(x), floor(x), trunc(x), modf(x) (separa parte inteira e fracionária de x).
# - Outras funções numéricas: fabs(x) (valor absoluto), factorial(x), gcd(a, b) (maior divisor comum), lcm(a, b) (mínimo múltiplo comum),
#   fsum(iterable) (soma precisa de floats), prod(iterable) (produto dos elementos de um iterável),
#   remainder(x, y) (resto da divisão conforme IEEE 754), copysign(x, y) (copia o sinal de y para x),
#   nextafter(x, y) (próximo float após x na direção de y), ulp(x) (unidade de precisão mínima para x).
# - Conversões e verificações: degrees(x) (converte radianos para graus), radians(x) (converte graus para radianos),
#   isclose(a, b) (verifica se a e b são próximos), isfinite(x), isinf(x), isnan(x).
# - Funções especiais: erf(x) (função de erro), erfc(x) (função de erro complementar), gamma(x) (função gama),
#   lgamma(x) (logaritmo natural da função gama).
# Este comentário serve como referência para o teste2, que explora o uso de funções matemáticas em Python.
# float em Python funciona como um double em C
