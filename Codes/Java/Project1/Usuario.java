package Project1;

import java.security.SecureRandom;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Objects;

/**
 * Representa um usuário no sistema da biblioteca.
 * <p>
 * A classe encapsula dados imutáveis do usuário ({@code id}, {@code nome}, {@code email}),
 * um inventário privado de livros ({@code inv}) e um {@link Estado status} mutável.
 * Métodos que alteram estado/inventário são sincronizados para fornecer proteção básica
 * contra acesso concorrente.
 * </p>
 *
 * <p><b>Responsabilidades:</b></p>
 * <ul>
 *   <li>Gerar identificador único do usuário;</li>
 *   <li>Fornecer getters seguros para atributos;</li>
 *   <li>Gerenciar empréstimos/devoluções respeitando limite {@code BORROW_LIMIT};</li>
 *   <li>Expor inventário somente por views imutáveis.</li>
 * </ul>
 *
 * @author neo-dev
 * @version 0.02
 */
public class Usuario {

    /**
     * Gerador criptograficamente seguro usado para criação de IDs.
     * <p>
     * Uso interno apenas — garante entropia superior ao {@link java.util.Random}.
     * </p>
     */
    private static final SecureRandom RG = new SecureRandom();

    /**
     * Limite máximo de empréstimos simultâneos por usuário.
     * <p>
     * Valor usado para validar operações de empréstimo.
     * </p>
     */
    private static final int BORROW_LIMIT = 5;

    /**
     * Gera um identificador único positivo para um usuário.
     * <p>
     * A máscara com {@code Long.MAX_VALUE} garante que o valor retornado seja não-negativo.
     * </p>
     *
     * @return identificador pseudo-aleatório não-negativo
     */
    private static Long gerarId() {
        return Long.valueOf(RG.nextLong() & Long.MAX_VALUE);
    }

    /**
     * Enum que descreve o estado de um {@code Usuario}.
     * <p>
     * Cada valor possui um código inteiro e um rótulo legível.
     * A enum provê o método {@link #fromCode(int)} para conversão a partir de inteiro.
     * </p>
     */
    public enum Estado {
        /**
         * Usuário ativo / online.
         */
        ONLINE(0, "Online"),
        /**
         * Usuário inativo.
         */
        INATIVO(1, "Inativo"),
        /**
         * Usuário offline.
         */
        OFFLINE(2, "Offline");

        /**
         * Código inteiro associado ao estado (útil para persistência).
         */
        private final int code;

        /**
         * Rótulo legível do estado (útil para exibição).
         */
        private final String label;

        /**
         * Construtor da enumeração.
         *
         * @param code  código inteiro do estado
         * @param label rótulo legível do estado
         */
        Estado(int code, String label) {
            this.code = code;
            this.label = label;
        }

        /**
         * Retorna o código inteiro deste estado.
         *
         * @return código inteiro do estado
         */
        public int getCode() {
            return code;
        }

        /**
         * Retorna o rótulo legível deste estado.
         *
         * @return rótulo legível do estado
         */
        public String getLabel() {
            return label;
        }

        /**
         * Converte um código inteiro em um {@link Estado}.
         *
         * @param code código inteiro a ser convertido
         * @return {@code Estado} correspondente ao código
         * @throws IllegalArgumentException se o código não corresponder a nenhum estado conhecido
         */
        public static Estado fromCode(int code) {
            for (Estado e : Estado.values()) {
                if (e.code == code) return e;
            }
            throw new IllegalArgumentException(
                "Código de estado inválido: " + code
            );
        }

        /**
         * Representação textual do estado (rótulo).
         *
         * @return rótulo legível do estado
         */
        @Override
        public String toString() {
            return label;
        }
    }

    /* ============================
     * Atributos de instância
     * ============================ */

    /**
     * Identificador único e imutável do usuário.
     * <p>
     * Gerado internamente via {@link #gerarId()} no momento da construção.
     * </p>
     */
    private final Long id;

    /**
     * Nome do usuário (não nulo).
     */
    private final String nome;

    /**
     * Email do usuário (não nulo).
     */
    private final String email;

    /**
     * Inventário de livros do usuário.
     * <p>
     * Internamente é um {@link ArrayList}. A exposição externa é feita via view imutável
     * ({@link Collections#unmodifiableList(List)}).
     * </p>
     */
    private final List<Livro> inv;

    /**
     * Estado atual do usuário (mutável).
     * <p>
     * Métodos que leem/escrevem este campo são sincronizados para fornecer visibilidade
     * e exclusão mútua em cenários concorrentes simples.
     * </p>
     */
    private Estado status;

    /* ============================
     * Construtor
     * ============================ */

    /**
     * Construtor principal da classe {@code Usuario}.
     *
     * @param nome       nome do usuário (não pode ser {@code null})
     * @param email      email do usuário (não pode ser {@code null})
     * @param estadoCode código inteiro inicial do estado; se {@code null} assume {@link Estado#ONLINE}
     * @throws NullPointerException     se {@code nome} ou {@code email} for {@code null}
     * @throws IllegalArgumentException se {@code estadoCode} não for {@code null} e não corresponder a um estado válido
     */
    public Usuario(String nome, String email, Integer estadoCode) {
        this.id = gerarId();
        this.nome = Objects.requireNonNull(nome, "nome não pode ser null");
        this.email = Objects.requireNonNull(email, "email não pode ser null");
        this.inv = new ArrayList<>();
        this.status = (estadoCode == null)
            ? Estado.ONLINE
            : Estado.fromCode(estadoCode);
    }

