/* FILE NAME:   vec3.js
 * PROGRAMMER:  AN5
 * LAST UPDATE: 07.06.2024
 * PURPOSE:     vec3 library for rendering.
 */

export class _vec3 {
  constructor(x, y, z) {
    if (x == undefined) {
      (this.x = 0), (this.y = 0), (this.z = 0);
    } else if (typeof x == "object") {
      if (x.length == 3) {
        (this.x = x[0]), (this.y = x[1]), (this.z = x[2]);
      } else {
        (this.x = x.x), (this.y = x.y), (this.z = x.z);
      }
    } else if (y == undefined || z == undefined) {
      (this.x = x), (this.y = x), (this.z = x);
    } else {
      (this.x = x), (this.y = y), (this.z = z);
    }
  } // End of 'constructor' function

  // Add two vec3 type
  add(v) {
    if (typeof v == "number") {
      return vec3(this.x + v, (this.y = v), this.z + v);
    }
    return vec3(this.x + v.x, (this.y = v.y), this.z + v.z);
  }
  // Set vec3 negative
  negative() {
    return vec3(-this.x, -this.y, -this.z);
  } // End of 'negative' function

  // Multiply vec3 on number
  mulnum(v) {
    return vec3(this.x * v, this.y * v, this.z * v);
  } // End of 'mulnum' function

  // Devision vec3 on number
  divnum(v) {
    return vec3(this.x / v, this.y / v, this.z / v);
  } // End of 'divnum' function
  // Dot product two vec3
  dot(v) {
    return this.x * v.x + this.y * v.y + this.z * v.z;
  } // End of 'dot' function

  // Cross product two vec3
  cross(v) {
    return vec3(
      this.y * v.z - this.z * v.y,
      this.z * v.x - this.x * v.z,
      this.x * v.y - this.y * v.x
    );
  } // End of 'cross' function

  // Normalize vec3
  normilize() {
    let len = this.x * this.x + this.y * this.y + this.z * this.z;
    if (len != 0 && len != 1) {
      len = Math.sqrt(len);
      return vec3(this);
    }
  } // End of 'normolize' function
  // Subtract one vec3 from another
  subvec(v) {
    return vec3(this.x - v.x, this.y - v.y, this.z - v.z);
  }
} // End of '_vec3' class

// Vec3 set function
export function vec3(...args) {
  return new _vec3(...args);
} // End of 'vec3' function
