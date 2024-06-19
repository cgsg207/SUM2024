/* Array of damaged ships */
let DamageShips = [];

/* Players step function */
function PlayerStep(position) {
  let i;
  let j;
  let aim = false;

  for (i = 0; i < coords.length; i++) {
    for (j = 0; j < coords[i].length; j++) {
      if (coords[i][j].x == position.x && coords[i][j].y == position.y) {
        aim = FindDamage(i, position);
      }
      if (aim == true) return true;
    }
  }
}

/* Find damaged ship function */
function FindDamage(type, position) {
  let i, j;

  if (type == 0) {
    for (i = 0; i < Ships1.length; i++) {
      if (Ships1[i].x == position.x && Ships1[i].y == position.y) {
        console.log(`Damaged ship: Ship:1: %d`, i);
        DamageShips.push[Ships1[i]];
        //delete element from Ships.. and coords
        return true;
      }
    }
  }
  if (type == 1) {
    for (i = 0; i < Ships2.length; i++) {
      for (j = 0; j < 2; j++) {
        if (Ships2[i][j].x == position.x && Ships2[i][j].y == position.y) {
          console.log(`Damaged ship: Ship:2: %d`, i);
          DamageShips.push[Ships2[i][j]];
          //delete element from Ships.. and coords
          return true;
        }
      }
    }
  }
  if (type == 2) {
    for (i = 0; i < Ships3.length; i++) {
      for (j = 0; j < 3; j++) {
        if (Ships2[i][j].x == position.x && Ships2[i][j].y == position.y) {
          console.log(`Damaged ship: Ship:3: %d`, i);
          DamageShips.push[Ships3[i][j]];
          //delete element from Ships.. and coords
          return true;
        }
      }
    }
  }
  if (type == 3) {
    for (i = 0; i < Ships4.length; i++) {
      if (Ships4[i].x == position.x && Ships4[i].y == position.y) {
        console.log(`Damaged ship: Ship:4: %d`, i);
        DamageShips.push[Ships1[i]];
        //delete element from Ships.. and coords
        return true;
      }
    }
  } else {
    console.log("Water");
    return false;
  }
}
