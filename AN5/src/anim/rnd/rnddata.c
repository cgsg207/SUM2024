/* FILE NAME  : rnddata.c
 * PROGRAMMER : AN5
 * LAST UPDATE: 26.01.2024
 * PURPOSE    : Global variables(for inicialisation) file.
 */
#include "rnd.h"

/* Project plane fit square */
FLT AN5_RndProjSize;
/* Distance to project plane from viewer (near) */
FLT AN5_RndProjDist;
/* Distance to project far clip plane (far) */
FLT AN5_RndProjFarClip;

/* View coordinate system matrix */
MATR AN5_RndMatrView;
/* Projection coordinate system matrix */
MATR AN5_RndMatrProj;
/* Stored (View * Proj) matrix */
MATR AN5_RndMatrVP;

/* Camera settings */
VEC
  AN5_RndCamLoc,   /* Render camera location */
  AN5_RndCamAt,    /* Render camera point-of-interest */
  AN5_RndCamUp,    /* Render camera up diraction */
  AN5_RndCamDir,   /* Render camera forward diraction */
  AN5_RndCamRight; /* Render camera right diraction */

UINT
  AN5_RndShdUBOPrimNo,     /* UBO reference for primitive UBO buffer */
  AN5_RndShdUBOCameraNo,   /* UBO reference for matrix UBO buffer */
  AN5_RndShdUBOMaterialNo, /* UBO reference for material UBO buffer */
  AN5_RndShdUBOSyncNo;     /* UBO reference for sync UBO buffer */

/* Work window handle */
HWND AN5_hRndhWnd;
/* Rendering window context handle */
HDC AN5_hRndDC;
/* OpenGL rendering context handle  */
HGLRC AN5_hRndGLRC;
/* Work window size */
INT AN5_RndFrameW, AN5_RndFrameH;
/* Render wireframe mode flag */
BOOL AN5_RndIsWireFrame;

/* Shaders addon parameters */
INT AN5_RndShdAddonI[4];
FLT AN5_RndShdAddonF[4];
VEC4 AN5_RndShdAddonV[4];

/* END OF 'rnddata.c' FILE */