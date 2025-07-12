use std::io;
use std::process;
use std::thread;
use std::time::Duration;

const PI: f64 = 3.14159265359; // constantes são sempre maiusculas

fn circunferencia(raio: f64) -> f64 {
    2.0 * PI * raio
}

fn area(raio: f64) -> f64 {
    PI * raio.powf(2.0) // ou powi(u32 || u64) se a função retornasse u32 ou u64 ( int && long int em C ) 
}

fn main() {
    loop {
        process::Command::new("clear") // lembrar de usar new ao usar Command, para limpar a tela
            .status()
            .expect("Não foi possível limpar a tela do terminal!");

        println!("Este é um código escrito em Rust que calcula área e circunferência do círculo");
        println!("\n\nDigite um raio para poder calcular a área e circunfêrencia de um círculo: ");

        let mut raio = String::new();

        io::stdin()
            .read_line(&mut raio)
            .expect("Não foi possível obter input do usuário!");

        let raio: f64 = match raio.trim().parse() {
            Ok(num) => num, // raio = atol ( raiostr) ; ?
            Err(_) => {
                println!("Digite um número válido!");
                thread::sleep(Duration::from_millis(500));
                println!("Limpando a tela...");
                thread::sleep(Duration::from_secs(1));
                continue;
            }
        }; // fim do parse aqui ( colocar ; no final do parse )

        if raio == 0.0 {
            // de 0 para 0.0 pois raio é f64
            println!("\n\nSaindo...");
            thread::sleep(Duration::from_secs(1));
            break;
        } else {
            thread::sleep(Duration::from_millis(300));
            println!("\n\nSaiba que digitando 0, você sai do programa.");
            thread::sleep(Duration::from_millis(300));
        }

        let circ = circunferencia(raio);
        let areacirc = area(raio);
        let formatcirc = format!("{:.2}", circ); // macro de formatação, onde {} é o placeholder e : representa a variavel
        // (provavelmente) e .2 indica o número de casas
        // decimais
        let formatarea = format!("{:.2}", areacirc);

        println!(
            "\n\nA área do círculo é {formatarea} unidades de área e sua circunferência é {formatcirc} unidades de comprimento."
        );

        thread::sleep(Duration::from_secs(5));
    } // fim do loop aqui
} // fim da main aqui
