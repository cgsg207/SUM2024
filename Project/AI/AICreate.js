/* FILE NAME  : AICreate.js
 * PROGRAMMER : AN5
 * LAST UPDATE: 20.06.2024
 * PURPOSE    : Create ships for AI.
 */
/* Coords which free for ships */

let freePlace = [];
/* For 1 point ships */
let Ships1AI = [];
let len1AI = 0;
/* For 2 points ships */
let Ships2AI = [[], [], []];
let len2AI = 0;
/* For 3 points ships */
let Ships3AI = [[], []];
let len3AI = 0;
/* For 4 point ship */
let Ship4AI = [];
/* All ships coords array */
let coordsAI = [[], [], [], []];
let array = [];

/* Check positions around ship function.
 * ARGUMENTS:
 *   - "length" of ship:
 *       let len;
 *   - X coordinate of first part:
 *       let xc;
 *   - Y coordinate of first part:
 *       let yc;
 * RETURNS: None.
 */
function CheckPlace(xc, yc, len) {
  let i, j;
  let nyc, nxc;

  array = [1, 2, 3, 4];
  nxc = xc - 1;
  nyc = yc - 1;
  for (i = 0, j = 0; i < 3; i++) {
    while (j < len + 2)
      if (freePlace[nyc + j][nxc + i] == false) {
        array[0] = 0;
        break;
      }
  }

  for (i = 0, j = 0; i < 3; i++) {
    while (j < len + 2)
      if (freePlace[nyc + i][nxc + j] == false) {
        array[1] = 0;
        break;
      }
  }

  nxc = xc + 1;
  nyc = yc + 1;

  for (i = 0, j = 0; i < 3; i++) {
    while (j < len + 2)
      if (freePlace[nyc - i][nxc - j] == false) {
        array[2] = 0;
        break;
      }
  }

  for (i = 0, j = 0; i < 3; i++) {
    while (j < len + 2)
      if (freePlace[nyc - j][nxc - i] == false) {
        array[3] = 0;
        break;
      }
  }
} /* End of "CheckPlace" function */

/* Add boat`s coordinates function.
 * ARGUMENTS:
 *   - direction number:
 *       let num;
 *   - X coordinate of first part:
 *       let xc;
 *   - Y coordinate of first part:
 *       let yc;
 * RETURNS: None.
 */
function CreateCoords1(xc, yc) {
  /* Set coordinates for ship */
  Ships1AI[len1AI] = vec2(xc, yc);
  /* Change free positions */
  freePlace[xc][yc] = false;

  /* Add ship`s coords to global array */
  for (i = 0; i < 4; i++) coordsAI[0][len1AI] = Ships1AI[len1AI];
} /* End of "CreateCoords1" function */

/* Add destroyers`s coordinates function.
 * ARGUMENTS:
 *   - direction number:
 *       let num;
 *   - X coordinate of first part:
 *       let xc;
 *   - Y coordinate of first part:
 *       let yc;
 * RETURNS: None.
 */
function CreateCoords2(xc, yc, num) {
  if (num == 1) {
    Ships2AI[len2AI][0] = vec2(xc, yc);
    Ships2AI[len2AI][1] = vec2(xc, yc + 1);
    Ships2AI[len2AI][2] = vec2(xc, yc + 2);
  }

  if (num == 2) {
    Ships2AI[len3AI][0] = vec2(xc, yc);
    Ships2AI[len3AI][1] = vec2(xc + 1, yc);
    Ships2AI[len3AI][2] = vec2(xc + 1, yc);
  }

  if (num == 3) {
    Ships2AI[len3AI][0] = vec2(xc, yc);
    Ships2AI[len3AI][1] = vec2(xc, yc - 1);
    Ships2AI[len3AI][2] = vec2(xc, yc - 2);
  }

  if (num == 4) {
    Ships2AI[len3AI][0] = vec2(xc, yc);
    Ships2AI[len3AI][1] = vec2(xc - 1, yc);
    Ships2AI[len3AI][2] = vec2(xc - 1, yc);
  }
  /* Change free positions */
  for (i = 0; i < 3; i++)
    freePlace[Ships2AI[len2AI][i].y][Ships2AI[len2AI][i].x] = false;

  /* Add ship`s coords to global array */
  for (i = 0; i < 3; i++) coordsAI[2].push[Ships2AI[len2AI][i]];
} /* End of "CreateCoords3" function */

/* Add cruiser`s coordinates function.
 * ARGUMENTS:
 *   - direction number:
 *       let num;
 *   - X coordinate of first part:
 *       let xc;
 *   - Y coordinate of first part:
 *       let yc;
 * RETURNS: None.
 */
