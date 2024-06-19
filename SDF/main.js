/* FILE NAME  : main.js
 * PROGRAMMER : AN5
 * LAST UPDATE: 15.06.2024
 * PURPOSE    :
 */

const img = Image();
let imgWH = [];

function setCanvas() {
  const canvas = document.createElement("canvas");

  canvas.height = img.height;
  canvas.width = img.width;
}

function getImage() {
  img.res = "smile.png";
}

function CreateArray() {
  let i;

  for (i = 0; i < img.height; i++) {
    imgWH[i] = new Array(img.width);
  }
}
