// Importações - Similar ao #include do C, mas mais específico
use std::io; // Para entrada/saída (como stdio.h)
use std::process; // Para controle de processos (como exit())
use std::thread; // Para pausas/sleep (não existe nativamente no C padrão)
use std::time::Duration; // Para definir durações de tempo

// Função para converter Fahrenheit para Celsius
// Em C seria: double fahrenheit_para_celsius(double fahrenheit)
// Rust usa 'fn' ao invés de especificar o tipo de retorno antes do nome
fn fahrenheit_para_celsius(fahrenheit: f64) -> f64 {
    // f64 = double do C (64 bits de precisão)
    // -> f64 indica o tipo de retorno (similar ao double antes da função em C)
    (fahrenheit - 32.0) * 5.0 / 9.0
    // Em Rust, a última expressão sem ';' é automaticamente retornada
    // Em C precisaríamos escrever: return (fahrenheit - 32.0) * 5.0 / 9.0;
}

// Função para converter Celsius para Fahrenheit
fn celsius_para_fahrenheit(celsius: f64) -> f64 {
    celsius * 9.0 / 5.0 + 32.0
    // Novamente, sem 'return' explícito - isso é idiomático em Rust
}

fn main() {
    // println! é uma macro (!) para impressão formatada
    // Similar ao printf() do C, mas type-safe (verifica tipos em tempo de compilação)

    process::Command::new("clear")
        .status()
        .expect("Falha ao rodar o comando"); // tive que usar new( parametro que ia no Command) para poder usar ele sem precisar adicionar o Command em process
    println!("Este é um conversor de temperatura escrito em Rust que faz a conversão de graus Celsius para graus Fahrenheit.");

    // Loop infinito - equivalente a while(1) ou for(;;) em C
    loop {
        // Pausa de 1 segundo - em C usaríamos sleep(1) após #include <unistd.h>
        thread::sleep(Duration::from_secs(1));

        // Menu do programa
        println!("\n\nMenu principal\n\n");
        println!("Opção 1 -> Calcular graus Fahrenheit.");
        println!("Opção 2 -> Calcular graus Celsius.");
        println!("Opção 3 -> Sair do programa.");
        println!("Leia atentamente as opções e digite sua escolha:");

        // Declaração de variável mutável
        // Em C: char escolha[100]; ou similar
        // String::new() cria uma string vazia e crescível (como malloc + gerenciamento automático)
        let mut escolha = String::new();

        // Leitura de entrada do usuário
        // Em C seria: fgets(escolha, sizeof(escolha), stdin);
        io::stdin()
            .read_line(&mut escolha) // &mut = referência mutável (como passar ponteiro em C)
            .expect("Falha ao obter input do usuário!"); // Tratamento de erro - em C checkaríamos if(fgets(...) == NULL)

        // Conversão de string para número com tratamento de erro
        // Em C seria: int escolha_num = atoi(escolha); (sem tratamento de erro robusto)
        let escolha: u32 = match escolha.trim().parse() {
            // trim() remove espaços e \n (como fazer manualmente em C)
            // parse() tenta converter para u32 (unsigned int de 32 bits)
            // match é como switch, mas mais poderoso
            Ok(num) => num, // Se conversão deu certo, usa o número
            Err(_) => {
                // Se deu erro (equivalente ao default: em switch)
                println!("Digite um número válido!");
                thread::sleep(Duration::from_secs(1));
                continue; // Volta para o inicio do loop (como continue; em C)
            }
        };

        // Switch case melhorado - match é exhaustivo (precisa cobrir todos os casos)
        match escolha {
            1 => {
                // case 1: em C
                // Loop para validar entrada de temperatura
                loop {
                    println!("Digite a temperatura em graus Celsius para fazer a conversão:");

                    // Nova string para a temperatura
                    let mut temp = String::new();

                    // Leitura da temperatura
                    io::stdin()
                        .read_line(&mut temp)
                        .expect("Falha ao obter input do usuário!");

                    // Tentativa de conversão para f64 (double)
                    let celsius: f64 = match temp.trim().parse() {
                        Ok(num) => {
                            // Se conversão foi bem-sucedida
                            println!("Ok! calculando..");
                            thread::sleep(Duration::from_millis(300)); // 300 milissegundos

                            // Chama a função de conversão
                            let result = celsius_para_fahrenheit(num);
                            let result = result.round();

                            // Imprime resultado formatado
                            // {} são placeholders (como %f no printf)
                            println!("{}°C = {}°F", num, result);

                            num // Retorna o número válido
                        }
                        Err(_) => {
                            // Se conversão falhou
                            println!("Entrada inválida do usuário.");
                            thread::sleep(Duration::from_secs(1));
                            println!("Digite novamente: ");
                            continue; // Continua o loop interno
                        }
                    };

                    // Se chegou aqui, conversão foi bem-sucedida
                    break; // Sai do loop interno (como break; dentro do case)
                }
            } // Fim do case 1

            2 => {
                // case 2: em C
                loop {
                    println!("Digite a temperatura em graus Fahrenheit para fazer a conversão:");

                    let mut temp = String::new();
                    io::stdin()
                        .read_line(&mut temp)
                        .expect("Falha ao obter input do usuário!");

                    let fahrenheit: f64 = match temp.trim().parse() {
                        Ok(num) => {
                            println!("Ok! Calculando...");
                            thread::sleep(Duration::from_millis(300));

                            // Chama função de conversão contrária
                            let result = fahrenheit_para_celsius(num);
                            let result = result.round();

                            // Note a ordem correta das unidades na saída
                            println!("{}°F = {}°C", num, result);

                            num
                        }
                        Err(_) => {
                            println!("Entrada inválida do usuário.");
                            thread::sleep(Duration::from_secs(1));
                            println!("Digite novamente: ");
                            continue;
                        }
                    };
                    break;
                }
            } // Fim do case 2

            3 => {
                // case 3: em C
                println!("Saindo do programa...");
                thread::sleep(Duration::from_secs(1));
                // Em C seria: exit(0);
                process::exit(0); // Termina o programa com código 0 (sucesso)
            }

            _ => {
                // default: em C
                // _ é um "wildcard" que captura qualquer valor não especificado acima
                println!("Opção inválida! Escolha entre 1, 2 ou 3.");
                thread::sleep(Duration::from_secs(1));
                // Não precisa de break aqui - match automaticamente sai após executar um braço
            }
        } // Fim do match (equivalente ao } do switch)
    } // Fim do loop principal
} // Fim da main

/*
PRINCIPAIS DIFERENÇAS ENTRE RUST E C:

1. GERENCIAMENTO DE MEMÓRIA:
   - C: malloc/free manual, possibilidade de vazamentos e erros
   - Rust: Ownership system - gerenciamento automático e seguro

2. TRATAMENTO DE ERROS:
   - C: Códigos de retorno, fácil esquecer de verificar
   - Rust: Result<T, E> força você a tratar erros

3. STRINGS:
   - C: Arrays de char, gerenciamento manual
   - Rust: String type com gerenciamento automático

4. PATTERN MATCHING:
   - C: switch limitado a inteiros/chars
   - Rust: match funciona com qualquer tipo, é exhaustivo

5. SAfETY:
   - C: Possível ter buffer overflows, null pointers, etc.
   - Rust: Compiler impede a maioria dos erros de memória

6. EXPRESSÕES:
   - C: Declarações vs expressões bem separadas
   - Rust: Quase tudo é expressão (pode retornar valores)
*/