function CreateCoords3(xc, yc, num) {
  if (num == 1) {
    Ships3AI[len3AI][0] = vec2(xc, yc);
    Ships3AI[len3AI][1] = vec2(xc, yc + 1);
    Ships3AI[len3AI][2] = vec2(xc, yc + 2);
  }

  if (num == 2) {
    Ships3AI[len3AI][0] = vec2(xc, yc);
    Ships3AI[len3AI][1] = vec2(xc + 1, yc);
    Ships3AI[len3AI][2] = vec2(xc + 1, yc);
  }

  if (num == 3) {
    Ships3AI[len3AI][0] = vec2(xc, yc);
    Ships3AI[len3AI][1] = vec2(xc, yc - 1);
    Ships3AI[len3AI][2] = vec2(xc, yc - 2);
  }

  if (num == 4) {
    Ships3AI[len3AI][0] = vec2(xc, yc);
    Ships3AI[len3AI][1] = vec2(xc - 1, yc);
    Ships3AI[len3AI][2] = vec2(xc - 1, yc);
  }
  /* Change free positions */
  for (i = 0; i < 3; i++)
    freePlace[Ships3AI[len3AI][i].y][Ships3AI[len3AI][i].x] = false;

  /* Add ship`s coords to global array */
  for (i = 0; i < 3; i++) coordsAI[2].push[Ships3AI[len3AI][i]];
} /* End of "CreateCoords3" function */

/* Add aircraft-carrier`s coordinates function.
 * ARGUMENTS:
 *   - direction number:
 *       let num;
 *   - X coordinate of first part:
 *       let xc;
 *   - Y coordinate of first part:
 *       let yc;
 * RETURNS: None.
 */
function CreateCoords4(xc, yc, num) {
  let i;

  /* Set coordinates for ship */
  if (num == 1) {
    Ship4AI[0] = vec2(xc, yc);
    Ship4AI[1] = vec2(xc, yc + 1);
    Ship4AI[2] = vec2(xc, yc + 2);
    Ship4AI[3] = vec2(xc, yc + 3);
  }
  if (num == 2) {
    Ship4AI[0] = vec2(xc, yc);
    Ship4AI[1] = vec2(xc + 1, yc);
    Ship4AI[2] = vec2(xc + 2, yc);
    Ship4AI[3] = vec2(xc + 3, yc);
  }
  if (num == 3) {
    Ship4AI[0] = vec2(xc, yc);
    Ship4AI[1] = vec2(xc, yc - 1);
    Ship4AI[2] = vec2(xc, yc - 2);
    Ship4AI[3] = vec2(xc, yc - 3);
  }
  if (num == 4) {
    Ship4AI[0] = vec2(xc, yc);
    Ship4AI[1] = vec2(xc - 1, yc);
    Ship4AI[2] = vec2(xc - 2, yc);
    Ship4AI[3] = vec2(xc - 3, yc);
  }
  /* Change free positions */
  for (i = 0; i < 4; i++) freePlace[Ship4AI[i].y][Ship4AI[i].x] = false;

  /* Add ship`s coords to global array */
  for (i = 0; i < 4; i++) coordsAI[3][i] = Ship4AI[i];
} /* End of "CreateCoords4" function */

/* Create empty field.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
function FreePlace() {
  let i, j;

  for (i = 0; i < 10; i++) {
    for (j = 0; i < 10; j++) {
      freePlace[i][j] = true;
    }
  }
} /* End of "FreePlace" function */

/* Generate arrays with AI ships function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
function CreateShips() {
  let mas = [];
  let xc, yc, num;

  while (Ships4AI.length < 1) {
    xc = Math.random() * 10;
    yc = Math.random() * 10;

    if (freePlace[yc][xc] == true) {
      CheckPlace(xc, yc, 4);
      if (array[0] == 1) mas.push[array[0]];
      else if (array[1] == 2) mas.push[array[1]];
      else if (array[2] == 3) mas.push[array[2]];
      else if (array[3] == 4) mas.push[array[3]];

      num = Math.random() * (mas.length + 1);
      CreateCoords4(xc, yc, mas[num]);
    } else continue;
  }
  array.length = 0;

  while (len3AI < 2) {
    xc = Math.random() * 10;
    yc = Math.random() * 10;

    if (freePlace[yc][xc] == true) {
      CheckPlace(xc, yc, 3);
      if (array[0] == 1) mas.push[array[0]];
      else if (array[1] == 2) mas.push[array[1]];
      else if (array[2] == 3) mas.push[array[2]];
      else if (array[3] == 4) mas.push[array[3]];

      num = Math.random() * (mas.length + 1);
      CreateCoords3(xc, yc, mas[num]);
      len3AI++;
    } else continue;
  }
  array.length = 0;

  while (len2AI < 3) {
    xc = Math.random() * 10;
    yc = Math.random() * 10;

    if (freePlace[yc][xc] == true) {
      CheckPlace(xc, yc, 2);
      if (array[0] == 1) mas.push[array[0]];
      else if (array[1] == 2) mas.push[array[1]];
      else if (array[2] == 3) mas.push[array[2]];
      else if (array[3] == 4) mas.push[array[3]];

      num = Math.random() * (mas.length + 1);
      CreateCoords2(xc, yc, mas[num]);
      len3AI++;
    } else continue;
  }
  array.length = 0;

  while (len1AI < 4) {
    xc = Math.random() * 10;
    yc = Math.random() * 10;

    if (freePlace[yc][xc] == true) {
      CheckPlace(xc, yc, 1);
      num = Math.random() * (mas.length + 1);
      CreateCoords1(xc, yc, mas[num]);
    } else continue;
  }
  array.length = 0;
} /* End of "CreateShips" function */

/* Start AI function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
export function AIStart() {
  FreePlace();
  CreateShips();
} /* End of "AIStart" function */
