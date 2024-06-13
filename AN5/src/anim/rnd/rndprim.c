/* FILE NAME  : rndprim.c
 * PROGRAMMER : AN5
 * LAST UPDATE: 17.01.2024
 * PURPOSE    : Primitives file.
 */

#include <string.h>
#include <stdio.h>

#include "anim/anim.h"
#include "anim/rnd/res/rndres.h"

/* Create primiteve function
 * ARGUMENTS:
 *   - Pointer on primiteve:
 *      an5PRIM *Pr;
 *   - Primitive type:
 *      an5PRIM_TYPE Type;
 *   - Vertex array:
 *      an5VERTEX *V;
 *   - Vertex array size:
 *      INT NoofV;
 *   - Index array:
 *      INT *I;
 *   - Index array size:
 *      INT NoofI;
 * RETURNS:
 *   - (BOOL) True if success, False otherwise.
 */
BOOL AN5_RndPrimCreate( an5PRIM *Pr, an5PRIM_TYPE Type, an5VERTEX *V, INT NoofV, INT *I, INT NoofI )
{
  memset(Pr, 0, sizeof(an5PRIM));

  glGenVertexArrays(1, &Pr->VA);

  /* Vertex data */
  if (V != NULL && NoofV != 0)
  {
    glBindVertexArray(Pr->VA);

    glGenBuffers(1, &Pr->VBuf);
    glBindBuffer(GL_ARRAY_BUFFER, Pr->VBuf);
    glBufferData(GL_ARRAY_BUFFER, sizeof(an5VERTEX) * NoofV, V, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, FALSE, sizeof(an5VERTEX),
                          (VOID *)0); /* position */
    glVertexAttribPointer(1, 2, GL_FLOAT, FALSE, sizeof(an5VERTEX),
                          (VOID *)sizeof(VEC)); /* texture cordinates */
    glVertexAttribPointer(2, 3, GL_FLOAT, FALSE, sizeof(an5VERTEX),
                          (VOID *)(sizeof(VEC) + sizeof(VEC2))); /* normal */
    glVertexAttribPointer(3, 4, GL_FLOAT, FALSE, sizeof(an5VERTEX),
                          (VOID *)(sizeof(VEC) * 2 + sizeof(VEC2))); /* color */
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
  }

  /* Index data */
  if (I !=NULL && NoofI != 0)
  {
    glGenBuffers(1, &Pr->IBuf);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Pr->IBuf);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(INT) * NoofI, I, GL_STATIC_DRAW);
    Pr->NumOfElements = NoofI;
  }
  else
    Pr->NumOfElements = NoofV;

  /* Set default transform (identity) */
  Pr->Trans = MatrIdentity();
  Pr->Type = Type;
  AN5_RndPrimEvalBB(&Pr->MinBB, &Pr->MaxBB, V, NoofV);
  return TRUE;
} /* End of 'AN5_RndPrimCreate' function */

/* Free primiteve function
 * ARGUMENTS:
 *   - Pointer on primiteve:
 *      an5Prim *Pr.
 * RETURNS: None.
 */
VOID AN5_RndPrimFree( an5PRIM *Pr )
{
  if (Pr->VA != 0)
  {
    glBindVertexArray(Pr->VA);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &Pr->VBuf);
    glBindVertexArray(0);
    glDeleteVertexArrays(1, &Pr->VA);
  }
  if (Pr->IBuf != 0)
    glDeleteBuffers(1, &Pr->IBuf);
  memset(Pr, 0, sizeof(an5PRIM));
}
/* End of 'AN5_RndPrimFree' function*/

/* Primitive vertex normals evaluate function.
 * ARGUMENTS:
 *   - Vertex array:
 *      an5VERTEX *V;
 *   - Vertex array size:
 *      INT NoofV;
 *   - Index array:
 *      INT *I;
 *   - Index array size:
 *      INT NoofI;
 * RETURNS: None.
 */
