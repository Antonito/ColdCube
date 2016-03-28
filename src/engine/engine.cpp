#include <GL/glew.h>
#include "engine/display.hpp"
#include "engine/shader.hpp"
#include "engine/mesh.hpp"
#include "engine/texture.hpp"
#include "engine/transform.hpp"
#include "engine/camera.hpp"
#include "engine/map.hpp"
#include <ctime>

#define WIDTH 1280
#define HEIGHT 720

#include <time.h>

using namespace glm;

Mesh	SetPlanes(int, vec3);

int	engineMain()
{
  Display display(WIDTH, HEIGHT, "The display title");

  Shader	shader("shaders/test1");

  Map		map("map");
  Camera camera(glm::vec3(0, 0, 10), 70.0f, (float)WIDTH / HEIGHT, 0.01f, 500.0f);
  Transform transform;
  int		fps = 0;
  int		t = time(NULL);
  // float		lights[120] =
  //   {2, 0, 0, 0,  5, 7, 4, 400.0,
  //    30, 40, 5, 10};

  while (!display.IsClosed())
    {
      fps++;
      if (t != time(NULL))
	{
	  t = time(NULL);
	  // printf("\r%d   ", fps);
	  // fflush(stdout);
	  fps = 0;
	}
      display.Clear(0.0f, 0.3f, 0.8f, 1.0f);

      shader.Bind();
      shader.Update(transform, camera// , 2, lights
		    );
      map.Draw();
      display.Update(camera, map);
    }
  return (0);
}
