/* FILE NAME  : RND.H
 * PROGRAMMER : AN5
 * LAST UPDATE: 05.02.2024
 * PURPOSE    : Rendering head file computer graphic.
 */

#include "def.h"
#define GLEW_STATIC
#include "glew.h"
#pragma comment(lib, "opengl32")

//#include "res/rndres.h"

typedef struct tagan5VERTEX
{
  VEC P;     /* Vertex position */
  VEC2 T;    /* Texsture coordinate */
  VEC N;     /* Point normal */
  VEC4 C;    /* Color(RGBA) */
} an5VERTEX;

/* Primitive type */
typedef enum tagan5PRIM_TYPE
{
  AN5_RND_PRIM_TRIMESH,  /* Triangle mesh - array of triangles */
  AN5_RND_PRIM_GRID,     /* Grid - regular 2D array of points (triangle strips) */
  AN5_RND_PRIM_LINES,    /* Line segments (by 2 points) */
  AN5_RND_PRIM_TRISTRIP, /* Triangle strip - array of stripped triangles */
  AN5_RND_PRIM_LINESTRIP, /* Line strip - array of stripped lines */
  AN5_RND_PRIM_PATCH
} an5PRIM_TYPE;

/* Primitive representation type */
typedef struct tagan5PRIM
{
  an5PRIM_TYPE Type;
  INT
    VA,               /* OpenGL vertex array Id */
    VBuf,             /* OpenGL vertex buffer Id */
    IBuf,             /* OpenGL vertex buffer Id */
    NumOfPatchPoints, /* Number of one patch points */
    NumOfElements,    /* Number of elements */
    InstanceCnt;      /* Counter for instancing, 0 - not use */

  MATR Trans;         /* Additional transformation matrix */
  VEC MinBB, MaxBB;   /* Bound box */
  INT MtlNo;          /* Material number in material array */
} an5PRIM;

/* Project plane fit square */
extern FLT AN5_RndProjSize;
/* Distance to project plane from viewer (near) */
extern FLT AN5_RndProjDist;
/* Distance to project far clip plane (far) */
extern FLT AN5_RndProjFarClip;

/* Render wireframe mode flag */
extern BOOL AN5_RndIsWireFrame;

/* View coordinate system matrix */
extern MATR AN5_RndMatrView;
/* Projection coordinate system matrix */
extern MATR AN5_RndMatrProj;
/* Stored (View * Proj) matrix */
extern MATR AN5_RndMatrVP;

/* Work window handle */
extern HWND AN5_hRndhWnd;
/* Rendering window context handle */
extern HDC AN5_hRndDC;
/* OpenGL rendering context handle  */
extern HGLRC AN5_hRndGLRC;
/* Work window size */
extern INT AN5_RndFrameW, AN5_RndFrameH;

/* UBOs */
extern UINT
  AN5_RndShdUBOPrimNo,     /* UBO reference for primitive UBO buffer */
  AN5_RndShdUBOCameraNo,   /* UBO reference for camera UBO buffer */
  AN5_RndShdUBOMaterialNo, /* UBO reference for material UBO buffer */
  AN5_RndShdUBOSyncNo;     /* UBO reference for sync UBO buffer */

/* Shaders addon parameters */
extern INT AN5_RndShdAddonI[4];
extern FLT AN5_RndShdAddonF[4];
extern VEC4 AN5_RndShdAddonV[4];


/* Camera */
extern VEC
  AN5_RndCamLoc,   /* Render camera location */
  AN5_RndCamAt,    /* Render camera point-of-interest */
  AN5_RndCamUp,    /* Render camera up diraction */
  AN5_RndCamDir,   /* Render camera forward diraction */
  AN5_RndCamRight; /* Render camera right diraction */

/***
 * UBO module
 ***/

/* Camera UBO data representation type */
typedef struct tagan5RND_UBO_CAMERA
{
  MATR MatrVP;              /* Premultiplied (View and Proj) matrix */
  MATR MatrV;               /* Matrix 'view' */
  MATR MatrP;               /*  */
  VEC4 CamLoc;              /* Camera location */
  VEC4 CamRight;            /* Camera right diraction */
  VEC4 CamUp;               /* Camera up diraction */
  VEC4 CamDir;              /* Camera forward diraction */
  VEC4 FrameWHProjSizeDist; /* Camera frame size, projection and distance */
} an5RND_UBO_CAMERA;

typedef struct taganRND_UBO_MTL
{
  VEC4 Ka;             /* Ambient coefficients */
  VEC4 KdTrans;        /* Defuse coefficient and transparency */
  VEC4 KsPh;           /* Specular coeficient and phong power value */
  INT TextureFlags[8]; /* Material texture flags */
} an5RND_UBO_MTL;

typedef struct tagan5RND_UBO_SYNC
{
  VEC4 TimeDeltaTimeGlobalTimeGlobalDeltaTime; /* Time parametres */
  INT IsWireFrameIsPause[4];                   /* Wireframe and pause flags */
} an5RND_UBO_SYNC;

