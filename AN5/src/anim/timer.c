/* FILE NAME  : timer.c
 * PROGRAMMER : AN5
 * LAST UPDATE: 22.01.2024
 * PURPOSE    : Timer file.
 */

#include "anim.h"

static UINT64
  StartTime,    /* Start program time */
  OldTime,      /* Previous frame time */
  OldTimeFPS,   /* Old time FPS measurement */
  PauseTime,    /* Time during pause period */
  TimePerSec,   /* Timer resolution */
  FrameCounter; /* Frames counter */

/* Timer initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AN5_TimerInit( VOID )
{
  LARGE_INTEGER t;

  QueryPerformanceFrequency(&t);
  TimePerSec = t.QuadPart;
  QueryPerformanceCounter(&t);
  StartTime = OldTime = OldTimeFPS = t.QuadPart;
  FrameCounter = 0;
  AN5_Anim.IsPause = FALSE;
  AN5_Anim.FPS = 30.0;
  PauseTime = 0;
} /* End of 'AN5_TimerResponse' function */

/* Timer response function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AN5_TimerResponse( VOID )
{
  LARGE_INTEGER t;

  QueryPerformanceCounter(&t);
  /* Global time */
  AN5_Anim.GlobalTime = (DBL)(t.QuadPart - StartTime) / TimePerSec;
  AN5_Anim.GlobalDeltaTime = (DBL)(t.QuadPart - OldTime) / TimePerSec;
  /* Time with pause */
  if (AN5_Anim.IsPause)
  {
    AN5_Anim.DeltaTime = 0;
    PauseTime += t.QuadPart - OldTime;
  }
  else
  {
    AN5_Anim.DeltaTime = AN5_Anim.GlobalDeltaTime;
    AN5_Anim.Time = (DBL)(t.QuadPart - PauseTime - StartTime) / TimePerSec;
  }
  /* FPS */
  FrameCounter++;
  if (t.QuadPart - OldTimeFPS > TimePerSec)
  {
    AN5_Anim.FPS = FrameCounter * TimePerSec / (DBL)(t.QuadPart - OldTimeFPS);
    OldTimeFPS = t.QuadPart;
    FrameCounter = 0;
  }
  OldTime = t.QuadPart;
} /* End of 'AN5_TimerResponse' function */

/* End of 'timer.c' */