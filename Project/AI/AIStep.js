/* FILE NAME  : AICreate.js
 * PROGRAMMER : AN5
 * LAST UPDATE: 20.06.2024
 * PURPOSE    : AI step file.
 */

/* Arrays: hitArray and posible hitArray */
let free = [];
/* Array of hits */
let hitArray = [[]];

function CreateHitArray() {
  let i, j;

  for (i = 0; i < 10; i++)
    for (j = 0; j < 10; j++) {
      hitArray[i][j] = false;
    }
}

function DelFromArrray() {}
/* Ai gsme step function.
 * ARGUMENTS: None;
 * RETURNS: None.
 */
function AIStep() {
  if (StepsFind4.length > 0) {
    let c;

    c = Math.random() * StepsFind4.lenth;
    if (freePlacePlayer[StepsFind4[c].y][StepsFind4[c].x] == true) {
      DelFromArray(StepsFind4, c);
    } else {
      AIDamage(StepsFind4[c]);
    }
  } else if (StepsFind32 > 0) {
    let c;

    c = Math.random() * StepsFind32.lenth;
    if (freePlacePlayer[StepsFind32[c].y][StepsFind32[c].x] == true) {
      DelFromArray(StepsFind32, c);
    } else {
      AIDamage(StepsFind32[c]);
    }
  } else {
  }
} /* End of "AIStep" function */

/* If AI hit players ships.
 * ARGUMENTS:
 *   - field coord:
 *       let coords(vec2);
 *   - message:
 *       let mes(bool);
 * RETURNS: None.
 */
function AIDamage(pos) {
  let i, j, c, d;

  c = FindInArray(pos, coordsPlayer);
  if (c.x == 0) {
    Swap(Ships1[c.y], Ships1[0]);
    d = Ships1.shift();
    CreateZoneAI(coordsPlayer[cx][c.y]);
    sinkedAI++;
  } else if (c.x == 1) {
    let num = c.y / 2;
    let c = c.y % 2;

    Swap(Ships2[num][c], Ships2[num][0]);
    if (Ships2[num].length == 1) {
      let del2 = [];

      for (i = 0; i < 2; i++) {
        del2.push(coordsPlayer[1][num * 2 + i]);
      }
      sinkedAI++;
      CreateZoneAI(del2);
    }
    d = Ships2[num].shift();
  } else if (c.x == 2) {
    let num = c.y / 3;
    let c = c.y % 3;

    if (Ships3[num].length == 1) {
      let del3 = [];

      for (i = 0; i < 3; i++) {
        del3.push(coordsPlayer[2][num * 3 + i]);
        CreateZoneAI[del3];
      }
    }
    Swap(Ships3[num][c], Ships3[num][0]);
    d = Ships3[num].shift();
  } else if (c.x == 3) {
    Swap(Ship4[c.y], Ship4[0]);
    d = Ship4.shift();
    if (Ship4.length == 0) {
      CreateZoneAI(coordsPlayer[3]);
    }
  }
  hitArray[pos.y][pos.x] = true;
} /* End of "AIDamage" function */

function CheckNear(pos) {
  if (hitArray[pos.y - 1][pos.x] == true) {
    return vec2(pos.x, pos.y + 1);
  } else if (hitArray[pos.y][pos.x - 1] == true) {
    return vec2(pos.x, pos.y + 1);
  } else if (hitArray[pos.y][pos.x + 1] == true) {
    return vec2(pos.x, pos.y + 1);
  } else if (hitArray[pos.y + 1][pos.x] == true) {
  } else {
    return GenerateNextStep(pos);
  }
}

function GenerateNextStep(pos) {
  let array = [];
  let t = Math.random() * 8;

  array[0] = vec2(pos.x - 1, pos.y - 1);
  array[1] = vec2(pos.x - 1, pos.y);
  array[2] = vec2(pos.x - 1, pos.y + 1);
  array[3] = vec2(pos.x, pos.y - 1);
  array[4] = vec2(pos.x, pos.y + 1);
  array[5] = vec2(pos.x + 1, pos.y - 1);
  array[6] = vec2(pos.x + 1, pos.y);
  array[7] = vec2(pos.x + 1, pos.y + 1);

  return array[t];
}

// function CheckLoc(pos) {
//   let i, j;

//   if (zonePlayer[pos.y][pos.x] == false) {
//     return false;
//   } else return true;
// }

function CreateZoneAI(array) {
  let i, j, g;

  if (Array.isArray(array)) {
    for (i = 0; i < array.length; i++) {
      hitArray[array[i].y - 1][array[i].x - 1] = true;
      hitArray[array[i].y][array[i].x - 1] = true;
      hitArray[array[i].y + 1][array[i].x - 1] = true;
      hitArray[array[i].y - 1][array[i].x] = true;
      hitArray[array[i].y][array[i].x] = true;
      hitArray[array[i].y + 1][array[i].x] = true;
      hitArray[array[i].y - 1][array[i].x + 1] = true;
      hitArray[array[i].y][array[i].x + 1] = true;
      hitArray[array[i].y + 1][array[i].x + 1] = true;
    }

    for (i = 0; i < 10; i++) {
      for (j = 0; j < 10; j++) {
        for (g = 0; g < StepsFind4.lenth; g++) {
          if (hitArray[StepsFind4.y][StepsFind4.x] == true) {
            DelFromArray(StepsFind4, g);
          }
        }
      }
    }

    for (i = 0; i < 10; i++) {
      for (j = 0; j < 10; j++) {
        for (g = 0; g < StepsFind32.lenth; g++) {
          if (hitArray[StepsFind32.y][StepsFind32.x] == true) {
            DelFromArray(StepsFind32, g);
          }
        }
      }
    }
  } else {
    hitArray[array[i].y - 1][array[i].x - 1] = true;
    hitArray[array[i].y][array[i].x - 1] = true;
    hitArray[array[i].y + 1][array[i].x - 1] = true;
    hitArray[array[i].y - 1][array[i].x] = true;
    hitArray[array[i].y][array[i].x] = true;
    hitArray[array[i].y + 1][array[i].x] = true;
    hitArray[array[i].y - 1][array[i].x + 1] = true;
    hitArray[array[i].y][array[i].x + 1] = true;
    hitArray[array[i].y + 1][array[i].x + 1] = true;

    for (i = 0; i < 10; i++) {
      for (j = 0; j < 10; j++) {
        for (g = 0; g < StepsFind4.lenth; g++) {
          if (hitArray[StepsFind4.y][StepsFind4.x] == true) {
            DelFromArray(StepsFind4, g);
          }
        }
      }
    }
    for (i = 0; i < 10; i++) {
      for (j = 0; j < 10; j++) {
        for (g = 0; g < StepsFind32.lenth; g++) {
          if (hitArray[StepsFind32.y][StepsFind32.x] == true) {
            DelFromArray(StepsFind32, g);
          }
        }
      }
    }
  }
}
