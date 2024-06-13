/* FILE NAME  : u_cow.c
 * PROGRAMMER : AN5
 * LAST UPDATE: 18.01.2024
 * PURPOSE    : 3D animation project.
 *              G3DM module.
 */

#include "units.h"

#define AN5_MAX_BIRDS 18

#define AN5_MAX_BIRDS_H 30
typedef struct tagan5UNIT_G3DM
{
  AN5_UNIT_BASE_FIELDS;
  an5PRIMS Model[AN5_MAX_BIRDS];   /* Primitives */
  an5VERTEX Coords[AN5_MAX_BIRDS]; /* Array of birds coords */
} an5UNIT_BIRDS;

/* G3DM object unit innitialisation function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       an5UNIT_BIRDS *Uni;
 *   - animation context:
 *       an5ANIM *Ani;
 * RETURNS: None.
 */
static VOID AN5_UnitInit( an5UNIT_BIRDS *Uni, an5ANIM *Ani )
{
  an5MATERIAL *mtl1, *mtl2;

  if (AN5_RndPrimsLoad(&Uni->Model[0], "bin/models/Bird/SEAGUL.g3dm"))
  {
    mtl1 = AN5_RndMtlGet(Uni->Model[0].Prims[0].MtlNo);
    mtl1->ShdNo = AN5_RndShdAdd("seagul");
    Uni->Model[0].Prims[0].InstanceCnt = 5;
  }
  if (AN5_RndPrimsLoad(&Uni->Model[1], "bin/models/Bird/gull1.g3dm"))
  {
    mtl2 = AN5_RndMtlGet(Uni->Model[1].Prims[0].MtlNo);
    mtl2->ShdNo = AN5_RndShdAdd("bird1");
  }
  /*for (i = 0; i < AN5_MAX_BIRDS; i++)
    Uni->Coords[i].P = VecSet(rand() * 30.0, rand () * 2.0 * AN5_MAX_BIRDS_H, rand() * 47);*/
} /* End of 'AN5_UnitInitCow' function */

/* Cow object unit deinicialisation function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       an5UNIT_BIRDS *Uni;
 *   - animation context:
 *       an5ANIM *Ani;
 * RETURNS: None.
 */
static VOID AN5_UnitClose( an5UNIT_BIRDS *Uni, an5ANIM *Ani )
{
  INT i;

  for (i = 0; 0 < AN5_MAX_BIRDS; i++);
    AN5_RndPrimsFree(&Uni->Model[i]);
} /* End of 'AN5_UnitClose' function */

/* Object response function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       an5UNIT_BIRDS *Uni;
 *   - animation context:
 *       an5ANIM *Ani;
 * RETURNS: None.
 */
static VOID AN5_UnitResponse( an5UNIT_BIRDS *Uni, an5ANIM *Ani )
{
} /* End of 'AN5_UnitResponse' function */

/* Object draw function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       an5UNIT_BIRDS *Uni;
 *   - animation context:
 *       an5ANIM *Ani;
 * RETURNS: None.
 */
static VOID AN5_UnitRender( an5UNIT_BIRDS *Uni, an5ANIM *Ani )
{
  AN5_RndPrimsDraw(&Uni->Model[0], MatrMulMatr(MatrIdentity(), MatrScale(VecSet1(6))));
  //Uni->Model[0].Trans = MatrMulMatr(MatrRotateY(90), MatrRotateZ(90));
} /* End of 'AN5_UnitDraw' function */

/* G3DM object draw function.
 * ARGUMENTS: None.
 * RETURNS:
 *   - (an5UNIT) pointer to create unit.
 */
an5UNIT * AN5_UnitCreateG3DMObject( VOID )
{
  an5UNIT *Uni;

  Uni = AN5_AnimUnitCreate(sizeof(an5UNIT_BIRDS));
  if (Uni == NULL)
    return NULL;

  Uni->Init = (VOID *)AN5_UnitInit;
  Uni->Close = (VOID *)AN5_UnitClose;
  Uni->Response = (VOID *)AN5_UnitResponse;
  Uni->Render = (VOID *)AN5_UnitRender;

  return (an5UNIT *)Uni;
} /* End of 'AN5_UnitCreateCowObject' file */

/* END OF 'u_cow.c' FILE */