/**/
layout(points) in;

layout(binding = 0) uniform sampler2D Tex;
uniform float Time;

/* Camera UBO data representation type */
layout(std140, binding = 0) uniform UBO_CAMERA
{
  mat4 MatrVP;              /* Premultiplied (View and Proj) matrix */
  mat4 MatrV;               /* Matrix 'view' */
  mat4 MatrP;               /*  */
  vec4 CamLoc4;              /* Camera location */
  vec4 CamRight4;            /* Camera right diraction */
  vec4 CamUp4;               /* Camera up diraction */
  vec4 CamDir4;              /* Camera forward diraction */
  vec4 FrameWHProjSizeDist; /* Camera frame size, projection and distance */
};

#define CamLoc CamLoc4.xyz
#define CamRight CamRight4.xyz
#define CamUp CamUp4.xyz
#define CamDir CamDir4.xyz
#define FrameW FrameWHProjSizeDist.x
#define FrameH FrameWHProjSizeDist.y
#define ProjSize FrameWHProjSizeDist.z
#define ProjDist FrameWHProjSizeDist.w

vec3 Get( float X, float Y )
{
  return vec3(X, Y, 0);
} 

out VS_OUT
{
  vec3 Position; 
  vec2 TexCoord;
  vec3 Normal;  
  vec4 Color;
} vs_out;
 
void main( void )
{
  vec3 p = gl_in[0].gl_Position.xyz;
  float z = 0;
  gl_Position = vec4(Get(-1, 1), 1);


}