VOID AN5_RndPrimAutoNormals( an5VERTEX *V, INT NoofV, INT *I, INT NoofI )
{
  INT i;

  /* Set all vertex normals to zero */
  for (i = 0; i < NoofV; i++)
    V[i].N = VecSet(0, 0, 0);
  /* Eval normal for every facet */
  for (i = 0; i < NoofI; i += 3)
  {
    INT
      n0 = I[i], n1 = I[i + 1], n2 = I[i + 2];
    VEC
      p0 = V[n0].P,
      p1 = V[n1].P,
      p2 = V[n2].P,
      N = VecNormalize(VecCrossVec(VecSubVec(p1, p0), VecSubVec(p2, p0)));

    V[n0].N = VecAddVec(V[n0].N, N);
    V[n1].N = VecAddVec(V[n1].N, N);
    V[n2].N = VecAddVec(V[n2].N, N);
  }
  /* Normalize all vertex normals */
  for (i = 0; i < NoofV; i++)
    V[i].N = VecNormalize(V[i].N);
} /* End of 'AN5_RndPrimAutoNormals' function */

/* Primiteve bound box obtain function.
 * ARGUMENTS:
 *   - ponter to result min-max vectors:
 *       VEC *MinBB, *MaxBB;
 *   - Vertex array:
 *      an5VERTEX *V;
 *   - Vertex array size:
 *      INT NoofV;
 * RETURNS: None.
 */
VOID AN5_RndPrimEvalBB( VEC *MinBB, VEC *MaxBB, an5VERTEX *V, INT NoofV )
{
  INT i;

  *MinBB = *MaxBB = VecSet1(0);
  if (V == NULL || NoofV == 0)
    return;

  for (i = 1; i < NoofV; i++)
  {
    if (MinBB->X > V[i].P.X)
      MinBB->X = V[i].P.X;
    if (MaxBB->X < V[i].P.X)
      MaxBB->X = V[i].P.X;

    if (MinBB->Y > V[i].P.Y)
      MinBB->Y = V[i].P.Y;
    if (MaxBB->Y < V[i].P.Y)
      MaxBB->Y = V[i].P.Y;

    if (MinBB->Z > V[i].P.Z)
      MinBB->Z = V[i].P.Z;
    if (MaxBB->Z < V[i].P.Z)
      MaxBB->Z = V[i].P.Z;
  }
} /* End of 'AN5_RndPrimEvalBB' function */

/* Load primiteve function
 * ARGUMENTS:
 *   - Pointer on primiteve:
 *      an5Prim *Pr.
 *   - Pointer on file which we load:
 *      CHAR FileName.
 * RETURNS:
 *   - (BOOL) True if correct, False in other results.
 */
BOOL AN5_RndPrimLoad( an5PRIM *Pr, CHAR *FileName )
{
  FILE *F;
  INT nv = 0, nf = 0, size;
  INT *I;
  an5VERTEX *V;
  static CHAR Buf[10000];

  /* Set all primittive data fields to 0 */
  memset(Pr, 0, sizeof(an5PRIM));
  if ((F = fopen(FileName, "r")) == NULL)
    return FALSE;
  /* Count vertices and indices */
  while (fgets(Buf, sizeof(Buf) - 1, F) != NULL)
    if (Buf[0] == 'v' && Buf[1] == ' ')
      nv++;
    else if (Buf[0] == 'f' && Buf[1] == ' ')
    {
      INT n = 0;
      CHAR *ptr = Buf + 2, old = ' ';

      while (*ptr != 0)
        n += *ptr != ' ' && old == ' ', old = *ptr++;
      nf += n - 2;
  }

  size = sizeof(an5VERTEX) * nv + sizeof(INT) * nf * 3;
  if ((V = malloc(size)) == NULL)
  {
    fclose(F);
    return FALSE;
  }
  I = (INT *)(V + nv);

  /* Read model data */
  rewind(F);
  nv = nf = 0;
  while (fgets(Buf, sizeof(Buf) - 1, F) != NULL)
    if (Buf[0] == 'v' && Buf[1] == ' ')
    {
      DBL  x, y, z;

      sscanf(Buf + 2, "%lf %lf %lf", &x, &y, &z);
      V[nv].C = Vec4Set(0.8, 0.6, 0.29, 1);
      V[nv++].P = VecSet(x, y, z);

    }
    else if (Buf[0] == 'f' && Buf[1] == ' ')
    {
      INT n = 0, c = 0, c0 = 0, c1 = 0, c2 = 0;
      CHAR *ptr = Buf + 2, old = ' ';

      while (*ptr != 0)
      {
        if (*ptr != ' ' && old == ' ')
        {
          sscanf(ptr, "%d", &c);
          if (c < 0)
            c = nv + c;
          else
            c--;

          if (n == 0)
            c0 = c;
          else if (n == 1)
            c1 = c;
          else
          {
            /* add new triangle */
            I[nf++] = c0;
            I[nf++] = c1;
            I[nf++] = c;
            c1 = c;
          }
          n++;
        }
        old = *ptr++;
      }
    }
  fclose(F);
  AN5_RndPrimAutoNormals(V, nv, I, nf);
  AN5_RndPrimCreate(Pr, AN5_RND_PRIM_TRIMESH, V, nv, I, nf);
  return TRUE;
} /* End of 'AN5_RndPrimLoad' function */

