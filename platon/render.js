/* FILE NAME:   vec3.js
 * PROGRAMMER:  AN5
 * LAST UPDATE: 11.06.2024
 * PURPOSE:     Render.
 */

class _render {
  constructor(canvas, initRenderFunc) {
    if (typeof canvas == "string")
      canvas = document.getElementById(canvas);
    let gl = canvas.getContext("webgl2");
    this.gl = gl;
    /*  . . . */
    if (initRenderFunc)
      initRenderFunc(this);
  }
  loop(func) {
    const draw = () => {
      this.gl.clear(this.gl.COLOR_BUFFER_BIT |
                    this.gl.DEPTH_BUFFER_BIT);
      window.requestAnimationFrame(draw);
    }
    draw();
  }
  primCreate(...args) {
    return prim(this, ...args);
  } // End of 'primCreate' function
} // End of '_render' class
