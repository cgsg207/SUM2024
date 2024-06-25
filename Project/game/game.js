/* FILE NAME  : game.js
 * PROGRAMMER : AN5
 * LAST UPDATE: 20.06.2024
 * PURPOSE    : Game process file.
 */

let DamageShips = [];
function CreateDamage() {
  let i, j;

  for (i = 0; i < 10; i++) {
    for (j = 0; j < 10; j++) {
      DamageShips[i][j] = false;
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
