/* FILE NAME  : rndres.h
 * PROGRAMMER : AN5
 * LAST UPDATE: 09.02.2024
 * PURPOSE    : 3D animaton project.
 *              Rendering system declaration module.
                Resourses header module.
 */

#include "anim/anim.h"

/* Resourse initialisation function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AN5_RndResInit( VOID );

/* Resourse deinitialisation function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AN5_RndResClose( VOID );

/***
 * Shaders handle functions.
 ***/

#define AN5_STR_MAX 300

/* Shader program store type */
typedef struct tagan5SHADER
{
  CHAR Name[AN5_STR_MAX]; /* Shader filename prefix */
  INT ProgId;             /* Shader program Id */
} an5SHADER;

/* Shaders stock */
#define AN5_MAX_SHADERS 30
extern an5SHADER AN5_RndShaders[AN5_MAX_SHADERS]; /* Array of shaders */
extern INT AN5_RndShadersSize;

/* Loud defalt shader function
 * ARGUMENTS: None.
 * RETURNS: None.
*/
VOID AN5_RndShdInit( VOID );

/* Upload all shaders.
 * ARGUMENTS: None.
 * RETURNS: None.
*/
VOID AN5_RndShdClose( VOID );


/* Stores in an array function
 * ARGUMENTS:
 *   - Shader name:
 *       CHAR *ShaderFileNamePrefix;
 * RETURNS:
 *   (CHAR *) returns the number of the added shader in an array(RndShaders).
 */
INT AN5_RndShdAdd( CHAR *ShaderFileNamePrefix );

/* Update all shaders function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AN5_RndShdUpdate( VOID );

/* Shader program load function.
 * ARGUMENTS:
 *   - shader directory files prefix (base from 'bin/shaders/'):
 *       CHAR *FileNamePrefix;
 * RETURNS:
 *   (INT) OpenGL shader program index (0 if error is occured).
 */
INT AN5_RndShdLoad( CHAR *FileNamePrefix );

/* Shader program free function.
 * ARGUMENTS:
 *   - shader program Id:
 *       INT Prg;
 * RETURNS: None.
 */
VOID AN5_RndShdFree( INT Prg );

/***
 * Texture module.
 ***/

/* Texture representation type */
typedef struct tagan5TEXTURE
{
  CHAR Name[AN5_STR_MAX]; /* Texture name */
  INT W, H;               /* Texture size in pixels */
  UINT TexId;             /* OpenGL texture Id */ 
} an5TEXTURE;

/* Textures stock */
#define AN5_MAX_TEXTURES 300
extern an5TEXTURE AN5_RndTextures[AN5_MAX_TEXTURES]; /* Array of textures */
extern INT AN5_RndTexturesSize;                      /* Textures array store size */

/* Texture handle initialisation function.
 * ARGUMAENTS: None.
 * RETURNS: None.
 */
VOID AN5_RndTexInit( VOID );

/* Texture handle deinitialisation function.
 * ARGUMAENTS: None.
 * RETURNS: None.
 */
VOID AN5_RndTexClose( VOID );

/* Add texture to stock function.
 * ARGUMENTS:
 *   - texture name:
 *       CHAR *Name;
 *   - texture size in pixels:
 *       INT W, H;
 *   - number of color components:
 *       INT C;
 *   - texture pixel data:
 *       VOID *Bits;
 * RETURNS:
 *   - (INT) texture stock number (0 if error is occused)
 */
INT AN5_RndTexAddImg( CHAR *Name, INT W, INT H, INT C, VOID *Bits );

/* Add texture to stock function.
 * ARGUMENTS:
 *   - texture file name:
 *       CHAR *FileName;
 * RETURNS:
 *   - (INT) texture stock number (0 if error is occused)
 */
INT AN5_RndTexAddFromFile( CHAR *FileName );

/* Load texture from .G24 file function.
 * ARGUMENTS:
 *   - file name:
 * RETURNS:
 *   - (INT) texture stock number (0 if error is occused)
 */
INT AN5_RndTexAddImgG24( CHAR *Name );

/***
 * Material handle function group.
 ***/

/* Material store type */
typedef struct tagan5MATERIAL
{
  CHAR Name[AN5_STR_MAX]; /* Material name */
  VEC Ka, Kd, Ks;         /* Ambient, diffuse, specular coefficients */
  FLT Ph;                 /* Phong power coefficient */
  FLT Trans;              /* Transparency factor */
  INT Tex[8];             /* Texture references from texture table (or -1) */
  INT ShdNo;              /* Shader number in shader table */
  INT UBONo;              /* UBO reference in OBO table */
} an5MATERIAL;

