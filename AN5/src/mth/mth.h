/* FILE NAME  : mth.h
 * PROGRAMMER : AN5
 * LAST UPDATE: 18.01.2024
 * PURPOSE    : Math in computer graphic.
 */
#ifndef __mth_h_
#define __mth_h_

#include <math.h>

#include <commondf.h>

/* Pi math constant */
#define PI 3.14159265358979323846

/* Degrees to radians conversion */
#define D2R(A) ((A) * (PI / 180.0))
#define Degree2Radian(a) D2R(a)


/* Base float point types */
typedef double DBL;
typedef float FLT;

/* Space vector/point representation type */
typedef struct tagVEC
{
  FLT X, Y, Z; /* Vector coordinates */
} VEC;
/* Transformation matrix representation type */
typedef struct tagMATR
{
  FLT A[4][4]; /* Matrix elements */
} MATR;


/* unit matrix */
static MATR UnitMatrix =
{
  {
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}
  }
};

/* New math types (for drawing primitives) */
typedef struct tagVEC4
{
  FLT X, Y, Z, W; /* Vector coordinates */
} VEC4;

typedef struct tagVEC2
{
  FLT X, Y; /* Vector coordinates */
} VEC2;


/* Set matrix function */
__inline MATR MatrSet( FLT A00, FLT A01, FLT A02, FLT A03,
                       FLT A10, FLT A11, FLT A12, FLT A13,
                       FLT A20, FLT A21, FLT A22, FLT A23,
                       FLT A30, FLT A31, FLT A32, FLT A33 )
{
  MATR m =
  {
    {
      {A00, A01, A02, A03},
      {A10, A11, A12, A13},
      {A20, A21, A22, A23},
      {A30, A31, A32, A33},
    }
  };
  return m;
}
/* End of 'MatrSet' function */

/* Set vector.
 * ARGUMENTS:
 *   - X cordinate:
 *      FLT x:
 * RETURNS:
 *   - Vector 'v':
 *      VEC v;
 */
__inline VEC VecSet( FLT X, FLT Y, FLT Z )
{
  VEC r = {X, Y, Z};

  return r;
} /* End of 'VecSet' function */

/* Set vector.
 * ARGUMENTS:
 *   - X cordinate:
 *      FLT X;
 *   - Y cordinate:
 *      FLT Y;
  *   - Z cordinate:
 *      FLT Z;
 * RETURNS:
 *   - Vector 'v':
 *      VEC4 v;
 */
__inline VEC4 Vec4Set( FLT X, FLT Y, FLT Z, FLT W)
{
  VEC4 r = {X, Y, Z, W};

  return r;
} /* End of 'VecSet' function */

/* Set vector.
 * ARGUMENTS:
 *   - X cordinate:
 *      FLT x:
 * RETURNS:
 *   - Vector 'v':
 *      VEC2 v;
 */
__inline VEC2 Vec2Set( FLT X, FLT Y )
{
  VEC2 r = {X, Y};

  return r;
} /* End of 'VecSet' function */


/*  */
__inline MATR MatrSetTranlate( VEC D )
{
  MATR r =
  {
    {
      {1, 0, 0, 0},
      {0, 1, 0, 0},
      {0, 0, 1, 0},
      {D.X, D.Y, D.Z, 1},
    }
  };

  return r;
} /* End of 'MatrSetTranlate' function */

/* Set vector negative.
 * ARGUMENTS:
 *   - Vector:
 *      VEC V:
 * RETURNS:
 *   - Negative vector:
 *      VEC V;
 */
__inline VEC VecNeg( VEC V )
{
  return VecSet(-V.X, -V.Y, -V.Z);
} /* End of 'VecNegative' functioin */

/* Set vector by one number.
 * ARGUMENTS:
 *   - Number:
 *      FLT A:
 * RETURNS:
 *   - Vector 'v':
 *      VEC v;
 */
__inline VEC VecSet1( FLT A )
{
  VEC v;

  v.X = A;
  v.Y = A;
  v.Z = A;
  return v;
} /* End of 'VecSet1' function */

