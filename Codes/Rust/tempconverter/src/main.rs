use chrono::{DateTime, Local};
use std::fs::{self, OpenOptions};
use std::io::{self, Read, Seek, Write}; // uso novo, Seek, para mover o cursor no arquivo
use std::path::Path; // módulo para manipulação de caminhos de arquivos
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
fn tempconverter() -> (String, String) {
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
            // as operações que uso no match em valores válidos são idênticas
            // é possível escrever uma função para simplificar o código
            // pensar em fazer isso quando começar a escrever código que se repete
            "1" => loop {
                sleep(Duration::from_millis(250));
                println!("Certo, por favor, digite a temperatura em Celsius.");
                io::stdin()
                    .read_line(&mut temp)
                    .expect("Falha ao ler stdin");
                match temp.trim().parse::<f64>() {
                    Ok(num) => {
                        println!("Gerando valor convertido.");
                        sleep(Duration::from_millis(250));
                        let fah = fahrenheit(num); // isso que faltava
                        let fah = format!("{:.2}", fah);
                        println!("{num}°C equivale a {fah}°F"); // shadowing para string
                        return (fah.trim().to_string(), escolha.trim().to_string());
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
                    Ok(num) => {
                        println!("Gerando valor convertido.");
                        sleep(Duration::from_millis(250));
                        let cels = celsius(num);
                        let cels = format!("{:.2}", cels); // shadowing para string
                        println!("{num}°F equivale a {cels}°C");
                        return (cels.trim().to_string(), escolha.trim().to_string());
                    }
                    Err(_) => {
                        sleep(Duration::from_millis(250));
                        println!("Entrada inválida, por favor, digite novamente.");
                        sleep(Duration::from_millis(250));
                        continue;
                    }
                }
            },

            // código genérico como esses abaixo podem ser modularizados
            // em uma função separada, para maior reutilização
            // e ter menos dor de cabeça escrevendo código.
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
    sleep(Duration::from_millis(250));

    loop {
        nome.clear();
        confirm.clear();
        println!("Por favor, digite o seu nome de usuário.");
        io::stdin()
            .read_line(&mut nome)
            .expect("Não foi possível ler stdin.");

        let nome_limpo = nome.trim().to_string();

        println!("O nome de usuário '{nome_limpo}' é o desejado? (S/N)");

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
fn salvar(conversao: (String, String), user: &String) {
    let (valor, escolha) = conversao; // desestruturando uma tupla de forma simples

    sleep(Duration::from_millis(250));
    println!("Iniciando salvamento dos dados!");
    sleep(Duration::from_secs(1));
    println!("Verificando se a pasta log do projeto existe.");
    let log = Path::new("log");
    // no diretório onde está sendo executado o binário, no caso, na raiz do meu projeto
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
                    "Como não foi possível criar a pasta, o programa está encerrado por aqui, obrigado por usá-lo!"
                );
                exit(0); // sai com código 0, pois a função de salvar é extra
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

    let identificador: &str;
    // identificador é uma string imutável,
    // apenas a criei vazia, posso determinar
    // seu valor usando um condicional

    if escolha == "1" {
        identificador = "°F";
    } else {
        identificador = "°C";
    }

    let agora: DateTime<Local> = Local::now();

    let time_stamp_format: String = agora.format("%d/%m/%Y - %H:%M").to_string();

    let registro = format!(
        "Nome do usuário: {} | Escolha: {} | Valor obtido pelo conversor: {}{} | Horário de uso do programa: {}",
        user, escolha, valor, identificador, time_stamp_format
    );

    match writeln!(log, "{}\n", registro) {
        Ok(_) => {
            sleep(Duration::from_millis(250));
            println!("Dados salvos com sucesso!");
            println!("Isso é o que será registrado no arquivo: {registro}");
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

    // segundo o chatgpt, todo arquivo tem um cursor interno, como o cursor do editor Helix, que é o que uso
    // para escrever os meus códigos, como eu fiz uma registro de dados, abrindo o arquivo "log", o cursor
    // onde o sistema operacional usa para escrever os dados através da execução do meu programa, ao rodar writeln!.
    // fica no final, então o cursor deve voltar para o início, por isso o método rewind.
    // -------------------------------------------------------------------------------------------------------------------
    // acho que é por isso que editores multimodais existem, para imitar os métodos de gerenciamento de arquivos que existem
    // nas linguagens de programação ( abrir o arquivo em modo de adição, sobrescrita, leitura)

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
// preciso prestar mais atenção, bugs críticos iam passar, é uma boa dar uma reavaliada em todos os códigos para depois prosseguir estudando.
