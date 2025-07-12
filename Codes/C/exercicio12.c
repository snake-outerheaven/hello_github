#include <stdio.h>
#include <stdlib.h>
#include <math.h>  // Para pow, sqrt e round
#include <unistd.h> // Para sleep

// Função que calcula o número de Fibonacci usando a fórmula de Binet
double binet_fib(int x) {
    double phi = (1 + sqrt(5)) / 2;  // Razão áurea
    double psi = (1 - sqrt(5)) / 2;  // 1 / phi
    return (pow(phi, x) - pow(psi, x)) / sqrt(5);
}

int main(void) {
    int x;

    while (1) {
        printf("\n\n");
        sleep(1);
        printf("Digite um número para saber o Fibonacci correspondente (0 para sair): ");

        // Validação de entrada
        while (scanf("%d", &x) != 1 || x < 0) {
            printf("\n\n");
            sleep(1);
            printf("Caráter inválido detectado! Digite novamente: ");
	    getchar();
        }
	getchar();
        // Condição de saída
        if (x == 0) {
            printf("\n");
            printf("Encerrando o código...\n\n");
            sleep(2);
            exit(0);
        }

        // Calcular Fibonacci com a fórmula de Binet
        double fib_approx = binet_fib(x);

        // Exibir resultado
        if (x <= 78) {
            // Valor exato para n <= 78
            double fib_exact = round(fib_approx);
            printf("\nFibonacci(%d) = %.0lf", x, fib_exact);
        } else {
            // Aproximação para n > 78
            printf("\nFibonacci(%d) ≈ %.5e\n", x, fib_approx);
        }
    }

    return 0;
}
