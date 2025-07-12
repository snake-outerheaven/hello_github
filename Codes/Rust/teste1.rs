use std::process::Command;
use std::thread;
use std::time::Duration; // chamando o tipo Duration de std::time, que me permite definir a duração
                         // Rust pega menos na mão que o esperado hehe, preciso ser claro no que
                         // defino, diferente de C, que Duration ja é o parâmetro da função sleep
                         // em C, já em rust, a função para dormir est

fn main() {
    //let mut n = 0; // não é necessário declarar ela
    for n in 0..10 {
        Command::new("clear")
            .status() //executa o meu comando
            .expect("Falha ao limpar o terminal"); //mensagem de erro se a função main der crash

        println!("O código rodou {} vezes.", n + 1);

        let string = "arroz";

        println!("O valor da string é {string}");

        let x = string.len();

        println!("A string tem {x} de tamanho");

        let string = "maracujá";

        println!("O valor da string é {string}");

        let x = string.len();

        println!("A string tem {x} de tamanho");

        thread::sleep(Duration::from_secs(1));
    }

    Command::new("clear")
        .status() //executa o meu comando
        .expect("Falha ao limpar o terminal"); //mensagem de erro se a função main der crash
}
