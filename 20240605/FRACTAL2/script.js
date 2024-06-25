let canvas, gl, timeLoc;

// let r = 1.0;
// let g = 1.0;
// let b = 1.0;
let timer;

// function keyboard(event) {
//   if (event.key == "p") {
//     timer.isPause = !timer.isPause;
//   }
//   if (event.key == "c") {
//     r = 0.6;
//     g = 0.6;
//     b = 0.6;
//   }
// }

// OpenGL initialization function
export function initGL() {
  canvas = document.getElementById("myCan");
  // body = document.getElementById("body");

  // canvas.addEventListener("keypress", keyboard);

  timer = new Timer();

  gl = canvas.getContext("webgl2");
  gl.clearColor(0.3, 0.47, 0.8, 1);

  // Shader creation
  let vs_txt = `#version 300 es
  precision highp float;
  in vec3 InPosition;
       
  out vec2 DrawPos;
  uniform float Time;
 
  void main( void )
  {
    gl_Position = vec4(InPosition, 1);
    DrawPos = InPosition.xy;
  }
  `;
  let fs_txt = `#version 300 es
  precision highp float;
  out vec4 OutColor;
  
    in vec2 DrawPos;
    uniform float Time;
 
  void main( void )
  {
    vec2 Z = DrawPos * 1.5;
    vec2 Z0 = Z, C = vec2(0.35 * sin(Time * 0.5) + 0.07, 0.38);
    float n = 0.0;
    
    while (n < 500.0 && length(Z) < 2.0)
    {
      Z = vec2(Z.x * Z.x - Z.y * Z.y, 2.0 * Z.x * Z.y) + C;
      n++;
    }

    OutColor = vec4(DrawPos, 0.4, 1.0) + 0.5;
    OutColor.r = n / 255.0 * sin(Time);
    OutColor.g = n / 255.0;
    OutColor.b = n / 255.0;
    
    OutColor = OutColor + vec4(0.7, 0.8, 0.9, 1.0);
  }`;

  let vs = loadShader(gl.VERTEX_SHADER, vs_txt),
    fs = loadShader(gl.FRAGMENT_SHADER, fs_txt),
    prg = gl.createProgram();
  gl.attachShader(prg, vs);
  gl.attachShader(prg, fs);
  gl.linkProgram(prg);
  if (!gl.getProgramParameter(prg, gl.LINK_STATUS)) {
    let buf = gl.getProgramInfoLog(prg);
    console.log("Shader program link fail: " + buf);
  }

  // Vertex buffer creation
  const size = 0.8;
  const vertexes = [
    -size,
    size,
    0,
    -size,
    -size,
    0,
    size,
    size,
    0,
    size,
    -size,
    0,
  ];
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
  // redLoc = gl.getUniformLocation(prg, "r");
  // greenLoc = gl.getUniformLocation(prg, "g");
  // blueLoc = gl.getUniformLocation(prg, "b");

  // rgb = gl.getUniformLocation(prg, "color");

  gl.useProgram(prg);
} // End of 'initGL' function

// Load and compile shader function
function loadShader(shaderType, shaderSource) {
  const shader = gl.createShader(shaderType);
  gl.shaderSource(shader, shaderSource);
  gl.compileShader(shader);
  if (!gl.getShaderParameter(shader, gl.COMPILE_STATUS)) {
    let buf = gl.getShaderInfoLog(shader);
    console.log("Shader compile fail: " + buf);
  }
  return shader;
} // End of 'loadShader' function

let x = 1;

// Main render frame function
export function render() {
  // console.log(`Frame ${x++}`);
  gl.clear(gl.COLOR_BUFFER_BIT);

  if (timeLoc != -1) {
    timer.response();
    gl.uniform1f(timeLoc, timer.localTime);
  }

  // if (redLoc != -1) {
  //   gl.uniform1f(redLoc, r);
  // }
  // if (greenLoc != -1) {
  //   gl.uniform1f(greenLoc, g);
  // }
  // if (blueLoc != -1) {
  //   gl.uniform1f(blueLoc, b);
  // }
  gl.drawArrays(gl.TRIANGLE_STRIP, 0, 4);
} // End of 'render' function

export function Timer() {
  const getTime = () => {
    const date = new Date();
    let t =
      date.getMilliseconds() / 1000.0 +
      date.getSeconds() +
      date.getMinutes() * 60;
    return t;
  };

  this.response = (tag_id = null) => {
    let t = getTime();
    // Global time
    this.globalTime = t;
    this.globalDeltaTime = t - this.oldTime;
    // Time with pause
    if (this.isPause) {
      this.localDeltaTime = 0;
      this.pauseTime += t - this.oldTime;
    } else {
      this.localDeltaTime = this.globalDeltaTime;
      this.localTime = t - this.pauseTime - this.startTime;
    }
    // FPS
    this.frameCounter++;
    if (t - this.oldTimeFPS > 3) {
      this.FPS = this.frameCounter / (t - this.oldTimeFPS);
      this.oldTimeFPS = t;
      this.frameCounter = 0;
      if (tag_id != null)
        document.getElementById(tag_id).innerHTML = this.getFPS();
    }
    this.oldTime = t;
  };

  // Obtain FPS as string method
  this.getFPS = () => this.FPS.toFixed(3);

  // Fill timer global data
  this.globalTime = this.localTime = getTime();
  this.globalDeltaTime = this.localDeltaTime = 0;

  // Fill timer semi global data
  this.startTime = this.oldTime = this.oldTimeFPS = this.globalTime;
  this.frameCounter = 0;
  this.isPause = false;
  this.FPS = 30.0;
  this.pauseTime = 0;

  return this;
} // End of 'Timer' function

console.log(`number: %d`, Math.random() * 9);
