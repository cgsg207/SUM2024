/* FILE NAME  : u_cow.c
 * PROGRAMMER : AN5
 * LAST UPDATE: 18.01.2024
 * PURPOSE    : Cow`s unit file.
 */

#include "units.h"

typedef struct tagan5UNIT_COW
{
  AN5_UNIT_BASE_FIELDS;
  an5PRIM Pr;
} an5UNIT_COW;

/* Cow object unit innitialisation function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       an5UNIT_COW *Uni;
 *   - animation context:
 *       an5ANIM *Ani;
 * RETURNS: None.
 */
static VOID AN5_UnitInit( an5UNIT_COW *Uni, an5ANIM *Ani )
{
  an5MATERIAL *mtl1;

  if (AN5_RndPrimLoad(&Uni->Pr, "bin/models/Bird/GULL.OBJ"))
  {
    mtl1 = AN5_RndMtlGet(15);
    mtl1->ShdNo = AN5_RndShdAdd("gull");
    /* Uni->Model[0].Prims[0].InstanceCnt = 5; */
  }
  if (Uni->Pr.NumOfElements > 0)
  {
    VEC B = VecSubVec(Uni->Pr.MaxBB, Uni->Pr.MinBB);
    MATR m = MatrTranslate(VecNeg(Uni->Pr.MaxBB));
    FLT sc = B.Z;

    if (sc < B.Y)
      sc = B.Y;
    if (sc < B.X)
      sc = B.X;
    m = MatrMulMatr(m, MatrScale(VecSet1(2 / sc)));
    Uni->Pr.Trans = m;
  }

  //Uni->Pr.MtlNo = AN5_RndMtlGetByName("Default");
} /* End of 'AN5_UnitInitCow' function */

/* Cow object unit deinicialisation function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       an5UNIT_COW *Uni;
 *   - animation context:
 *       an5ANIM *Ani;
 * RETURNS: None.
 */
static VOID AN5_UnitClose( an5UNIT_COW *Uni, an5ANIM *Ani )
{
  AN5_RndPrimFree(&Uni->Pr);
} /* End of 'AN5_UnitClose' function */

/* Cow object response function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       an5UNIT_COW *Uni;
 *   - animation context:
 *       an5ANIM *Ani;
 * RETURNS: None.
 */
static VOID AN5_UnitResponse( an5UNIT_COW *Uni, an5ANIM *Ani )
{
} /* End of 'AN5_UnitResponse' function */

/* Cow object draw function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       an5UNIT_COW *Uni;
 *   - animation context:
 *       an5ANIM *Ani;
 * RETURNS: None.
 */
static VOID AN5_UnitRender( an5UNIT_COW *Uni, an5ANIM *Ani )
{
  INT i = 3;

  AN5_RndPrimDraw(&Uni->Pr, MatrIdentity()/*MatrTranslate(VecSet(AN5_Anim.Time, AN5_Anim.Time / (AN5_Anim.Time + 1), cos(AN5_Anim.Time)))*/);
} /* En of 'AN5_UnitDraw' function */

/* Cow object draw function.
 * ARGUMENTS: None.
 * RETURNS:
 *   - (an5UNIT) pointer to create unit.
 */
an5UNIT * AN5_UnitCreateCowObject( VOID )
{
  an5UNIT *Uni;

  Uni = AN5_AnimUnitCreate(sizeof(an5UNIT_COW));
  if (Uni == NULL)
    return NULL;

  Uni->Init = (VOID *)AN5_UnitInit;
  Uni->Close = (VOID *)AN5_UnitClose;
  Uni->Response = (VOID *)AN5_UnitResponse;
  Uni->Render = (VOID *)AN5_UnitRender;

  return (an5UNIT *)Uni;
} /* End of 'AN5_UnitCreateCowObject' file */

/* END OF 'u_cow.c' FILE */