/* Set vector by one number.
 * ARGUMENTS:
 *   - Number:
 *      FLT A:
 * RETURNS:
 *   - Vector 'v':
 *      VEC v;
 */
__inline VEC4 Vec4Set1( FLT A )
{
  VEC4 v;

  v.X = A;
  v.Y = A;
  v.Z = A;
  v.W = A;
  return v;
} /* End of 'Vec4Set1' function */

/* Set vector by one number.
 * ARGUMENTS:
 *   - Number:
 *      FLT A:
 * RETURNS:
 *   - Vector 'v':
 *      VEC v;
 */
__inline VEC2 Vec2Set1( FLT A )
{
  VEC2 v;

  v.X = A;
  v.Y = A;
  return v;
} /* End of 'Vec2Set1' function */

/* Set vector by vector and number.
 * ARGUMENTS:
 *   - Number:
 *      FLT A:
 * RETURNS:
 *   - Vector 'v':
 *      VEC v;
 */
__inline VEC4 Vec4SetVec3 ( VEC V, FLT A )
{
  VEC4 V1 = {V.X, V.Y, V.Z, A};

  return V1;
} /* End of "Vec4SetVec3" function */

/* Sum up two vectors.
 * ARGUMENTS:
 *   - Vector:
 *      VEC V1:
     - Vector:
 *      VEC V2;
 * RETURNS:
 *   - New vector 'v':
 *      VEC v;
 */
__inline VEC VecAddVec( VEC V1, VEC V2 )
{
  VEC v = VecSet(V1.X + V2.X, V1.Y + V2.Y, V1.Z + V2.Z);

  return v;
} /* End of 'VecAddVec' function */

/* Sum up two vectors.
 * ARGUMENTS:
 *   - Vectors for sum:
 *      VEC V1, V2, V3.
 * RETURNS:
 *   - New vector 'v':
 *      VEC v;
 */
__inline VEC VecAddVec3( VEC V1, VEC V2, VEC V3 )
{
  VEC v = VecAddVec(VecAddVec(V1, V2), V3);

  return v;
} /* End of 'VecAddVec3' function */

/* Subtract one vector from another.
 * ARGUMENTS:
 *   - Vectors from which one we subtract:
 *      VEC V1:
     - Vector from which one we subtract:
 *      VEC V2;
 * RETURNS:
 *   - New vector 'V1':
 *      VEC V1;
 */
__inline VEC VecSubVec( VEC V1, VEC V2 )
{
  VEC v = VecSet(V1.X - V2.X, V1.Y - V2.Y, V1.Z - V2.Z);
  return v;
} /* End of 'VecSubVec' function */

/* Multiply vector on number.
 * ARGUMENTS:
 *   - Vectors that needed in calculating in number:
 *      VEC V1:
     - Numer:
 *      FLT N;
 * RETURNS:
 *   - New vector 'V1':
 *      VEC V1;
 */
__inline VEC VecMulNum( VEC V1, FLT N )
{
  V1.X *= N, V1.Y *= N, V1.Z *= N;
  return V1;
} /* End of 'VecMulNum' function */

/* Dot product function
 * ARGUMENTS:
 *   - Vectors that needed in calculatind in dot product:
 *      VEC V1, VEC V2.
 * RETURNS:
 *   - Vector:
 *      VEC V;
 */
__inline FLT VecDotVec( VEC V1, VEC V2 )
{
  return V1.X * V2.X + V1.Y * V2.Y + V1.Z * V2.Z;
} /* End of 'VecDotVec' function */

/* Cross product function
 * ARGUMENTS:
 *   - Vectors that needed in calculatind in cross product:
 *      VEC V1, VEC V2.
 * RETURNS:
 *   - Vector:
 *      VEC V;
 */
__inline VEC VecCrossVec( VEC V1, VEC V2 )
{
  return VecSet(V1.Y * V2.Z - V1.Z * V2.Y, V1.Z * V2.X - V1.X * V2.Z, V1.X * V2.Y - V1.Y * V2.X);
} /* End of 'VecCrossVec' function */

