function main() {
  const message = "Hello World!";
  try {
    console.log(message);
    return 0;
  } catch (err) {
    console.err("Aconteceu o erro " + err);
    return 1;
  }
}

const ExitCode = main();
process.exit(ExitCode);
