use std::io; // biblioteca de funções de saída e entrada
use std::process; // biblioteca para usar command
use std::thread; // biblioteca para controle de processos
use std::time::Duration; // biblioteca de tempo que até entao eu só estou importando Duration ( um tipo para determinar tempo)

/* determinar a média ponderada de 3 notas com 3 pesos, para um aluno, e determinar se o aluno está aprovado ( M > 6.0 )
se precisa prestar Exame ( 5.0 < M < 6.0), ou reprovado ( M < 5.0)*/

/*aqui vem a função que retorna o nome do aluno */

fn nome() -> String {
    thread::sleep(Duration::from_secs(1));

    println!("Digite o nome do aluno: ");

    let mut aluno = String::new();

    io::stdin()
        .read_line(&mut aluno)
        .expect("Não foi possível ler stdin!");

    let aluno = aluno.trim().to_string(); // trim devolve &str, que é imutável, entao converto para string
                                          // para poder retornar no código

    println!("O nome '{aluno}' está certo?");

    let mut resposta = String::new();

    io::stdin()
        .read_line(&mut resposta)
        .expect("Não foi possível ler stdin!");

    let resposta = resposta.trim().to_lowercase();

    if resposta == "sim" || resposta == "ss" || resposta == "s" {
        thread::sleep(Duration::from_millis(400));
        println!("Nome: {aluno} confirmado!");
        return aluno;
    } else if resposta == "não"
        || resposta == "n"
        || resposta == "ñ"
        || resposta == "nao"
        || resposta == "nn"
    {
        println!("Ok!");

        thread::sleep(Duration::from_millis(400));

        println!("Repetindo a função...");

        thread::sleep(Duration::from_millis(400));

        process::Command::new("clear")
            .status()
            .expect("Não foi possível limpar a tela!");

        return nome();
    } else {
        thread::sleep(Duration::from_millis(200));

        println!("Resposta inválida detectada! Digite novamente a resposta de forma correta ou o programa será encerrado.");

        let mut resposta = String::new();

        io::stdin()
            .read_line(&mut resposta)
            .expect("Não foi possível ler stdin!");

        println!("Sua resposta final é : {resposta}?");

        resposta.clear(); // limpo a string resposta, aplicando esse método

        io::stdin()
            .read_line(&mut resposta)
            .expect("Não foi possível ler stdin!");

        let resposta = resposta.trim().to_lowercase();

        if resposta == "sim" || resposta == "ss" || resposta == "s" {
            thread::sleep(Duration::from_millis(400));

            println!("Nome do aluno confirmado: {aluno}");

            return aluno;
        } else if resposta == "não"
            || resposta == "n"
            || resposta == "ñ"
            || resposta == "nao"
            || resposta == "nn"
        {
            thread::sleep(Duration::from_millis(500));
            println!("Retornando a função");
            thread::sleep(Duration::from_millis(500));
            process::Command::new("clear")
                .status()
                .expect("Não foi possível limpar a tela!");
            return nome();
        } else {
            println!("Encerrando...");
            thread::sleep(Duration::from_millis(400));
            process::exit(1);
        }
    }
} // fim da função aqui

/*Aqui vem a função que retorna dois vetores, o de notas e o de pesos ( notas é float e pesos é int)*/
/// Função para obter as notas e pesos de um aluno.
///
/// # O que faz
/// - Pergunta 3 notas e 3 pesos.
/// - Cada nota deve ser de 0 a 10.
/// - Cada peso deve ser de 1 a 10.
/// - Confirma cada par nota/peso.
/// - Se não confirmar, repete a entrada.
/// - Retorna (Vec<f64>, Vec<u32>)
///
/// # Parâmetro
/// - `aluno`: nome do aluno para exibir.
///
/// # Retorno
/// Dupla de vetores: (notas, pesos).
fn obter_notas_e_pesos(aluno: String) -> (Vec<f64>, Vec<u32>) {
    let mut notas = Vec::new();
    let mut pesos = Vec::new();

    // Contador manual para controlar a iteração.
    let mut i = 0;

    while i < 3 {
        // -------------------------------------------
        // LEITURA DA NOTA
        // -------------------------------------------
        loop {
            println!("Digite a {}ª nota de {} (0 a 10):", i + 1, aluno);

            let mut entrada = String::new();
            std::io::stdin()
                .read_line(&mut entrada)
                .expect("Erro na leitura da entrada.");

            match entrada.trim().parse::<f64>() {
                // usar um match, em cima da string, para avaliar tamanho, genio ( executa ações mas nao salva variável )
                Ok(nota) if nota >= 0.0 && nota <= 10.0 => {
                    println!("Nota ({}) registrada.", nota);
                    notas.push(nota);
                    break; // Vai pro peso.
                }
                Ok(_) => {
                    println!("Nota fora do intervalo! Deve ser entre 0 e 10.");
                    continue;
                }
                Err(_) => {
                    println!("Erro: digite um número real.");
                    continue;
                }
            }
        }

        // -------------------------------------------
        // LEITURA DO PESO
        // -------------------------------------------
        loop {
            println!("Digite o peso da {}ª nota (1 a 10):", i + 1);

            let mut entrada = String::new();
            std::io::stdin()
                .read_line(&mut entrada)
                .expect("Erro na leitura da entrada.");

            match entrada.trim().parse::<u32>() {
                Ok(peso) if peso >= 1 && peso <= 10 => {
                    println!("Peso ({}) registrado.", peso);
                    pesos.push(peso);
                    break; // Vai pra confirmação.
                }
                Ok(_) => {
                    println!("Peso fora do intervalo! Deve ser entre 1 e 10.");
                    continue;
                }
                Err(_) => {
                    println!("Erro: digite um número inteiro.");
                    continue;
                }
            }
        }

        // -------------------------------------------
        // CONFIRMAÇÃO
        // -------------------------------------------
        loop {
            println!(
                "Confirma a {}ª nota ({}) com peso ({})? (s/n)",
                i + 1,
                notas[i],
                pesos[i]
            );

            let mut conf = String::new();
            std::io::stdin()
                .read_line(&mut conf)
                .expect("Erro na leitura da entrada.");

            let conf = conf.trim().to_lowercase();

            if conf == "s" {
                println!("Par confirmado.\n");
                i += 1; // Avança pra próxima nota/peso.
                break;
            } else if conf == "n" {
                println!("Ok! Vamos repetir a {}ª nota/peso.\n", i + 1);
                notas.pop(); // remove o ultimo item colocado, inverso de push
                pesos.pop();
                break; // Não avança o i → repete.
            } else {
                println!("Digite 's' ou 'n'.");
                // Repete o loop de confirmação.
            }
        }
    }

    (notas, pesos) // retorna notas e pesos
}

/*Aqui vem a função que retorna a média ponderada do aluno, recebendo como argumentos as notas e os pesos*/

/*Aqui vem a função principal*/

fn main() {
    let aluno = nome(); // nome é string ( tipagem implicita pelo valor do retorno )
    println!("{aluno}"); // função funciona e retorna o valor desejado
    let (notas, pesos) = obter_notas_e_pesos(aluno.clone()); // funçao retorna dois vetores, encapsulados em uma tupla
                                                             //tive que utilizar o método clone, orientado pelo compilador, pois o parametro da função obtem posse da variavel aluno, o clone como o nome diz, com certeza
                                                             // deve servir para criar uma nova instância da variável
    println!(
        "As notas e pesos determinados para {aluno} são, respectivamente: {:.?} e {:.?}",
        notas, pesos
    );
    return;
}