/* Find vector lenth.
 * ARGUMENTS:
 *   - Vector which lenth we need:
 *      VEC V.
 * RETURNS:
 *   - Lenth:
 *      FLT len;
 */
__inline FLT VecLen( VEC V )
{
  FLT len = VecDotVec(V, V);

  if (len == 1 || len == 0)
    return len;
  return sqrt(len);
} /* End of 'VecLen' function */

/* Division vector on number.
 * ARGUMENTS:
 *   - Vector which needed division on number:
 *      VEC V
 * RETURNS:
 *   - Vector:
 *      VEC V;
 */
__inline VEC VecDivNum( VEC V1, FLT N )
{
  V1.X /= N, V1.Y /= N, V1.Z /= N;
  return V1;
} /* End of 'VecDivNum' function*/

/* Normalize vector.
 * ARGUMENTS:
 *   - Vector which needed multyply on number:
 *      VEC V
 * RETURNS:
 *   - Vector:
 *      VEC V;
 */
__inline VEC VecNormalize( VEC V )
{
  FLT len = VecDotVec(V, V);

  if (len == 1 || len == 0)
    return V;
  return VecDivNum(V, sqrt(len));
} /* End of 'VecNormalize' function */

/* Matrix`s (3 x 3) translate function.
 * ARGUMENTS:
 *   - multiplied matrix:
 *       MATR M;
 * RETURNS:
 *   (MATR) translated matrix.
 */
__inline MATR MatrTranslate( VEC T )
{
  MATR m = UnitMatrix;

  m.A[3][0] = T.X;
  m.A[3][1] = T.Y;
  m.A[3][2] = T.Z;
  return m;
} /* End of 'MatrTranslate' function */

/* Matrix`s (3 x 3) determinat function.
 * ARGUMENTS:
 *   - multiplied matrix:
 *       MATR M;
 * RETURNS:
 *   (FLT) determinant.
 */
__inline FLT MatrDeterm3x3( FLT A11, FLT A12, FLT A13,
                            FLT A21, FLT A22, FLT A23,
                            FLT A31, FLT A32, FLT A33 )
{
  return A11 * A22 * A33 + A12 * A23 * A31 + A13 * A21 * A32 -
         A11 * A23 * A32 - A12 * A21 * A33 - A13 * A22 * A31;
} /* End of 'MatrDeterm3x3' function */

/* Matrix`s determinat function.
 * ARGUMENTS:
 *   - multiplied matrix:
 *       MATR M;
 * RETURNS:
 *   (FLT) determinant.
 */
__inline FLT MatrDeterm( MATR M )
{
  return
    + M.A[0][0] * MatrDeterm3x3(M.A[1][1], M.A[1][2], M.A[1][3],
                               M.A[2][1], M.A[2][2], M.A[2][3],
                               M.A[3][1], M.A[3][2], M.A[3][3]) +
    - M.A[0][1] * MatrDeterm3x3(M.A[1][0], M.A[1][2], M.A[1][3],
                               M.A[2][0], M.A[2][2], M.A[2][3],
                               M.A[3][0], M.A[3][2], M.A[3][3]) +
    + M.A[0][2] * MatrDeterm3x3(M.A[1][0], M.A[1][1], M.A[1][3],
                               M.A[2][0], M.A[2][1], M.A[2][3],
                               M.A[3][0], M.A[3][1], M.A[3][3]) +
    - M.A[0][3] * MatrDeterm3x3(M.A[1][0], M.A[1][1], M.A[1][2],
                               M.A[2][0], M.A[2][1], M.A[2][2],
                               M.A[3][0], M.A[3][1], M.A[3][2]);
} /* End of 'MatrDeterm' function */

/* Return Unitmatrix function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrIdentity( VOID )
{
  MATR I = UnitMatrix;
  return I;
} /* End of 'MatrIdentity' function */

