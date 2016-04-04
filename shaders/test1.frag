#version 130

varying vec2 texCoord0;
varying vec3 normal0;
varying float z0;
varying float lum;
// varying	vec3 v;
// varying vec3 N;

uniform sampler2D diffuse;

void	main()
{
  // float z = z0;
  // vec3 L = normalize(gl_LightSource[0].position.xyz - v);
  // vec3 E = normalize(-v); we are in Eye Coordinates, so EyePos is (0,0,0)
  // vec3 R = normalize(-reflect(L,N));

  // calculate Ambient Term:
  // vec4 Iamb = gl_FrontLightProduct[0].ambient;

  // calculate Diffuse Term:
  // vec4 Idiff = gl_FrontLightProduct[0].diffuse * max(dot(N, L), 0.0);
  // Idiff = clamp(Idiff, 0.0, 1.0);

  // calculate Specular Term:
  // vec4 Ispec = gl_FrontLightProduct[0].specular
  //   * pow(max(dot(R, E), 0.0), 0.3 * gl_FrontMaterial.shininess);
  // Ispec = clamp(Ispec, 0.0, 1.0);
  // write Total Color:
  // gl_FragColor = texture2D(diffuse, texcoord0) * gl_FrontLightModelProduct.sceneColor + Iamb + Idiff + Ispec;

  gl_FragColor = texture2D(diffuse, texCoord0) * clamp(dot(normalize(-vec3(0.3, 0.5, 0.6)), normal0) * lum, 0.2, 1.0);

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
