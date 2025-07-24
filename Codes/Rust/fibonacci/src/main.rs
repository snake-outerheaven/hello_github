use std::fs::{self, OpenOptions};
use std::io::{self, Read, Seek, Write};
use std::path::Path;
use std::process::{Command, exit};
use std::thread::sleep;
use std::time::Duration;

// este código será menor, o objetivo dele é escrever um simples gerador de números fibonnaci, mas
// tentando manter o código no estilo Unix, cada função vai fazer uma unica tarefa, para deixar
// o código mais fácil de manter
//
// Então teremos: uma função de limpar tela, uma função que devolve um número parseado de string para f64,
// uma função de validação de dados, e claro, uma função que implementa a criação automática do diretório
// log, na raíz deste projeto, provavelmente é mais fácil criar módulos para deixar este aqui mais limpo.

/// verif(x: &str) -> Bool
///
/// função que busca deixar o código mais reutilizável, para a construção de algo de maior nível, esta função
/// serve somente para o caso base de confirmação de uma entrada do usuário, sendo usada em uma estrutura match
/// para avaliar o valor que ela retorna.
fn verif(x: &str) -> bool {
    let mut verif: String = String::new();

    let mut tentativas: u32 = 0;

    while tentativas < 3 {
        verif.clear();

        sleep(Duration::from_millis(250));

        println!("Você confirma a entrada {x}?");

        io::stdin()
            .read_line(&mut verif)
            .expect("Falha ao ler stdin, encerrando o código");
        tentativas += 1;
        match verif.trim().to_uppercase().as_str() {
            "S" => {
                sleep(Duration::from_millis(250));
                println!("{x} confirmado!");
                return true;
            }

            "N" => {
                sleep(Duration::from_millis(250));
                println!("{x} não confirmado, favor repetir entrada.");
                return false;
            }
            _ => {
                sleep(Duration::from_millis(250));
                println!(
                    "Entrada inválida detectada, voce tem {tentativas} tentativas para digitar corretamente"
                );
                continue;
            }
        }
    }
    println!("Máximo de tentativas alcançado, saindo do código.");
    sleep(Duration::from_secs(1));
    exit(0);
}

/// obtendo_string() -> String
///
/// Obtém uma string do usuário, sendo uma das funções mais elementares do código. ( pode ser uada para obter valores para passar para uma função de conversão numérica, nomes, quaisquer dados importantes )
fn obtendo_string() -> String {
    let mut entrada = String::new();
    loop {
        entrada.clear();
        sleep(Duration::from_millis(250));
        io::stdin()
            .read_line(&mut entrada)
            .expect("falha ao ler stdin");

        if verif(&entrada) {
            println!("Entrada {entrada} validada!");
            return entrada.trim().to_string();
        } else {
            println!("Por favor, aguarde para digitar novamente.");
        }
    }
}

/// obter_numero() -> u32
///
/// Se utiliza de verif e obtendo_string para gerar um valor u32, serve mais para obter um número válido para ser
/// parseado para um f64 dentro da função que vai chamar a fórmula de binet para de fato gerar o n-ésimo fibonacci
fn obter_numero() -> u32 {
    loop {
        sleep(Duration::from_millis(250));
        println!("Digite um número válido.");
        let numero = obtendo_string(); // obtem uma string validada
        match numero.trim().parse::<u32>() {
            Ok(num) => {
                sleep(Duration::from_millis(250));
                println!("Número lido: {num}");
                return num;
            }
            Err(_) => {
                sleep(Duration::from_millis(250));
                println!("Valor inválido detectado, por favor, digite números positivos inteiros.");
                continue;
            }
        }
    }
}
