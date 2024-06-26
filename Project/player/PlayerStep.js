/* Array of player steps */
let Steps = [[]];
let Damage1 = [];
let Damage2 = [[]];
let Damage3 = [[]];
let Damage4 = [];
let zone = [];
let DamageShips = [[]];
function CreateSteps() {
  let i, j;

  for (i = 0; i < 10; i++) {
    for (j = 0; j < 10; j++) {
      Step[i][j] = false;
    }
  }
}

/* */
function CreateDamagesArrays() {
  let i, j;

  for (i = 0; i < 10; i++) {
    Damage1[i] = Ships1AI[i];
  }

  for (i = 0; i < 10; i++) {
    for (j = 0; j < 10; j++) {
      Damage2[i][j] = Ships2AI[i][j];
    }
  }

  for (i = 0; i < 10; i++) {
    for (j = 0; j < 10; j++) {
      Damage3[i][j] = Ships3AI[i][j];
    }
  }

  for (i = 0; i < 10; i++) {
    Damage4[i] = Ships4AI[i];
  }
}

/* Player step function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
function PlayerStep() {
  let pos;
  pos = ReadCoords();

  if (freePlaceAI[pos.y][pos.x] == false && Steps[pos.y][pos.x] == false) {
    let sc = FindAIShip(pos);

    DelFromArray(sc, pos);
    return true;
  } else {
    return false;
  }
} /* End of "PlayerStep" function */

function FindAIShip(pos) {
  let i, j;

  for (i = 0; i < coordsPlayer.length; i++) {
    for (j = 0; j < coordsPlayer[i].length; j++) {
      if (coordsPlayer[i][j] == pos) {
        return vec2(j, i);
      }
    }
  }
}

function DelFromArray(sc, pos) {
  Swap(coordsAI[sc.y][sc.x], coordsAI[sc.y][0]);
  coordsAI[sc.y].shift();

  if (sc.y == 0) {
    Swap(Ships1AI[sc.x], Ships1[0]);
    Ships1.shift();

    sinkedPlayer++;
    createzone(Damage1[sc.x]);
  }

  if (sc.x == 3) {
    Swap(Ship4AI[sc.x], Ship4AI[0]);
    Ship4AI.shift();
    if (Ship4.length == 0) {
      sinkedPlayer++;
      createzone(Damage4);
    }
  }
  if (sc.x == 1) {
    let num = sc.y / 2;
    let c = sc.y % 2;

    Swap(Ships2AI[num][c], Ships2AI[num][0]);
    if (Ships2AI[num].length == 1) {
      sinkedPlayer++;
      createzone(Damage2[num]);
    }
    Ships2AI[num].shift();
  }
  if (sc.x == 2) {
    let num = sc.y / 3;
    let c = sc.y % 3;

    Swap(Ships3AI[num][c], Ships3AI[num][0]);
    if (Ships3AI[num].lenth == 1) {
      sinkedPlayer++;
      createzone(Damage3[num]);
    }
    Ships3AI[num].shift();
  }
  freePlaceAI[pos.y][pos.x] = true;
  DamageShips[pos.y][pos.x] = true;
}

function FindInArray(pos, array) {
  let i, j;

  for (i = 0; i < array.lenth; i++) {
    for (j = 0; j < array[i].length; i++) {
      if (array[i][j] == pos) return true;
    }
  }
  return false;
}

function createzone(array) {
  let i, j, g;
  let zonec = [];

  for (i = 0; i < array.length; i++) {
    zonec = coordzone(array[i]);
    for (j = 0; j < zonec.length; j++) {
      for (g = 0; g < array.length; g++) {
        if (zonec[j] == array[g] || zonec[j].x == 10 || zonec[j].y == 10) {
          Swap(zonec[j], zonec[0]);
          zonec.shift();
        } else {
          zone.push(zonec[j]);
        }
      }
    }
  }
}

function coordzone(pos) {
  let array = [];

  array[0] = vec2(pos.x - 1, pos.y - 1);
  array[1] = vec2(pos.x - 1, pos.y);
  array[2] = vec2(pos.x - 1, pos.y + 1);
  array[3] = vec2(pos.x, pos.y - 1);
  array[4] = vec2(pos.x, pos.y + 1);
  array[5] = vec2(pos.x + 1, pos.y - 1);
  array[6] = vec2(pos.x + 1, pos.y);
  array[7] = vec2(pos.x + 1, pos.y + 1);

  return array;
}
