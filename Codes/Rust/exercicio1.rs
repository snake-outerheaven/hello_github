use std::io; // biblioteca de funções de entrada e saida
use std::process; // process::Command para rodar comandos do sistema
use std::thread; // manipulação de processos ( thread::sleep(Duration::from_millis ou from_secs))
use std::time::Duration; // bibilioteca de tipos temporais, Duration significa exatamente o que significa no cotidiano

/* reescrever os ultimos exercicios de C em Rust */

fn fatorial(n: u128) -> Result<u128, &'static str> {
    if n == 0 || n == 1 {
        Ok(1)
    } else if n > 20 {
        // Limite para evitar overflow
        Err("Número muito grande para calcular o fatorial!")
    } else {
        Ok(n * fatorial(n - 1)?) // Propaga erro com ?
    }
}

/*Criando este comentário porque a explicação vai ser grande, a minha variavel n, do tipo u128 ( unsigned int de 128 bits), retorna um tipo Result
capaz de processar o u118 para retornar o meu numero em ok, e uma &'static' &str,  que é uma referencia( ponteiro ), cujo lifetime, determinado por
static, dura durante toda a execução do problema, e é usado em err ( acho que o programa gera crash, ou volta no loop, colocar um condicional para isso)
acredito que o ? propaga o erro adiante, durante a chamada recursiva da função, que converge para 1, quando a função vai retornar o fatorial inteiro*/

fn main() {
    process::Command::new("clear")
        .status()
        .expect("Falha ao limpar a tela!");

    loop {
        println!("Este é um código que estuda a aplicação de funções recursivas em Rust, usando o fatorial (x!) como instrumento.");

        thread::sleep(Duration::from_millis(500));
        println!("Digitando sair você  encerra o código");
        thread::sleep(Duration::from_millis(500));

        println!("Insira um número para saber seu fatorial:");

        let mut entrada = String::new();

        io::stdin()
            .read_line(&mut entrada)
            .expect("Não foi possivel ler stdin!"); //stdin é uma função, faltou ()

        thread::sleep(Duration::from_millis(500));

        if entrada.trim().to_lowercase() == "sair" {
            thread::sleep(Duration::from_millis(400));
            println!("Saindo do programa...");
            thread::sleep(Duration::from_millis(400));
            break;
        }

        let entrada: u128 = match entrada.trim().parse() {
            Ok(num) => num,
            Err(_) => {
                thread::sleep(Duration::from_secs(1));
                println!("Valor inválido detectado!");
                thread::sleep(Duration::from_millis(100));
                process::Command::new("clear")
                    .status()
                    .expect("Falha ao limpar tela!");
                println!("Tente novamente!");
                continue;
            }
        }; // fim da linha do bloco de comando do meu parse

        let resultado = fatorial(entrada);
        match resultado {
            Ok(resultado) => println!("O fatorial de {entrada} é {resultado}"),
            Err(e) => println!("Erro {e}"),
        }
        thread::sleep(Duration::from_millis(1200));
        println!("Limpando tela...");
        thread::sleep(Duration::from_millis(300));
        process::Command::new("clear")
            .status()
            .expect("Nao foi possível limpar a tela!");
    } // fim do meu loop aqui
} // fim da função principal aqui
