let canvas, gl, timeLoc;

// OpenGL initialization function
export function initGL() {
  canvas = document.getElementById("myCan");
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
    vec2 Z = DrawPos;
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
    

    OutColor = OutColor;
  }
  `;
  // vec2 C = vec2(sin(Time * 1.2) * 0.05 + 0.3 , 0.05 * sin(Time * 0.5) + 0.3);
  //   vec2 D = vec2(cos(Time * 0.5) * 0.47 - 0.3 , 0.47 * sin(Time * 0.5));
  //   vec2 E = vec2(sin(Time * 0.5) / cos(Time * 0.5) * 0.47 - 0.3 , 0.47 * cos(Time * 0.5) / sin(Time * 0.5));
  // OutColor = vec4(DrawPos, 1.7, 1.3) * 2.5;
  // vec2(0.35 + 0.05 * sin(Time * 1.3), 0.35 + 0.05 * sin(Time * 0.8));

  // vec2 Z = DrawPos;
  //   vec2 Z0 = Z;

  //   vec2 F = vec2(sin(Time * 0.5) * 0.47 - 0.3, sin(Time * 0.5) * 0.47 + 0.3);
  //   float n = 0.0;

  //   while (n < 100.0 && length(Z) < 2.0)
  //   {
  //     Z = vec2(Z.x * Z.x  - Z.y * Z.y, 6.0 * Z.y * Z.x) + Z0;
  //     n++;
  //   }
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
    const date = new Date();
    let t =
      date.getMinutes() * 60 +
      date.getSeconds() +
      date.getMilliseconds() / 1000;

    gl.uniform1f(timeLoc, t);
  }
  gl.drawArrays(gl.TRIANGLE_STRIP, 0, 4);
} // End of 'render' function

console.log("FRACTAL");
