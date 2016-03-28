#version 330 core

in vec3 in_position;
uniform mat4 MVP;

void main(void)
{
  gl_Position = MVP * vec4(in_position, 1);
}
