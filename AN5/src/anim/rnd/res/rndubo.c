/* FILE NAME  : rndres.h
 * PROGRAMMER : AN5
 * LAST UPDATE: 09.02.2024
 * PURPOSE    : 3D animaton project.
 *              Rendering system imlemention module.
                Resourses implemention module.
 *              Uniform Buffer Object (UBO) handle functions.
 */

#include "rndres.h"

an5UBO AN5_RndUBOs[AN5_MAX_UBOS];
INT AN5_RndUBOsSize;              /* UBO array store size */

/* UBO handle initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AN5_RndUBOInit( VOID )
{
  AN5_RndUBOsSize = 0;
} /* End of 'AN5_RndUBOInit' function */

/* UBO handle deinitialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AN5_RndUBOClose( VOID )
{
  INT i;
 
  for (i = 0; i < AN5_RndUBOsSize; i++)
    glDeleteBuffers(1, &AN5_RndUBOs[i].UBOId);
  AN5_RndUBOsSize = 0;
} /* End of 'AN5_RndUBOClose' function */
 
/* Add UBO to stock function.
 * ARGUMENTS:
 *   - UBO name:
 *       CHAR *Name;
 *   - OpenGL UBO bind point:
 *       UINT BindPoint;
 *   - UBO size in bytes:
 *       INT Size;
 *   - UBO data:
 *       VOID *Bits;
 * RETURNS:
 *   (INT) UBO stock number (-1 if error is occured).
 */
INT AN5_RndUBOCreate( CHAR *Name, UINT BindPoint, INT Size, VOID *Bits )
{
  if (AN5_RndUBOsSize >= AN5_MAX_UBOS)
    return -1;

  glGenBuffers(1, &AN5_RndUBOs[AN5_RndUBOsSize].UBOId);
  glBindBuffer(GL_UNIFORM_BUFFER, AN5_RndUBOs[AN5_RndUBOsSize].UBOId);
  glBufferData(GL_UNIFORM_BUFFER, Size, NULL, GL_STATIC_DRAW);

  if (Bits != NULL)
    glBufferSubData(GL_UNIFORM_BUFFER, 0, Size, Bits);
  glBindBuffer(GL_UNIFORM_BUFFER, 0);

  /* Add to stock */
  AN5_RndUBOs[AN5_RndUBOsSize].Size = Size;
  AN5_RndUBOs[AN5_RndUBOsSize].BindPoint = BindPoint;
  strncpy(AN5_RndUBOs[AN5_RndUBOsSize].Name, Name, AN5_STR_MAX - 1);
  return AN5_RndUBOsSize++;
} /* End of 'AN5_RndUBOCreate' function */

/* UBO data update function.
 * ARGUMENTS:
 *   - UBO number in stock:
 *       INT UBONo;
 *   - UBO offset in bytes:
 *       INT Offset;
 *   - UBO update data size in bytes:
 *       INT Size;
 *   - UBO data ('Size' bytes):
 *       VOID *Bits;
 * RETURNS: None.
 */
VOID AN5_RndUBOUpdate( INT UBONo, INT Offset, INT Size, VOID *Bits )
{
  if (UBONo < 0 || UBONo >= AN5_RndUBOsSize)
    return;

  /* Update UBO data */
  if (Offset >= AN5_RndUBOs[UBONo].Size)
    return;
  if (Offset < 0)
    Offset = 0;
  if (Size == 0)
    Size = AN5_RndUBOs[UBONo].Size;
  if (Offset + Size >= AN5_RndUBOs[UBONo].Size)
    Size = AN5_RndUBOs[UBONo].Size - Offset;

  glBindBuffer(GL_UNIFORM_BUFFER, AN5_RndUBOs[UBONo].UBOId);
  glBufferSubData(GL_UNIFORM_BUFFER, Offset, Size, Bits);
  glBindBuffer(GL_UNIFORM_BUFFER, 0);
} /* End of 'AN5_RndUBOUpdate' function */

/* UBO apply function.
 * ARGUMENTS:
 *   - UBO number in stock:
 *       INT UBONo;
 * RETURNS: None.
 */
VOID AN5_RndUBOApply( INT UBONo )
{
  if (UBONo < 0 || UBONo >= AN5_RndUBOsSize)
    return;

  glBindBufferBase(GL_UNIFORM_BUFFER, AN5_RndUBOs[UBONo].BindPoint,
    AN5_RndUBOs[UBONo].UBOId);
} /* End of 'AN5_RndUBOApply' function */