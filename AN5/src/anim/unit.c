/* FILE NAME  : anim.c
 * PROGRAMMER : AN5
 * LAST UPDATE: 29.01.2024
 * PURPOSE    : Unit file.
 *              Unit functions.
 */

#include "anim/anim.h"

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       an5UNIT *Uni;
 *   - animation context:
 *       an5ANIM *Ani;
 * RETURNS: None.
 */
static VOID AN5_UnitInit( an5UNIT *Uni, an5ANIM *Ani )
{
} /* End of 'AN5_UnitInit' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       an5UNIT *Uni;
 *   - animation context:
 *       an5ANIM *Ani;
 * RETURNS: None.
 */
static VOID AN5_UnitClose( an5UNIT *Uni, an5ANIM *Ani )
{
} /* End of 'AN5_UnitClose' function */

/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       an5UNIT *Uni;
 *   - animation context:
 *       an5ANIM *Ani;
 * RETURNS: None.
 */

static VOID AN5_UnitResponse( an5UNIT *Uni, an5ANIM *Ani )
{
} /* End of 'AN5_UnitResponse' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       an5UNIT *Uni;
 *   - animation context:
 *       an5ANIM *Ani;
 * RETURNS: None.
 */
static VOID AN5_UnitRender( an5UNIT *Uni, an5ANIM *Ani )
{
} /* End of 'AN5_UnitRender' function */

/* Unit creation function.
 * ARGUMENTS:
 *   - unit structure size in bytes:
 *       INT Size;
 * RETURNS:
 *   (an5UNIT *) pointer to created unit.
 */
an5UNIT * AN5_AnimUnitCreate( INT Size )
{
  an5UNIT *Uni;

  /* Memory allocation */
  if (Size < sizeof(an5UNIT) || (Uni = malloc(Size)) == NULL)
    return NULL;
  memset(Uni, 0, Size);

  /* Setup unit methods */
  Uni->Init = (VOID *)AN5_UnitInit;
  Uni->Close = (VOID *)AN5_UnitClose;
  Uni->Response = (VOID *)AN5_UnitResponse;
  Uni->Render = (VOID *)AN5_UnitRender;

  return (an5UNIT *)Uni;
} /* End of 'AN5_ AnimUnitCreate' function */

/* End of 'unit.c' file */

