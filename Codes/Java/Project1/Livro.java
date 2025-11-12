package Project1;

import java.security.SecureRandom;
import java.util.Objects;

/**
 * Representa um item do catálogo (livro) em um sistema de gestão.
 * <p>
 * Cada instância contém metadados imutáveis (id, nome, autor, tipo) e um
 * estado mutável {@link Estado} que representa o ciclo de vida do item
 * (disponível, emprestado, reservado, perdido).
 * </p>
 *
 * <p>
 * Contratos principais:
 * <ul>
 *   <li>Os campos {@code nome}, {@code autor} e {@code tipo} não podem ser {@code null}.</li>
 *   <li>O identificador {@code id} é gerado internamente e é imutável.</li>
 *   <li>Operações que alteram o estado do livro são atômicas em relação à
 *       própria instância (métodos sincronizados) para ajudar a evitar condições
 *       de corrida em cenários simples de concorrência.</li>
 * </ul>
 * </p>
 *
 * <p><b>Uso típico:</b>
 * criar instâncias via construtor, consultar atributos via getters e manipular
 * estado chamando os métodos {@link #emprestar()}, {@link #reservar()},
 * {@link #perder()} e {@link #disponibilizar()}.</p>
 *
 * @author neo-dev
 * @version 0.02
 * @since 1.0
 */
public class Livro {

    /* ============================================================
     * Utilitários de classe
     * ============================================================ */

    /**
     * Gerador de números aleatórios criptograficamente seguro para criação de IDs.
     * <p>
     * Usar {@link SecureRandom} garante maior entropia que {@link java.util.Random}.
     * </p>
     */
    private static final SecureRandom RG = new SecureRandom();

    /**
     * Gera um identificador único positivo para um livro.
     * <p>
     * A máscara com {@code Long.MAX_VALUE} garante que o valor retornado seja não-negativo
     * (evita problemas com {@code Math.abs(Long.MIN_VALUE)}).
     * </p>
     *
     * @return identificador positivo pseudo-aleatório
     */
    private static Long gerarId() {
        return RG.nextLong() & Long.MAX_VALUE;
    }

    /* ============================================================
     * Enumerações
     * ============================================================ */

    /**
     * Representa os estados possíveis de um {@code Livro} no sistema.
     * <p>
     * Cada enum possui um código inteiro fixo (útil para persistência/integração)
     * e um {@link #getLabel() label} legível.
     * </p>
     */
    public enum Estado {
        /**
         * Livro disponível para empréstimo ou reserva.
         */
        DISPONIVEL(0, "Disponível"),

        /**
         * Livro atualmente emprestado.
         */
        EMPRESTADO(1, "Emprestado"),

        /**
         * Livro reservado e não livre para empréstimo.
         */
        RESERVADO(2, "Reservado"),

        /**
         * Livro declarado perdido.
         */
        PERDIDO(3, "Perdido");

        private final Integer code;
        private final String label;

        Estado(Integer code, String label) {
            this.code = code;
            this.label = label;
        }

        /**
         * Retorna o código inteiro associado ao estado.
         *
         * @return código inteiro do estado
         */
        public Integer getCode() {
            return code;
        }

        /**
         * Rótulo legível do estado (para exibição em UI/relatórios).
         *
         * @return rótulo legível do estado
         */
        public String getLabel() {
            return label;
        }

        /**
         * Converte um código inteiro em {@link Estado}.
         *
         * @param code código inteiro
         * @return {@link Estado} correspondente
         * @throws IllegalArgumentException se o código não corresponder a nenhum estado
         */
        public static Estado fromCode(int code) {
            for (Estado e : Estado.values()) {
                if (e.code == code) return e;
            }
            throw new IllegalArgumentException(
                "Código de estado inválido: " + code
            );
        }

        @Override
        public String toString() {
            return label;
        }
    }

    /* ============================================================
     * Atributos de instância
     * ============================================================ */

    /**
     * Identificador único do livro (imóvel após construção).
     */
    private final Long id;

