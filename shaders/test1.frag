#version 120

varying vec2 texCoord0;
varying vec3 normal0;
varying float z0;
// varying float lum;

uniform sampler2D diffuse;

void	main()
{
  // float z = z0;
  gl_FragColor = texture2D(diffuse, texCoord0) * clamp(dot(normalize(-vec3(0.3, 0.5, 0.6)), normal0), 0.2, 1.0);

  if (gl_FragColor.a == 0.0)
    discard ;
  // z = 1 - z0 / 200.0;
  // if (z >= 0)
  //   {
  //     gl_FragColor.r *= z;
  //     gl_FragColor.g = gl_FragColor.g * z + (1 - z) * 0.3;
  //     gl_FragColor.b = gl_FragColor.b * z + (1 - z) * 0.8;
  //   }
  //  gl_FragColor *= clamp(dot(vec3(0, 0, -1), normal0), 0.5, 0.8);
//	     vec4(0.9, 0.9, 0.9, 0.1)
// * clamp(dot(-vec3(0, 0.2, 0.8), normal0), 0.0, 1.0);
}
