/* FILE NAME:   mat4.js
 * PROGRAMMER:  AN5
 * LAST UPDATE: 07.06.2024
 * PURPOSE:     mat4 library for rendering.
 */

//From degrees to redian
function D2R(a) {
 const pi = 3.14159265358979323846;
 return a * (pi / 180.0);
} // End of 'D2R' function

class _mat4 {
 constructor(m = null) {
  if (m == null) {
   this.m = [
    [1, 0, 0, 0],
    [0, 1, 0, 0],
    [0, 0, 1, 0],
    [0, 0, 0, 1],
   ];
  } else if (typeof m == "object" && m.length == 4) {
   this.m = m;
  } else {
   this.m = m.m;
  }
 } // End of constructor
 transpose(m) {
  return mat4(
   [m.m[0][0], m.m[0][1], m.m[0][2], m.m[0][3]],
   [m.m[1][0], m.m[1][1], m.m[1][2], m.m[1][3]],
   [m.m[2][0], m.m[2][1], m.m[2][2], m.m[2][3]],
   [m.m[3][0], m.m[3][1], m.m[3][2], m.m[3][3]]
  );
 }
 mulmatr(m1, m2) {
  return mat4(
   [
    m1.m[0][0] * m2.m[0][0] +
     m1.m[0][1] * m2.m[1][0] +
     m1.m[0][2] * m2.m[2][0] +
     m1.m[0][3] * m2.m[3][0],

    m1.m[0][0] * m2.m[0][1] +
     m1.m[0][1] * m2.m[1][1] +
     m1.m[0][2] * m2.m[2][1] +
     m1.m[0][3] * m2.m[3][1],

    m1.m[0][0] * m2.m[0][2] +
     m1.m[0][1] * m2.m[1][2] +
     m1.m[0][2] * m2.m[2][2] +
     m1.m[0][3] * m2.m[3][2],

    m1.m[0][0] * m2.m[0][3] +
     m1.m[0][1] * m2.m[1][3] +
     m1.m[0][2] * m2.m[2][3] +
     m1.m[0][3] * m2.m[3][3],
   ], // [0][0-3]
   [
    m1.m[1][0] * m2.m[0][0] +
     m1.m[1][1] * m2.m[1][0] +
     m1.m[1][2] * m2.m[2][0] +
     m1.m[1][3] * m2.m[3][0],

    m1.m[1][0] * m2.m[0][1] +
     m1.m[1][1] * m2.m[1][1] +
     m1.m[1][2] * m2.m[2][1] +
     m1.m[1][3] * m2.m[3][1],

    m1.m[1][0] * m2.m[0][2] +
     m1.m[1][1] * m2.m[1][2] +
     m1.m[1][2] * m2.m[2][2] +
     m1.m[1][3] * m2.m[3][2],

    m1.m[1][0] * m2.m[0][3] +
     m1.m[1][1] * m2.m[1][3] +
     m1.m[1][2] * m2.m[2][3] +
     m1.m[1][3] * m2.m[3][3],
   ],
   [
    m1.m[2][0] * m2.m[0][0] +
     m1.m[2][1] * m2.m[1][0] +
     m1.m[2][2] * m2.m[2][0] +
     m1.m[2][3] * m2.m[3][0],

    m1.m[2][0] * m2.m[0][1] +
     m1.m[2][1] * m2.m[1][1] +
     m1.m[2][2] * m2.m[2][1] +
     m1.m[2][3] * m2.m[3][1],

    m1.m[2][0] * m2.m[0][2] +
     m1.m[2][1] * m2.m[1][2] +
     m1.m[2][2] * m2.m[2][2] +
     m1.m[2][3] * m2.m[3][2],

    m1.m[2][0] * m2.m[0][3] +
     m1.m[2][1] * m2.m[1][3] +
     m1.m[2][2] * m2.m[2][3] +
     m1.m[2][3] * m2.m[3][3],
   ],
   [
    m1.m[3][0] * m2.m[0][0] +
     m1.m[3][1] * m2.m[1][0] +
     m1.m[3][2] * m2.m[2][0] +
     m1.m[3][3] * m2.m[3][0],

    m1.m[3][0] * m2.m[0][1] +
     m1.m[3][1] * m2.m[1][1] +
     m1.m[3][2] * m2.m[2][1] +
     m1.m[3][3] * m2.m[3][1],

    m1.m[3][0] * m2.m[0][2] +
     m1.m[3][1] * m2.m[1][2] +
     m1.m[3][2] * m2.m[2][2] +
     m1.m[3][3] * m2.m[3][2],

    m1.m[3][0] * m2.m[0][3] +
     m1.m[3][1] * m2.m[1][3] +
     m1.m[3][2] * m2.m[2][3] +
     m1.m[3][3] * m2.m[3][3],
   ]
  );
 }
 // Rotate vector by 'Y'
 rotateY(a) {
  let A = D2R(a),
   si = sin(A),
   co = cos(A);

  return mat4([
   [co, 0, -si, 0],
   [0, 1, 0, 0],
   [si, 0, co, 0],
   [0, 0, 0, 1],
  ]);
 } // End of 'rotateY'

