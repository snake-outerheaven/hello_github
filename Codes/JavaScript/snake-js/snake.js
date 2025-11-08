// Configurações
const width = 20;
const height = 20;
let snake = [{ x: 5, y: 5 }];
let direction = { x: 1, y: 0 };
let apple = { x: 10, y: 5 };
let gameOver = false;

function draw() {
  console.clear();
  for (let y = 0; y < height; y++) {
    let row = "";
    for (let x = 0; x < width; x++) {
      if (snake.some((s) => s.x === x && s.y === y)) {
        row += "#";
      } else if (apple.x === x && apple.y === y) {
        row += "O";
      } else {
        row += "*";
      }
    }
    console.log(row);
  }
}

function update() {
  const head = { x: snake[0].x + direction.x, y: snake[0].y + direction.y };

  // Checar colisão com parede
  if (head.x < 0 || head.x >= width || head.y < 0 || head.y >= height) {
    gameOver = true;
    return;
  }

  if (snake.some((s) => s.x === head.x && s.y === head.y)) {
    gameOver = true;
    return;
  }

  snake.unshift(head);

  if (head.x === apple.x && head.y === apple.y) {
    apple = {
      x: Math.floor(Math.random() * width),
      y: Math.floor(Math.random() * height),
    };
  } else {
    snake.pop(); // remove a cauda
  }
}
const readline = require("readline");
readline.emitKeypressEvents(process.stdin);
process.stdin.setRawMode(true);
process.stdin.on("keypress", (str, key) => {
  if (key.ctrl && key.name === "c") process.exit();
  switch (key.name) {
    case "up":
      direction = { x: 0, y: -1 };
      break;
    case "down":
      direction = { x: 0, y: 1 };
      break;
    case "left":
      direction = { x: -1, y: 0 };
      break;
    case "right":
      direction = { x: 1, y: 0 };
      break;
  }
});

// Loop do jogo
function gameLoop() {
  if (gameOver) {
    console.clear();
    console.log("Game Over! Pontuação:", snake.length - 1);
    process.exit();
  }
  update();
  draw();
}

setInterval(gameLoop, 200); // atualiza a cada 200ms
