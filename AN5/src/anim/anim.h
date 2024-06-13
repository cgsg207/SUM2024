/* FILE NAME  : ANIM.C
 * PROGRAMMER : AN5
 * LAST UPDATE: 26.01.2024
 * PURPOSE: Animation sustem in computer graphic.
 */
#ifndef __anim_h__
#define __anim_h__

#include "rnd/rnd.h"

#define AN5_MAX_UNITS 3000

typedef struct tagan5UNIT an5UNIT;
typedef struct tagan5ANIM an5ANIM;


#define AN5_UNIT_BASE_FIELDS \
  VOID (*Init)( an5UNIT *Uni, an5ANIM *Ani );     \
  VOID (*Close)( an5UNIT *Uni, an5ANIM *Ani );    \
  VOID (*Response)( an5UNIT *Uni, an5ANIM *Ani ); \
  VOID (*Render)( an5UNIT *Uni, an5ANIM *Ani )

struct tagan5UNIT
{
  AN5_UNIT_BASE_FIELDS;
};

typedef struct tagan5ANIM
{
  HWND hWnd;
  HDC hDC;
  INT W, H;

  an5UNIT *Units[AN5_MAX_UNITS];
  INT NumOfUnits;

  /* Timer data */
  DBL
    GlobalTime, GlobalDeltaTime, /* Global time and interframe interval */
    Time, DeltaTime,             /* Time with pause and interframe interval */
    FPS;                         /* Frames per second value */
  BOOL
    IsPause;                      /* Pause flag */
  BYTE Keys[256];
  BYTE KeysClick[256];
};

/**/
extern an5ANIM AN5_Anim;
/* Animaton initialisation function.
 * Arguments:
 *   - window handle:
 *      HWND hWnd.
 * Returns: None.
*/
VOID AN5_AnimInit( HWND hWnd );

/* Animaton deinitialisation function.
 * Arguments: None.
 * Returns: None.
*/
VOID AN5_AnimCLose( VOID );

/* Animaton resize function.
 * Arguments:
 *   - Window  W, H:
 *      INT W, H.
 * Returns: None.
*/
VOID AN5_AnimResize( INT W, INT H );

/* Animaton copy frame to window function.
 * Arguments: None.
 * Returns: None.
*/
VOID AN5_AnimCopyFrame( VOID );

/* Animaton rendering function.
 * Arguments:
 *   - Window  W, H:
 *      INt W, H.
 * Returns: None.
*/
VOID AN5_AnimRender( VOID );

/* Animaton flip full screen function.
 * ARGUMENTS:
 *   - window handle:
 *       HWND hWnd;
 * RETURNS: None.
 */
VOID AN5_AnimFlipFullScreen( VOID );

/* Animaton add unit function.
 * Arguments:
 *   - Pointer to unit object:
 *      an5UINT * UNI.
 * Returns: None.
*/
VOID AN5_AnimUnitAdd( an5UNIT *Uni );

/* Unit creation function.
 * ARGUMENTS:
 *   - unit structure size in bytes:
 *       INT Size;
 * RETURNS:
 *   (an5UNIT *) pointer to created unit.
 */
an5UNIT * AN5_AnimUnitCreate( INT Size );

/***
 * Timer handle
 ***/

/* Timer initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AN5_TimerInit( VOID );

/* Timer response function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AN5_TimerResponse( VOID );


VOID AN5_AnimInputResponse( VOID );
#endif /* __anim_h__ */
/* End of 'anim.h' file */