/*  Matr rotate function.
 * ARGUMENTS:
 *   - source vector:
 *       VEC R;
 *   - angle:
 *       FLT AngleInDegree;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrRotate( FLT AngleInDegree, VEC R )
{
  FLT
    A = D2R(AngleInDegree),
    si = sin(A), co = cos(A);
  VEC V = VecNormalize(R);
  MATR M = 
  {
    {
      {co + V.X * V.X * ( 1 - co),
        V.X * V.Y * (1 - co) + V.Z * si,
         V.X * V.Z * (1 - co) - V.Y * si, 0},
      {V.Y * V.X * (1 - co) - V.Z * si,
        co + V.Y * V.Y * (1 - co),
         V.Y * V.Z * (1 - co) + V.X * si, 0},
      {V.Z * V.X * (1 - co) + V.Y * si,
        V.Z * V.Y * (1 - co) - V.X * si,
         co + V.Z * V.Z * (1 - co), 0},
      {0, 0, 0, 1}
    }
  };

  return M;
}

/* Rotate vector by 'Y' function.
 * ARGUMENTS:
 *   - angle:
 *       FLT AngleInDegree;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrRotateY( FLT AngleInDegree )
{
    DBL
    A = D2R(AngleInDegree),
    si = sin(A), co = cos(A);
  MATR M = 
  {
    {
      {co , 0, -si, 0},
      {0, 1, 0, 0},
      {si, 0, co , 0},
      {0, 0, 0, 1}
    }
  };
  return M;
} /* End of 'MatrRotateY' function */

/* Rotate  vector by 'Y' function.
 * ARGUMENTS:
 *   - angle:
 *       FLT AngleInDegree;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrRotateZ( FLT AngleInDegree )
{
    FLT
    A = D2R(AngleInDegree),
    si = sin(A), co = cos(A);
  MATR M = 
  {
    {
      {co , si, 0, 0},
      {-si, co, 1, 0},
      {0, 0, 1, 0},
      {0, 0, 0, 1}
    }
  };
  return M;
} /* End of 'MatrRotateZ' function */

/* Rotate  vector by 'Y' function.
 * ARGUMENTS:
 *   - angle:
 *       FLT AngleInDegree;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrRotateX( FLT AngleInDegree )
{
  FLT
    A = D2R(AngleInDegree),
    si = sin(A), co = cos(A);
  MATR M = 
  {
    {
      {1, 0, 0, 0},
      {0, co, si, 0},
      {0, -si, co , 0},
      {0, 0, 0, 1}
    }
  };
  return M;
} /* End of 'MatrRotateX' function */

/* Vector by matrix multiplication (with homogenious devide) function.
 * ARGUMENTS:
 *   - source vector:
 *       VEC V;
 *   - multiplied matrix:
 *       MATR M;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VecMulMatr( VEC V, MATR M )
{
  FLT w = V.X * M.A[0][3] + V.Y * M.A[1][3] + V.Z * M.A[2][3] + M.A[3][3];

  return VecSet((V.X * M.A[0][0] + V.Y * M.A[1][0] + V.Z * M.A[2][0] + M.A[3][0]) / w,
                (V.X * M.A[0][1] + V.Y * M.A[1][1] + V.Z * M.A[2][1] + M.A[3][1]) / w,
                (V.X * M.A[0][2] + V.Y * M.A[1][2] + V.Z * M.A[2][2] + M.A[3][2]) / w);
} /* End of 'VecMulMatr' function */