/* Draw primiteve function
 * ARGUMENTS:
 *   - Pointer on primiteve:
 *      an5Prim *Pr.
 *   - Matrix for cordinates
 *      MATR World.
 * RETURNS: None.
 */
VOID AN5_RndPrimDraw( an5PRIM *Pr, MATR World )
{
  an5RND_UBO_PRIM PrimData;
  MATR
    w = MatrMulMatr(Pr->Trans, World),
    wnormal = MatrTranspose(MatrInverse(w)),
    wvp = MatrMulMatr(w, AN5_RndMatrVP);
  INT
    i,
    loc,
    ProgId,
    gl_prim_type = Pr->Type == AN5_RND_PRIM_LINES ? GL_LINES :
                   Pr->Type == AN5_RND_PRIM_TRIMESH ? GL_TRIANGLES :
                   Pr->Type == AN5_RND_PRIM_TRISTRIP ? GL_TRIANGLE_STRIP :
                   Pr->Type == AN5_RND_PRIM_LINESTRIP ? GL_LINE_STRIP :
                   Pr->Type == AN5_RND_PRIM_PATCH ? GL_PATCHES :
                   GL_POINTS;

  if ((ProgId = AN5_RndMtlApply(Pr->MtlNo)) == 0)
    return;

  memset(&PrimData, 0, sizeof(PrimData));

  /* PrimData.MatrW = w;
  PrimData.MatrWInv = wnormal;
  PrimData.MatrWVP = wvp;
  */
  for (i = 0; i < 4; i++)
  {
    PrimData.AddonI[i] = AN5_RndShdAddonI[i];
    PrimData.AddonF[i] = AN5_RndShdAddonF[i];
    PrimData.AddonV[i] = AN5_RndShdAddonV[i];
  }

  if ((loc = glGetUniformLocation(ProgId, "GlobalTime")) != -1)
    glUniform1f(loc, AN5_Anim.GlobalTime);

  if ((loc = glGetUniformLocation(ProgId, "MatrWVP")) != -1)
    glUniformMatrix4fv(loc, 1, FALSE, wvp.A[0]);
  if ((loc = glGetUniformLocation(ProgId, "MatrInv")) != -1)
    glUniformMatrix4fv(loc, 1, FALSE, wnormal.A[0]);
  if ((loc = glGetUniformLocation(ProgId, "MatrW")) != -1)
    glUniformMatrix4fv(loc, 1, FALSE, w.A[0]);
  if ((loc = glGetUniformLocation(ProgId, "AddonI")) != -1)
    glUniform1iv(loc, sizeof(AN5_RndShdAddonI) / sizeof(AN5_RndShdAddonI[0]), AN5_RndShdAddonI);

  //AN5_RndUBOUpdate(AN5_RndShdUBOPrimNo, 0, 0, &PrimData);

  glBindVertexArray(Pr->VA);
  if (Pr->Type == AN5_RND_PRIM_PATCH)
    glPatchParameteri(GL_PATCH_VERTICES, Pr->NumOfPatchPoints);

  /*glEnable(GL_PRIMITIVE_RESTART);
  glPrimitiveRestartIndex(-1);*/

  if (Pr->InstanceCnt < 2)
  {
    if (Pr->IBuf == 0)
      glDrawArrays(gl_prim_type, 0, Pr->NumOfElements);
    else
    {
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Pr->IBuf);
      glDrawElements(gl_prim_type, Pr->NumOfElements, GL_UNSIGNED_INT, NULL);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
  }
  else
  {
    if (Pr->IBuf == 0)
      glDrawArraysInstanced(gl_prim_type, 0, Pr->NumOfElements, Pr->InstanceCnt);
    else
    {
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Pr->IBuf);
      glDrawElementsInstanced(gl_prim_type, Pr->NumOfElements, GL_UNSIGNED_INT, NULL,
        Pr->InstanceCnt);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
  }
  glBindVertexArray(0);
  glUseProgram(0);
} /* End of 'AN5_RndPrimDraw' function*/

/* END OF 'rndprim.c' FILE */