/* FILE NAME  : t48anim.c
 * PROGRAMMER : AN5
 * LAST UPDATE: 18.01.2024
 * PURPOSE    : Main file.
 */

#include <time.h>
#include <stdio.h>

#include "units/units.h"

#define WND_CLASS_NAME "Window class"

/* Link on processing function */
LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg,
                              WPARAM wParam, LPARAM lParam );


/* Main startup program function.
 * ARGUMENTS:
 *   - application instance handle:
 *       HINSTANCE hInstance;
 *   - previouse application instance handle
 *     (not used, alway NULL):
 *       HINSTANCE hPrevInstance;
 *   - command line string:
 *       CHAR *CmdLine;
 *   - command line window show parameter (see SW_***):
 *       INT CmdShow;
 * RETURNS:
 *   (INT) system error level value.
 */
INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    CHAR *CmdLine, INT ShowCmd )
{
  WNDCLASS wc;
  HWND hWnd;
  MSG msg;

  wc.style = CS_VREDRAW | CS_HREDRAW; /* Window style: completely redraw
                                       * after changing vertical or
                                       * horizontal size
                                       * you can use CS_DBLCLKS for adding double-click practice */

  wc.cbClsExtra = 0; /* Additional number of bytes for class */
  wc.cbWndExtra = 0; /* Additional number of bytes for window */
  wc.hbrBackground = (HBRUSH)COLOR_WINDOW; /* Background color - picked by sistem */
  wc.hCursor = LoadCursor(NULL, IDC_ARROW); /* Loading cursor( sistem ) */
  wc.hIcon = LoadIcon(NULL, IDI_INFORMATION); /* Loading icon( sistem ) */
  wc.lpszMenuName = NULL; /*Name of menu`s resources */
  wc.hInstance = hInstance; /* Discipler of registaring class application */
  wc.lpfnWndProc = MyWindowFunc;
  wc.lpszClassName = WND_CLASS_NAME; /* Class`s name */

  /* Registreing class on sistem */
  if (!RegisterClass(&wc))
  {
    MessageBox(NULL, "Error register window class", "ERROR", MB_OK);
    return 0;
  }

  hWnd = 
    CreateWindow(WND_CLASS_NAME,    /* Name of class`s window */
      "T48ANIM",                       /* Name of title */
      WS_OVERLAPPEDWINDOW,          /* Window`s style - general view window */
      CW_USEDEFAULT, CW_USEDEFAULT, /* Window position (x, y) - default */
      CW_USEDEFAULT, CW_USEDEFAULT, /* Window size (w, h) - default*/
      NULL,                         /* Parent`s window discipler*/
      NULL,                         /* Appload menu`s discipler */
      hInstance,                    /* Application`s discipler */
      NULL);                        /* Pointer on additional parameters */

  /* Show and redraw window */
  ShowWindow(hWnd, SW_SHOWNORMAL);

  //AN5_AnimUnitAdd(AN5_UnitCreateCowObject());
  AN5_AnimUnitAdd(AN5_UnitCreateG3DMObject());
  AN5_AnimUnitAdd(AN5_UnitCreateControl());
  //AN5_AnimUnitAdd(AN5_UnitCreateTexSample());
  //AN5_AnimUnitAdd(AN5_UnitCreateG3DMBuilding());
  //AN5_AnimUnitAdd(AN5_UnitCreateG3DMBuilding2());
  UpdateWindow(hWnd);

  /* Cycle of treatment, while 'WM_QUIT' */
  while (TRUE)
  {
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
      if (msg.message == WM_QUIT)
        break;
      DispatchMessage(&msg);
    }
    AN5_AnimRender();
    AN5_AnimCopyFrame();
  }
  return msg.wParam;
} /* End of 'WinMain' function */

/* Window handle function.
 * ARGUMENTS:
 *   - window handle:
 *       HWND hWnd;
 *   - message type (see WM_***):
 *       UINT Msg;
 *   - message 'word' parameter:
 *       WPARAM wParam;
 *   - message 'long' parameter:
 *       LPARAM lParam;
 * RETURNS:
 *   (LRESULT) message depende return value.
 */
LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg,
                              WPARAM wParam, LPARAM lParam )
{
  PAINTSTRUCT ps;
  static INT W, H;
  static HDC hDC;
  MINMAXINFO *minmax;

  switch(Msg)
  {
  case WM_GETMINMAXINFO:
    minmax = (MINMAXINFO *)lParam;
    minmax->ptMaxTrackSize.y = GetSystemMetrics(SM_CYMAXTRACK) +
      GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYBORDER) * 2;
    return 0;
  case WM_CREATE:
    AN5_AnimInit(hWnd);
    SetTimer(hWnd, 30, 2, NULL);
    return 0;
  case WM_SIZE:
    AN5_AnimResize(LOWORD(lParam), HIWORD(lParam));
    AN5_AnimCopyFrame();
    return 0;
  case WM_TIMER:
    AN5_AnimRender();
    AN5_AnimCopyFrame();
    return 0;
  case WM_LBUTTONDOWN:
    SetCapture(hWnd);
    return 0;
  case WM_LBUTTONUP:
    ReleaseCapture();
    return 0;
  case WM_KEYDOWN:
    if (wParam == VK_ESCAPE)
      SendMessage(hWnd, WM_CLOSE, 0, 0);
    else if (wParam == 'W')
      AN5_RndIsWireFrame = !AN5_RndIsWireFrame;
    else if (wParam == 'P')
      AN5_Anim.IsPause = !AN5_Anim.IsPause;
    else if (wParam == 'F')
      AN5_AnimFlipFullScreen();
  case WM_ERASEBKGND:
    return 1;
  case WM_PAINT:
    AN5_AnimRender();
    AN5_AnimCopyFrame();
    hDC = BeginPaint(hWnd, &ps);
    EndPaint(hWnd, &ps);
    return 0;
  case WM_CLOSE:
    if (MessageBox(NULL, "Are you sure to close window?", "CLOSE", MB_YESNO | MB_ICONQUESTION) == IDYES)
      break;
    return 0;
  case WM_DESTROY:
    AN5_AnimCLose();
    KillTimer(hWnd, 30);
    PostQuitMessage(30);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
} /* End of 'MyWindowFunc' function */

/* End of 'main.c' file */
