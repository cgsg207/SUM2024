import { mat4 } from "./mat4.js";
import { vec3 } from "./vec3.js";
import { Cam } from "./camera.js";
import {render} from "./render.js"

let canvas, gl, timeLoc;

// OpenGL initialization function
export function initGL() {
  canvas = document.getElementById("myCan");
  gl = canvas.getContext("webgl2");
  gl.clearColor(0.3, 0.47, 0.8, 1);

  
  const posLoc = gl.getAttribLocation(prg, "InPosition");
  let vertexArray = gl.createVertexArray();
  gl.bindVertexArray(vertexArray);
  let vertexBuffer = gl.createBuffer();
  gl.bindBuffer(gl.ARRAY_BUFFER, vertexBuffer);
  gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(vertexes), gl.STATIC_DRAW);
  if (posLoc != -1) {
    gl.vertexAttribPointer(posLoc, 3, gl.FLOAT, false, 0, 0);
    gl.enableVertexAttribArray(posLoc);
  }

  // Uniform data
  timeLoc = gl.getUniformLocation(prg, "Time");

  gl.useProgram(prg);
} // End of 'initGL' function

function myOnLoad() {
  let canvas = document.getElementById("myCan");
  let prg;
  const rnd = render(canvas, (rnd) => {
    prg = rnd.CreatePrim({});
  });
  rnd.loop((rnd) => {
    rnd.Cam.CamSet(vec3(8), vec3(0), vec3(0, 1, 0));
    prg.transpose(mat4.RotateY()
  }
  )
}