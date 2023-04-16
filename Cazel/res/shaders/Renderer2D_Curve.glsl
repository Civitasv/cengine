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
  vec4 Vertex;
};

layout (location = 0) out VertexOutput Output;
layout (location = 1) out flat int v_EntityID;

float length2(in vec2 v) {
  return dot(v,v);
}

float sdSegmentSq(in vec2 p, in vec2 a, in vec2 b)
{
	vec2 pa = p-a, ba = b-a;
	float h = clamp( dot(pa,ba)/dot(ba,ba), 0.0, 1.0 );
	return length2( pa - ba*h );
}

vec2 udBezier(vec2 p0, vec2 p1, vec2 p2, in vec2 p3, vec2 pos)
{   
    const int kNum = 50;
    vec2 res = vec2(1e10,0.0);
    vec2 a = p0;
    for( int i=1; i<kNum; i++ )
    {
        float t = float(i)/float(kNum-1);
        float s = 1.0-t;
        vec2 b = p0*s*s*s + p1*3.0*s*s*t + p2*3.0*s*t*t + p3*t*t*t;
        float d = sdSegmentSq( pos, a, b );
        if( d<res.x ) res = vec2(d,t);
        a = b;
    }
    
    return vec2(sqrt(res.x),res.y);
}

void main()
{
	Output.Color = a_Color;
	Output.Vertex = vec4(a_Position, 1.0);

	v_EntityID = a_EntityID;

	gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
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
layout (location = 1) in flat int v_EntityID;

void main()
{
	o_Color = Input.Color;
	o_EntityID = v_EntityID;
}
