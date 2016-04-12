#version 130

attribute vec3 position;
attribute vec2 texCoord;
attribute vec3 normal;

varying vec2 texCoord0;
varying vec3 normal0;
varying float z0;
varying float lum;

uniform mat4 transform;
uniform mat4 shadow_mat;
uniform vec4 light;
uniform mat4 mvp;

out vec3 normal2;
out vec3 eye2;
out vec3 lightDir2;

void main () {

  vec4 pos = shadow_mat * vec4(position, 1.0);
  texCoord0 = texCoord;
  normal2 = vec3(normalize(shadow_mat * vec4(normal, 0.0)));
  lightDir2 = vec3(light - pos);
  eye2 = vec3(pos);

  gl_Position = transform * vec4(position, 1.0);
}
