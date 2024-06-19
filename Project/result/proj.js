let gl = [];
// OpenGL initialization function
export function initGL() {
  canvas1 = document.getElementById("canvas1");
  canvas2 = document.getElementById("canvas2");

  canvas.addEventListener("keypress", keyboard);

  timer = new Timer();

  gl[0] = canvas1.getContext("webgl2");
  //gl[1] = canvas2.getContext("webgl2");

  gl[0].clearColor(0.3, 0.47, 0.8, 1);
  //gl[1].clearColor(0.3, 0.47, 0.8, 1);
}

function ChangeCoords(x, y) {
  let i, xc, yc;

  for (i = 0; i <= 10; i++) {
    if (x < 100 + i * 100 && x > 100 + (i - 1) * 100) xc = (i - 1) * 100 + 50;
  }

  for (i = 0; i <= 10; i++) {
    if (y < 100 + i * 100 && y > 100 + (i - 1) * 100) yc = (i - 1) * 100 + 50;
  }
  return vec2(xc, yc);
}
