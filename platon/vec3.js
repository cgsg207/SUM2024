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
 add(v1, v2) {
  if (typeof v == "number") {
   return vec3(v1.x + v, v1.y + v, v1.z + v);
  }
  return vec3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
 }
 // Set vec3 negative
 negative(v1) {
  return vec3(-v1.x, -v1.y, -v1.z);
 } // End of 'negative' function

 // Multiply vec3 on number
 mulnum(v, n) {
  return vec3(v.x * n, v.y * n, v.z * n);
 } // End of 'mulnum' function

 // Devision vec3 on number
 divnum(v, n) {
  return vec3(v.x / n, v.y / n, v.z / n);
 } // End of 'divnum' function
 // Dot product two vec3
 dot(v1, v2) {
  return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
 } // End of 'dot' function

 // Cross product two vec3
 cross(v1, v2) {
  return vec3(
   v1.y * v2.z - v1.z * v2.y,
   v1.z * v2.x - v1.x * v2.z,
   v1.x * v2.y - v1.y * v2.x
  );
 } // End of 'cross' function

 // Normalize vec3
 normilize(v) {
  let len = v.x * v.x + v.y * v.y + v.z * v.z;
  if (len != 0 && len != 1) {
   len = Math.sqrt(len);
   return vec3(v);
  }
 } // End of 'normolize' function
 // Subtract one vec3 from another
 subvec(v1, v2) {
  return vec3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
 }
} // End of '_vec3' class

// Vec3 set function
export function vec3(...args) {
 return new _vec3(...args);
} // End of 'vec3' function
