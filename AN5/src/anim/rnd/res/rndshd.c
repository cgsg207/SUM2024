/* FILE NAME  : rndshd.c
 * PROGRAMMER : AN5
 * LAST UPDATE: 21.02.2024
 * PURPOSE    : 3D animation project.
 *              Rendering system resourses.
 *              Shaders handle module.
 */

#include <stdio.h>
#include "rndres.h"

/* Maximum shader include files */
#define AN5_MAX_SHADERS_FILES 30

/***
 * Shaders handle functions
 ***/

an5SHADER AN5_RndShaders[AN5_MAX_SHADERS]; /* Array of shaders */
INT AN5_RndShadersSize;

/* Loud defalt shader function
 * ARGUMENTS: None.
 * RETURNS: None.
*/
VOID AN5_RndShdInit( VOID )
{
  AN5_RndShadersSize = 0;
  AN5_RndShdAdd("default");
} /* End of 'AN5_RndShdInit' function */

/* Upload all shaders.
 * ARGUMENTS: None.
 * RETURNS: None.
*/
VOID AN5_RndShdClose( VOID )
{
  INT i;

  for (i = 0; i < AN5_RndShadersSize; i++)
    AN5_RndShdFree(AN5_RndShaders[AN5_RndShadersSize].ProgId);
  AN5_RndShadersSize = 0;
} /* End of 'AN5_RndShdClose' function */

/* Stores in an array function
 * ARGUMENTS:
 *   - Shader name:
 *       CHAR *ShaderFileNamePrefix;
 * RETURNS:
 *   (CHAR *) returns the number of the added shader in an array(RndShaders).
 */
INT AN5_RndShdAdd( CHAR *ShaderFileNamePrefix )
{
  INT i;

  /* Look for existed shader */
  for (i = 0; i < AN5_RndShadersSize; i++)
    if (strcmp(ShaderFileNamePrefix, AN5_RndShaders[i].Name) == 0)
      return i;
  /* Add a new one */
  if (AN5_RndShadersSize >= AN5_MAX_SHADERS)
    return 0;
  strncpy(AN5_RndShaders[AN5_RndShadersSize].Name, ShaderFileNamePrefix,
          AN5_STR_MAX);
  AN5_RndShaders[AN5_RndShadersSize].ProgId =
    AN5_RndShdLoad(ShaderFileNamePrefix);
  return AN5_RndShadersSize++;
} /* End of 'AN5_RndShdAdd' function */

/* Update all shaders function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AN5_RndShdUpdate( VOID )
{
  INT i;

  for (i = 0; i < AN5_RndShadersSize; i++)
  {
    AN5_RndShdFree(AN5_RndShaders[i].ProgId);
    AN5_RndShaders[i].ProgId = AN5_RndShdLoad(AN5_RndShaders[i].Name);
  }
} /* End of 'AN5_RndShdUpdate' function */

/* Load text from file function.
 * ARGUMENTS:
 *   - file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (CHAR *) loaded text (allocated through 'malloc') or NULL (if error is occured).
 */
static CHAR * AN5_RndShdLoadTextFromFile( CHAR *FileName )
{
  FILE *F;
  INT flen;
  CHAR *txt;

  if ((F = fopen(FileName, "rb")) == NULL)
    return NULL;

  /* Get file length */
  fseek(F, 0, SEEK_END);
  flen = ftell(F);

  /* Allocate memory */
  if ((txt = malloc(flen + 1)) == NULL)
  {
    fclose(F);
    return NULL;
  }

  /* Read text from file */
  rewind(F);
  fread(txt, 1, flen, F);
  txt[flen] = 0;

  fclose(F);
  return txt;
} /* End of 'AN5_RndShdLoadTextFromFile' function */


/* Store shader log to file function.
 * ARGUMENTS:
 *   - shader directory files prefix:
 *       CHAR *FileNamePrefix;
 *   - shader handle part name:
 *       CHAR *Part;
 *   - loggin text:
 *       CHAR *Text;
 * RETURNS: None.
 */
static VOID AN5_RndShdLog( CHAR *FileNamePrefix, CHAR *Part, CHAR *Text )
{
  FILE *F;
 
  if ((F = fopen("bin/shaders/AN5{30}SHD.LOG", "a")) == NULL)
    return;
  fprintf(F, "%s/%s\n%s\n", FileNamePrefix, Part, Text);
  fclose(F);
} /* End of 'AN5_RndShdLog' function */

/* Shader program load function.
 * ARGUMENTS:
 *   - shader directory files prefix (base from 'bin/shaders/'):
 *       CHAR *FileNamePrefix;
 * RETURNS:
 *   (INT) OpenGL shader program index (0 if error is occured).
 */
