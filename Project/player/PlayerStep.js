/* Array of player steps */
let Steps = [[]];

function CreateSteps() {
  let i, j;

  for (i = 0; i < 10; i++) {
    for (j = 0; j < 10; j++) {
      Step[i][j] = false;
    }
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
    sinked++;
  }
  if (sc.x == 3) {
    Swap(Ship4AI[sc.x], Ship4AI[0]);
    Ship4AI.shift();
    if (Ship4.length == 0) {
      sinked++;
    }
  }
  if (sc.x == 1) {
    let num = sc.y / 2;
    let c = sc.y % 2;

    Swap(Ships2AI[num][c], Ships2AI[num][0]);
    if (Ships2AI[num].lenth == 1) sinked++;
    Ships2AI[num].shift();
  }
  if (sc.x == 2) {
    let num = sc.y / 3;
    let c = sc.y % 3;

    Swap(Ships3AI[num][c], Ships3AI[num][0]);
    if (Ships2AI[num].lenth == 1) sinked++;
    Ships3AI[num].shift();
  }
  freePlaceAI[pos.y][pos.x] = true;
  DamageShips[pos.y][pos.x] = true;
}
