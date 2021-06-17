let canvas;
let ctx;
let CELL_SIZE = 8;
let MAX_COLUMN;
let MAX_ROW;
let currentCells = new Array();
let buttonStart;
let buttonRandom;
let buttonReset;
let timer;
let running = false;

window.onload = function () {
  canvas = document.getElementById('lifegame');
  ctx = canvas.getContext('2d', { alpha: false });
  MAX_COLUMN = Math.floor(canvas.width / CELL_SIZE);
  MAX_ROW = Math.floor(canvas.height / CELL_SIZE);
  initCells();
  buttonStart = document.getElementById('buttonStart');
  buttonRandom = document.getElementById('buttonRandom');
  buttonReset = document.getElementById('buttonReset');
  buttonStart.addEventListener('click', onStart, false);
  buttonRandom.addEventListener('click', randomCells, false);
  buttonReset.addEventListener('click', initCells, false);
  canvas.addEventListener('click', canvasClick, false);
};

function onStart() {
  if (running) {
    clearInterval(timer);
    buttonStart.value = "Start";
    running = false;
  } else {
    nextGeneration();
    timer = setInterval(nextGeneration, 100);
    buttonStart.value = "Stop";
    running = true;
  }
}

function initCells() {
  ctx.fillStyle = 'rgb(255, 255, 255)';
  ctx.fillRect(0, 0, canvas.width, canvas.height);
  for (let col = 0; col < MAX_COLUMN; col++) {
    currentCells[col] = new Array();
    for (let row = 0; row < MAX_ROW; row++) {
      currentCells[col][row] = 0;
    }
  }
  redraw();
}

function randomCells() {
  for (let col = 0; col < MAX_COLUMN; col++) {
    currentCells[col] = new Array();
    for (let row = 0; row < MAX_ROW; row++) {
      currentCells[col][row] = Math.round(Math.random());
    }
  }
  redraw();
}

function redraw() {
  for (let col = 0; col < MAX_COLUMN; col++) {
    for (let row = 0; row < MAX_ROW; row++) {
      drawCell(col, row, currentCells[col][row]);
    }
  }
}

function drawCell(x, y, state) {
  if (state === 1) {
    ctx.fillStyle = "rgb(0, 0, 0)";
  } else {
    ctx.fillStyle = "rgb(255, 255, 255)";
  }
  ctx.fillRect(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE - 1, CELL_SIZE - 1);
}

function nextGeneration() {
  let nextCells = new Array();
  for (let col = 0; col < MAX_COLUMN; col++) {
    nextCells[col] = new Array();
    for (let row = 0; row < MAX_ROW; row++) {
      var count = countNeighbor(col, row);
      if (currentCells[col][row]) {
        if (count == 2 || count == 3) {
          nextCells[col][row] = 1;
        } else {
          nextCells[col][row] = 0;
        }
      } else {
        if (count == 3) {
          nextCells[col][row] = 1;
        } else {
          nextCells[col][row] = 0;
        }
      }
    }
  }
  currentCells = nextCells;
  redraw();
}

function countNeighbor(x, y) {
  return currentCells[(x + MAX_ROW - 1) % MAX_ROW][(y + MAX_COLUMN - 1) % MAX_COLUMN]
    + currentCells[(x + MAX_ROW - 1) % MAX_ROW][y % MAX_COLUMN]
    + currentCells[(x + MAX_ROW - 1) % MAX_ROW][(y + 1) % MAX_COLUMN]
    + currentCells[x % MAX_ROW][(y + MAX_COLUMN - 1) % MAX_COLUMN]
    + currentCells[x % MAX_ROW][(y + 1) % MAX_COLUMN]
    + currentCells[(x + 1) % MAX_ROW][(y + MAX_COLUMN - 1) % MAX_COLUMN]
    + currentCells[(x + 1) % MAX_ROW][y % MAX_COLUMN]
    + currentCells[(x + 1) % MAX_ROW][(y + 1) % MAX_COLUMN];
}

function canvasClick(e) {
  let x = e.clientX - canvas.offsetLeft;
  let y = e.clientY - canvas.offsetTop;
  let col = Math.floor(x / CELL_SIZE);
  let row = Math.floor(y / CELL_SIZE);
  if(currentCells[col][row] > 0){
    currentCells[col][row] = 0;
  }else{
    currentCells[col][row] = 1;
  }
  drawCell(col, row, currentCells[col][row]);
}