    /**
     * Título do livro (não nulo).
     */
    private final String nome;

    /**
     * Nome do autor (não nulo).
     */
    private final String autor;

    /**
     * Tipo ou categoria do livro (não nulo).
     */
    private final String tipo;

    /**
     * Estado atual do livro (mutável).
     * <p>
     * Métodos que alteram este campo são sincronizados para manter consistência
     * em operações concorrentes simples.
     * </p>
     */
    private Estado status;

    /* ============================================================
     * Construtores
     * ============================================================ */

    /**
     * Construtor principal.
     *
     * @param nome       título do livro; não pode ser {@code null}
     * @param autor      nome do autor; não pode ser {@code null}
     * @param tipo       tipo/categoria; não pode ser {@code null}
     * @param estadoCode código inicial do estado (inteiro); se {@code null}, assume {@link Estado#DISPONIVEL}
     * @throws NullPointerException     se {@code nome}, {@code autor} ou {@code tipo} for {@code null}
     * @throws IllegalArgumentException se {@code estadoCode} for inválido (quando não nulo)
     */
    public Livro(String nome, String autor, String tipo, Integer estadoCode) {
        this.id = gerarId();
        this.nome = Objects.requireNonNull(nome, "nome não pode ser null");
        this.autor = Objects.requireNonNull(autor, "autor não pode ser null");
        this.tipo = Objects.requireNonNull(tipo, "tipo não pode ser null");
        this.status = (estadoCode == null)
            ? Estado.DISPONIVEL
            : Estado.fromCode(estadoCode);
    }

    /**
     * Construtor de conveniência que cria um livro com estado padrão {@link Estado#DISPONIVEL}.
     *
     * @param nome  título do livro; não pode ser {@code null}
     * @param autor nome do autor; não pode ser {@code null}
     * @param tipo  tipo/categoria; não pode ser {@code null}
     * @throws NullPointerException se {@code nome}, {@code autor} ou {@code tipo} for {@code null}
     */
    public Livro(String nome, String autor, String tipo) {
        this(nome, autor, tipo, null);
    }

    /* ============================================================
     * Sobrescritas e utilitários
     * ============================================================ */

    /**
     * Retorna uma representação legível do livro.
     * <p>
     * Formato:
     * <pre>
     * Livro #id
     * Nome: ...
     * Autor: ...
     * Tipo: ...
     * Estado: ...
     * </pre>
     * </p>
     *
     * @return string com os principais atributos do livro
     */
    @Override
    public String toString() {
        return String.format(
            "Livro #%d%nNome: %s%nAutor: %s%nTipo: %s%nEstado: %s%n",
            this.id,
            this.nome,
            this.autor,
            this.tipo,
            this.status
        );
    }

