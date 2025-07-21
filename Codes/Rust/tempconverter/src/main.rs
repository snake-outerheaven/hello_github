use std::fs::{self, OpenOptions};
use std::io::{self, Read, Seek, Write}; // uso novo, Seek, para mover o cursor no arquivo
use std::path::Path; // pasta para manipulação de
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
    (temp - 32.0) * (5.0 / 9.0)
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
                        println!("{f}°C equivale a {}°F", fahrenheit(f));
                        return (f.round(), escolha.trim().to_string()); // retornando para futuro registro em arquivo
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
                        println!("{c}°F equivale a {}°C", celsius(c));
                        return (c.round(), escolha.trim().to_string());
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

/// obtendo_nome() -> String
///
/// Função que obtem o nome do usuário de forma segura.

fn obtendo_nome() -> String {
    let mut confirm: String = String::new();
    let mut nome: String = String::new();

    println!("Inicializando função de registro...");
    println!("\n\n");
    sleep(Duration::from_millis(250));

    loop {
        nome.clear();
        confirm.clear();
        println!("Por favor, digite o seu nome de usuário.");
        io::stdin()
            .read_line(&mut nome)
            .expect("Não foi possível ler stdin.");

        let nome_limpo = nome.trim().to_string();

        println!("O nome de usuário {nome_limpo} é o desejado? (S/N)");

        io::stdin()
            .read_line(&mut confirm)
            .expect("Falha ao ler stdin");

        match confirm.trim().to_uppercase().as_str() {
            "S" => {
                sleep(Duration::from_millis(250));
                println!("Nome '{nome_limpo}' confirmado!");
                return nome_limpo;
            }
            "N" => {
                sleep(Duration::from_millis(250));
                println!("Certo, repetindo loop...");
                sleep(Duration::from_secs(1));
                limpar_tela();
                continue;
            }

            _ => {
                println!("Por favor digite S ou N.");
                sleep(Duration::from_millis(250));
                continue;
            }
        }
    }
}

///salvar(conversao: (f64, String), user: String)
///
/// Esta função busca salvar os dados gerados, sendo totalmente opcional.
fn salvar(conversao: (f64, String), user: &String) {
    let (valor, escolha) = conversao; // desestruturando uma tupla de forma simples

    sleep(Duration::from_millis(250));
    println!("Iniciando salvamento dos dados!");
    sleep(Duration::from_secs(1));
    println!("Verificando se a pasta log do projeto existe.");
    let log = Path::new("log");

    if log.exists() {
        println!(
            "Pasta de registro encontrada! Continuando com o fluxo padrão do programa ( Ultimos registros serão mostrados )"
        );
    } else {
        println!(
            "Infelizmente a pasta log não existe, e nem os ultimos registros, vamos começar do zero"
        );
        sleep(Duration::from_millis(250));
        println!("Tentando criar pasta.");
        sleep(Duration::from_secs(1));
        match fs::create_dir(log) {
            Ok(_) => {
                println!("Pasta criada com sucesso!");
            }
            Err(_) => {
                println!(
                    "Não foi possível criar a pasta, verifique se você tem permissões de escrita."
                );
                sleep(Duration::from_millis(250));
                println!(
                    "Como não foi possível criar a pasta, o programa está encerrado por aqui, obrigado por usar!"
                );
                exit(0);
            }
        }
    }

    sleep(Duration::from_millis(250));

    let mut log = OpenOptions::new()
        .append(true)
        .create(true)
        .read(true)
        .open("log/registro.txt")
        .expect("Falha ao criar o arquivo.");

    let registro = format!(
        "Nome do usuário: {} | Escolha: {} | Valor: {}",
        user, escolha, valor
    );

    match writeln!(log, "{}\n", registro) {
        Ok(_) => {
            sleep(Duration::from_millis(250));
            println!("Dados salvos com sucesso!");
            println!("Isso foi o que será registrado no arquivo: {registro}");
        }
        Err(_) => {
            sleep(Duration::from_millis(250));
            println!("Algo inesperado aconteceu! Registro não foi feito com sucesso!");
        }
    }

    sleep(Duration::from_millis(250));

    println!("Agora, será mostrado as ultimas sessões desse código:");

    sleep(Duration::from_millis(250));

    log.rewind()
        .expect("Falha ao mover o cursor dentro do arquivo para o início");

    // preciso fazer a ação de cima para poder registrar o conteúdo, pois o método .append move o cursor interno do arquivo
    // para o final

    let mut conteudo = String::new();

    log.read_to_string(&mut conteudo)
        // esse método varre o arquivo, movendo o cursor e coletando os bits para
        // a string, que então é movida
        .expect("Falha ao ler o arquivo!");

    println!("Ultimas sessões: \n\n{}", conteudo);
}

/// main
///
/// função que amarra toda a lógica em algo funcional
fn main() {
    limpar_tela();
    let nome = obtendo_nome();
    let conversao = tempconverter();
    salvar(conversao, &nome);
}
