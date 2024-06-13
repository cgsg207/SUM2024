/* FILE NAME  : anim.c
 * PROGRAMMER : AN5
 * LAST UPDATE: 26.01.2024
 * PURPOSE    : Animation sustem in computer graphic.
 */

#include "anim/anim.h"

/**/
an5ANIM AN5_Anim;

/* Animaton initialisation function.
 * Arguments:
 *   - window handle:
 *      HWND hWnd.
 * Returns: None.
*/
VOID AN5_AnimInit( HWND hWnd )
{
  memset(&AN5_Anim, 0, sizeof(an5ANIM));

  /* Fill animation context */
  AN5_Anim.hWnd = hWnd;
  AN5_RndInit(hWnd);
  AN5_Anim.hDC = AN5_hRndDC;
  AN5_Anim.W = AN5_RndFrameW;
  AN5_Anim.H = AN5_RndFrameH;

  AN5_TimerInit();
} /* End of 'AN5_AnimInit' function */

/* Animaton deinitialisation function.
 * Arguments: None.
 * Returns: None.
*/
VOID AN5_AnimCLose( VOID )
{
  INT i;

  for (i = 0; i < AN5_Anim.NumOfUnits; i++)
  {
    AN5_Anim.Units[i]->Close(AN5_Anim.Units[i], &AN5_Anim);
    free(AN5_Anim.Units[i]);
  }
  AN5_RndClose();
  memset(&AN5_Anim, 0, sizeof(an5ANIM));
} /* End of 'AN5_AnimCLose' functon. */

/* Animaton rendering function.
 * Arguments:
 *   - Window  W, H:
 *      INt W, H.
 * Returns: None.
*/
VOID AN5_AnimRender( VOID )
{
  INT i;

  AN5_TimerResponse();


  /* Input request */
  AN5_AnimInputResponse();

  for (i = 0; i < AN5_Anim.NumOfUnits; i++)
    AN5_Anim.Units[i]->Response(AN5_Anim.Units[i], &AN5_Anim);
  AN5_RndStart();

  for (i = 0; i < AN5_Anim.NumOfUnits; i++)
    AN5_Anim.Units[i]->Render(AN5_Anim.Units[i], &AN5_Anim);
  AN5_RndEnd();
} /* End of 'AN5_AnimRender' function */

/* Animaton resize function.
 * Arguments:
 *   - Window  W, H:
 *      INT W, H.
 * Returns: None.
*/
VOID AN5_AnimResize( INT W, INT H )
{
  AN5_RndResize(W, H);
  AN5_Anim.W = W;
  AN5_Anim.H = H;
  AN5_AnimRender();
} /* End of 'AN5_AnimResize' function */


/* Animaton copy frame to window function.
 * Arguments: None.
 * Returns: None.
*/
VOID AN5_AnimCopyFrame( VOID )
{
  AN5_RndCopyFrame();
} /* End of 'AN5_AnimCopyFrame' function */

/* Animaton flip full screen function.
 * ARGUMENTS:
 *   - window handle:
 *       HWND hWnd;
 * RETURNS: None.
 */
VOID AN5_AnimFlipFullScreen( VOID )
{
  static BOOL IsFullScreen = FALSE; /* store current mode */
  static RECT SaveRC;               /* save old window size */

  if (!IsFullScreen)
  {
    HMONITOR hMon;
    MONITORINFOEX moninfo;
    RECT rc;

    IsFullScreen = TRUE;

    /* Save old window size and position */
    GetWindowRect(AN5_Anim.hWnd, &SaveRC);

    /* Get closest monitor */
    hMon = MonitorFromWindow(AN5_Anim.hWnd, MONITOR_DEFAULTTONEAREST);
    moninfo.cbSize = sizeof(moninfo);
    GetMonitorInfo(hMon, (MONITORINFO *)&moninfo);
 
    rc = moninfo.rcMonitor;
    AdjustWindowRect(&rc, GetWindowLong(AN5_Anim.hWnd, GWL_STYLE), FALSE);


    /* Restore window size and position */
    SetWindowPos(AN5_Anim.hWnd, HWND_TOP,
      rc.left, rc.top,
      rc.right - rc.left, rc.bottom - rc.top,
      SWP_NOOWNERZORDER);
  }
  else
  {
    IsFullScreen = FALSE;

    /* Restore window size and position */
    SetWindowPos(AN5_Anim.hWnd, HWND_NOTOPMOST,
      SaveRC.left, SaveRC.top,
      SaveRC.right - SaveRC.left, SaveRC.bottom - SaveRC.top,
      SWP_NOOWNERZORDER);
  }

} /* End of 'AN5_AnimFlipFullScreen' function */

/* Animaton add unit function.
 * Arguments:
 *   - Pointer to unit object:
 *      an5UINT * UNI.
 * Returns: None.
*/
VOID AN5_AnimUnitAdd( an5UNIT *Uni )
{
  if (AN5_Anim.NumOfUnits < AN5_MAX_UNITS)
    AN5_Anim.Units[AN5_Anim.NumOfUnits++] = Uni, Uni->Init(Uni, &AN5_Anim);
} /* End of 'AN5_AnimUnitAdd' function */

/* End of 'anim.c' file */