    /* ============================
     * Getters públicos
     * ============================ */

    /**
     * Retorna o identificador único deste usuário.
     *
     * @return id do usuário (não nulo)
     */
    public Long getId() {
        return id;
    }

    /**
     * Retorna o nome deste usuário.
     *
     * @return nome do usuário (não nulo)
     */
    public String getNome() {
        return nome;
    }

    /**
     * Retorna o email deste usuário.
     *
     * @return email do usuário (não nulo)
     */
    public String getEmail() {
        return email;
    }

    /**
     * Retorna uma view imutável do inventário do usuário.
     * <p>
     * A lista retornada não permite operações mutáveis (lançará {@link UnsupportedOperationException}
     * caso se tente {@code add/remove}). Para modificar o inventário, utilize os métodos
     * {@link #adicionarLivro(Livro)} e {@link #devolverLivro(Livro)}.
     * </p>
     *
     * @return lista imutável com os livros emprestados a este usuário
     */
    public List<Livro> getInv() {
        return Collections.unmodifiableList(inv);
    }

    /**
     * Retorna o estado atual do usuário.
     * <p>
     * Método sincronizado para garantir visibilidade entre threads que sincronizam no mesmo monitor.
     * </p>
     *
     * @return estado atual do usuário (não nulo)
     */
    public synchronized Estado getEstado() {
        return status;
    }

    /**
     * Define o estado do usuário a partir de um código inteiro.
     * <p>
     * Usar quando for necessário reconstruir estado a partir de persistência externa.
     * Método sincronizado para consistência em cenário concorrente.
     * </p>
     *
     * @param code código inteiro do estado
     * @throws IllegalArgumentException se {@code code} não corresponder a um estado válido
     */
    public synchronized void setEstadoFromCode(int code) {
        this.status = Estado.fromCode(code);
    }

    /* ============================
     * Operações sobre inventário (domínio)
     * ============================ */

    /**
     * Tenta adicionar (emprestar) um livro ao inventário do usuário.
     * <p>
     * Regras aplicadas:
     * <ol>
     *   <li>Valida que {@code livro} não é {@code null}.</li>
     *   <li>Verifica se o usuário ainda não atingiu {@code BORROW_LIMIT}.</li>
     *   <li>Tenta emprestar o livro via {@link Livro#emprestar()}; apenas se este método
     *       retornar {@code true} o livro é adicionado ao inventário.</li>
     * </ol>
     * O método é sincronizado para prover exclusão mútua ao modificar {@code inv}.
     * </p>
     *
     * @param livro livro a ser emprestado ao usuário
     * @return {@code true} se o empréstimo foi realizado e o livro adicionado; {@code false} caso contrário
     * @throws NullPointerException se {@code livro} for {@code null}
     */
    public synchronized boolean adicionarLivro(Livro livro) {
        Objects.requireNonNull(livro, "livro não pode ser null");
        if (inv.size() >= BORROW_LIMIT) {
            return false; // atingiu limite
        }
        if (!livro.emprestar()) {
            return false; // livro não disponível
        }
        inv.add(livro);
        return true;
    }

    /**
     * Devolve um livro do inventário do usuário.
     * <p>
     * Se o livro estiver presente no inventário, ele é removido e marcado como disponível
     * via {@link Livro#disponibilizar()}. Método sincronizado para modificar {@code inv}.
     * </p>
     *
     * @param livro livro a ser devolvido
     * @return {@code true} se a devolução ocorreu (livro estava no inventário); {@code false} caso contrário
     * @throws NullPointerException se {@code livro} for {@code null}
     */
    public synchronized boolean devolverLivro(Livro livro) {
        Objects.requireNonNull(livro, "livro não pode ser null");
        boolean removed = inv.remove(livro);
        if (removed) {
            livro.disponibilizar();
        }
        return removed;
    }

    /**
     * Lista os livros atualmente emprestados por este usuário.
     * <p>
     * Retorna uma cópia imutável dos elementos para leitura segura em contexto concorrente.
     * </p>
     *
     * @return lista imutável com os livros do inventário
     */
    public synchronized List<Livro> listarLivros() {
        return Collections.unmodifiableList(new ArrayList<>(inv));
    }

    /* ============================
     * equals / hashCode
     * ============================ */

    /**
     * Dois usuários são considerados iguais se compartilharem o mesmo {@code id}.
     *
     * @param o outro objeto a comparar
     * @return {@code true} se os objetos representam o mesmo usuário (id igual)
     */
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Usuario)) return false;
        Usuario other = (Usuario) o;
        return Objects.equals(this.id, other.id);
    }

    /**
     * Hash code baseado no {@code id} do usuário.
     *
     * @return hash code do usuário
     */
    @Override
    public int hashCode() {
        return Objects.hashCode(this.id);
    }
}
