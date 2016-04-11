#version 130

varying vec2 texCoord;

uniform sampler2D tex;

void main()
{
  vec2	p = texCoord;
  p = 2 * p - 1.0;
  float radius = length(p);
  radius = pow(radius, 1) / 3.0;
  p = p * (1 + radius);
  // p.y *= 1.5;
  p /= 1.2;

  vec2 r = 0.5 * (p + 1.0);
  p *= 1.012;
  vec2 g = 0.5 * (p + 1.0);
  p *= 1.02;
  vec2 b = 0.5 * (p + 1.0);
  gl_FragColor.r = texture2D(tex, r).r;
  gl_FragColor.g = texture2D(tex, g).g;
  gl_FragColor.b = texture2D(tex, b).b;
}
