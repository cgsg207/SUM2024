let gl = [];
// OpenGL initialization function
export function initGL() {
  canvas1 = document.getElementById("canvas1");
  canvas2 = document.getElementById("canvas2");

  canvas.addEventListener("keypress", keyboard);

  timer = new Timer();

  gl[0] = canvas1.getContext("webgl2");
  gl[1] = canvas2.getContext("webgl2");

  gl[0].clearColor(0.3, 0.47, 0.8, 1);
  gl[1].clearColor(0.3, 0.47, 0.8, 1);
}
