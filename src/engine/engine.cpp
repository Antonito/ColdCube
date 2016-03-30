//#include <GL/glew.h>
#include <ctime>
#include "game.hpp"
#include "common_structs.hpp"
#include "engine/display.hpp"
#include "engine/shader.hpp"
#include "engine/mesh.hpp"
#include "engine/player.hpp"
#include "engine/texture.hpp"
#include "engine/transform.hpp"
#include "engine/camera.hpp"
#include "engine/map.hpp"
#include <time.h>

using namespace glm;

Mesh	SetPlanes(int, vec3);

int	engineMain(Display &display, t_data *data)
{
  Shader	shader("shaders/test1");

  Map		map("map");
  Player	player(vec3(10, 5, 1), 90, &map, data->net->playerIndexUdp);
  t_player	players[10];
  Camera camera(glm::vec3(0, 0, 10), 70.0f, (float)WIN_X / WIN_Y, 0.01f, 500.0f);
  Transform transform;
  int		fps = 0;
  int		t = time(NULL);
  Vertex v[] = {Vertex(vec3(0, 0, 0), vec2(0, 0)),
		Vertex(vec3(0, 0, PLAYER_SIZE), vec2(0, 0)),
		Vertex(vec3(0, PLAYER_SIZE, PLAYER_SIZE), vec2(0, 0)),
		Vertex(vec3(0, PLAYER_SIZE, 0), vec2(0, 0)),
		Vertex(vec3(PLAYER_SIZE, 0, 0), vec2(0, 0)),
		Vertex(vec3(PLAYER_SIZE, 0, PLAYER_SIZE), vec2(0, 0)),
		Vertex(vec3(PLAYER_SIZE, PLAYER_SIZE, PLAYER_SIZE), vec2(0, 0)),
		Vertex(vec3(PLAYER_SIZE, PLAYER_SIZE, 0), vec2(0, 0))};
  unsigned int i[] = {0, 3, 2,  0, 2, 1,
		      0, 1, 5,  0, 5, 4,
		      1, 2, 6,  1, 6, 5,
		      2, 3, 7,  2, 7, 6,
		      3, 0, 4,  3, 4, 7,
		      5, 6, 7,  5, 7, 4};
  Mesh playerModel(v, 8, i, 36);
  int	i;

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
      shader.Update(transform, camera);
      map.Draw();
      i = 0;
      while (i < 10)
	{
	  transform.GetPos() = players[i].pos;
	  shader.Update(transform, camera);
	  playerModel.Draw();
	}
      display.Update(camera, map, player);
    }
  return (0);
}
