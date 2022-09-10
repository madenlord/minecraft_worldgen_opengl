#shader vertex
#version 430 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

out vec2 v_texCoord;

uniform mat4 u_VP;
uniform mat4 u_M;

void main()
{
   gl_Position = u_VP * u_M * position;
   v_texCoord = texCoord;
};

#shader fragment
#version 430 core

layout(location = 0) out vec4 color;

in vec2 v_texCoord;

uniform vec4 u_color;
uniform sampler2D u_texture;

void main()
{
   vec4 texColor = texture(u_texture, v_texCoord);
   color = texColor; 
};