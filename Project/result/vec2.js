class _vec2 {
  constructor(x, y) {
    if (x == undefined) {
      (this.x = 0), (this.y = 0);
    } else if (typeof x == "object") {
      if (x.length == 2) {
        (this.x = x[0]), (this.y = x[1]);
      } else {
        (this.x = x.x), (this.y = x.y);
      }
    } else if (y == undefined) {
      (this.x = x), (this.y = x);
    } else {
      (this.x = x), (this.y = y);
    }
  } //End of 'constructor' function
}

// Vec2 set function
export function vec2(...args) {
  return new _vec2(...args);
} // End of 'vec2' function
