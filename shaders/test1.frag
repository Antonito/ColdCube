#version 130

varying vec2 texCoord0;

uniform sampler2D diffuse;

out vec4 colorOut;

in  vec3 normal2;
in  vec3 eye2;
in  vec3 lightDir2;

void main() {
  float minimum = 0.5;
  vec4 diff = vec4(0.3, 0.3, 0.3, 1.0);
  vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);
  vec4 specular = vec4(0.75, 0.75, 0.75, 1.0);
  float shininess = 0.5;

  vec4 spec = vec4(0.0, 0.0, 0.0, 0.0);

  vec3 n = normalize(normal2);
  vec3 l = normalize(lightDir2);
  vec3 e = normalize(eye2);

  float intensity = max(dot(n,l), 0.0);
  if (intensity > 0.0) {
    vec3 h = normalize(l + e);
    float intSpec = max(dot(h,n), 0.0) / 5;
    spec = specular * pow(intSpec, shininess);
  }

  colorOut = max(intensity * diff + spec, ambient) *
    texture2D(diffuse, texCoord0);
  if (colorOut.a == 0.0)
    discard ;
}