 // Rotate vector by 'X'
 rotateX(a) {
  let A = D2R(a),
   si = sin(A),
   co = cos(A);

  return mat4([
   [1, 0, 0, 0],
   [0, co, si, 0],
   [0, -si, co, 0],
   [0, 0, 0, 1],
  ]);
 } // End of 'rotateX'

 // Rotate vector by Z'
 rotateZ(a) {
  let A = D2R(a),
   si = sin(A),
   co = cos(A);

  return mat4([
   [co, si, 0, 0],
   [-si, co, 1, 0],
   [0, 0, 1, 0],
   [0, 0, 0, 1],
  ]);
 } // End of 'rotateZ'

 // Vector by matrix multiplication (with homogenious devide)
 mulvec(m, v) {
  let w = v.x * m.m[0][3] + v.y * m.m[1][3] + v.z * m.m[2][3] + m.m[3][3];

  return vec3(
   (v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0] + m.m[3][0]) / w,
   (v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1] + m.m[3][1]) / w,
   (v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2] + m.m[3][2]) / w
  );
 } // End of 'mulvec' function

 // Matrix frustum setup function.
 matrfrustum(left, right, bottom, top, near, far) {
  return mat4(
   [(2 * near) / (right - left), 0, 0, 0],
   [0, (2 * near) / (top - bottom), 0, 0],
   [
    (right + left) / (right - left),
    (top + bottom) / (top - bottom),
    (f + n) / (n - f),
    -1,
   ],
   [0, 0, (2 * near * far) / (near - far), 0]
  );
 } // End of 'MatrFrustum' function

 view(At, Up1) {
  let Dir = vec3.normolize(vec3.subvec(At, Loc)),//At.subvec(Loc).normalize(),
   Right = vec3.normalize(vec3.cross(Dir, Up1)),//Dir.cross(Up1).normalize(),
   Up = vec3.cross(Right, Dir);//Right.cross(Dir);

  return mat4(
   [Right.x, Up.x, -Dir.x, 0],
   [Right.y, Up.y, -Dir.y, 0],
   [Right.z, Up.z, -Dir.z, 0],
   [vec3.dot(-Loc, Right), vec3.dot(Up, -Loc), vce3.dot(Dir, Loc), 1]
  );
 }

 // Multiplay 3 matrixs
 mulmatr3(m1, m2, m3) {
  return mat4(mulmatr(mulmatr(m1, m2), m3));
 }
 // Scaling function
 scale(m) {
  return mat4([m.x, 0, 0, 0], [0, m.y, 0, 0], [0, 0, m.z], [0, 0, 0, 1]);
 }
} // End of '_mat4' class

// mat4 set function
export function mat4(...args) {
 return new _mat4(...args);
} // End of 'mat4' function