/* Matrix multiply on matrix (with homogenious devide) function.
 * ARGUMENTS:
 *   - multiplied matrix:
 *       MATR M1;
 *   - multiplied matrix:
 *       MATR M2;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrMulMatr( MATR M1, MATR M2 )
{
  MATR r = {{{0}}};

  r.A[0][0] = M1.A[0][0] * M2.A[0][0] + M1.A[0][1] * M2.A[1][0] + M1.A[0][2] * M2.A[2][0] +
    M1.A[0][3] * M2.A[3][0];

  r.A[0][1] = M1.A[0][0] * M2.A[0][1] + M1.A[0][1] * M2.A[1][1] + M1.A[0][2] * M2.A[2][1] +
    M1.A[0][3] * M2.A[3][1];

  r.A[0][2] = M1.A[0][0] * M2.A[0][2] + M1.A[0][1] * M2.A[1][2] + M1.A[0][2] * M2.A[2][2] +
    M1.A[0][3] * M2.A[3][2];

  r.A[0][3] = M1.A[0][0] * M2.A[0][3] + M1.A[0][1] * M2.A[1][3] + M1.A[0][2] * M2.A[2][3] +
    M1.A[0][3] * M2.A[3][3];


  r.A[1][0] = M1.A[1][0] * M2.A[0][0] + M1.A[1][1] * M2.A[1][0] + M1.A[1][2] * M2.A[2][0] +
    M1.A[1][3] * M2.A[3][0];

  r.A[1][1] = M1.A[1][0] * M2.A[0][1] + M1.A[1][1] * M2.A[1][1] + M1.A[1][2] * M2.A[2][1] +
    M1.A[1][3] * M2.A[3][1];

  r.A[1][2] = M1.A[1][0] * M2.A[0][2] + M1.A[1][1] * M2.A[1][2] + M1.A[1][2] * M2.A[2][2] +
    M1.A[1][3] * M2.A[3][2];

  r.A[1][3] = M1.A[1][0] * M2.A[0][3] + M1.A[1][1] * M2.A[1][3] + M1.A[1][2] * M2.A[2][3] +
    M1.A[1][3] * M2.A[3][3];


  r.A[2][0] = M1.A[2][0] * M2.A[0][0] + M1.A[2][1] * M2.A[1][0] + M1.A[2][2] * M2.A[2][0] +
    M1.A[2][3] * M2.A[3][0];

  r.A[2][1] = M1.A[2][0] * M2.A[0][1] + M1.A[2][1] * M2.A[1][1] + M1.A[2][2] * M2.A[2][1] +
    M1.A[2][3] * M2.A[3][1];

  r.A[2][2] = M1.A[2][0] * M2.A[0][2] + M1.A[2][1] * M2.A[1][2] + M1.A[2][2] * M2.A[2][2] +
    M1.A[2][3] * M2.A[3][2];

  r.A[2][3] = M1.A[2][0] * M2.A[0][3] + M1.A[2][1] * M2.A[1][3] + M1.A[2][2] * M2.A[2][3] +
    M1.A[2][3] * M2.A[3][3];


  r.A[3][0] = M1.A[3][0] * M2.A[0][0] + M1.A[3][1] * M2.A[1][0] + M1.A[3][2] * M2.A[2][0] +
    M1.A[3][3] * M2.A[3][0];

  r.A[3][1] = M1.A[3][0] * M2.A[0][1] + M1.A[3][1] * M2.A[1][1] + M1.A[3][2] * M2.A[2][1] +
    M1.A[3][3] * M2.A[3][1];

  r.A[3][2] = M1.A[3][0] * M2.A[0][2] + M1.A[3][1] * M2.A[1][2] + M1.A[3][2] * M2.A[2][2] +
    M1.A[3][3] * M2.A[3][2];

  r.A[3][3] = M1.A[3][0] * M2.A[0][3] + M1.A[3][1] * M2.A[1][3] + M1.A[3][2] * M2.A[2][3] +
    M1.A[3][3] * M2.A[3][3];

  return r;
} /* End of 'MatrMulMatr' function */

