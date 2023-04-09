#type vertex
#version 330 core
layout(location = 0) in vec2 position;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;
void main() {
  gl_Position = u_ViewProjection * u_Transform * vec4(position, 1.0, 1.0);
}

#type fragment
#version 330 core
out vec4 FragColor;

void main() { FragColor = vec4(1.0, 0.0, 1.0, 1.0); }