// aqui vou escrever o código do jogo da adivinhação do capítulo 2 do livro The Rust Programming Language, mas
// vou fazer umas pequenas alterações do original, primeiramente, pretendo modularizar o código, criando uma
// função que obtenha a entrada do número ( a função vai retornar um result)

use rand::Rng;
use std::cmp::Ordering;
use std::io;
use std::process::Command;
use std::thread::sleep;
use std::time::Duration;

// função que busca limpar tela de forma portátil no Windows e sistemas Unix-like

fn limpar_tela() {
    println!("Limpando tela...");
    sleep(Duration::from_millis(500));
    let clear = if cfg!(target_os = "windows ") {
        "cls"
    } else {
        "clear"
    };
    Command::new(clear)
        .status()
        .expect("Não foi possível limpar tela!");
}

// função que faz a captura do valor do número do

fn obtendo_palpite() -> u32 {
    sleep(Duration::from_millis(500));
    println!("Digite o seu palpite para o número misterioso:");
    let mut palpite = String::new();
    loop {
        io::stdin()
            .read_line(&mut palpite)
            .expect("crash and burn! ( falha ao ler o palpite )");
        match palpite.trim().parse::<u32>() {
            Ok(palpite) if palpite >= 1 && palpite <= 100 => {
                sleep(Duration::from_secs(1));
                println!("Você acha que é {palpite}.");
                return palpite;
            }
            Ok(_) => {
                println!("Por favor, digite um número válido!");
            }
            Err(_) => {
                println!("Por favor, digite um número válido!");
            }
        };
    } //loop
}

fn main() {
    limpar_tela();
    // agora vem o uso principal de tudo até então, a função main deve rodar a lógica principal, que é gerar o
    // número secreto, obter a entrada do usuário, comparar a entrada com o número secreto ( tudo de acordo

    let numero_secreto = rand::thread_rng().gen_range(1..=100);
    // este é o gerador de números aleatórios
    // coisas como RNG geralmente tem uma semente de geração, como os mundos do minecraft, e aqui não
    // é diferente, thread_rng faz a mesma coisa usando as fontes de entropia do meu sistema ( caos ) para gerar um número
    // e o gen_range apenas limita o alcance da geração de números aleatórios para o intervalo de 1 a 100

    loop {
        let palpite: u32 = obtendo_palpite();

        match palpite.cmp(&numero_secreto) {
            Ordering::Less => {
                sleep(Duration::from_millis(500));
                println!("{palpite} é menor que o número secreto!");
                continue;
            }
            Ordering::Equal => {
                sleep(Duration::from_millis(500));
                println!("Bingo! Você adivinhou o número secreto!");
                return;
            }
            Ordering::Greater => {
                sleep(Duration::from_millis(500));
                println!("{palpite} é maior que o número secreto!");
                continue;
            }
        };

        // comparar números é verboso, mas a forma como rust aborda as coisas não é muito difícil de entender, agora é seguir lendo o livro
        
    } // fim do loop aqui
}
