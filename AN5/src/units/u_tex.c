/* FILE NAME  : u_tex.c
 * PROGRAMMER : AN5
 * LAST UPDATE: 28.02.2024
 * PURPOSE    : 3D animation project.
 *              Texture view sample.
 */

#include <stdio.h>
#include <string.h>

#include "units.h"

/* Animationn representation type */
typedef struct tagan5UNIT_TEXSAMPLES
{
  AN5_UNIT_BASE_FIELDS;
  an5PRIM Pr;
  an5TEXTURE Tex;
} an5UNIT_TEXSAMPLES;

/* Unit initialisation function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       an5UNIT_TEXSAMPLES *Uni;
 *   - animation context:
 *       an5ANIM *Ani;
 * RETURNS: None.
 */
static VOID AN5_UnitInit( an5UNIT_TEXSAMPLES *Uni, an5ANIM *Ani )
{
  FILE *F;
  an5VERTEX V[] = 
  {
    {{0, 0, 0}, {0, 0}, {0, 0, 1}, {1, 1, 1, 1}},
    {{1, 0, 0}, {1, 0}, {0, 0, 1}, {1, 1, 1, 1}},
    {{0, 1, 0}, {0, 1}, {0, 0, 1}, {1, 1, 1, 1}},
    {{1, 1, 0}, {1, 1}, {0, 0, 1}, {1, 1, 1, 1}},
  };
  an5MATERIAL mtl = AN5_RndMtlGetDef();
  BYTE Txt[2][2] = {{255, 0}, {0, 255}};

  if ((F = fopen("X:/PICS/GRASS.G24", "rb")) != NULL)
  {
    INT w = 0, h = 0;
    BYTE *mem;

    fread(&w, 2, 1, F);
    fread(&h, 2, 1, F);

    if ((mem = malloc(w * h * 3)) != NULL)
    {
      fread(mem, 3, w * h, F);
      mtl.Tex[0] = AN5_RndTexAddImg("Sample", w, h, 3, mem);
      free(mem);
    }
    fclose(F);
  }
  else
    mtl.Tex[0] = AN5_RndTexAddImg("Sample", 2, 2, 1, Txt);

  AN5_RndPrimCreate(&Uni->Pr, AN5_RND_PRIM_TRISTRIP, V, 4, NULL, 0);

  strcpy(mtl.Name, "Texture sample");
  mtl.ShdNo = AN5_RndShdAdd("texture_sample");
  Uni->Pr.MtlNo = AN5_RndMtlAdd(&mtl);
} /* End of 'AN5_UnitInit' function */

/* Cow object unit deinicialisation function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       an5UNIT_TEXSAMPLES *Uni;
 *   - animation context:
 *       an5ANIM *Ani;
 * RETURNS: None.
 */
static VOID AN5_UnitClose( an5UNIT_TEXSAMPLES *Uni, an5ANIM *Ani )
{
  AN5_RndPrimFree(&Uni->Pr);
} /* End of 'AN5_UnitClose' function */

/* Control object response function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       an5UNIT_TEXSAMPLES *Uni;
 *   - animation context:
 *       an5ANIM *Ani;
 * RETURNS: None.
 */
static VOID AN5_UnitResponse( an5UNIT_TEXSAMPLES *Uni, an5ANIM *Ani )
{
} /* End of 'AN5_UnitResponse' function */

/* Cow object draw function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       an5UNIT_TEXSAMPLES *Uni;
 *   - animation context:
 *       an5ANIM *Ani;
 * RETURNS: None.
 */
static VOID AN5_UnitRender( an5UNIT_TEXSAMPLES *Uni, an5ANIM *Ani )
{
  INT c, o, i = 32;

  for (o = - i; o <= i ; o++)
    for (c = -i; c <= i ; c++)
      AN5_RndPrimDraw(&Uni->Pr, MatrMulMatr(MatrRotateX(90), MatrTranslate(VecDivNum(VecSet(o , -0.865, c), 1))));
} /* End of 'AN5_UnitDraw' function */

/* Texture sample creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   - (an5UNIT) pointer to create unit.
 */
an5UNIT * AN5_UnitCreateTexSample( VOID )
{
  an5UNIT *Uni;

  if ((Uni = AN5_AnimUnitCreate(sizeof(an5UNIT_TEXSAMPLES))) == NULL)
    return NULL;
  /* Setup unit methods */
  Uni->Init = (VOID *)AN5_UnitInit;
  Uni->Close = (VOID *)AN5_UnitClose;
  Uni->Response = (VOID *)AN5_UnitResponse;
  Uni->Render = (VOID *)AN5_UnitRender;
  return Uni;
} /* End of 'AN5_UnitCreateTexSample' file */

