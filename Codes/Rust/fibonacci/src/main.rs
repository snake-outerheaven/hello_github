use std::fs::{self, OpenOptions};
use std::io::{self, Read, Seek, Write};
use std::path::Path;
use std::process::{Command, exit};
use std::thread::sleep;
use std::time::Duration;

// este código será menor, o objetivo dele é escrever um simples gerador de números fibonnaci, mas
// tentando manter o código no estilo Unix, cada função vai fazer uma unica tarefa, para deixar
// o código mais fácil de manter
//
// Então teremos: uma função de limpar tela, uma função que devolve um número parseado de string para f64,
// uma função de validação de dados, e claro, uma função que implementa a criação automática do diretório
// log, na raíz deste projeto, provavelmente é mais fácil criar módulos para deixar este aqui mais limpo.
