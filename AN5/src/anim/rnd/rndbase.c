/* FILE NAME  : rndbase.c
 * PROGRAMMER : AN5
 * LAST UPDATE: 18.01.2024
 * PURPOSE    : Base functions in computer graphic.
 */

#include "anim/rnd/res/rndres.h"

#include <wglew.h>
#include <gl/wglext.h>

/***
 * Base render subsystem functions
 ***/

/* Init wiindow function
 * ARGUMENTS:
 *   - Window context:
 *      HWND hWnd.
 * RETURNS: None.
 */
VOID AN5_RndInit( HWND hWnd )
{
  INT i, nums;
  PIXELFORMATDESCRIPTOR pfd = {0};

  HGLRC hRC;
  INT PixelAttribs[] =
  {
    WGL_DRAW_TO_WINDOW_ARB, TRUE,
    WGL_SUPPORT_OPENGL_ARB, TRUE,
    WGL_DOUBLE_BUFFER_ARB, TRUE,
    WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
    WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
    WGL_COLOR_BITS_ARB, 32,
    WGL_DEPTH_BITS_ARB, 32,
    0
  };
  INT ContextAttribs[] =
  {
    WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
    WGL_CONTEXT_MINOR_VERSION_ARB, 6,
    WGL_CONTEXT_PROFILE_MASK_ARB, /* WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB, */
                                  WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
    0
  };

  AN5_hRndhWnd = hWnd;
  AN5_hRndDC = GetDC(hWnd);

  /* OpenGL init: pixel format setup */
  pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
  pfd.nVersion = 1;
  pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL;
  pfd.cColorBits = 32;
  pfd.cDepthBits = 32;
  i = ChoosePixelFormat(AN5_hRndDC, &pfd);
  DescribePixelFormat(AN5_hRndDC, i, sizeof(pfd), &pfd);
  SetPixelFormat(AN5_hRndDC, i, &pfd);
  /* OpenGL init: renderning comtex setup */
  AN5_hRndGLRC = wglCreateContext(AN5_hRndDC);
  wglMakeCurrent(AN5_hRndDC, AN5_hRndGLRC);

  /* OpenGL extension init */
  if (glewInit() != GLEW_OK)
   exit(0);
  /* Enable a new OpenGL profile support */
  wglChoosePixelFormatARB(AN5_hRndDC, PixelAttribs, NULL, 1, &i, &nums);
  hRC = wglCreateContextAttribsARB(AN5_hRndDC, NULL, ContextAttribs);

  wglMakeCurrent(NULL, NULL);
  wglDeleteContext(AN5_hRndGLRC);

  AN5_hRndGLRC = hRC;
  wglMakeCurrent(AN5_hRndDC, AN5_hRndGLRC);

#ifndef NDEBUG
  OutputDebugString(glGetString(GL_VERSION));
  OutputDebugString("\n");
  OutputDebugString(glGetString(GL_VENDOR));
  OutputDebugString("\n");
  OutputDebugString(glGetString(GL_RENDERER));
  OutputDebugString("\n");

  glEnable(GL_DEBUG_OUTPUT);
  glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
  glDebugMessageCallback(glDebugOutput, NULL);
  glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
#endif /* NDEBUG */

  /* Inicialisation resourses */
  AN5_RndResInit();

  AN5_RndShdUBOPrimNo = AN5_RndUBOCreate("Prim UBO", AN5_RND_UBO_BIND_MATRIX, sizeof(an5RND_UBO_PRIM), NULL);
  AN5_RndShdUBOCameraNo = AN5_RndUBOCreate("Camera UBO", AN5_RND_UBO_BIND_CAMERA, sizeof(an5RND_UBO_CAMERA), NULL);
  AN5_RndShdUBOSyncNo = AN5_RndUBOCreate("Sync UBO", AN5_RND_UBO_BIND_SYNC, sizeof(an5RND_UBO_SYNC), NULL);

  //AN5_RndUBOApply(AN5_RndShdUBOPrimNo);
  AN5_RndUBOApply(AN5_RndShdUBOCameraNo);
 // AN5_RndUBOApply(AN5_RndShdUBOMaterialNo);

  /* Render parameters setup */
  glClearColor(0.29, 0.47, 0.8, 1);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_PRIMITIVE_RESTART);
  glPrimitiveRestartIndex(-1);

  /* Render parameters setup */
  AN5_RndIsWireFrame = TRUE;
  AN5_RndProjSize = 0.1;
  AN5_RndProjDist = AN5_RndProjSize;
  AN5_RndProjFarClip = 300;
  AN5_RndFrameH = 47;
  AN5_RndFrameW = 47;
  AN5_RndCamSet(VecSet1(5), VecSet1(0), VecSet(0, 0, 0));
} /* End of 'AN5_RndInit' function */

