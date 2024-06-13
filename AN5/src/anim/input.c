/* FILE NAME  : INPUT.C
 * PROGRAMMER : AN5
 * LAST UPDATE: 23.02.2024
 * PURPOSE    : 3D animation project.
 *              Input subsystem module.
 */

/*** 
 * Keyboard support.
 ***/

#include "anim/anim.h"

//#include <mmsytem.h>

//#pragma comment(lib, "winmm");

static BYTE KeysOld[256];

/* Keyboard input initialization function.
 * ARGUMENTS: None.
 *RETURNS: None.
 */
static VOID KeyboardInit( VOID )
{
  INT i;

  GetKeyboardState(AN5_Anim.Keys);
  for (i = 0; i < 256; i++)
    AN5_Anim.Keys[i] >>= 7;
  memcpy(KeysOld, AN5_Anim.Keys, 256);
} /* End of 'KeyboardInit' function */
/* Response keyboard function.
 * ARGUMENTS: None.
 * RETURNS: None.
*/
static VOID KeyboardResponse( VOID )
{
  INT i;

  GetKeyboardState(AN5_Anim.Keys);
  for (i = 0; i < 256; i++)
  {
    AN5_Anim.Keys[i] >>= 7;
    AN5_Anim.KeysClick[i] = AN5_Anim.Keys[i] && !KeysOld[i];
  }
  memcpy(KeysOld, AN5_Anim.Keys, 256);
} /* End of 'KeyboardResponse' function */

/* Input subsustem interframe response function.
 * ARGUMENTS: None.
 * RETURNS: None.
*/
VOID AN5_AnimInputResponse( VOID )
{
  KeyboardResponse();
} /* End of 'AN5_AnimInputResponse' function */

/* END OF 'input.c' FILE */
