//--------------------------
// - Cazel 2D -
// Renderer2D Curve Shader
// --------------------------

#type vertex
#version 450 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in int a_EntityID;

layout(std140, binding = 0) uniform Camera
{
  mat4 u_ViewProjection;
};

struct VertexOutput
{
  vec4 Color;
};

layout (location = 0) out VertexOutput Output;
layout (location = 1) out flat int v_EntityID;

void main()
{
	Output.Color = a_Color;

	v_EntityID = a_EntityID;

	gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
}

#type geom
#version 450 core
layout (lines_adjacency) in; // 基元类型模式 lines_adjacency, 输入图元邻接线，输入数组 gl_in[] 大小为4，刚好绘制三次 bezier 曲线需要四个控制点
layout (line_strip, max_vertices = 32) out; // 将一个点变为最多 32 个可连成线条的点 交给 FragShader

struct VertexOutput {
  vec4 Color;
};
layout (location = 0) in VertexOutput Input[];
layout (location = 1) in flat int v_EntityID[];

layout (location = 0) out VertexOutput Output;
layout (location = 1) out flat int g_EntityID;

void creatBezier(){
  int segments = 32;
  float delta = 1.0 / float(segments);
  vec4 v;
  for (int i = 0; i <= segments; ++i)
  {
    float   t   =   delta * float(i); // 插值计算参数 t 与 segment 关联起来
    vec3    p0  =   gl_in[0].gl_Position.xyz;   
    vec3    p1  =   gl_in[1].gl_Position.xyz;   
    vec3    p2  =   gl_in[2].gl_Position.xyz;   
    vec3    p3  =   gl_in[3].gl_Position.xyz;   
    float   len =   length(p1 - p0)/2.0;   
    // Linear interpolation 
    vec3    p;  
    p.x = (1 - t) * (1 - t) * (1 - t) * p0.x + 3 * t * (1 - t) * (1 - t)* p1.x + 3 * t * t * (1 - t) * p2.x + t * t * t * p3.x;
    p.y = (1 - t) * (1 - t) * (1 - t) * p0.y + 3 * t * (1 - t) * (1 - t)* p1.y + 3 * t* t * (1 - t) * p2.y + t * t * t * p3.y;
    p.z =   0;
    gl_Position = vec4(p, 1);
    Output.Color = Input[0].Color;
    g_EntityID = v_EntityID[0];
    EmitVertex();
  }
  EndPrimitive();
}
 
void main(){
  creatBezier();
}

#type fragment
#version 450 core

layout(location = 0) out vec4 o_Color;
layout(location = 1) out int o_EntityID;

struct VertexOutput
{
	vec4 Color;
};

layout (location = 0) in VertexOutput Input;
layout (location = 1) in flat int g_EntityID;

void main()
{
	o_Color = Input.Color;
	o_EntityID = g_EntityID;
}
