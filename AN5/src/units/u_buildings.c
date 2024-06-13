 /* FILE NAME  : u_cow.c
 * PROGRAMMER : AN5
 * LAST UPDATE: 18.01.2024
 * PURPOSE    : 3D animation project.
 *              G3DM module.
 */

#include "units.h"

typedef struct tagan5UNIT_BUILDING
{
  AN5_UNIT_BASE_FIELDS;
  an5PRIMS Model;
} an5UNIT_BUILDING;

/* Building (G3DM) object unit innitialisation function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       an5UNIT_BUILDING *Uni;
 *   - animation context:
 *       an5ANIM *Ani;
 * RETURNS: None.
 */
static VOID AN5_UnitInit( an5UNIT_BUILDING *Uni, an5ANIM *Ani )
{
  AN5_RndPrimsLoad(&Uni->Model, "bin/models/Building_A02.g3dm");
} /* End of 'AN5_UnitInitCow' function */

/* Building object unit deinicialisation function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       an5UNIT_BUILDING *Uni;
 *   - animation context:
 *       an5ANIM *Ani;
 * RETURNS: None.
 */
static VOID AN5_UnitClose( an5UNIT_BUILDING *Uni, an5ANIM *Ani )
{
  AN5_RndPrimsFree(&Uni->Model);
} /* End of 'AN5_UnitClose' function */

/* Building object response function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       an5UNIT_BUILDING *Uni;
 *   - animation context:
 *       an5ANIM *Ani;
 * RETURNS: None.
 */
static VOID AN5_UnitResponse( an5UNIT_BUILDING *Uni, an5ANIM *Ani )
{
} /* End of 'AN5_UnitResponse' function */

/* Cow object draw function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       an5UNIT_BUILDING *Uni;
 *   - animation context:
 *       an5ANIM *Ani;
 * RETURNS: None.
 */
static VOID AN5_UnitRender( an5UNIT_BUILDING *Uni, an5ANIM *Ani )
{
  INT b, i = 1;

  for (b = -i; b <= i; b++)
  {
    AN5_RndPrimsDraw(&Uni->Model, MatrMulMatr(MatrRotateY(270),
                                  MatrTranslate(VecSet(0, -1, -17 + b * 15))));
  }
} /* End of 'AN5_UnitDraw' function */

/* G3DM object draw function.
 * ARGUMENTS: None.
 * RETURNS:
 *   - (an5UNIT) pointer to create unit.
 */
an5UNIT * AN5_UnitCreateG3DMBuilding2( VOID )
{
  an5UNIT *Uni;

  Uni = AN5_AnimUnitCreate(sizeof(an5UNIT_BUILDING));
  if (Uni == NULL)
    return NULL;

  Uni->Init = (VOID *)AN5_UnitInit;
  Uni->Close = (VOID *)AN5_UnitClose;
  Uni->Response = (VOID *)AN5_UnitResponse;
  Uni->Render = (VOID *)AN5_UnitRender;

  return (an5UNIT *)Uni;
} /* End of 'AN5_UnitCreateCowObject' file */

/* END OF 'u_cow.c' FILE */