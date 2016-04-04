#version 130

attribute vec3 position;
attribute vec2 texCoord;
attribute vec3 normal;

varying vec2 texCoord0;
varying vec3 normal0;
varying float z0;

// varying	vec3 N;
// varying vec3 v;
varying float lum;

uniform mat4 transform;
uniform mat4 shadow_mat;
uniform vec3 light;

void	main()
{
vec4	temp;
vec3 l = light;
vec4 pa = shadow_mat * vec4(position, 1.0);
vec3 p = vec3(pa.x, pa.y, pa.z);
	// lum = 0;
	// int i = 1;
	// vec3 v;
	// while (i < lights[0].x)
	//   {
	//     v = vec3(lights[i]) - position;
	//     lum += lights[i].z * dot(normalize(v), normal)
	//        / length(v);
	//     i++;
	//   }
	// lum /= lights[0].x;
	// lum += 1;
	gl_Position = transform * vec4(position, 1.0);
	// v = vec3(gl_Position);
	// N = normal;
	texCoord0 = texCoord;
	temp = shadow_mat * vec4(normal, 0.0);
	normal0 = vec3(temp.x, temp.y, temp.z);
	z0 = gl_Position.z;

	lum = dot(normalize(l - p), normal0) + 1;
	lum = 1;
}
