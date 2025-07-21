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

/// tempconverter -> (f64, String)
///
/// Retorna uma tupla, com o f64 representando o valor convertido e String a escolha do usuário, para uso na função
/// de salvamento de dados.
fn tempconverter() -> (f64, String) {
    let mut temp: String = String::new();
    let mut escolha: String = String::new();

    println!("Iniciando função de conversão.");
    sleep(Duration::from_millis(500));

    loop {
        escolha.clear(); // quase passou kkk, read_line não sobrescreve, apenas adiciona, então preciso resetar as strings
        temp.clear();
        println!("Por favor, selecione abaixo a operação desejada.");
        println!("1 -> Converter Celsius para Fahrenheit");
        println!("2 -> Converter Fahrenheit para Celsius");
        println!("3 -> Sair do programa.");

        io::stdin()
            .read_line(&mut escolha)
            .expect("Não foi possível ler stdin, encerrando o código");

        match escolha.trim() {
            "1" => loop {
                sleep(Duration::from_millis(250));
                println!("Certo, por favor, digite a temperatura em Celsius.");
                io::stdin()
                    .read_line(&mut temp)
                    .expect("Falha ao ler stdin");
                match temp.trim().parse::<f64>() {
                    Ok(f) => {
                        println!("Gerando valor convertido.");
                        sleep(Duration::from_millis(250));
                        println!("{temp}°C equivale a {}°F", fahrenheit(f));
                        return (f, escolha); // retornando para futuro registro em arquivo
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
                        return (c, escolha);
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

// agora falta a função que obtém o nome do usuário, criar a pasta onde será registrado o arquivo de texto contendo o log
// do programa, escrever a função de salvamento e depois organizar tudo na função main
