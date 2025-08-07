import java.io.*; // importa classes de leitura e escrita de arquivos
import java.util.Random; // utilidade de geração de números pseudoaleatórios
import java.util.Scanner; // classe que para escanear entrada do teclado


public class GuessingGame {

    // Objeto que representa o meu conversor de temperatura



    static Scanner scanner = new Scanner(System.in); // crio objeto scanner global para todos os métodos do programa

    // keyword static indica que o método funciona como uma função, ainda não toquei no OOP propriamente dito, mas apenas esotu
    // me acostumando com a sintaxe da linguagem.
    
    public static void limpartela () {

        // método simples que tenta conter o componente de limpar tela do programa.

        // Parte mais importante deste método, tratamento de exceções ( erros )
        
        try {
            System.out.println("Limpando tela..."); // Imprimindo no terminal
            Thread.sleep(750); // Método para fazer o processo do programa dormir, número em milisegundos

            if (System.getProperty("os.name").toLowerCase().contains("windows")) {

                new ProcessBuilder("cmd","/c","cls").inheritIO().start().waitFor(); 
                // construtor de Processos, que herda o stdin e stdout do programa, inicia, e espera até o processo iniciado
                // seja encerrado

            } else {

                new ProcessBuilder("clear").inheritIO().start().waitFor();

            }

        }

        //tenta isso, se não, roda o abaixo
        //
        // a linha abaixo significa de forma literal, que ele vai pegar alguma exceção no programa

        catch (Exception e) {

            System.out.println("Não foi possível limpar tela.");

        }

    } // fim do método aqui


    // sabendo que os métodos sempre retornam alguma coisa (tipo void é válido aqui), vamos obter o nome do usuário

    public static String obter_nome() {

        // tratamento de erros para checar se o processo consegue dormir

        try {

            Thread.sleep(750);

        }

        catch (Exception e) {

            System.out.println("Não foi possível gerar pausa visual para UX");
        }

        // loop principal, bem tranquilo

        while(true) {

            System.out.println("Este programa necessita de seu nome de usuário, por favor, digite-o abaixo.");

            String nome = scanner.nextLine().trim();
            // a variável nome é inicializada ao se fazer necessária, o que deixa o código meio diferente do estilo C, mesmo Java sendo descendente
            // desta família de linguagens.

            // a forma de representar strings formatadas em stdout é quase a mesma coisa de C

            System.out.printf("O nome %s está correto? (S/N)\n", nome);

            String resposta = scanner.nextLine().trim().toUpperCase();

            switch (resposta) {

                case "S":
                    System.out.printf("Certo, bem vindo ao programa %s!", nome);
                    return nome;

                case "N":

                    System.out.printf("Certo, entendi que %s não é o seu nome, repetindo o código...\n", nome);            

                    try {
                        Thread.sleep(750);
                    }
                    catch (Exception e) {
                        System.out.println("Não foi possível gera pausa visual para UX");
                    }
                    limpartela();

                    break;

                default:

                    System.out.println("Reiniciando a função por motivos de segurança...");

                    limpartela();

                    break;
            
            }

        }

    }

    // método que obtém o palpite
    public static int obter_palpite (String usuario) {
        while (true) {
            try {
                Thread.sleep(750);
            } catch ( Exception e) {
                System.out.println("Não foi possível pausar o processo.");
            }
            System.out.printf("\nCerto %s, por favor, digite um número de 1 a 100 para o jogo:\n", usuario);
            String buffer = scanner.nextLine().trim();

            // este é o melhor método de leitura de números, obter strings e fazer parsing para o tipo de entrada

            try {
                int palpite = Integer.parseInt(buffer);
                if (palpite >= 1 && palpite <= 100) {
                    System.out.printf("Certo, valor %d é válido e será utilizado pelo jogo.\n", palpite);
                    return palpite;
                } else {
                    System.out.printf("%s, %s não está no intervalo correto, digite novamente.\n", usuario, buffer);
                } 
            } catch (Exception e) {
                System.err.printf("%s, %s não é uma entrada válida para o jogo", usuario, buffer);
            }
        }
    }

    // método de confirmação 
    
    // método principal ( em OOP puro, eu criaria uma classe separada onde os objetos são criados e começam a interagir entre si )
    public static void main(String[] args){
        limpartela();
        String user = obter_nome();
        int palpite = obter_palpite(user);
        System.out.println("DEBUG Nome de usuário é: " + user); // para debug, função funciona corretamente
        System.out.println("DEBUG Número digitado é: " + palpite);
    }
} // fim da classe
