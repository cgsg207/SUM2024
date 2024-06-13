/* FILE NAME  : rndtex.c
 * PROGRAMMER : AN5
 * LAST UPDATE: 21.02.2024
 * PURPOSE    : 3D animation project.
 *              Rendering system resourses.
 *              Textures handle module.
 */

#include <stdio.h>

#include "rndres.h"

/***
 * Texture function.
 ***/

an5TEXTURE AN5_RndTextures[AN5_MAX_TEXTURES]; /* Array of textures */
INT AN5_RndTexturesSize;                      /* Textures array store size */

/* Texture handle initialisation function.
 * ARGUMAENTS: None.
 * RETURNS: None.
 */
VOID AN5_RndTexInit( VOID )
{
  AN5_RndTexturesSize = 0;
} /* End of 'AN5_RndTexInit' function */

/* Texture handle deinitialisation function.
 * ARGUMAENTS: None.
 * RETURNS: None.
 */
VOID AN5_RndTexClose( VOID )
{
  INT i;

  for (i = 0; i < AN5_RndTexturesSize; i++)
    glDeleteTextures(1, &AN5_RndTextures[i].TexId);
  AN5_RndTexturesSize = 0;
} /* End of 'AN5_RndTexClose' function */

/* Add texture to stock function.
 * ARGUMENTS:
 *   - texture name:
 *       CHAR *Name;
 *   - texture size in pixels:
 *       INT W, H;
 *   - number of color components:
 *       INT C;
 *   - texture pixel data:
 *       VOID *Bits;
 * RETURNS:
 *   - (INT) texture stock number (0 if error is occused)
 */
INT AN5_RndTexAddImg( CHAR *Name, INT W, INT H, INT C, VOID *Bits )
{
  INT mips;

  if (AN5_RndTexturesSize >= AN5_MAX_TEXTURES)
    return -1;

  /* Allocate terxture space */
  glGenTextures(1, &AN5_RndTextures[AN5_RndTexturesSize].TexId);
  glBindTexture(GL_TEXTURE_2D, AN5_RndTextures[AN5_RndTexturesSize].TexId);

  mips = log(W > H ? W : H) / log(2);
  mips = mips < 1 ? 1 : mips;

  glTexStorage2D(GL_TEXTURE_2D, mips,
                 C == 4 ? GL_RGBA8 : C == 3 ? GL_RGB8 : GL_R8, W, H);
  /* Upload tetures */
  if (Bits != NULL)
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, W, H,
                    C == 4 ? GL_BGRA : C == 3 ? GL_BGR : GL_LUMINANCE, GL_UNSIGNED_BYTE, Bits);

  glGenerateMipmap(GL_TEXTURE_2D);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  strncpy(AN5_RndTextures[AN5_RndTexturesSize].Name, Name, AN5_STR_MAX -1);
  AN5_RndTextures[AN5_RndTexturesSize].W = W;
  AN5_RndTextures[AN5_RndTexturesSize].H = H;

  glBindTexture(GL_TEXTURE_2D, 0);

  return AN5_RndTexturesSize++;
} /* End of 'AN5_RndTexAddImg' function */

/* Load texture from .G24 file function.
 * ARGUMENTS:
 *   - file name:
 * RETURNS:
 *   - (INT) texture stock number (0 if error is occused)
 */
INT AN5_RndTexAddImgG24( CHAR *Name )
{
  unsigned char *img;
  FILE *F;
  INT w = 0, h = 0;

  if (AN5_RndTexturesSize >= AN5_MAX_TEXTURES)
    return -1;

  if ((F = fopen(Name, "rb")) != NULL)
  {
    fread(&w, 2, 1, F);
    fread(&h, 2, 1, F);

    if ((img = malloc(w * h * 3)) != NULL)
    {
      INT mips;

      fread(img, 3, w * h, F);

      glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

      mips = log(w > h ? w : h) / log(2);
      mips = mips < 1 ? 1 : mips;

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

      glTexStorage2D(GL_TEXTURE_2D, mips, GL_RGB8, w, h);
      glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, w, h, GL_BGR, GL_UNSIGNED_BYTE, img);

      glGenerateMipmap(GL_TEXTURE_2D);

      free(img);
    }
    fclose(F);
  }
  strncpy(AN5_RndTextures[AN5_RndTexturesSize].Name, Name, AN5_STR_MAX -1);
  AN5_RndTextures[AN5_RndTexturesSize].W = w;
  AN5_RndTextures[AN5_RndTexturesSize].H = h;

  glBindTexture(GL_TEXTURE_2D, 0);

  return AN5_RndTexturesSize++;
} /* End of 'AN5_RndTexAddImgG24' function */


/* Add texture to stock function.
 * ARGUMENTS:
 *   - texture file name:
 *       CHAR *FileName;
 * RETURNS:
 *   - (INT) texture stock number (0 if error is occused)
 */
INT AN5_RndTexAddFromFile( CHAR *FileName )
{
  return 1;
} /* End off 'AN5_RndTexAddFromFile' function */

/* END OF 'rndtex.c' FILE */