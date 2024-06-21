/* FILE NAME  : AICreate.js
 * PROGRAMMER : AN5
 * LAST UPDATE: 21.06.2024
 * PURPOSE    : Create and change ships for Player.
 */

/* Coords which free for ships */
let freePlacePlayer = [[]];
/* For 1 point ships */
let Ships1 = [];
let len1 = 0;
/* For 2 points ships */
let Ships2 = [[], [], []];
let len2 = 0;
/* For 3 points ships */
let Ships3 = [[], []];
let len3 = 0;
/* For 4 point ship */
let Ship4 = [];
/* All ships coords array */
let coordsPlayer = [[], [], [], []];
let array = [];

/* Start game by player function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
function PlayerStart() {
  freePlacePlayer();
  AddPlayersShips();
} /* End of "PlayerStart" function */

/* Fill "freePlace" array function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
function FreePlace() {
  let i, j;

  for (i = 0; i < 10; i++) {
    for (j = 0; i < 10; j++) {
      freePlacePlayer[i][j] = true;
    }
  }
} /* End of "FreePlace" function */

/* Add boat`s coordinates function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
function AddPlayersShips() {
  // это для одного корабля
  ReadCoords();
  CreateShips();
  array.length = 0;
  if (ListenMesChange()) ChangeShips();
} /* End of "AddPlayersShips" function*/

/* Create arrays with ship`s coordinates function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
function CreateShips() {
  let type = array.length,
    i;

  if (type == 1 && Ships1.length < 4) {
    Ships1.push(array[0]);
    freePlacePlayer[array[0].y][array[0].x] = false;
    coordsPlayer[0].push(array[0]);
    len1++;
  }

  if (type == 2 && Ships2.length < 3) {
    for (i = 0; i < array.length; i++) {
      Ships2[len2].push(array[i]);
      freePlacePlayer[array[i].y][array[i].x] = false;
      coordsPlayer[1].push(array[i]);
    }
    len2++;
  }

  if (type == 3 && Ships3.length < 3) {
    for (i = 0; i < array.length; i++) {
      Ships3[len3].push(array[i]);
      freePlacePlayer[array[i].y][array[i].x] = false;
      coordsPlayer[2].push(array[i]);
    }
    len3++;
  }

  if (type == 4 && Ship4.length < 4) {
    for (i = 0; i < array.length; i++) {
      Ship4.push(array[i]);
      freePlacePlayer[array[i].y][array[i].x] = false;
      coordsPlayer[3].push(array[i]);
    }
  }
} /* End of "CreateShips" function */

/* Read coordinates from player function.
 * ARGUMENTS: None/
 * RETURNS: None.
 */
function ReadCoords() {
  let coord, i, g;

  while (array.length < 4 || ListenMes()) {
    coord = ListenCoords();
    if (
      freePlacePlayer[coord.y - 1][coord.x - 1] == false ||
      freePlacePlayer[coord.y - 1][coord.x] == false ||
      freePlacePlayer[coord.y - 1][coord.x + 1] == false ||
      freePlacePlayer[coord.y][coord.x - 1] == false ||
      freePlacePlayer[coord.y][coord.x] == false ||
      freePlacePlayer[coord.y][coord.x + 1] == false ||
      freePlacePlayer[coord.y + 1][coord.x - 1] == false ||
      freePlacePlayer[coord.y + 1][coord.x] == false ||
      freePlacePlayer[coord.y + 1][coord.x + 1] == false
    ) {
      console.log(
        "You already have ship in this coordinates or in the near by coordinates",
      );
      continue;
    } else {
      for (i = 0; i < array.length; i++) {
        if (
          (coord.x == array[i].x + 1 || coord.x == array[i].x - 1) &&
          (coord.y == array[i].y + 1 || coord.y == array[i].y - 1)
        ) {
          console.log("You can`t install ships diagonally");
          break;
        } else {
          array.push[coord];
        }
      }
    }
  }
} /*End of "ReadCoords" function */

/***
 Change ship`s coordinates module 
 ***/

/* Change ships coords function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
function ChangeShips() {
  let count = DelCount();

  while (count > 0) {
    SelectShips();
    DelShips();
  }
} /* End of "ChangeShips" function */

/* Change ships coords function.
 * ARGUMENTS:
 *   - coordinates of ship:
 *       let pos(vec2);
 * RETURNS:
 *   - (let) position in array of all coords;
 */
function FindShip(pos) {
  let i, j;

  for (i = 0; i < coordsPlayer.length; i++) {
    for (j = 0; j < coordsPlayer[i].length; j++) {
      if (coordsPlayer[i][j].x == pos.x && coordsPlayer[i][j].y == pos.y)
        return i;
    }
  }
} /* End of "FindShip" function */

/* Change ships coords function.
 * ARGUMENTS:
 *   - type of ship:
 *       let type;
 * RETURNS:
 *   - (let) position in array of all coords;
 */
function CreateNewPosition(type, pos) {
  let i, j, del;
} /* End of "ChangeShipPosition" function */
