/* FILE NAME  : U_CTRL.C
 * PROGRAMMER : AN5
 * LAST UPDATE: 18.01.2024
 * PURPOSE    : Control unit file.
 */

#include <stdio.h>

#include "units.h"
#include "anim/anim.h"

typedef struct tagan5UNIT_CONTROL
{
  AN5_UNIT_BASE_FIELDS;
} an5UNIT_CONTROL;

/* Control object unit innitialisation function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       an5UNIT_CONTROL *Uni;
 *   - animation context:
 *       an5ANIM *Ani;
 * RETURNS: None.
 */
static VOID AN5_UnitInit( an5UNIT_CONTROL *Uni, an5ANIM *Ani )
{
  AN5_RndCamSet(AN5_RndCamLoc = VecSet1(9), VecSet1(0), VecSet(0, 1, 0));
}

/* Cow object unit deinicialisation function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       an5UNIT_COW *Uni;
 *   - animation context:
 *       an5ANIM *Ani;
 * RETURNS: None.
 */
static VOID AN5_UnitClose( an5UNIT_CONTROL *Uni, an5ANIM *Ani )
{
} /* End of 'AN5_UnitClose' function */

/* Control object response function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       an5UNIT_CONTROL *Uni;
 *   - animation context:
 *       an5ANIM *Ani;
 * RETURNS: None.
 */
static VOID AN5_UnitResponse( an5UNIT_CONTROL *Uni, an5ANIM *Ani )
{
  if (Ani->Keys[VK_CONTROL])
  {
    AN5_RndCamLoc =
      VecAddVec(AN5_RndCamLoc, 
       VecMulNum(AN5_RndCamDir, Ani->GlobalDeltaTime * 10 * (Ani->Keys[VK_PRIOR] - Ani->Keys[VK_NEXT])));
    AN5_RndCamLoc =
      VecAddVec(AN5_RndCamLoc, 
      VecMulNum(AN5_RndCamRight, Ani->GlobalDeltaTime * 10 * (Ani->Keys[VK_RIGHT] - Ani->Keys[VK_LEFT])));
    AN5_RndCamLoc =
      VecAddVec(AN5_RndCamLoc, 
      VecMulNum(AN5_RndCamUp, Ani->GlobalDeltaTime * 10 * (Ani->Keys[VK_UP] - Ani->Keys[VK_DOWN])));
  }
  if (Ani->Keys['w'])
    AN5_RndIsWireFrame = !AN5_RndIsWireFrame;
  if (Ani->Keys['p'])
    AN5_Anim.IsPause = !AN5_Anim.IsPause;
  if (Ani->Keys['f'])
    AN5_AnimFlipFullScreen();
  AN5_RndCamSet(AN5_RndCamLoc, VecSet1(0), VecSet(0, 1, 0));
} /* End of 'AN5_UnitResponse' function */

/* Cow object draw function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       an5UNIT_COW *Uni;
 *   - animation context:
 *       an5ANIM *Ani;
 * RETURNS: None.
 */
static VOID AN5_UnitRender( an5UNIT_CONTROL *Uni, an5ANIM *Ani )
{
} /* End of 'AN5_UnitDraw' function */

/* Control create function.
 * ARGUMENTS: None.
 * RETURNS:
 *   - (an5UNIT) pointer to create unit.
 */
an5UNIT * AN5_UnitCreateControl( VOID )
{
  an5UNIT *Uni;

  if ((Uni = AN5_AnimUnitCreate(sizeof(an5UNIT_CONTROL))) == NULL)
    return NULL;
  Uni->Init = (VOID *)AN5_UnitInit;
  Uni->Close = (VOID *)AN5_UnitClose;
  Uni->Response = (VOID *)AN5_UnitResponse;
  Uni->Render = (VOID *)AN5_UnitRender;
  return Uni;
} /* End of 'AN5_UnitCreateControl' file */
