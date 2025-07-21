use std::fs::OpenOptions;
use std::io::{self, Write};
use std::process::{Command, exit};
use std::thread::sleep;
use std::time::Duration;

// O objetivo deste código é escrever um simples conversor de temperaturas que faz registros de suas operações em
// um arquivo de texto.

/// limpar_tela -> ()
///
/// Função que busca limpar a tela de forma portátil no Windows e sistemas baseados em UNIX
fn limpar_tela() {
    println!("Limpando tela...");
    sleep(Duration::from_millis(500));
    let clear = if cfg!(target_os = "windows") {
        "cls"
    } else {
        "clear"
    };
    Command::new(clear)
        .status()
        .expect("Não foi possível limpar tela!");
}

/// fahrenheit -> f64
///
/// Função de baixo nível que capta o valor em Celsius digitado pelo usuário e faz prontamente a sua conversão

fn fahrenheit(temp: f64) -> f64 {
    (temp * (9.0 / 5.0)) + 32.0 // em rust, devo usar numeros inteiros com .0 se eu quiser usa-los como float
}

/// celsius -> f64
///
/// Função de baixo nivel que capta o valor em Fahrenheit digitado pelo usuário e faz prontamente a sua conversão

fn celsius(temp: f64) -> f64 {
    (temp - 32.0) * (9.0 / 5.0)
}

/// tempconverter -> f64
///
/// Gera o valor convertido, ao receber o valor desejado pelo usuário, fazendo as operações de conversão conforme
/// a vontade do usuário.
fn tempconverter(user: String) -> f64 {
    let mut temp: String = String::new();
    let mut escolha: String = String::new();

    println!("Iniciando função de conversão.");
    sleep(Duration::from_millis(500));

    loop {
        println!("Por favor, selecione abaixo a operação desejada.");
        println!("1 -> Converter Celsius para Fahrenheit");
        println!("2 -> Converter Fahrenheit para Celsius");
        println!("3 -> Sair do programa.");

        io::stdin()
            .read_line(&mut escolha)
            .expect("Não foi possível ler stdin, encerrando o código");

        match escolha.trim() {
            "1" => loop {
                sleep(Duration::from_secs(250));
                println!("Certo, por favor, digite a temperatura em Celsius.");
                io::stdin()
                    .read_line(&mut temp)
                    .expect("Falha ao ler stdin");
                match temp.trim().parse::<f64>() {
                    Ok(f) => {
                        println!("Gerando valor convertido.");
                        sleep(Duration::from_millis(250));
                        println!("{temp}°C equivale a {}°F", fahrenheit(f));
                        return f; // retornando para futuro registro em arquivo
                    }
                    Err(_) => {
                        sleep(Duration::from_millis(250));
                        println!("Entrada inválida, por favor, digite novamente.");
                        sleep(Duration::from_millis(250));
                        continue;
                    }
                }
            },

            "2" => loop {
                sleep(Duration::from_millis(250));
                println!("Certo, por favor, digite a temperatura em Fahrenheit.");
                io::stdin()
                    .read_line(&mut temp)
                    .expect("Falha ao ler stdin.");
                match temp.trim().parse::<f64>() {
                    Ok(c) => {
                        println!("Gerando valor convertido.");
                        sleep(Duration::from_millis(250));
                        println!("{temp}°F equivale a {}°C", celsius(c));
                        return c;
                    }
                    Err(_) => {
                        sleep(Duration::from_millis(250));
                        println!("Entrada inválida, por favor, digite novamente.");
                        sleep(Duration::from_millis(250));
                        continue;
                    }
                }
            },
            "3" => {
                sleep(Duration::from_millis(250));
                println!("Certo, saindo do código.");
                limpar_tela();
                exit(0);
            }
            _ => {
                sleep(Duration::from_millis(250));
                println!("Escolha inválida, favor digitar novamente!");
                limpar_tela();
                continue;
            }
        }
    }
}
