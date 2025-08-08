import java.io.*; // importa classes de leitura e escrita de arquivos
import java.util.Random; // utilidade de geração de números pseudoaleatórios
import java.util.Scanner; // classe que para escanear entrada do teclado

public class GuessingGame {

  // Objeto que representa o meu conversor de temperatura

  static Scanner scanner = new Scanner(System.in); // crio objeto scanner global para todos os métodos do programa

  // keyword static indica que o método funciona como uma função, ainda não toquei
  // no OOP propriamente dito, mas apenas esotu
  // me acostumando com a sintaxe da linguagem.

  public static void limpartela() {

    // método simples que tenta conter o componente de limpar tela do programa.

    // Parte mais importante deste método, tratamento de exceções ( erros )

    try {
      System.out.println("Limpando tela..."); // Imprimindo no terminal
      Thread.sleep(750); // Método para fazer o processo do programa dormir, número em milisegundos

      if (System.getProperty("os.name").toLowerCase().contains("windows")) {

        new ProcessBuilder("cmd", "/c", "cls").inheritIO().start().waitFor();
        // construtor de Processos, que herda o stdin e stdout do programa, inicia, e
        // espera até o processo iniciado
        // seja encerrado

      } else {

        new ProcessBuilder("clear").inheritIO().start().waitFor();

      }

    }

    // tenta isso, se não, roda o abaixo
    //
    // a linha abaixo significa de forma literal, que ele vai pegar alguma exceção
    // no programa

    catch (Exception e) {

      System.out.println("Não foi possível limpar tela.");

    }

  } // fim do método aqui

  // sabendo que os métodos sempre retornam alguma coisa (tipo void é válido
  // aqui), vamos obter o nome do usuário

  public static String obter_nome() {

    // tratamento de erros para checar se o processo consegue dormir

    try {

      Thread.sleep(750);

    }

    catch (Exception e) {

      System.out.println("Não foi possível gerar pausa visual para UX");
    }

    // loop principal, bem tranquilo

    while (true) {

      System.out.println("Este programa necessita de seu nome de usuário, por favor, digite-o abaixo.");

      System.out.printf("\n: ");

      String nome = scanner.nextLine().trim();
      // a variável nome é inicializada ao se fazer necessária, o que deixa o código
      // meio diferente do estilo C, mesmo Java sendo descendente
      // desta família de linguagens.

      // a forma de representar strings formatadas em stdout é quase a mesma coisa de
      // C

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
          } catch (Exception e) {
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
  public static int obter_palpite(String usuario) {
    while (true) {
      try {
        Thread.sleep(750);
      } catch (Exception e) {
        System.out.println("Não foi possível pausar o processo.");
      }
      System.out.printf("\nCerto %s, por favor, digite um número de 1 a 100 para o jogo:\n", usuario);
      String buffer = scanner.nextLine().trim();

      // este é o melhor método de leitura de números, obter strings e fazer parsing
      // para o tipo de entrada

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

  public static boolean verif(String user, int palpite) {
    try {
      Thread.sleep(750);
    } catch (Exception e) {
      System.out.println("Não foi possível pausar este trecho do programa para melhor UX.");
    }
    while (true) {
      System.out.println(user + ", " + palpite + " não está correto. você deseja continuar com o jogo?");
      System.out.printf("\nDigite S ou N.\n\n: ");
      String resposta = scanner.nextLine().trim().toUpperCase();
      switch (resposta) {
        case "S":
          System.out.println("Certo! Reiniciando jogo.");
          return true;

        case "N":
          System.out.println("Ok! Encerrando jogo.");
          return false;

        default:
          System.out.println("Por favor, digite S ou N.");
          limpartela();
          break;
      }
    }
  }

  // método do jogo, que retorna o valor criado

  public static int[] Jogar(String user) {
    try {
      Thread.sleep(750);
    } catch (Exception e) {
      System.out.println("Não foi possível pausar o tempo para melhor experiência do usuário.");
    }
    Random rand = new Random(); // construindo gerador de números pseudoaleatórios.
    int numero_secreto = rand.nextInt(100) + 1; // usando o gerador de números aleatórios
    int tentativa = 0;

    while (true) {
      tentativa++;
      int palpite = obter_palpite(user);
      if (palpite != numero_secreto) {
        if (palpite < numero_secreto) {
          System.out.println(palpite + " é menor que o número secreto!");
        } else {
          System.out.println(palpite + " é maior que o número secreto!");
        }
        boolean verif = verif(user, palpite);
        if (verif) {
          System.out.println("Certo, vamos continuar o jogo");
          continue;
        } else {
          System.out.println("Certo, obrigado por jogar o jogo!");
          System.exit(0);
        }
      } else {
        System.out.println("Parabéns " + user + " você descobriu o número secreto com " + tentativa + " tentativas.");
        try {
          System.out.println("Retornando...");
          Thread.sleep(750);
        } catch (Exception e) {
          System.out.println("Não foi possível pausar o tempo para uma boa experiência do usuário.");
        }
        return new int[] { numero_secreto, tentativa };
      }
    }
  }

  // método que executa salvamento de dados.
  public static void salvarLog(String user, int numSec, int tents) {

    File logDir = new File("GuessingGame_logdir");
    if (!logDir.exists()) {
      logDir.mkdir();
    }

    File logFile = new File(logDir, "game_log.txt");

    try (FileWriter fw = new FileWriter(logFile, true);
        BufferedWriter bw = new BufferedWriter(fw)) {
      String log = String.format("Nome do jogador: %s | Número secreto: %d | Tentativas: %d", user, numSec, tents);
      bw.write(log); // escrita de arquivos
      bw.newLine();
      System.out.println("Log criado com sucesso!");
    } catch (Exception e) {
      e.printStackTrace();
    }

    System.out.println("Abaixo vem o histório de partidas:");

    try (BufferedReader br = new BufferedReader(new FileReader(logFile))) {
      String linha;
      while ((linha = br.readLine()) != null) {
        System.out.println(linha);
      }
    } catch (Exception e) {
      System.out.println("Erro ao ler o arquivo.");
    }

  }

  // método principal ( em OOP puro, eu criaria uma classe separada onde os
  // objetos são criados e começam a interagir entre si )
  public static void main(String[] args) {
    limpartela();
    System.out.println("Bem vindo ao jogo da adivinhação! Espero que se divirta muito!");
    String user = obter_nome();
    int[] resultado = Jogar(user);
    salvarLog(user, resultado[0], resultado[1]);
    System.out.println("Obrigado por jogar!");
  }
} // fim da classe