INT AN5_RndShdLoad( CHAR *FileNamePrefix )
{
  INT prg = 0, txt_size = 0, txt_common_size = 0, bufline_size = 0;
  CHAR *chr_pos, *txt[AN5_MAX_SHADERS_FILES];
  BOOL isok = TRUE;
  struct
  {
    CHAR *Name;   /* Shader name */
    INT Type;     /* Shader OpenGL type (see GL_***_SHADER) */
    CHAR *Define; /* Mandatory define and shader version */
    INT Id;       /* Result shader OpenGL Id */
  } shds[] =
  {
    {"vert", GL_VERTEX_SHADER, "#version 460\n#define VERTEX_SHADER 1\n"},
    {"frag", GL_FRAGMENT_SHADER, "#version 460\n#define FRAGMENT_SHADER 1\n"},
    {"geom", GL_GEOMETRY_SHADER, "#version 460\n#define GEOMETRY_SHADER 1\n"},
    {"ctrl", GL_TESS_CONTROL_SHADER, "#version 460\n#define TESS_CONTROL_SHADER 1\n"},
    {"eval", GL_TESS_EVALUATION_SHADER, "#version 460\n#define TESS_EVALUATION_SHADER 1\n"},
  };
  INT i, res, NoofS = sizeof(shds) / sizeof(shds[0]);
  static CHAR Buf[30000], Buf1[300], BufLine[AN5_MAX_SHADERS_FILES / 2][102];

  /* Skip '#version' line */
  txt_size++;

  /* Load 'commondf.glsl' */
  if ((txt[txt_size + 1] = AN5_RndShdLoadTextFromFile("bin/shaders/includes/commondf.glsl")) != NULL)
  {
    txt[txt_size++] = "\n";/*"#line 1 \"commondf.glsl\"\n"; /* \commondf.glsl\" */
    txt_size++;
  }

  /* Load local 'incl.glsl' files */
  chr_pos = FileNamePrefix;
  do
  {
    chr_pos = strchr(chr_pos, '/');
    strcpy(Buf1, FileNamePrefix);
    if (chr_pos != NULL)
      Buf1[chr_pos++ - FileNamePrefix] = 0;
    sprintf(Buf, "bin/shaders/%s/incl.glsl", Buf1);
    if ((txt[txt_size + 1] = AN5_RndShdLoadTextFromFile(Buf)) != NULL)
    {
      sprintf(BufLine[bufline_size], "\n""#line 1 \"%s/incl.glsl\"\n", Buf1);
      txt[txt_size++] = BufLine[bufline_size++];
      txt_size++;
    }
  } while (chr_pos != NULL);

  for (i = 0; i < NoofS; i++)
  {
    txt[0] = shds[i].Define;
    /* Load file */
    sprintf(Buf, "bin/shaders/%s/%s.glsl", FileNamePrefix, shds[i].Name);
    txt[txt_size + 1] = AN5_RndShdLoadTextFromFile(Buf);
    sprintf(Buf, "\n"/*"#line 1 \"%s/%s.glsl\"\n"; \%s/%s.glsl\" */, FileNamePrefix, shds[i].Name);
    txt[txt_size] = Buf;
    if (txt[txt_size + 1] == NULL)
    {
      if (i >= 2)
        continue;
      AN5_RndShdLog(FileNamePrefix, shds[i].Name, "Error load file");
      isok = FALSE;
      break;
    }
    /* Create shader */
    if ((shds[i].Id = glCreateShader(shds[i].Type)) == 0)
    {
      AN5_RndShdLog(FileNamePrefix, shds[i].Name, "Error shader creation");
      free(txt[txt_size + 1]);
      isok = FALSE;
      break;
    }
    /* Send text to shader for compile */
    glShaderSource(shds[i].Id, txt_size + 2, txt, NULL);
    free(txt[txt_size + 1]);

    /* Compile shader */
    glCompileShader(shds[i].Id);
    glGetShaderiv(shds[i].Id, GL_COMPILE_STATUS, &res);
    if (res != 1)
    {
      glGetShaderInfoLog(shds[i].Id, sizeof(Buf), &res, Buf);
      AN5_RndShdLog(FileNamePrefix, shds[i].Name, Buf);
      isok = FALSE;
      break;
    }
  }

  while (txt_size-- > 1)
    free(txt[txt_size--]);

  /* Create program */
  if (isok)
    if ((prg = glCreateProgram()) == 0)
    {
      AN5_RndShdLog(FileNamePrefix, "PROG", "Error program creation");
      isok = FALSE;
    }
    else
    {
      /* Attach shaders to program */
      for (i = 0; i < NoofS; i++)
        if (shds[i].Id != 0)
          glAttachShader(prg, shds[i].Id);

      /* Link program */
      glLinkProgram(prg);
      glGetProgramiv(prg, GL_LINK_STATUS, &res);
      if (res != 1)
      {
        glGetProgramInfoLog(prg, sizeof(Buf), &res, Buf);
        AN5_RndShdLog(FileNamePrefix, "PROG", Buf);
        isok = FALSE;
      }
    }

  if (!isok)
  {
    /* Handle errors */

    /* Delete shaders */
    for (i = 0; i < NoofS; i++)
      if (shds[i].Id != 0)
      {
        if (prg != 0)
          glDetachShader(prg, shds[i].Id);
        glDeleteShader(shds[i].Id);
      }
    /* Delete program */
    if (prg != 0)
      glDeleteProgram(prg);
    prg = 0;
  }

  return prg;
} /* END OF 'AN5_RndShdLoad' FUNCTION */

/* Shader program free function.
 * ARGUMENTS:
 *   - shader program Id:
 *       INT Prg;
 * RETURNS: None.
 */
VOID AN5_RndShdFree( INT Prg )
{
  INT shds[5] = {0}, n, i;

  if (Prg == 0 || !glIsProgram(Prg))
    return;
  glGetAttachedShaders(Prg, 5, &n, shds);
  /* Delete shaders */
  for (i = 0; i < n; i++)
    if (shds[i] != 0 && glIsShader(shds[i]))
    {
      glDetachShader(Prg, shds[i]);
      glDeleteShader(shds[i]);
    }
  /* Delete program */
  glDeleteProgram(Prg);
} /* End of 'AN5_RndShdFree' function */

/* END OF 'rndshd.c' FILE */