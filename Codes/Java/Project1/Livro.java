package Project1;

import java.security.SecureRandom;
import java.util.*;

/**
 * Representa um livro cadastrado no sistema da biblioteca.
 * <p>
 * Cada livro possui um identificador único, nome, autor, tipo e um estado
 * que define sua disponibilidade no sistema. Os objetos desta classe são
 * imutáveis em relação aos atributos básicos (id, nome, autor e tipo),
 * mas o estado pode ser alterado conforme o livro é emprestado,
 * reservado ou devolvido.
 * </p>
 *
 * <b>Autor:</b> neo-dev</p>
 * <p><b>Versão:</b> 0.01<br>
 */
public class Livro {

    // ============================================================
    // Utilitários de classe
    // ============================================================

    /**
     * Gerador de números aleatórios seguro utilizado para criação de IDs de livros.
     * <p>
     * {@link SecureRandom} é preferido em relação a {@link java.util.Random}
     * por fornecer entropia criptograficamente segura, garantindo que
     * os IDs sejam menos previsíveis.
     * </p>
     */
    private static final SecureRandom rg = new SecureRandom();

    /**
     * Gera um identificador único para um novo livro.
     *
     * @return um número positivo representando o ID do livro
     */
    private static Long gerarId() {
        Long a = rg.nextLong();
        Long b = rg.nextLong();
        return Math.abs(a ^ b); // XOR mistura bits, gerando maior aleatoriedade
    }

    // ============================================================
    // Enumerações
    // ============================================================

    /**
     * Enumeração que define os possíveis estados de um livro no sistema.
     * <ul>
     *     <li>{@link #DISPONIVEL} — o livro está livre para empréstimo ou reserva;</li>
     *     <li>{@link #EMPRESTADO} — o livro está atualmente emprestado a um usuário;</li>
     *     <li>{@link #RESERVADO} — o livro foi reservado e não pode ser emprestado;</li>
     *     <li>{@link #PERDIDO} — o livro foi declarado como perdido;</li>
     * </ul>
     */
    public enum Estado {
        DISPONIVEL,
        EMPRESTADO,
        RESERVADO,
        PERDIDO,
    }

    /**
     * Converte um Integer em um {@link Estado} correspondente.
     * <p>
     * Os códigos válidos são:
     * <ul>
     *     <li>0 — {@link Estado#DISPONIVEL}</li>
     *     <li>1 — {@link Estado#EMPRESTADO}</li>
     *     <li>2 — {@link Estado#RESERVADO}</li>
     *     <li>3 — {@link Estado#PERDIDO}</li>
     * </ul>
     * </p>
     * <p>
     * Este método é utilizado para inicializar ou alterar o estado de um livro
     * a partir de um valor numérico, facilitando integração com interfaces ou
     * sistemas externos que utilizem códigos inteiros.
     * </p>
     *
     * @param code Código inteiro representando o estado do livro.
     * @return O {@link Estado} correspondente ao código informado.
     * @throws IllegalArgumentException Se o código não estiver entre 0 e 3, indicando um valor inválido.
     */
    private static Estado estadoFromInt(Integer code) {
        if (code == null) {
            throw new IllegalArgumentException(
                "Código de estado não pode ser null."
            );
        }
        return switch (code) {
            case 0 -> Estado.DISPONIVEL;
            case 1 -> Estado.EMPRESTADO;
            case 2 -> Estado.RESERVADO;
            case 3 -> Estado.PERDIDO;
            default -> throw new IllegalArgumentException(
                "Código de estado inválido: " + code
            );
        };
    }

    // ============================================================
    // Atributos de instância
    // ============================================================

    /**
     * Identificador único do livro.
     */
    private final Long id;

    /**
     * Nome (título) do livro.
     */
    private final String nome;

    /**
     * Nome do autor do livro.
     */
    private final String autor;

    /**
     * Tipo ou categoria do livro (ex.: Romance, Técnico, Infantil etc.).
     */
    private final String type;

    /**
     * Estado atual do livro no sistema.
     */
    private Estado status;

    // ============================================================
    // Construtor
    // ============================================================