typedef struct tagan5RND_UBO_PRIM
{
  MATR MatrW;     /* World primitives matrix */
  MATR MatrWInv;  /* Inverse transposed warld matrix */
  MATR MatrWVP;   /* Premultiplayed 'world' - 'view' - 'projection' matrixes (for normals) */
  INT AddonI[4];  /*  */
  FLT AddonF[4];  /*  */
  VEC4 AddonV[4]; /*  */
} an5RND_UBO_PRIM;

/* System UBO bind points */
#define AN5_RND_UBO_BIND_CAMERA   0
#define AN5_RND_UBO_BIND_SYNC     1
#define AN5_RND_UBO_BIND_MATERIAL 2
#define AN5_RND_UBO_BIND_MATRIX   3


/* Init wiindow function
 * ARGUMENTS:
 *   - Window:
 *      HWND hWnd.
 * RETURNS: None.
 */
VOID AN5_RndInit( HWND hWnd );

/* Start function
 * ARGUMENTS:
 *   - Window width and hieght:
 *      INT h,
 *      INT w.
 * RETURNS: None.
 */
VOID AN5_RndStart( VOID );

/* Close function
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AN5_RndClose( VOID );

/* Ending function
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AN5_RndEnd( VOID );

/* Copy frame function
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AN5_RndCopyFrame( VOID );

/* Resize wiindow function
 * ARGUMENTS:
 *   - Window width and hieght:
 *      INT h,
 *      INT w.
 * RETURNS: None.
 */
VOID AN5_RndResize( INT W, INT H );

/* Correcting size of window function
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AN5_RndProjSet( VOID );

/* Camera set function
 * ARGUMENTS:
 *   - Window where we need copy :
 *      HDC hDC.
 * RETURNS: None.
 */
VOID AN5_RndCamSet( VEC Loc, VEC At, VEC Up1 );

/* Debug output function.
 * ARGUMENTS:
 *   - source APi or device:
 *       UINT Source;
 *   - error type:
 *       UINT Type;
 *   - error message id:
 *       UINT Id, 
 *   - message severity:
 *       UINT severity, 
 *   - message text length:
 *       INT Length, 
 *   - message text:
 *       CHAR *Message, 
 *   - user addon parameters pointer:
 *       VOID *UserParam;
 * RETURNS: None.
 */
VOID APIENTRY glDebugOutput( UINT Source, UINT Type, UINT Id, UINT Severity,
                             INT Length, const CHAR *Message,
                             const VOID *UserParam );

/* Free primiteve function
 * ARGUMENTS:
 *   - Pointer on primiteve:
 *      an5Prim *Pr.
 * RETURNS: None.
 */
VOID AN5_RndPrimFree( an5PRIM *Pr );

/* Create primiteve function
 * ARGUMENTS:
 *   - Pointer on primiteve:
 *      an5PRIM *Pr;
 *   - Primitive type:
 *      an5PRIM_TYPE Type;
 *   - Vertex array:
 *      an5VERTEX *V;
 *   - Vertex array size:
 *      INT NoofV;
 *   - Index array:
 *      INT *I;
 *   - Index array size:
 *      INT NoofI;
 * RETURNS:
 *   - (BOOL) True if success, False otherwise.
 */
BOOL AN5_RndPrimCreate( an5PRIM *Pr, an5PRIM_TYPE Type, an5VERTEX *V, INT NoofV, INT *I, INT NoofI );

/* Load primiteve function
 * ARGUMENTS:
 *   - Pointer on primiteve:
 *      an5Prim *Pr.
 *   - Pointer on file which we load:
 *      CHAR FileName.
 * RETURNS:
 *   - (BOOL) True if correct, False in other results.
 */
VOID AN5_RndPrimDraw( an5PRIM *Pr, MATR World );

/* Load primiteve function
 * ARGUMENTS:
 *   - Pointer on primiteve:
 *      an5Prim *Pr.
 *   - Pointer on file which we load:
 *      CHAR FileName.
 * RETURNS:
 *   - (BOOL) True if correct, False in other results.
 */
BOOL AN5_RndPrimLoad( an5PRIM *Pr, CHAR *FileName );

/* Primiteve bound box obtain function.
 * ARGUMENTS:
 *   - ponter to result min-max vectors:
 *       VEC *MinBB, *MaxBB;
 *   - Vertex array:
 *      an5VERTEX *V;
 *   - Vertex array size:
 *      INT NoofV;
 * RETURNS: None.
 */
VOID AN5_RndPrimEvalBB( VEC *MinBB, VEC *MaxBB, an5VERTEX *V, INT NoofV );

/* Primitive vertex normals evaluate function.
 * ARGUMENTS:
 *   - Vertex array:
 *      an5VERTEX *V;
 *   - Vertex array size:
 *      INT NoofV;
 *   - Index array:
 *      INT *I;
 *   - Index array size:
 *      INT NoofI;
 * RETURNS: None.
 */
VOID AN5_RndPrimAutoNormals( an5VERTEX *V, INT NoofV, INT *I, INT NoofI );

/* END OF 'rnd.h' FILE */