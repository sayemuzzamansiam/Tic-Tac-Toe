const X_CLASS = "x";
const O_CLASS = "o";
const WINNING_COMBINATIONS = [
  [0, 1, 2],
  [3, 4, 5],
  [6, 7, 8],
  [0, 3, 6],
  [1, 4, 7],
  [2, 5, 8],
  [0, 4, 8],
  [2, 4, 6],
];

const cellElements = document.querySelectorAll("[data-cell]");
const board = document.getElementById("board");
const playerElements = document.querySelectorAll(".player");
const score1Element = document.getElementById("score1");
const score2Element = document.getElementById("score2");
const restartButton = document.getElementById("restart");
const winMessage = document.getElementById("winMessage");
const drawMessage = document.getElementById("drawMessage");
const overlay = document.getElementById("overlay");
let xTurn = true;
let gameActive = true;
let scores = [0, 0];

startGame();

restartButton.addEventListener("click", startGame);

function startGame() {
  winMessage.style.display = "none";
  drawMessage.style.display = "none";
  overlay.style.display = "none";
  xTurn = true;
  gameActive = true;
  cellElements.forEach((cell) => {
    cell.classList.remove(X_CLASS, O_CLASS, "winning-cell");
    cell.textContent = "";
    cell.style.transform = "";
    cell.removeEventListener("click", handleClick);
    cell.addEventListener("click", handleClick);
  });
  updatePlayerStatus();
}

function handleClick(e) {
  const cell = e.target;
  if (
    !gameActive ||
    cell.classList.contains(X_CLASS) ||
    cell.classList.contains(O_CLASS)
  )
    return;

  const currentClass = xTurn ? X_CLASS : O_CLASS;
  placeMark(cell, currentClass);

  if (checkWin(currentClass)) {
    endGame(true);
    confetti({
      particleCount: 100,
      spread: 70,
      origin: { y: 0.6 },
      colors: ["#00ff00", "#00ffff", "#bc13fe"],
    });
  } else if (isDraw()) {
    endGame(false);
  } else {
    swapTurns();
    updatePlayerStatus();
  }
}

function placeMark(cell, currentClass) {
  cell.classList.add(currentClass);
  cell.textContent = currentClass.toUpperCase();
}

function swapTurns() {
  xTurn = !xTurn;
}

function updatePlayerStatus() {
  playerElements.forEach((player) => player.classList.remove("active"));
  const activePlayer = xTurn ? playerElements[0] : playerElements[1];
  activePlayer.classList.add("active");
}

function checkWin(currentClass) {
  return WINNING_COMBINATIONS.some((combination) => {
    return combination.every((index) => {
      return cellElements[index].classList.contains(currentClass);
    });
  });
}

function isDraw() {
  return [...cellElements].every((cell) => {
    return cell.classList.contains(X_CLASS) || cell.classList.contains(O_CLASS);
  });
}

function endGame(win) {
  gameActive = false;
  if (win) {
    const winner = xTurn ? 0 : 1;
    scores[winner]++;
    updateScores();
    highlightWinningCombination();
    winMessage.textContent = `PLAYER ${winner + 1} WON THE GAME!`;
    winMessage.style.display = "block";
    overlay.style.display = "block";
    setTimeout(() => {
      winMessage.style.display = "none";
      overlay.style.display = "none";
    }, 2000);
  } else {
    drawMessage.style.display = "block";
    overlay.style.display = "block";
    setTimeout(() => {
      drawMessage.style.display = "none";
      overlay.style.display = "none";
    }, 2000);
  }
}

function updateScores() {
  score1Element.textContent = scores[0];
  score2Element.textContent = scores[1];
}

function highlightWinningCombination() {
  WINNING_COMBINATIONS.forEach((combination) => {
    if (
      combination.every((index) =>
        cellElements[index].classList.contains(xTurn ? X_CLASS : O_CLASS)
      )
    ) {
      combination.forEach((index) => {
        cellElements[index].classList.add("winning-cell");
      });
    }
  });
}