/* Start function
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AN5_RndStart( VOID )
{
  static DBL OldTime = -2;

  if (AN5_Anim.GlobalTime - OldTime > 2)
  {
    AN5_RndShdUpdate();
    OldTime = AN5_Anim.GlobalTime;
  }
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
} /* End of 'AN5_RndStart' function */


/* Close function
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AN5_RndClose( VOID )
{
  AN5_RndResClose();
  wglMakeCurrent(NULL, NULL);
  wglDeleteContext(AN5_hRndGLRC);
  ReleaseDC(AN5_hRndhWnd, AN5_hRndDC);
}
/* End of 'AN5_RndClose' function */

/* Copy frame function
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AN5_RndCopyFrame( VOID )
{
  SwapBuffers(AN5_hRndDC);
} /* End of 'AN5_RndCopyFrame' function */

/* Resize wiindow function
 * ARGUMENTS:
 *   - Window width and hieght:
 *      INT h,
 *      INT w.
 * RETURNS: None.
 */
VOID AN5_RndResize( INT W, INT H )
{
  glViewport(0, 0, W, H);
  /* save window size */
  AN5_RndFrameW = W;
  AN5_RndFrameH = H;
  /* find new proection */
  AN5_RndProjSet();
} /* End of 'AN5_RndResize' function */

/***
 * Camera handle functions
 ***/

/* Camera UBO update function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
static VOID AN5_RndUBOCamUpdate( VOID )
{
  an5RND_UBO_CAMERA CamData;

  CamData.MatrVP = AN5_RndMatrVP;
  CamData.MatrV = AN5_RndMatrView;
  CamData.MatrP = AN5_RndMatrProj;

  CamData.CamLoc = Vec4SetVec3(AN5_RndCamLoc, 0);
  CamData.CamUp = Vec4SetVec3(AN5_RndCamUp, 0);
  CamData.CamDir = Vec4SetVec3(AN5_RndCamDir, 0);
  CamData.CamRight = Vec4SetVec3(AN5_RndCamRight, 0);
  CamData.FrameWHProjSizeDist = Vec4Set(AN5_RndFrameW, AN5_RndFrameH, AN5_RndProjSize, AN5_RndProjDist);

  AN5_RndUBOUpdate(AN5_RndShdUBOCameraNo, 0, 0, &CamData);
} /* End of 'AN5_RndUBOCamUpdate' function */

/* Camera set function
 * ARGUMENTS:
 *   - Window where we need copy :
 *      HDC hDC.
 * RETURNS: None.
 */
VOID AN5_RndCamSet( VEC Loc, VEC At, VEC Up )
{
  AN5_RndMatrView = MatrView(Loc, At, Up);
  /* Store camera parameters */
  AN5_RndCamRight = VecSet(AN5_RndMatrView.A[0][0],
                           AN5_RndMatrView.A[1][0],
                           AN5_RndMatrView.A[2][0]);
  AN5_RndCamUp = VecSet(AN5_RndMatrView.A[0][1],
                        AN5_RndMatrView.A[1][1],
                        AN5_RndMatrView.A[2][1]);
  AN5_RndCamDir = VecSet(-AN5_RndMatrView.A[0][2],
                         -AN5_RndMatrView.A[1][2],
                         -AN5_RndMatrView.A[2][2]);
  AN5_RndCamLoc = Loc;
  AN5_RndCamAt = At;

  AN5_RndMatrVP = MatrMulMatr(AN5_RndMatrView, AN5_RndMatrProj);
  AN5_RndUBOCamUpdate();
} /* End of 'AN5_RndCamSet' function */

/* Correcting size of window function
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AN5_RndProjSet( VOID )
{
  FLT rx, ry;

  rx = ry = AN5_RndProjSize;

  /* Correct aspect ratio */
  if (AN5_RndFrameW >= AN5_RndFrameH)
    rx *= (FLT)AN5_RndFrameW / AN5_RndFrameH;
  else
    ry *= (FLT)AN5_RndFrameH / AN5_RndFrameW;

  AN5_RndMatrProj =
    MatrFrustum(-rx / 2, rx / 2, -ry / 2, ry / 2,
      AN5_RndProjDist, AN5_RndProjFarClip);
  AN5_RndMatrVP = MatrMulMatr(AN5_RndMatrView, AN5_RndMatrProj);
  AN5_RndUBOCamUpdate();
} /* End of 'AN5_RndProjSet' function */

/* Ending function
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AN5_RndEnd( VOID )
{
  glFinish();
} /* End of 'AN5_RndEnd' function */

/* END OF 'rndbase.c' FILE */