    /**
     * Dois livros são considerados iguais se compartilharem o mesmo {@code id}.
     *
     * @param o outro objeto
     * @return {@code true} se o outro for um {@code Livro} com mesmo {@code id}
     */
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Livro)) return false;
        Livro other = (Livro) o;
        return Objects.equals(this.id, other.id);
    }

    /**
     * Hash code baseado no {@code id}.
     *
     * @return hash code do livro
     */
    @Override
    public int hashCode() {
        return Objects.hashCode(this.id);
    }

    /* ============================================================
     * Getters
     * ============================================================ */

    /**
     * Retorna o identificador único do livro.
     *
     * @return id (não nulo)
     */
    public Long getId() {
        return id;
    }

    /**
     * Retorna o título do livro.
     *
     * @return título (não nulo)
     */
    public String getNome() {
        return nome;
    }

    /**
     * Retorna o autor do livro.
     *
     * @return autor (não nulo)
     */
    public String getAutor() {
        return autor;
    }

    /**
     * Retorna o tipo/categoria do livro.
     *
     * @return tipo (não nulo)
     */
    public String getTipo() {
        return tipo;
    }

    /**
     * Retorna o estado atual do livro.
     *
     * @return estado atual (não nulo)
     */
    public synchronized Estado getStatus() {
        return status;
    }

    /* ============================================================
     * Operações de ciclo de vida (mutações de estado)
     * ============================================================ */

    /**
     * Tenta emprestar o livro.
     * <p>
     * Pré-condição: somente é possível emprestar se o estado atual for {@link Estado#DISPONIVEL}.
     * Pós-condição: se retornado {@code true}, o estado será alterado para {@link Estado#EMPRESTADO}.
     * </p>
     *
     * @return {@code true} se o empréstimo foi efetuado; {@code false} caso contrário
     */
    public synchronized boolean emprestar() {
        if (this.status != Estado.DISPONIVEL) {
            return false;
        }
        this.status = Estado.EMPRESTADO;
        return true;
    }

    /**
     * Marca o livro como perdido.
     * <p>
     * Não permite marcar como perdido se já estiver {@link Estado#RESERVADO} ou {@link Estado#PERDIDO}.
     * Se bem-sucedido, atualiza o estado para {@link Estado#PERDIDO}.
     * </p>
     *
     * @return {@code true} se a operação foi realizada; {@code false} caso contrário
     */
    public synchronized boolean perder() {
        if (this.status == Estado.RESERVADO || this.status == Estado.PERDIDO) {
            return false;
        }
        this.status = Estado.PERDIDO;
        return true;
    }

    /**
     * Reserva o livro.
     * <p>
     * Só é possível reservar quando o estado atual é {@link Estado#DISPONIVEL}.
     * Em caso de sucesso, altera o estado para {@link Estado#RESERVADO}.
     * </p>
     *
     * @return {@code true} se a reserva foi efetuada; {@code false} caso contrário
     */
    public synchronized boolean reservar() {
        if (this.status != Estado.DISPONIVEL) {
            return false;
        }
        this.status = Estado.RESERVADO;
        return true;
    }

    /**
     * Disponibiliza o livro novamente (ex.: devolução).
     * <p>
     * Não realiza ação se o livro já estiver {@link Estado#DISPONIVEL}.
     * Caso a transição ocorra, o novo estado será {@link Estado#DISPONIVEL}.
     * </p>
     *
     * @return {@code true} se o estado foi alterado; {@code false} se já estava disponível
     */
    public synchronized boolean disponibilizar() {
        if (this.status == Estado.DISPONIVEL) {
            return false;
        }
        this.status = Estado.DISPONIVEL;
        return true;
    }

    /**
     * Define o estado do livro a partir de um código inteiro.
     * <p>
     * Útil para desserialização de registros persistidos. Se o código for inválido,
     * será lançada {@link IllegalArgumentException}.
     * </p>
     *
     * @param code código inteiro do estado
     * @throws IllegalArgumentException se {@code code} não corresponder a um estado válido
     */
    public synchronized void setStatusFromCode(int code) {
        this.status = Estado.fromCode(code);
    }

    /* ============================================================
     * Notas de concorrência e integração
     * ============================================================ */

    /**
     * Observações sobre concorrência:
     * <ul>
     *   <li>Os métodos que alteram {@code status} são sincronizados para fornecer
     *       uma proteção básica contra condições de corrida quando múltiplas threads
     *       acessam a mesma instância.</li>
     *   <li>Em cenários de alta concorrência ou quando a integridade do sistema
     *       depende de transações complexas (por exemplo, atualizações em persistência,
     *       notificação de usuários, logs), recomenda-se orquestrar mudanças de estado
     *       em um nível superior (serviço/repositório) usando mecanismos transacionais
     *       ou locks adequados.</li>
     * </ul>
     *
     * Integração/persistência:
     * <ul>
     *   <li>Para persistência, recomenda-se armazenar o {@link #id} (chave primária)
     *       e o {@link Estado#getCode()} para reconstruir o objeto posteriormente.</li>
     *   <li>Ao expor dados via API, prefira transformar objetos {@code Livro} em
     *       DTOs imutáveis para evitar vazamento de referências mutáveis.</li>
     * </ul>
     */
}
