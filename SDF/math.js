/* FILE NAME  : main.js
 * PROGRAMMER : AN5
 * LAST UPDATE: 15.06.2024
 * PURPOSE    :
 */

let infinity = 100000;
let porables_vertexes = [];

/* Find intection */
function intection(x1, y1, x2, y2) {
  let s;

  s = ((y1 + x1 * x1 - (y2 + x2 * x2)) / 2) * (x1 - x2);
  return s;
}

/* Marching porables */
function marchP() {
  let i;
  for (i = 0; i < porables.length; i++) {
    //
  }
}

/* Transpose image */
function transpose(img) {}

/* go by hieght */
function stepHeight() {}

/* Result function */
export function result() {
  let i;
  // ....
  for (i = 0; i < img.width; i++) {
    transpose(img);
  }

  //...
  for (i = 0; i < img.width; i++) {
    transpose(img);
  }
}
