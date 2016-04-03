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
  Player	player(vec3(10, 5, 1), 90, &map, data->net.playerIndexUdp);
  Camera camera(glm::vec3(0, 0, 10), 70.0f, (float)WIN_X / WIN_Y, 0.01f, 500.0f);
  Transform transform;
  int		fps = 0;
  int		t = time(NULL);
  Vertex v[] = {Vertex(vec3(0, 0, 0), vec2(0, 0)),
		Vertex(vec3(0, 0, PLAYER_HEIGHT), vec2(0, 1)),
		Vertex(vec3(0, PLAYER_SIZE, PLAYER_HEIGHT), vec2(1, 1)),
		Vertex(vec3(0, PLAYER_SIZE, 0), vec2(0, 1)),
		Vertex(vec3(PLAYER_SIZE, 0, 0), vec2(0, 1)),
		Vertex(vec3(PLAYER_SIZE, 0, PLAYER_HEIGHT), vec2(1, 1)),
		Vertex(vec3(PLAYER_SIZE, PLAYER_SIZE, PLAYER_HEIGHT), vec2(1, 0)),
		Vertex(vec3(PLAYER_SIZE, PLAYER_SIZE, 0), vec2(0, 0))};
  unsigned int index[] = {0, 2, 3,  0, 1, 2,
		      0, 5, 1,  0, 4, 5,
		      1, 6, 2,  1, 5, 6,
		      2, 7, 3,  2, 6, 7,
		      3, 4, 0,  3, 7, 4,
		      5, 7, 6,  5, 4, 7};
  Mesh playerModel(v, 36, index, 36);
  unsigned char	tt[] = {255, 255, 255, 255};
  Texture text(tt, 1, 1, false);
  int	i;
  int	count(1), tot(0);

  // float		lights[120] =
  //   {2, 0, 0, 0,  5, 7, 4, 400.0,
  //    30, 40, 5, 10};

  while (!display.IsClosed())
    {
      fps++;
      if (t != time(NULL))
	{
	  t = time(NULL);
	  tot += fps;
	  printf("\r%d\t%.2f\t", fps, (double)tot / count);
	  fflush(stdout);
	  fps = 0;
	  count++;
	}

      shader.Bind();

      shader.Update(transform, camera);
      display.Clear(0.0f, 0.3f, 0.8f, 1.0f);
      map.Draw();
      i = 0;
      while (i < 10)
      	{
      	  if (i != player.GetId())
      	    {
      	      transform.GetPos() = data->players[i].position;
      	      shader.Bind();
      	      shader.Update(transform, camera);
      	      text.Bind(0);
      	      playerModel.Draw();
      	    }
      	  i++;
      	}
      display.Update(camera, map, player, data);
      player.FillCPlayer(data->players + player.GetId(), camera.GetFor());
    }
  return (0);
}
