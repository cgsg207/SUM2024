/* FILE NAME  : main.js
 * PROGRAMMER : AN5
 * LAST UPDATE: 15.06.2024
 * PURPOSE    :
 */

let inf = 100000;
let vert = [];
let inter = [];

/* Find intection */
function intection(v1, v2) {
  let s;

  s = (v1.y + v1.x * v1.x - (v2.y + v2.x * v2.x)) / (2 * v1.x - 2 * v2.x);
  return s;
}

/* Marching porables */
function marchP() {
  let i;
}

function BottomlinePorables(array) {
  let k;

  vert[0] = vec2();
  for (k = 0; k < array.lenth; k++) {
    let z = vec2(i, array[i]);
  }
}

// def find_hull_parabolas(single_row, hull_vertices, hull_intersections):
//     d = single_row
//     v = hull_vertices
//     z = hull_intersections
//     k = 0
//     v[0].x = 0
//     z[0].x = -INF
//     z[1].x = +INF
//     for i in range(1, len(d)):
//         q = (i, d[i])
//         p = v[k]
//         s = intersect_parabolas(p, q)
//         while s.x <= z[k].x:
//             k = k - 1
//             p = v[k]
//             s = intersect_parabolas(p, q)
//         k = k + 1
//         v[k] = q
//         z[k].x = s.x
//         z[k + 1].x = +INF

/* Transpose image */
function transpose(img) {}

/* go by hieght */
function stepWidth() {}

/* Result function */
export function result() {
  let i;
  // ....
  transpose(img);

  //...
  transpose(img);
}