    /**
     * Construtor principal da classe {@code Livro}.
     * <p>
     * Permite criar um livro já definindo o estado inicial via código inteiro.
     * O código é mapeado para a enum {@link Estado} conforme:
     * <ul>
     *     <li>0 — DISPONIVEL</li>
     *     <li>1 — EMPRESTADO</li>
     *     <li>2 — RESERVADO</li>
     *     <li>3 — PERDIDO</li>
     * </ul>
     * </p>
     *
     * @param nome        título do livro (não pode ser {@code null})
     * @param autor       nome do autor do livro (não pode ser {@code null})
     * @param type        tipo ou categoria do livro (não pode ser {@code null})
     * @param estadoCode  código do estado inicial do livro
     * @throws NullPointerException      se qualquer parâmetro {@code nome}, {@code autor} ou {@code type} for {@code null}
     * @throws IllegalArgumentException  se {@code estadoCode} não estiver entre 0 e 3
     */
    public Livro(String nome, String autor, String type, Integer estadoCode) {
        this.id = gerarId();
        this.nome = Objects.requireNonNull(nome);
        this.autor = Objects.requireNonNull(autor);
        this.type = Objects.requireNonNull(type);
        this.status = estadoFromInt(estadoCode);
    }

    // ============================================================
    // Métodos herdados
    // ============================================================

    /**
     * Retorna uma representação textual dos atributos do livro.
     * <p>
     * O formato é legível por humanos e exibe todas as informações básicas,
     * incluindo o estado atual.
     * </p>
     *
     * @return uma {@link String} com os principais atributos do livro
     */
    @Override
    public String toString() {
        return """
        Livro #%d
        Nome: %s
        Autor: %s
        Tipo: %s
        Estado: %s
        """.formatted(this.id, this.nome, this.autor, this.type, this.status);
    }

    // ============================================================
    // Getters
    // ============================================================

    /**
     * Retorna o identificador único do livro.
     *
     * @return o ID do livro
     */
    public Long getId() {
        return this.id;
    }

    /**
     * Retorna o nome (título) do livro.
     *
     * @return o nome do livro
     */
    public String getNome() {
        return this.nome;
    }

    /**
     * Retorna o autor do livro.
     *
     * @return o autor do livro
     */
    public String getAutor() {
        return this.autor;
    }

    /**
     * Retorna o tipo ou categoria do livro.
     *
     * @return o tipo do livro
     */
    public String getTipo() {
        return this.type;
    }

    /**
     * Retorna o estado atual do livro.
     *
     * @return o estado do livro no sistema
     */
    public Estado getStatus() {
        return this.status;
    }

    /**
     * Métodos responsáveis por alterar o estado de um item no sistema de biblioteca.
     * Cada método realiza uma verificação antes de atualizar o estado,
     * garantindo a consistência lógica do ciclo de vida do item.
     */

    /**
     * Tenta emprestar o item.
     * <p>Um item só pode ser emprestado se estiver disponível.</p>
     *
     * @return {@code true} se o empréstimo for bem-sucedido;
     *         {@code false} caso o item não esteja disponível.
     */
    public boolean emprestar() {
        if (this.status != Estado.DISPONIVEL) {
            return false;
        }
        this.status = Estado.EMPRESTADO;
        return true;
    }

    /**
     * Marca o item como perdido.
     * <p>Um item não pode ser marcado como perdido se já estiver reservado ou perdido.</p>
     *
     * @return {@code true} se a operação for bem-sucedida;
     *         {@code false} caso contrário.
     */
    public boolean perder() {
        if (this.status == Estado.RESERVADO || this.status == Estado.PERDIDO) {
            return false;
        }
        this.status = Estado.PERDIDO;
        return true;
    }

    /**
     * Reserva o item.
     * <p>Um item só pode ser reservado se estiver disponível.</p>
     *
     * @return {@code true} se a reserva for bem-sucedida;
     *         {@code false} caso o item não esteja disponível.
     */
    public boolean reservar() {
        if (this.status != Estado.DISPONIVEL) {
            return false;
        }
        this.status = Estado.RESERVADO;
        return true;
    }

    /**
     * Disponibiliza novamente o item.
     * <p>Um item não pode ser disponibilizado se já estiver disponível.</p>
     *
     * @return {@code true} se a operação for bem-sucedida;
     *         {@code false} caso o item já esteja disponível.
     */
    public boolean disponibilizar() {
        if (this.status == Estado.DISPONIVEL) {
            return false;
        }
        this.status = Estado.DISPONIVEL;
        return true;
    }
}