/* Matrix inversion function.
 * ARGUMENTS:
 *   - multiplied matrix:
 *       MATR M;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrInverse( MATR M )
{
  FLT det = MatrDeterm(M);
  MATR r;

  if (det == 0)
    return MatrIdentity();

  /* build adjoint matrix */
  r.A[0][0] =
    +MatrDeterm3x3(M.A[1][1], M.A[1][2], M.A[1][3],
                   M.A[2][1], M.A[2][2], M.A[2][3],
                   M.A[3][1], M.A[3][2], M.A[3][3]) / det;

  r.A[1][0] =
    -MatrDeterm3x3(M.A[1][0], M.A[1][2], M.A[1][3],
                   M.A[2][0], M.A[2][2], M.A[2][3],
                   M.A[3][0], M.A[3][2], M.A[3][3]) / det;

  r.A[2][0] =
    +MatrDeterm3x3(M.A[1][0], M.A[1][1], M.A[1][3],
                   M.A[2][0], M.A[2][1], M.A[2][3],
                   M.A[3][0], M.A[3][1], M.A[3][3]) / det;

  r.A[3][0] =
    -MatrDeterm3x3(M.A[1][0], M.A[1][1], M.A[1][2],
                   M.A[2][0], M.A[2][1], M.A[2][2],
                   M.A[3][0], M.A[3][1], M.A[3][2]) / det;

  r.A[0][1] =
    -MatrDeterm3x3(M.A[0][1], M.A[0][2], M.A[0][3],
                   M.A[2][1], M.A[2][2], M.A[2][3],
                   M.A[3][1], M.A[3][2], M.A[3][3]) / det;

  r.A[1][1] =
    +MatrDeterm3x3(M.A[0][0], M.A[0][2], M.A[0][3],
                   M.A[2][0], M.A[2][2], M.A[2][3],
                   M.A[3][0], M.A[3][2], M.A[3][3]) / det;

  r.A[2][1] =
    -MatrDeterm3x3(M.A[0][0], M.A[0][1], M.A[0][3],
                   M.A[2][0], M.A[2][1], M.A[2][3],
                   M.A[3][0], M.A[3][1], M.A[3][3]) / det;

  r.A[3][1] =
    +MatrDeterm3x3(M.A[0][0], M.A[0][1], M.A[0][2],
                   M.A[2][0], M.A[2][1], M.A[2][2],
                   M.A[3][0], M.A[3][1], M.A[3][2]) / det;

  r.A[0][2] =
    +MatrDeterm3x3(M.A[0][1], M.A[0][2], M.A[0][3],
                   M.A[1][1], M.A[1][2], M.A[1][3],
                   M.A[3][1], M.A[3][2], M.A[3][3]) / det;

  r.A[1][2] =
    -MatrDeterm3x3(M.A[0][0], M.A[0][2], M.A[0][3],
                   M.A[1][0], M.A[1][2], M.A[1][3],
                   M.A[3][0], M.A[3][2], M.A[3][3]) / det;

  r.A[2][2] =
    +MatrDeterm3x3(M.A[0][0], M.A[0][1], M.A[0][3],
                   M.A[1][0], M.A[1][1], M.A[1][3],
                   M.A[3][0], M.A[3][1], M.A[3][3]) / det;

  r.A[3][2] =
    -MatrDeterm3x3(M.A[0][0], M.A[0][1], M.A[0][2],
                   M.A[1][0], M.A[1][1], M.A[1][2],
                   M.A[3][0], M.A[3][1], M.A[3][2]) / det;

  r.A[0][3] =
    -MatrDeterm3x3(M.A[0][1], M.A[0][2], M.A[0][3],
                   M.A[1][1], M.A[1][2], M.A[1][3],
                   M.A[2][1], M.A[2][2], M.A[2][3]) / det;

  r.A[1][3] =
    +MatrDeterm3x3(M.A[0][0], M.A[0][2], M.A[0][3],
                   M.A[1][0], M.A[1][2], M.A[1][3],
                   M.A[2][0], M.A[2][2], M.A[2][3]) / det;

  r.A[2][3] =
    -MatrDeterm3x3(M.A[0][0], M.A[0][1], M.A[0][3],
                   M.A[1][0], M.A[1][1], M.A[1][3],
                   M.A[2][0], M.A[2][1], M.A[2][3]) / det;

  r.A[3][3] =
    +MatrDeterm3x3(M.A[0][0], M.A[0][1], M.A[0][2],
                   M.A[1][0], M.A[1][1], M.A[1][2],
                   M.A[2][0], M.A[2][1], M.A[2][2]) / det;

  return r;
} /* End of 'MatrInverse' function */

