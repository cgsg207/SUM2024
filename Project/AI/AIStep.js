/* FILE NAME  : AICreate.js
 * PROGRAMMER : AN5
 * LAST UPDATE: 20.06.2024
 * PURPOSE    : AI step file.
 */

/* Arrays: steps and posible steps */
let Steps = [];
let free = [];
/* Array of hits */
let hitArray = [];
/* Ai gsme step function.
 * ARGUMENTS: None;
 * RETURNS: None.
 */
function AIStep() {} /* End of "AIStep" function */

/* If AI hit players ships.
 * ARGUMENTS:
 *   - field coord:
 *       let coords(vec2);
 *   - message:
 *       let mes(bool);
 * RETURNS: None.
 */
function AIDamage(coords, mes) {
  if (mes == true) {
    hitArray[0] = vec2(coords.x, coords.y);
  }
} /* End of "AIDamage" function */
