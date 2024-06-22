/* FILE NAME  : AICreate.js
 * PROGRAMMER : AN5
 * LAST UPDATE: 22.06.2024
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
let loadarray = [];

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
  while (len1 < 4 && len2 < 3 && len3 < 2 && Ship4.length < 1) {
    ReadCoords();
    CreateShip();
    loadarray.length = 0;
  }
  if (ListenMesChange()) ChangeShips();
} /* End of "AddPlayersShips" function*/

/* Create arrays with ship`s coordinates function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
function CreateShip() {
  let type = loadarray.length,
    i;

  if (type == 1 && Ships1.length < 4) {
    Ships1.push(loadarray[0]);
    freePlacePlayer[loadarray[0].y][loadarray[0].x] = false;
    coordsPlayer[0].push(loadarray[0]);
    len1++;
  }

  if (type == 2 && Ships2.length < 3) {
    for (i = 0; i < loadarray.length; i++) {
      Ships2[len2].push(loadarray[i]);
      freePlacePlayer[loadarray[i].y][loadarray[i].x] = false;
      coordsPlayer[1].push(loadarray[i]);
    }
    len2++;
  }

  if (type == 3 && Ships3.length < 3) {
    for (i = 0; i < loadarray.length; i++) {
      Ships3[len3].push(loadarray[i]);
      freePlacePlayer[loadarray[i].y][loadarray[i].x] = false;
      coordsPlayer[2].push(loadarray[i]);
    }
    len3++;
  }

  if (type == 4 && Ship4.length < 4) {
    for (i = 0; i < loadarray.length; i++) {
      Ship4.push(loadarray[i]);
      freePlacePlayer[loadarray[i].y][loadarray[i].x] = false;
      coordsPlayer[3].push(loadarray[i]);
    }
  }
} /* End of "CreateShips" function */

/* Read coordinates from player function.
 * ARGUMENTS: None/
 * RETURNS: None.
 */
function ReadCoords() {
  let coord, i, g;

  while (loadarray.length < 4 || ListenMes()) {
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
      for (i = 0; i < loadarray.length; i++) {
        if (
          (coord.x == loadarray[i].x + 1 || coord.x == loadarray[i].x - 1) &&
          (coord.y == loadarray[i].y + 1 || coord.y == loadarray[i].y - 1)
        ) {
          console.log("You can`t install ships diagonally");
          break;
        } else {
          loadarray.push[coord];
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

  ReadChange(count);
  for (i = 0; i < loadarray.length; i++) {
    type = SelectShip(loadarray[i]);
    DelShip(type, loadarray[i]);
  }
  loadarray.length = 0;
  while (len1 < 4 && len2 < 3 && len3 < 2 && Ship4.length < 1) {
    ReadCoords();
    CreateShip();
    loadarray.length = 0;
  }
} /* End of "ChangeShips" function */

/* Read coordinates from player to delete ships function.
 * ARGUMENTS: None/
 * RETURNS: None.
 */
function ReadChange(count) {
  let i, j;

  while (count > 0) {
    coord = ListenCoords();

    if (freePlacePlayer[coord.y][coord.x]) {
      console.log("You can`t choose empty field.");
    } else {
      loadarray.push(coord);
    }
  }
} /* End of "ReadChange" function */

/* Find index by element for Ships1 function.
 * ARGUMENTS:
 *   - coordinates of ship:
 *       let pos(vec2);
 * RETURNS:
 *   - (let) position in array of all coords;
 */
function DelShip(type, pos) {
  let index, number;

  if (type == 3) {
    for (i = 0; i < 4; i++) {
      freePlacePlayer[Ship4[i].y][Ship4[i].x] = true;
    }
    coordsPlayer[4].lenth = 0;
    Ship4.length = 0;
  }

  if (type == 0) {
    index = FindIndex1(pos);
    freePlacePlayer[Ships1[index].y][Ships1[index].x] = true;
    Swap(coordsPlayer[0][index], coordsPlayer[0][0]);
    number = coordsPlayer[0].shift();
    len1--;
  }

  if (type == 2) {
    index = FindIndex3(pos);
    for (i = 0; i < 3; i++) {
      freePlacePlayer[Ships3[index][i].y][Ships3[index][i].x] = true;
    }
    if (index == 0) {
      for (i = 0; i < 3; i++) {
        number = coordsPlayer[2].shift();
      }
    } else {
      for (i = 0; i < 3; i++) {
        number = coordsPlayer[2].pop();
      }
    }
    Ships3[index].lenth = 0;
    len3--;
  }

  if (type == 1) {
    index = FindIndex23(pos, 1);
    for (i = 0; i < 2; i++) {
      freePlacePlayer[Ships2[index][i].y][Ships2[index][i].x] = true;
    }
    if (index == 0) {
      for (i = 0; i < 2; i++) {
        number = coordsPlayer[1].shift();
      }
    } else if (index == 2) {
      for (i = 0; i < 2; i++) {
        number = coordsPlayer[1].pop();
      }
    } else {
      for (i = 0; i < 3; i++) {
        Swap(coordsPlayer[1][i], coordsPlayer[1][i + 3]);
      }
    }
    Ships2[index].lenth = 0;
    len2--;
  }
} /* End of "DelShip" function */

/* Find index by element for Ships1 function.
 * ARGUMENTS:
 *   - coordinates of ship:
 *       let pos(vec2);
 * RETURNS:
 *   - (let) position in array of all coords;
 */
function FindIndex1(pos) {
  let i;

  for (i = 0; i < Ships1.length; i++) {
    if (Ships1[i] == pos) return i;
  }
} /* End of "FindIndex1" function */

/* Find index by element for Ships2 / 3 function.
 * ARGUMENTS:
 *   - coordinates of ship:
 *       let pos(vec2);
 *   - type of ship:
 *       let type;
 * RETURNS:
 *   - (let) position in array of all coords;
 */
function FindIndex23(pos, type) {
  let i, j;

  if (type == 0) {
    for (i = 0; i < len3; i++) {
      for (j = 0; j < 3; j++) {
        if (pos == Ships3[i][j]) return i;
      }
    }
  } else {
    for (i = 0; i < len2; i++) {
      for (j = 0; j < 3; j++) {
        if (pos == Ships2[i][j]) return i;
      }
    }
  }
} /* End of "FindIndex23" function */

/* Select ships by thier coordinates function.
 * ARGUMENTS:
 *   - coordinates of ship:
 *       let pos(vec2);
 * RETURNS:
 *   - (let) position in array of all coords;
 */
function SelectShip(pos) {
  let i, j;

  for (i = 0; i < coordsPlayer.length; i++) {
    for (j = 0; j < coordsPlayer[i].length; j++) {
      if (coordsPlayer[i][j] == pos) {
        return i;
      }
    }
  }
} /* End of "SelectShip" function */
