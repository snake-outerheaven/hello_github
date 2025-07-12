use rand::Rng; // chamando o biblioteca externa (crate library) de números aleatorios, com o módulo rng ( nome sugestivo )
use std::cmp::Ordering;
// isso aqui parece trazer a biblioteca de comparação, chamando o tipo Ordering, que é do tipo enum ( um tipo de
// variavel que tem vários valores, dependendo do tipo ) que possui o valor
// Less, para quando o número comparado é menor que o numero com o qual ele
// é comparado, Greater para quando o número é maior, e Equal quando o
// número é igual
use std::io; // chamando a biblioteca de entrada e saida padrão de rust, mesma coisa de #include <stdio.h>
use std::process::Command; // para limpar o terminal com o comando clear
use std::thread; // para adicionar pausas (delays) no jogo
use std::time::Duration; // para especificar a duração das pausas

fn main() {
    let numero_secreto = rand::thread_rng().gen_range(1..=100); // atualizei para a API moderna do rand
    // thread_rng() gera o número aleatório, e gen_range limita de 1 a 100
    // sua versão anterior usava rng().random_range(), que pode estar obsoleta

    // println!("O número secreto é {numero_secreto}"); // linha que mostra o valor do numero aleatorio gerado pelas funções acima
    // sera removido depois

    loop {
        // mesma coisa que while True ou while (1), loop infinito

        // limpa o terminal a cada iteração
        Command::new("clear")
            .status()
            .expect("Falha ao limpar o terminal");

        println!("Este é um jogo da adivinhação de números");
        thread::sleep(Duration::from_millis(500)); // pausa de 0,5 segundo para efeito visual

        println!("Digite o seu palpite: ");
        thread::sleep(Duration::from_millis(200)); // pausa de 0,2 segundo

        let mut guess = String::new(); // aqui, declaro uma variavel mutavel chamada guess
        // e ela recebe o tipo string, e new é uma função
        // associada ao tipo string, e significa que guess
        // resebe uma string vazia, depois ver o que () em
        // new significa { new é uma função sem parametros que
        // inicaliza o tipo String para guess)

        // aqui vem a parte que eu uso guess para armazenar a entrada do usuario, que vem do buffer
        // stdin

        io::stdin()
            .read_line(&mut guess)
            .expect("Falha ao ler entrada do usuário");

        // read_line parece funcionar igualzinho ao fgets de C para ler strings, com & sendo referente
        // a variavel mutavel guess, e expect é o tratamento de erros, provavelmente ao usuario apenas
        // apertar enter, e pular, deve ter alguma forma de condicionar, de forma parecida ao
        // while ( scanf("%s",&guess) != 1 ){ codigoblabla }.

        // aqui vem a magica, guess é mutável, entao vou determinar ela agora como um numero sem sinal
        // de 32 bits, pois nao posso comparar uma string com números

        let guess: u32 = match guess.trim().parse() {
            Ok(num) => num, // Ok contem o valor convertido, que vai retornar o valor (num)
            Err(_) => {
                // em Err, o _ pega todo o tipo de valor nao importando o valor que está errado
                println!("Por favor, digite um número válido entre 1 e 100!");
                // nova mensagem para entradas inválidas (ex.: letras, números negativos)
                thread::sleep(Duration::from_secs(1)); // pausa para o usuário ler a mensagem
                continue;
            }
        };

        // validação para garantir que o palpite está entre 1 e 100
        if guess < 1 || guess > 100 {
            println!("O número deve estar entre 1 e 100!");
            thread::sleep(Duration::from_secs(1)); // pausa para o usuário ler a mensagem
            continue;
        }

        // partimos de um expect para uma função do tipo match, para trocar expect, que indica a
        // mensagem de erro apos o crash da função main, ao escrevermos o que não devemos, aqui é
        // pra deixar de forma clara que parse retorna um enum ( variavel com valor variavel, cujos
        // valores são chamados de variantes ) chamado Result, e que suas variantes são Ok, ao ler
        // certo, e Err, que indica quando parse recebe um valor que nao pode converter para u32
        // _ aqui significa qualquer tipo de valor que gere Err, e isso está para um continue,
        // que repete o loop, muito interessante

        // tive que comentar pq o livro falou pra reescrever isso de outra forma
        // u32 é um unsigned number de 32 bits, número sem sinal ( naturais )
        // .trim() // remove os espaços laterais, quando o usuario digita espaçoespaçoespaçoNUMEROespaçoespaçoespaço
        // .parse() // parse faz a mágica, converte a string digitada pelo usuário em um número sem sinal de 32 bits
        // .expect("Por favor, digite um número"); // tratamento de erros, acontece se o result ( outro enum ) retornado por parse
        // indicar erro, quebra o código kkkkk

        // em Rust, é possível converter os tipos de variáveis de forma impressionante, vamos ver se o
        // código compila

        println!("Voce palpitou o número {}", guess); // println! é um macro, não sendo associado à std::io
        // vou testar sem o !, vendo se consigo usar o println da
        // biblioteca direramente
        // hehe, deu pra "concatenar"a string desse jeito, usando
        // {} desse jeito, é possível ver que parece um %s, só que
        // nao preciso determinar o tipo, sendo dinamico, o jeito
        // original do código é {}", guess ou { guess }
        // para concatenar com ela mesma, usei a função .clone() e
        // somei com a referencia de guess, é possível fazer
        // concatenação simples apenas "somando" guess com "2"
        // ficando assim {}", guess +
        thread::sleep(Duration::from_millis(300)); // pausa de 0,3 segundo

        match guess.cmp(&numero_secreto) {
            Ordering::Less => {
                println!("{guess} é menor que o número secreto.");
                thread::sleep(Duration::from_secs(1)); // pausa de 1 segundo
            }
            Ordering::Equal => {
                println!("Parabéns, vc adivinhou o número!");
                thread::sleep(Duration::from_secs(1)); // pausa de 1 segundo
                break;
            }
            Ordering::Greater => {
                println!("{guess} é maior que o número secreto.");
                thread::sleep(Duration::from_secs(1)); // pausa de 1 segundo
            }
        } // fim do meu caso de comparação
        // aqui basicamente, funciona da seguinte maneira, guess.cmp ( &numero_secreto) gerencia a
        // comparação de guess com numero_secreto, e isso é jogado para match, que é uma expressão
        // que decide o que fazer com o valor do enum Ordering, o livro fala pra eu prestar bastante
        // atenção em padrões e o constructo match, pois são ferramentas poderosas de Rust, pois me
        // permitem expressar uma variedade de situações que o código pode encontrar e fazer com que
        // eu saiba lidar com o que acontecer.
    } // fim da determinação do loop, o que estiver dentro roda infintamente
} // fim da função main aqui

/*
 * Post Scriptum: tive que adicionar o "crate" que basicamente é uma biblioteca externa, chamado
 * rand, que é a biblitoeca de números aleatórios o que é interessante, pelo que vi, posso tanto
 * adicionar o crate através do cargo, com cargo add rand ou editando diretamente o arquivo de
 * configuração do cargo, o cargo.toml, colocando embaixo de dependencies rand = "versao"
 *
 * O livro falou que é possivel rodar cargo doc --open para poder ler a documentação das crates que
 * eu instalar, vou rodar aqui para ver mais sobre a documentação de rand
 */
