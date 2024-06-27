/* FILE NAME  : game.js
 * PROGRAMMER : AN5
 * LAST UPDATE: 20.06.2024
 * PURPOSE    : Game process file.
 */

let DamageShips = [];
let StepsFind4 = [];
let StepsFind32 = [];

function CreateDamage() {
  let i, j;

  for (i = 0; i < 10; i++) {
    for (j = 0; j < 10; j++) {
      DamageShips[i][j] = false;
    }
  }
}

// Create arrays to Ai step.
function CreateAIArraysToStep() {
  let i, j;
  // look for 4 point ship
  for (i = 0; i < 10; i++) {
    if (i % 4 == 2) {
      StepsFind4.push(vec2(i, 1));
      StepsFind4.push(vec2(i, 5));
      StepsFind4.push(vec2(i, 9));
    } else if (i % 4 == 3) {
      StepsFind4.push(vec2(i, 0));
      StepsFind4.push(vec2(i, 4));
      StepsFind4.push(vec2(i, 8));
    } else if (i % 4 == 0) {
      StepsFind4.push(vec2(i, 3));
      StepsFind4.push(vec2(i, 7));
    } else if (i % 4 == 1) {
      StepsFind4.push(vec2(i, 2));
      StepsFind4.push(vec2(i, 6));
    }
  }
  // look for 2 or 3 point ship
  for (i = 0; i < 10; i++) {
    if (i % 4 == 2) {
      StepsFind32.push(vec2(i, 1));
      StepsFind32.push(vec2(i, 5));
      StepsFind32.push(vec2(i, 9));
    } else if (i % 4 == 1) {
      StepsFind32.push(vec2(i, 0));
      StepsFind32.push(vec2(i, 4));
      StepsFind32.push(vec2(i, 8));
    } else if (i % 4 == 2) {
      StepsFind32.push(vec2(i, 3));
      StepsFind32.push(vec2(i, 7));
    } else if (i % 4 == 3) {
      StepsFind32.push(vec2(i, 2));
      StepsFind32.push(vec2(i, 6));
    }
  }
}

/* Start game function */
function gameStart() {
  AIStart();
  PlayerStart();
}

/* Game process function */
function gameStep() {
  /* while (....)
    ....
  while (*/
}

/* End of game*/
function gameEnd() {}
