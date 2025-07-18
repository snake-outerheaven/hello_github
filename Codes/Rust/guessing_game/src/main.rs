// aqui vou escrever o código do jogo da adivinhação do capítulo 2 do livro The Rust Programming Language, mas
// vou fazer umas pequenas alterações do original, primeiramente, pretendo modularizar o código, criando uma
// função que obtenha a entrada do número ( a função vai retornar um result)

use rand::Rng; // biblioteca externa para geração de valores aleatórios
use std::cmp::Ordering; // estrutura de comparação de números, da biblioteca padrão de comparativos
use std::io; // biblioteca padrão de entrada e saída
use std::process::Command; // estrutura Command usada para rodar comandos do shell
use std::thread::sleep; // função que pausa o código, da biblioteca de manipulação de threads
use std::time::Duration; // estrutura que me permite manipular o tempo, usada principalmente no sleep
// vem da biblioteca padrão de tipos temporais ( não sei melhor forma de descrever)
// função que busca limpar tela de forma portátil no Windows e sistemas Unix-like

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

// função que faz a captura do valor do número do usuário

fn obtendo_palpite() -> u32 {
    sleep(Duration::from_millis(500));
    println!("Digite o seu palpite para o número misterioso:");
    let mut palpite = String::new();
    loop {
        palpite.clear();
        // faltou limpar palpite a cada iteração, causando um bug de lógica, pois read_line insere o conteúdo do buffer, não limpando
        // entradas anteriores
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
                println!("Por favor, digite um número entre 1 e 100!");
            }
            Err(_) => {
                println!("Por favor, digite um número válido!");
            }
        };
    } //loop
}

// aqui vem a função que modulariza a obtenção de input do usuário

fn verif(tentativas: u32) -> bool {
    sleep(Duration::from_millis(300));
    println!("Você tentou {tentativas} vezes, deseja continuar? (S/N)");
    let mut entrada = String::new();
    io::stdin()
        .read_line(&mut entrada)
        .expect("crash and burn! não foi possível ler stdin.");

    match entrada.trim().to_uppercase().as_str() {
        "S" => {
            sleep(Duration::from_millis(250));
            println!("Certo, vamos continuar o jogo!");
            return false;
        }

        "N" => {
            sleep(Duration::from_millis(250));
            println!("Certo, obrigado por jogar este jogo!");
            return true;
        }
        _ => {
            sleep(Duration::from_millis(250));
            println!("Resposta inválida! Favor responder S ou N.");
            return verif(tentativas); // recursão mesmo, nao acho que vai pesar muito na stack
        }
    }
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

    let mut usuario_quer_parar = false;

    let mut tentativas: u32 = 0;

    while !usuario_quer_parar {
        tentativas += 1;
        let palpite: u32 = obtendo_palpite();

        match palpite.cmp(&numero_secreto) {
            Ordering::Less => {
                sleep(Duration::from_millis(500));
                println!("{palpite} é menor que o número secreto!");
            }
            Ordering::Equal => {
                sleep(Duration::from_millis(500));
                println!("Bingo! Você adivinhou o número secreto com {tentativas}. Parabéns!");
                return;
            }
            Ordering::Greater => {
                sleep(Duration::from_millis(500));
                println!("{palpite} é maior que o número secreto!");
            } // vou fazer uma função vazia que executa o que quero fazer
        };

        // verificação se o usuário quer parar ou continuar
        usuario_quer_parar = verif(tentativas);

        // comparar números é verboso, mas a forma como rust aborda as coisas não é muito difícil de entender, agora é seguir lendo o livro
    } // fim do loop aqui
}
