use std::io; // biblioteca de funções de entrada e saida
use std::process; // biblioteca para usar Command
use std::thread; // biblioteca de controle de processos, estou usando para thread::sleep(Duration::from_millis()) ou (Duration::from_secs())
use std::time::Duration; // escrever desse jeito apenas para
                         // usar o tipo Duration de time

// reescrever o código do fibonacci, usando a fórmula de binet

fn binet_fib(num: u32) -> Result<f64, &'static str> {
    let phi: f64 = (1.0 + 5.0_f64.sqrt()) / 2.0;
    let psi: f64 = (1.0 - 5.0_f64.sqrt()) / 2.0;
    let resultado = ((phi.powi(num as i32)) - (psi.powi(num as i32))) / 5.0_f64.sqrt();
    if num > 78 {
        Err("Valor muito grande!")
    } else {
        Ok(resultado)
    }
}

/* Calcula o número de Fibonacci usando a fórmula de Binet (φ^x - ψ^x) / √5.
 * Baseado em exercicio1.rs, usa Result para tratar erros.
 * Parâmetro: num (u32) é convertido para i32 com as para powi (potência inteira).
 * Novo: 5.0_f64 melhora legibilidade, sendo float 64 bits.
 * Limita a 78 por precisão de f64; retorna erro se num > 78.
 * Corrigi a fórmula com parênteses para ordem correta. */

/* Dados que deixei passar:
 * - PSI estava errado como (1.0 + √5) / 2, corrigido para (1.0 - √5) / 2.
 * - Fórmula original tinha erro de precedência, ajustei para ((φ^x - ψ^x) / √5).
 * - Variável x no if era num, corrigida.
 * - powi exige i32, por isso num as i32, não explorei alternativas como powf.
 * - Testei só com 5, preciso verificar outros valores. */

fn main() {
    loop {
        process::Command::new("clear")
            .status()
            .expect("Não foi possível limpar tela!");

        thread::sleep(Duration::from_millis(700));

        println!("Este é um programa em Rust que calcula o valor correspondente à posição dada pelo usuário na sequencia de Fibonnacci, usando a formula de Binet.");

        thread::sleep(Duration::from_millis(700));

        println!("Digite sair ou zero (0) para encerrar o código");

        thread::sleep(Duration::from_millis(700));

        println!("Digite um número para saber o Fibonnacci correspondente:");

        let mut entrada = String::new();

        io::stdin()
            .read_line(&mut entrada)
            .expect("Não foi possível ler stdin!");

        let entrada_normalizada = entrada.trim().to_lowercase();

        if entrada_normalizada == "sair"
            || entrada_normalizada == "0"
            || entrada_normalizada == "zero"
        {
            thread::sleep(Duration::from_millis(1500));
            println!("Saindo do código...");
            thread::sleep(Duration::from_millis(1500));
            break;
        }

        let x: u32 = match entrada_normalizada.parse() {
            Ok(num) => num,
            Err(_) => {
                thread::sleep(Duration::from_millis(1500));
                println!("Valor inválido digitado, limpando tela para permitir nova entrada...");
                thread::sleep(Duration::from_millis(1500));
                process::Command::new("clear")
                    .status()
                    .expect("Não foi possível limpar tela!");
                continue;
            }
        }; // é uma boa ideia colocar comentários no final do match, que está avaliando o Result de parse

        let fib = binet_fib(x);

        match fib {
            Ok(resultado) => println!("O Fibonnacci correspondente à {x} é {:.0}", resultado),
            Err(e) => println!("Erro: {e}"),
        };

        println!("Limpando tela em 5 segundos.");

        thread::sleep(Duration::from_secs(5));
    }
}
