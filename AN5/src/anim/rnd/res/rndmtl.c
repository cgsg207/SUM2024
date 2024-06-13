/* FILE NAME  : rndmtl.c
 * PROGRAMMER : AN5
 * LAST UPDATE: 21.02.2024
 * PURPOSE    : 3D animation project.
 *              Rendering system resourses.
 *              Material handle module.
 */

#include "rndres.h"
#include "string.h"

an5MATERIAL AN5_RndMaterials[AN5_MAX_MATERIALS]; /* Array of materials */
INT AN5_RndMaterialsSize;                        /* Materials array */

static struct
{
  CHAR *Name;
  VEC Amb, Dif, Spec;
  FLT Shininess;
} MatLib[] =
{
  {"Black Plastic", {0.0, 0.0, 0.0},             {0.01, 0.01, 0.01},           {0.5, 0.5, 0.5},               32},
  {"Brass",         {0.329412,0.223529,0.027451}, {0.780392,0.568627,0.113725}, {0.992157,0.941176,0.807843}, 27.8974},
  {"Bronze",        {0.2125,0.1275,0.054},       {0.714,0.4284,0.18144},       {0.393548,0.271906,0.166721},  25.6},
  {"Chrome",        {0.25, 0.25, 0.25},          {0.4, 0.4, 0.4},              {0.774597, 0.774597, 0.774597}, 76.8},
  {"Copper",        {0.19125,0.0735,0.0225},     {0.7038,0.27048,0.0828},      {0.256777,0.137622,0.086014},  12.8},
  {"Gold",          {0.24725,0.1995,0.0745},     {0.75164,0.60648,0.22648},    {0.628281,0.555802,0.366065},  51.2},
  {"Peweter",       {0.10588,0.058824,0.113725}, {0.427451,0.470588,0.541176}, {0.3333,0.3333,0.521569},      9.84615},
  {"Silver",        {0.19225,0.19225,0.19225},   {0.50754,0.50754,0.50754},    {0.508273,0.508273,0.508273},  51.2},
  {"Polished Silver", {0.23125,0.23125,0.23125}, {0.2775,0.2775,0.2775},       {0.773911,0.773911,0.773911},  89.6},
  {"Turquoise",     {0.1, 0.18725, 0.1745},      {0.396, 0.74151, 0.69102},    {0.297254, 0.30829, 0.306678}, 12.8},
  {"Ruby",          {0.1745, 0.01175, 0.01175},  {0.61424, 0.04136, 0.04136},  {0.727811, 0.626959, 0.626959}, 76.8},
  {"Polished Gold", {0.24725, 0.2245, 0.0645},   {0.34615, 0.3143, 0.0903},    {0.797357, 0.723991, 0.208006}, 83.2},
  {"Polished Bronze", {0.25, 0.148, 0.06475},    {0.4, 0.2368, 0.1036},        {0.774597, 0.458561, 0.200621}, 76.8},
  {"Polished Copper", {0.2295, 0.08825, 0.0275}, {0.5508, 0.2118, 0.066},      {0.580594, 0.223257, 0.0695701}, 51.2},
  {"Jade",          {0.135, 0.2225, 0.1575},     {0.135, 0.2225, 0.1575},      {0.316228, 0.316228, 0.316228}, 12.8},
  {"Obsidian",      {0.05375, 0.05, 0.06625},    {0.18275, 0.17, 0.22525},     {0.332741, 0.328634, 0.346435}, 38.4},
  {"Pearl",         {0.25, 0.20725, 0.20725},    {1.0, 0.829, 0.829},          {0.296648, 0.296648, 0.296648}, 11.264},
  {"Emerald",       {0.0215, 0.1745, 0.0215},    {0.07568, 0.61424, 0.07568},  {0.633, 0.727811, 0.633},       76.8},
  {"Black Plastic", {0.0, 0.0, 0.0},             {0.01, 0.01, 0.01},           {0.5, 0.5, 0.5},                32.0},
  {"Black Rubber",  {0.02, 0.02, 0.02},          {0.01, 0.01, 0.01},           {0.4, 0.4, 0.4},                10.0},
};
#define AN5_MAT_LIB_SIZE (sizeof(MatLib) / sizeof(MatLib[0]))

/* Material store system initialization.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AN5_RndMtlInit( VOID )
{
  INT i;
  an5MATERIAL mtl = AN5_RndMtlGetDef();

  /* Add default material */
  AN5_RndMaterialsSize = 0;
  AN5_RndMtlAdd(&mtl);

  for (i = 0; i < AN5_MAT_LIB_SIZE; i++)
  {
    strncpy(mtl.Name, MatLib[i].Name, AN5_STR_MAX - 1);
    mtl.Ka = MatLib[i].Amb;
    mtl.Kd = MatLib[i].Dif;
    mtl.Ks = MatLib[i].Spec;
    mtl.Ph = MatLib[i].Shininess;
    mtl.Trans = 1;
    AN5_RndMtlAdd(&mtl);

  }
} /* End of 'AN5_RndMtlInit' function */

/* Material store system deinitialization.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AN5_RndMtlClose( VOID )
{
  AN5_RndMaterialsSize = 0;
} /* End of 'AN5_RndMtlClose' function */

