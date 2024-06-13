/* FILE NAME  : PRIMS.C
 * PROGRAMMER : AN5
 * LAST UPDATE: 06.03.2024
 * PURPOSE    : 3D animation project.
 *              Prims module.
 */

#include <stdio.h>
#include "res/rndres.h"

/* Create array of primitives function.
 * ARGUMENTS:
 *   - pointer to primitives structure:
 *       an5PRIMS *Prs;
 *   - number of primitives to be add:
 *       INT NumOfPrims;
 * RETURNS:
 *   (BOOL) TRUE if successful, FALSE otherwise.
 */
BOOL AN5_RndPrimsCreate( an5PRIMS *Prs, INT NumOfPrims )
{
  memset(Prs, 0, sizeof(an5PRIMS));

  if ((Prs->Prims = malloc(sizeof(an5PRIM) * NumOfPrims)) == NULL)
    return FALSE;
  memset(Prs->Prims, 0, sizeof(an5PRIM) * NumOfPrims);
  Prs->NumOfPrims = NumOfPrims;
  Prs->Trans = MatrIdentity();
  return TRUE;
} /* End of 'AN5_RndPrimsCreate' function */

/* Load array of primitives from .G3DM fi;e function.
 * ARGUMENTS:
 *   - pointer to primitives structure:
 *       an5PRIMS *Prs;
 *   - file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (BOOL) TRUE if successful, FALSE otherwise.
 */
BOOL AN5_RndPrimsLoad( an5PRIMS *Prs, CHAR *FileName )
{
  FILE *F;
  INT flen;
  BYTE *mem, *ptr;
  DWORD Sign; /* == "G3DM" */
  DWORD NumOfPrims;
  DWORD NumOfMaterials;
  DWORD NumOfTextures;
  INT p, m, t;

  memset(Prs, 0, sizeof(an5PRIMS));

  /* Open file */
  if ((F = fopen(FileName, "rb")) == NULL)
    return FALSE;

  /* Obtain file length */
  fseek(F, 0, SEEK_END);
  flen = ftell(F);
  rewind(F);

  /* Allocate memory and load whole file to memory */
  if ((mem = malloc(flen)) == NULL)
  {
    fclose(F);
    return FALSE;
  }
  fread(mem, 1, flen, F);
  fclose(F);

  ptr = mem;
  /* Signature */
  Sign = *(DWORD *)ptr;
  ptr += 4;
  if (Sign != *(DWORD *)"G3DM")
  {
    free(mem);
    return FALSE;
  }
  NumOfPrims = *(DWORD *)ptr;
  ptr += 4;
  NumOfMaterials = *(DWORD *)ptr;
  ptr += 4;
  NumOfTextures = *(DWORD *)ptr;
  ptr += 4;

  if (!AN5_RndPrimsCreate(Prs, NumOfPrims))
  {
    free(mem);
    return FALSE;
  }

  /* Load primitives */
  for (p = 0; p < NumOfPrims; p++)
  {
    DWORD NumOfVertex;
    DWORD NumOfFaceIndexes; /* num of facets * 3 */
    DWORD MtlNo;            /* Material number */
    an5VERTEX *V;
    INT *Ind;

    NumOfVertex = *(DWORD *)ptr;
    ptr += 4;
    NumOfFaceIndexes = *(DWORD *)ptr;
    ptr += 4;
    MtlNo = *(DWORD *)ptr;
    ptr += 4;

    V = (an5VERTEX *)ptr;
    ptr += sizeof(an5VERTEX) * NumOfVertex;
    Ind = (INT *)ptr;
    ptr += sizeof(INT) * NumOfFaceIndexes;
    AN5_RndPrimCreate(&Prs->Prims[p], AN5_RND_PRIM_TRIMESH, V, NumOfVertex, Ind, NumOfFaceIndexes);
    Prs->Prims[p].MtlNo = AN5_RndMaterialsSize + MtlNo;
    if (p == 0)
      Prs->MinBB = Prs->Prims[p].MinBB, Prs->MaxBB = Prs->Prims[p].MaxBB;
    else
    {
      if (Prs->MinBB.X > Prs->Prims[p].MinBB.X)
        Prs->MinBB.X = Prs->Prims[p].MinBB.X;
      if (Prs->MaxBB.X < Prs->Prims[p].MaxBB.X)
        Prs->MaxBB.X = Prs->Prims[p].MaxBB.X;
 
      if (Prs->MinBB.Y > Prs->Prims[p].MinBB.Y)
        Prs->MinBB.Y = Prs->Prims[p].MinBB.Y;
      if (Prs->MaxBB.Y < Prs->Prims[p].MaxBB.Y)
        Prs->MaxBB.Y = Prs->Prims[p].MaxBB.Y;
 
      if (Prs->MinBB.Z > Prs->Prims[p].MinBB.Z)
        Prs->MinBB.Z = Prs->Prims[p].MinBB.Z;
      if (Prs->MaxBB.Z < Prs->Prims[p].MaxBB.Z)
        Prs->MaxBB.Z = Prs->Prims[p].MaxBB.Z;
    }
  }
  free(mem);
  return TRUE;
} /* End of 'AN5_RndPrimsLoad' function */

/* Delete array of primitives function.
 * ARGUMENTS:
 *   - pointer to primitives structure:
 *       an5PRIMS *Prs;
 * RETURNS: None.
 */
VOID AN5_RndPrimsFree( an5PRIMS *Prs )
{
  if (Prs->Prims != NULL)
    free(Prs->Prims);
  memset(Prs, 0, sizeof(an5PRIMS));
} /* End of 'AN5_RndPrimsFree' function */

/* Draw array of primitives function.
 * ARGUMENTS:
 *   - pointer to primitives structure:
 *       vg4PRIMS *Prs;
 *   - global transformation matrix:
 *       MATR World;
 * RETURNS: None.
 */
VOID AN5_RndPrimsDraw( an5PRIMS *Prs, MATR World )
{
  INT i;
  MATR m = MatrMulMatr(Prs->Trans, World);

  /* Draw all nontransparent primitives */
  AN5_RndShdAddonI[0] = Prs->NumOfPrims;
  for (i = 0; i < Prs->NumOfPrims; i++)
    if (AN5_RndMtlGet(Prs->Prims[i].MtlNo)->Trans == 1)
    {
      AN5_RndShdAddonI[1] = i;
      AN5_RndPrimDraw(&Prs->Prims[i], m);
    }
  /* Draw all transparent primitives */
  glEnable(GL_CULL_FACE);

  /* Draw all front-face-culling */
  glCullFace(GL_FRONT);
  for (i = 0; i < Prs->NumOfPrims; i++)
    if (AN5_RndMtlGet(Prs->Prims[i].MtlNo)->Trans != 1)
    {
      AN5_RndShdAddonI[1] = i;
      AN5_RndPrimDraw(&Prs->Prims[i], m);
    }
  /* Draw all back-face-culling */
  glCullFace(GL_BACK);
  for (i = 0; i < Prs->NumOfPrims; i++)
    if (AN5_RndMtlGet(Prs->Prims[i].MtlNo)->Trans != 1)
    {
      AN5_RndShdAddonI[1] = i;
      AN5_RndPrimDraw(&Prs->Prims[i], m);
    }
  glDisable(GL_CULL_FACE);
} /* End of 'AN5_RndPrimsDraw' function */

/* END OF 'prims.c' FILE*/
