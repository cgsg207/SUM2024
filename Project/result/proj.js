import { vec2 } from "./vec2.js";
let array, arrayAI;
let img1 = new Image();
img1.src = "img.jpg";
let img2 = new Image();
img2.src = "img.jpg";

//img.src = "explode2.gif";

function initBoard() {
  let i;
  let canvas1 = document.getElementById("canvas1");
  const can1 = canvas1.getContext("2d");

  let canvas2 = document.getElementById("canvas2");
  const can2 = canvas2.getContext("2d");

  for (i = 0; i < 9; i++) {
    can1.beginPath();
    can1.lineWidth = 1;
    can1.moveTo(i * 101 + 101, 0);
    can1.lineTo(i * 101 + 101, 1009);
    can1.moveTo(0, i * 101 + 101);
    can1.lineTo(1009, i * 101 + 101);
    console.log(i * 101 + 101);
    can1.stroke();
  }

  for (i = 0; i < 9; i++) {
    can2.beginPath();
    can2.lineWidth = 1;
    can2.moveTo(i * 101 + 101, 0);
    can2.lineTo(i * 101 + 101, 1009);
    can2.moveTo(0, i * 101 + 101);
    can2.lineTo(1009, i * 101 + 101);
    console.log(i * 101 + 101);
    can2.stroke();
  }
  Create();
  drawShips();
  drawAI();
  canvas1.onmousemove = (e) => {
    const rect = canvas1.getBoundingClientRect();
    let x = e.clientX - rect.left,
      y = e.clientY - rect.top;
    let c = ChangeCoords(x, y);
    console.log(`Курсор: x=${c.x}, y=${c.y}`);
  };
  // let c = ReadCoordPlayer();
  // console.log(`Курсор: x=${c.x}, y=${c.y}`);
  // c = ReadCoordAI();
  // console.log(`Курсор: x=${c.x}, y=${c.y}`);
  canvas2.onmousemove = (e) => {
    const rect = canvas2.getBoundingClientRect();
    let x = e.clientX - rect.left,
      y = e.clientY - rect.top;
    let c = ChangeCoords(x, y);
    console.log(`Курсор: x=${c.x}, y=${c.y}`);
  };
}

function ChangeCoords(x, y) {
  let i, xc, yc;

  for (i = 0; i <= 10; i++) {
    if (x < 101 + i * 101 && x > 101 + (i - 1) * 101) xc = (i - 1) * 101 + 50;
  }

  for (i = 0; i <= 10; i++) {
    if (y < 101 + i * 101 && y > 101 + (i - 1) * 101) yc = (i - 1) * 101 + 50;
  }
  return vec2(Math.floor(xc / 100 + 1), Math.floor(yc / 100 + 1));
}

initBoard();

function ReadCoordPlayer() {
  let canvas1 = document.getElementById("canvas1");

  canvas1.onmousemove = (e) => {
    const rect = canvas1.getBoundingClientRect();
    let x = e.clientX - rect.left,
      y = e.clientY - rect.top;
    let c = ChangeCoords(x, y);
    return vec2(c.x, c.y);
  };
}

function ReadCoordAI() {
  let canvas2 = document.getElementById("canvas1");

  canvas2.onmousemove = (e) => {
    const rect = canvas1.getBoundingClientRect();
    let x = e.clientX - rect.left,
      y = e.clientY - rect.top;
    let c = ChangeCoords(x, y);
    return vec2(c.x, c.y);
  };
}

function Create() {
  let i, j;

  array = new Array(10);
  arrayAI = new Array(10);

  for (i = 0; i < 10; i++) {
    array[i] = new Array(10);
    arrayAI[i] = new Array(10);
  }

  //AI
  arrayAI[3][3] = 2;
  arrayAI[9][9] = 2;
  ////player
  array[0][0] = 2;
  array[0][1] = 2;
  array[0][2] = 1;
  array[0][3] = 1;

  array[9][0] = 1;
  array[2][7] = 1;
  array[6][4] = 1;
  array[6][7] = 1;

  array[3][1] = 1;
  array[3][2] = 1;
  array[6][4] = 1;
  array[6][7] = 1;

  array[0][6] = 1;
  array[0][7] = 1;
  array[6][4] = 1;
  array[6][7] = 1;

  array[9][2] = 1;
  array[9][3] = 1;
  array[9][4] = 1;
  array[6][9] = 1;
  array[7][9] = 1;
  array[8][9] = 1;
}

function drawShips() {
  let canvas1 = document.getElementById("canvas1");
  const can1 = canvas1.getContext("2d");

  let i, j;

  img2.onload = () => {
    for (i = 0; i < 10; i++)
      for (j = 0; j < 10; j++) {
        if (array[i][j] == 1) can1.fillRect(i * 101, j * 101, 101, 101);
        if (array[i][j] == 2) {
          can1.fillRect(i * 101, j * 101, 101, 101);
          can1.drawImage(img2, i * 101 - 0, j * 102 - 0, 100, 100);
        }
      }
  };
}

function drawAI() {
  let canvas2 = document.getElementById("canvas2");
  const can2 = canvas2.getContext("2d");
  let i, j;

  img1.onload = () => {
    for (i = 0; i < 10; i++)
      for (j = 0; j < 10; j++) {
        if (arrayAI[i][j] == 2) {
          //can2.fillRect(i * 101, j * 101, 101, 101);
          can2.drawImage(img1, i * 101 - 0, j * 101 - 0, 100, 100);
        }
      }
  };
  can2.fillStyle = "grey";
  can2.fillRect(202, 202, 101, 101);
  can2.fillRect(202, 303, 101, 101);
  can2.fillRect(202, 404, 101, 101);

  can2.fillRect(303, 202, 101, 101);
  can2.fillRect(303, 404, 101, 101);

  can2.fillRect(404, 202, 101, 101);
  can2.fillRect(404, 303, 101, 101);
  can2.fillRect(404, 404, 101, 101);
}
