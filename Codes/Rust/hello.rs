// hello rust!

fn main() {
    // em rust, a função funciona de forma parecida em C, sendo a função que o compilador executa primeiro, nao sendo
    // muito diferente na pratica, no livro, é explicado que a linha fn main, declara a
    // função main, que nao tem parametros { () está vazio } e ela não retorna nada e o
    // corpo da função é definido pelo que está escrito ao redor das chaves { codigo },
    // funcionando igual C na prática, onde as funções, não só a main, tbm são definidas
    // com {}
    // é possível usar {} para fazer o sombreamento de variáveis imutáveis, útil mudar valores
    // de variáveis imutáveis, mantendo a segurança geral do código e separando as areas onde
    // quero que a variavel assuma valores diferente, deixando o código mais organizado

    println!("Hello World!");
    //aqui, a mágica é que println! técnicamente cumpre a mesma função de printf em c
    //, só que ela é
    //definida como um macro de Rust, e se fosse ser chamada como uma
    //função (código), teria sido definida sem o ! no final, e que eu
    //deveria fixar que macros não funcionam da mesma forma que uma
    //função as vezes ( interessante notar isso), aqui também assim como
    //C e outras linguagens, strings (vetores de caracteres) também são
    //definidas com "conteudodastring".
    //
    //; serve para finalizar linhas de código, e mandar o compilador
    //seguir para a próxima linha
}

/* o livro também fala que a linguagem Rust, que no Gentoo Linux defini para ser inclusa no pacote
 * instalado do sistema, possui uma ferramenta que se chama rustfmt, que formata meu código no
 * modelo padrão da linguagem, mais sobre essa ferramenta está no apêndice D do livro The Rust
 * Programming Language, e estou interessado em saber mais sobre isso */
