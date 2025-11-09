package Project1;

import java.security.SecureRandom;
import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

public class Usuario {

    private static final SecureRandom rg = new SecureRandom();

    private static Long gerarId() {
        Long a = rg.nextLong();
        Long b = rg.nextLong();
        return Math.abs(a ^ b);
    }

    public enum Estado {
        ONLINE,
        INATIVO,
        OFFLINE,
    }

    private static Estado estadoFromInt(Integer code) {
        if (code == null) {
            throw new IllegalArgumentException(
                "Código de estado não pode ser null,"
            );
        }
        return switch (code) {
            case 0 -> Estado.ONLINE;
            case 1 -> Estado.INATIVO;
            case 2 -> Estado.OFFLINE;
            default -> throw new IllegalArgumentException(
                "Código de estado inválido: " + code
            );
        };
    }

    private static final Integer borrowLimit = 5;
    private final Long id;
    private final String nome;
    private final String email;
    private final List<Livro> inv;
    private Estado status;

    public Usuario(String nome, String email, Integer num) {
        this.id = gerarId();
        this.nome = Objects.requireNonNull(nome);
        this.email = Objects.requireNonNull(email);
        this.inv = new ArrayList<Livro>();
        this.status = estadoFromInt(num);
    }
}