/*  */
__inline MATR MatrView( VEC Loc, VEC At, VEC Up1 )
{
  VEC
    Dir = VecNormalize(VecSubVec(At, Loc)),
    Right = VecNormalize(VecCrossVec(Dir, Up1)),
    Up = VecCrossVec(Right, Dir);
  MATR m = 
  {
    {
      {Right.X, Up.X, -Dir.X, 0},
      {Right.Y, Up.Y, -Dir.Y, 0},
      {Right.Z, Up.Z, -Dir.Z, 0},
      {-VecDotVec(Loc, Right), -VecDotVec(Loc, Up), VecDotVec(Loc, Dir), 1}
    }
  };
  return m;
} /* End of 'MatrView' function */

/*  */
__inline MATR MatrOrtho( FLT Left, FLT Right,
               FLT Bottom, FLT Top,
               FLT Near, FLT Far )
{
  return MatrSet(2 / (Right - Left), 0, 0, 0,
                 0, 2 / (Top - Bottom), 0, 0,
                 0, 0, -2 / (Far - Near), 0,
                 -(Right + Left) / (Right - Left), -(Top + Bottom) / (Top - Bottom), -(Far + Near) / (Far - Near), 1);
} /* End of 'MatrOrtho' function */

/*  */
__inline MATR MatrFrustum(FLT l, FLT r, FLT b, FLT t, FLT n, FLT f )
{
  return MatrSet(2 * n / (r - l), 0, 0, 0,
                 0, 2 * n / (t - b), 0, 0,
                 (r + l) / (r - l), (t + b) / (t - b), (f + n) / (n - f), -1,
                 0, 0, 2 * n  * f / (n - f), 0);

} /* End of 'MatrFrustum' function */

/*  */
__inline MATR MatrMulMatr3( MATR M1, MATR M2, MATR M3 )
{
  return MatrMulMatr(MatrMulMatr(M1, M2), M3);
} /* End of 'MatrMulMatr3' function */

/* Matrix transpose function.
 * ARGUMENTS:
 *   - multiplied matrix:
 *       MATR M;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrTranspose( MATR M )
{
  MATR r;

  r.A[0][0] = M.A[0][0];
  r.A[1][0] = M.A[0][1];
  r.A[2][0] = M.A[0][2];
  r.A[3][0] = M.A[0][3];

  r.A[0][1] = M.A[1][0];
  r.A[1][1] = M.A[1][1];
  r.A[2][1] = M.A[1][2];
  r.A[3][1] = M.A[1][3];

  r.A[0][2] = M.A[2][0];
  r.A[1][2] = M.A[2][1];
  r.A[2][2] = M.A[2][2];
  r.A[3][2] = M.A[2][3];

  r.A[0][3] = M.A[3][0];
  r.A[1][3] = M.A[3][1];
  r.A[2][3] = M.A[3][2];
  r.A[3][3] = M.A[3][3];

  return r;
} /* End of 'MatrTranspose' function */

/* Vector transform function.
 * ARGUMENTS:
 *   - multiplied matrix:
 *       MATR M;
 *   - vector:
 *       VEC V;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VectorTransform( VEC V, MATR M )
{
  return VecSet(V.X * M.A[0][0] + V.Y * M.A[1][0] + V.Z * M.A[2][0],
                V.X * M.A[0][1] + V.Y * M.A[1][1] + V.Z * M.A[2][1],
                V.X * M.A[0][2] + V.Y * M.A[1][2] + V.Z * M.A[2][2]);
} /* End of 'VectorTransform' functon */

/*  */
__inline MATR MatrScale( VEC S )
{
  MATR m = 
  {
    {
      {S.X, 0, 0, 0},
      {0, S.Y, 0, 0},
      {0, 0, S.Z, 0},
      {0, 0, 0, 1}
    }
  };
  return m;
}
#endif /* __mth_h_ */

/* End of 'mth.h' file */