/* FILE NAME  : rndgrid.c
 * PROGRAMMER : AN5
 * LAST UPDATE: 28.02.2024
 * PURPOSE    : 3D animation project.
 *              Marker darwing file.
 */

#include "rnd.h"

INT AN5_RndShdAddonI[4];
FLT AN5_RndShdAddonF[4];
VEC4 AN5_RndShdAddonV[4];

/*** Marker semiglobal data ***/
static an5PRIM
  AN5_RndMarkerPrimSphere; /* Sphere marker primitive */


/* Marker system initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AN5_RndMarkerInit( VOID )
{
  //an5MATERIAL mtl = AN5_RndMtlGetDef();

  AN5_RndPrimCreate(&AN5_RndMarkerPrimSphere, AN5_RND_PRIM_PATCH, NULL, 1, NULL, 0);
  AN5_RndMarkerPrimSphere.NumOfPatchPoints = 1;

} /* End of 'AN5_RndMarkerInit' function */

/* Marker system deinitialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AN5_RndMarkerClose( VOID )
{
  AN5_RndPrimFree(&AN5_RndMarkerPrimSphere);
} /* End of 'AN5_RndMarkerClose' function */


/* Draw sphere function.
 * ARGUMENTS:
 *   - sphere center point:
 *       VEC C;
 *   - sphere (ellipsoid) radiuses:
 *       VEC R;
 *   - sphere color:
 *       VEC Color;
 *   - transform matrix:
 *       MATR Transform;
* RETURNS: None.
 */
VOID AN5_RndMrkDrawSphere( VEC C, VEC R, VEC Color, MATR Transform )
{
  AN5_RndShdAddonV[0] = Vec4SetVec3(C, 0);
  AN5_RndShdAddonV[1] = Vec4SetVec3(R, 0);
  AN5_RndShdAddonV[2] = Vec4SetVec3(Color, 0);
  AN5_RndPrimDraw(&AN5_RndMarkerPrimSphere, Transform);
} /* End of 'AN5_RndMrkDrawSphere' function */

