/* FILE NAME:   camera.js
 * PROGRAMMER:  AN5
 * LAST UPDATE: 08.06.2024
 * PURPOSE:     camera functions library for rendering.
 */

import * as mat4 from "./mat4.js";
import * as vec3 from "./vec3.js";

export class Cam {
 constructor() {
  this.Loc = 0;
  this.At = 0;
  this.Dir = 0;
  this.Right = 0;
  this.Up = 0;
  this.MatrView = 0;
  this.MatrProj = 0;
  this.MatrVP = 0;
  this.Wp = 0;
  this.Hp = 0;
  this.ProjSize = 0;
  this.ProjDist = 0;
  this.ProjFarClip = 0;
  this.FrameW = 0;
  this.FrameH = 0;
 } // End of 'Cam' constructor
 CamSet(Loc, At, Up) {
  MatrView = mat4().MatrView(Loc, At, Up);

  Cam.Right = vec3(MatrView.m[0][0], MatrView.m[1][0], MatrView.m[2][0]);
  Cam.Up = vec3(MatrView.m[0][1], MatrView.m[1][1], MatrView.m[2][1]);
  Cam.Dir = Vec3Set(-MatrView.m[0][2], -MatrView.m[1][2], -MatrView.m[2][2]);
  Cam.Loc = Loc;
  Cam.At = At;

  Cam.MatrVP = mat4().MatrView(MatrProj);
 } /* End of 'CamSet' function */
 CamSetProj(ProjSize, ProjDist, ProjFarClip) {
  let rx, ry;

  Cam.ProjDist = ProjDist;
  Cam.ProjFarClip = ProjFarClip;
  rx = ry = Cam.ProjSize = ProjSize;

  /* Correct aspect ratio */
  if (Cam.FrameW >= Cam.FrameH) rx *= Cam.FrameW / Cam.FrameH;
  else ry *= Cam.FrameH / Cam.FrameW;

  Cam.Wp = rx;
  Cam.Hp = ry;
  Cam.MatrProj = mat4().MatrFrustum(
   -rx / 2,
   rx / 2,
   -ry / 2,
   ry / 2,
   Cam.ProjDist,
   Cam.ProjFarClip
  );
  Cam.MatrVP = mat4().Cam.MatrView.mulmatr(Cam.MatrProj);
 } /* End of 'CamSetProj' function */

 CamSetSize(FrameW, FrameH) {
  Cam.FrameW = FrameW;
  Cam.FrameH = FrameH;
  Cam.CamSetProj(Cam, Cam.ProjSize, Cam.ProjDist, Cam.ProjFarClip);
 } /* End of 'CamSetSize' function */
}
