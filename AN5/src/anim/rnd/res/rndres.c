/* FILE NAME  : rndres.c
 * PROGRAMMER : AN5
 * LAST UPDATE: 09.02.2024
 * PURPOSE    : 3D animaton project.
 *              Rendering system implemention module.
 *              .
 */

#include "rndres.h"

/***
 * Common resource handle function
 ***/

/* Resourse initialisation function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AN5_RndResInit( VOID )
{
  AN5_RndUBOInit();
  AN5_RndTexInit();
  AN5_RndShdInit();
  AN5_RndMtlInit();
} /* End of 'AN5_RndResInit' function */

/* Resourse deinitialisation function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AN5_RndResClose( VOID )
{
  AN5_RndMtlClose();
  AN5_RndShdClose();
  AN5_RndTexClose();
  AN5_RndUBOClose();
} /* End of 'AN5_RndResClose' function */

/* END OF 'rndres.c' FILE */