/* Add material function
 * ARGUMENTS:
 *   - material data structure pointer:
 *       an5Materual *Mtl;
 * RETURNS:
 *   (INT) material table index or -1 if error is occured.
 */
INT AN5_RndMtlAdd( an5MATERIAL *Mtl )
{
  INT i;
  an5RND_UBO_MTL MtlData;

  /* Check for free space */
  if (AN5_RndMaterialsSize >= AN5_MAX_MATERIALS)
    return -1;

  AN5_RndMaterials[AN5_RndMaterialsSize] = *Mtl;

  MtlData.Ka = Vec4SetVec3(Mtl->Ka, 0);
  MtlData.KdTrans = Vec4SetVec3(Mtl->Kd, Mtl->Trans);
  MtlData.KsPh = Vec4SetVec3(Mtl->Ks, Mtl->Ph);
  for (i = 0; i < 8; i++)
    MtlData.TextureFlags[i] = Mtl->Tex[i] != -1;

  AN5_RndMaterials[AN5_RndMaterialsSize].UBONo = AN5_RndUBOCreate(Mtl->Name, AN5_RND_UBO_BIND_MATERIAL, sizeof(an5RND_UBO_MTL), &MtlData);

  return AN5_RndMaterialsSize++;
} /* End of 'AN5_RndMtlAdd' function */

/* Get default material function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (an5MATERIAL) default material.
 */
an5MATERIAL AN5_RndMtlGetDef( VOID )
{
  an5MATERIAL def_mtl =
  {
    "Default",
    {0.1, 0.1, 0.1},
    {0.9, 0.9, 0.9},
    {0.3, 0.3, 0.3},
    30, 1,
    {-1, -1, -1, -1, -1, -1, -1, -1},
    0
  };

  return def_mtl;
} /* End of 'AN5_RndMtlGetDef' function */

/* Material apply function.
 * ARGUMENTS:
 *   - material data structure point:
 *       INT MtlNo;
 * RETURNS:
 *   (INT) apply result shader program identifier.
 */
INT AN5_RndMtlApply( INT MtlNo )
{
  INT prg, loc, i;
  an5MATERIAL *mtl;

  /* Set material pointer */
  mtl = AN5_RndMtlGet(MtlNo);

  /* Set shader program Id */
  prg = mtl->ShdNo;
  if (prg < 0 || prg >= AN5_RndShadersSize)
    prg = 0;
  prg = AN5_RndShaders[prg].ProgId;

  glUseProgram(prg);
  if (prg == 0)
    return 0;

  AN5_RndUBOApply(mtl->UBONo);
  /*Set shading parameters */
  if ((loc = glGetUniformLocation(prg, "Ka")) != -1)
    glUniform3fv(loc, 1, &mtl->Ka.X);
  if ((loc = glGetUniformLocation(prg, "Kd")) != -1)
    glUniform3fv(loc, 1, &mtl->Kd.X);
  if ((loc = glGetUniformLocation(prg, "Ks")) != -1)
    glUniform3fv(loc, 1, &mtl->Ks.X);
  if ((loc = glGetUniformLocation(prg, "Ph")) != -1)
    glUniform1f(loc, mtl->Ph);
  if ((loc = glGetUniformLocation(prg, "Trans")) != -1)
    glUniform1f(loc, mtl->Trans);

  /* Set textures */
  for (i = 0; i < 8; i++)
  {
    CHAR tname[] = "IsTexture0";

    tname[9] = '0' + i;
    if (mtl->Tex[i] != -1)
    {
      glActiveTexture(GL_TEXTURE0 + i);
      glBindTexture(GL_TEXTURE_2D, AN5_RndTextures[mtl->Tex[i]].TexId);
    }
    if ((loc = glGetUniformLocation(prg, tname)) != -1)
      glUniform1i(loc, mtl->Tex[i] != -1);
  }
  if (AN5_RndTexturesSize > 0)
  {
    glActiveTexture(GL_TEXTURE0 + 8);
    glBindTexture(GL_TEXTURE_2D, AN5_RndTextures[0].TexId);
  }
  return prg;
} /* End of 'AN5_RndMtlApply' function */

/* Get material pointer by material table number function.
 * ARGUMENTS:
 *   - number of material at materials table:
 *       INT MtlNo;
 * RETURNS:
 *   (an5MATERIAL *) found material.
 */
an5MATERIAL * AN5_RndMtlGet( INT MtlNo )
{
  /* Get material pointer */
  if (MtlNo < 0 || MtlNo >= AN5_RndMaterialsSize)
    MtlNo = 0;
  return &AN5_RndMaterials[MtlNo];
} /* End of 'AN5_RndMtlGet' function */

/* Get material pointer by material name function.
 * ARGUMENTS:
 *   - material name:
 *       CHAR *MtlName
 * RETURNS:
 *   (INT) found material.
 */
INT AN5_RndMtlGetByName( CHAR *MtlName )
{
  INT i;
  /* Look for material by name */
  for (i = 0; i < AN5_RndMaterialsSize; i++)
    if (strcmp(MtlName, AN5_RndMaterials[i].Name) == 0)
      return i;
  return 0;
} /* End of 'AN5_RndMtlGet' function */

/* END OF 'rndmtl.c' FILE */