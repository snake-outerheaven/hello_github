use std::fs::OpenOptions;
use std::io::{self, Write};
use std::process::{Command, exit};
use std::thread::sleep;
use std::time::Duration;

// O objetivo deste código é escrever um simples conversor de temperaturas que faz registros de suas operações em
// um arquivo de texto.