/* Material stock */
#define AN5_MAX_MATERIALS 300
extern an5MATERIAL AN5_RndMaterials[AN5_MAX_MATERIALS]; /* Array of materials */
extern INT AN5_RndMaterialsSize;                        /* Materials array */

/* Material store system initialization.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AN5_RndMtlInit( VOID );

/* Material store system deinitialization.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AN5_RndMtlClose( VOID );

/* Add material function
 * ARGUMENTS:
 *   - material data structure pointer:
 *       an5Materual *Mtl;
 * RETURNS:
 *   (INT) material table index or -1 if error is occured.
 */
INT AN5_RndMtlAdd( an5MATERIAL *Mtl );

/* Get default material function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (an5MATERIAL) default material.
 */
an5MATERIAL AN5_RndMtlGetDef( VOID );

/* Get material pointer by material table number function.
 * ARGUMENTS:
 *   - number of material at materials table:
 *       INT MtlNo;
 * RETURNS:
 *   (an5MATERIAL *) found material.
 */
an5MATERIAL * AN5_RndMtlGet( INT MtlNo );

/* Material apply function.
 * ARGUMENTS:
 *   - material data structure point:
 *       INT MtlNo;
 * RETURNS:
 *   (INT) apply result shader program identifier.
 */ 
INT AN5_RndMtlApply( INT MtlNo );

/* Get material pointer by material name function.
 * ARGUMENTS:
 *   - material name:
 *       CHAR *MtlName
 * RETURNS:
 *   (INT) found material.
 */
INT AN5_RndMtlGetByName( CHAR *MtlName );


/***
 * UBO module
 ***/

/* UBOs stock */
#define AN5_MAX_UBOS 3000

/* UBO representation type */
typedef struct tagan5UBO
{
  CHAR Name[AN5_STR_MAX]; /* UBO name */
  INT Size;               /* UBO size in bytes */
  UINT UBOId;             /* OpenGL UBO Id */ 
  UINT BindPoint;         /* OpenGL UBO bind point */
} an5UBO;

extern an5UBO AN5_RndUBOs[AN5_MAX_UBOS]; /* Array of UBO */
extern INT AN5_RndUBOsSize;              /* UBO array store size */

/* UBO handle initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AN5_RndUBOInit( VOID );

/* UBO handle deinitialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AN5_RndUBOClose( VOID );

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
INT AN5_RndUBOCreate( CHAR *Name, UINT BindPoint, INT Size, VOID *Bits );

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
VOID AN5_RndUBOUpdate( INT UBONo, INT Offset, INT Size, VOID *Bits );

/* UBO apply function.
 * ARGUMENTS:
 *   - UBO number in stock:
 *       INT UBONo;
 * RETURNS: None.
 */
VOID AN5_RndUBOApply( INT UBONo );

/***
 * Prims module
 ***/

/* Primitive collection data type */
typedef struct tagan5PRIMS
{
  INT NumOfPrims;   /* Number of primitives in array */
  an5PRIM *Prims;   /* Array of primitives */
  MATR Trans;       /* Common transformation matrix */
  VEC MinBB, MaxBB; /* Bound Box coordinates*/
} an5PRIMS;

/* Create array of primitives function.
 * ARGUMENTS:
 *   - pointer to primitives structure:
 *       an5PRIMS *Prs;
 *   - number of primitives to be add:
 *       INT NumOfPrims;
 * RETURNS:
 *   (BOOL) TRUE if successful, FALSE otherwise.
 */
BOOL AN5_RndPrimsCreate( an5PRIMS *Prs, INT NumOfPrims );

/* Load array of primitives from .G3DM fi;e function.
 * ARGUMENTS:
 *   - pointer to primitives structure:
 *       an5PRIMS *Prs;
 *   - file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (BOOL) TRUE if successful, FALSE otherwise.
 */
BOOL AN5_RndPrimsLoad( an5PRIMS *Prs, CHAR *FileName );

/* Delete array of primitives function.
 * ARGUMENTS:
 *   - pointer to primitives structure:
 *       an5PRIMS *Prs;
 * RETURNS: None.
 */
VOID AN5_RndPrimsFree( an5PRIMS *Prs );

/* Draw array of primitives function.
 * ARGUMENTS:
 *   - pointer to primitives structure:
 *       vg4PRIMS *Prs;
 *   - global transformation matrix:
 *       MATR World;
 * RETURNS: None.
 */
VOID AN5_RndPrimsDraw( an5PRIMS *Prs, MATR World );

/* END OF 'rndres.h' FILE */