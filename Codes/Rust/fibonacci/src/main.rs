use std::io;
use std::process::exit;
use std::thread::sleep;
use std::time::Duration;

// bibliotecas externas
use num_bigint::BigUint;
use num_traits::{One, Zero};

// este código será menor, o objetivo dele é escrever um simples gerador de números fibonnaci, mas
// tentando manter o código no estilo Unix, cada função vai fazer uma unica tarefa, para deixar
// o código mais fácil de manter
//
// Então teremos: uma função de limpar tela, uma função que devolve um número parseado de string para f64,
// uma função de validação de dados, e claro, uma função que implementa a criação automática do diretório
// log, na raíz deste projeto, provavelmente é mais fácil criar módulos para deixar este aqui mais limpo.

//
//

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

        println!("Você confirma a entrada {}?", x.trim()); // faltou limpar o \n da entrada.

        io::stdin()
            .read_line(&mut verif)
            .expect("Falha ao ler stdin, encerrando o código");
        tentativas += 1;
        match verif.trim().to_uppercase().as_str() {
            "S" => {
                sleep(Duration::from_millis(250));
                return true;
            }

            "N" => {
                sleep(Duration::from_millis(250));
                return false;
            }
            _ => {
                sleep(Duration::from_millis(250));
                println!(
                    "Entrada inválida detectada, voce tem {tentativas} tentativas para digitar corretamente antes do código ser encerrado."
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
            entrada = entrada.trim().to_string();
            println!("Entrada {entrada} validada!");
            return entrada.trim().to_string();
        } else {
            println!("Por favor, aguarde para digitar novamente.");
        }
    }
}

/// obter_numero() -> BigUint
///
/// Se utiliza de verif e obtendo_string para gerar um inteiro sem sinal arbitrário, serve mais para obter um número válido para ser
/// parseado para um f64 dentro da função que vai chamar a fórmula de Fibonacci para de fato gerar o n-ésimo fibonacci
fn obter_numero() -> BigUint {
    loop {
        sleep(Duration::from_millis(250));
        println!("Digite um número válido.");
        let numero = obtendo_string(); // obtem uma string validada
        match numero.trim().parse::<BigUint>() {
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

/// fib(n: BigUint) -> BigUint
///
/// Gera meu fibonacci usando a fórmula clássica, Fib = x + (x-1)
fn fib(n: &BigUint) -> BigUint {
    let zero: BigUint = Zero::zero(); // usando o zero da biblioteca externa
    let one: BigUint = One::one(); // usando o um da biblioteca externa

    // clonando as variaveis

    let mut a = zero.clone();

    let mut b = one.clone();

    let mut i = zero.clone();

    while &i < n {
        let temp = b.clone(); // b guarda f(n)
        b = a + &b; // x + ( x - 1 )
        a = temp; // a necessita manter o b antigo para manter o fib.
        i += one.clone();
    }

    a// retorno o valor 
}

/// format_biguint(x:BigUint) -> String
///
/// Formata um BigUint para valores maiores que 1 bilhão
fn format_biguint(x: &BigUint) -> String {
    let valor_a_formatar: String = x.to_string();
    let len: usize = valor_a_formatar.len();

    if len > 7 {
        let primeiro_digito: &str = &valor_a_formatar[..1]; // forma de iterar sobre os dados de forma mais rápida
        let decimal: &str = &valor_a_formatar[1..3];
        let expoente: usize = len - 1;
        format!("{primeiro_digito}.{decimal}e{expoente}")
    } else {
        valor_a_formatar
    }
}

/// main() -> ()
///
/// Executa o conjunto das funções acima de modo a fornecer a saida do código
fn main() {
    println!(
        "Este é um programa gerador de números Fibonacci que calcula o enésimo termo da sequência de Fibonacci de acordo com o número que você digitar."
    );
    sleep(Duration::from_millis(250));
    println!(
        "Ele gera os números usando a forma iterativa, simples de se gera um Fibonacci, então números absurdamente grandes podem travar o processo do programa."
    );
    sleep(Duration::from_millis(250));
    println!(
        "Isso será corrigido em uma versão posterior, quando a função que obtém o Fibonacci for reescrita com um algoritmo melhor."
    );
    let x: BigUint = obter_numero();
    let fib: BigUint = fib(&x);
    let fib_formatado: String = format_biguint(&fib);

    println!("O {x}º número da sequência de Fibonacci é {fib_formatado}.");
}

// pretendo implementar uma função que salve em breve, por enquanto, vamos manter o código simples
//
//
// & na prática é um ponteiro que aponta para os dados, em Rust, sempre devo usar ele para acessar dados de outras
// variáveis, depois de terminar esse código vou seguir para o capitulo 4.
