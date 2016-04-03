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
#include "engine/animation_player.hpp"
#include <time.h>

using namespace glm;

Mesh	SetPlanes(int, vec3);

int	engineMain(Display &display, t_data *data)
{
  Shader	shader("shaders/test1");

  Map		map("map");
  Player	player(vec3(10, 5, 1), 90, &map, data->net.playerIndexUdp);
  Camera camera(glm::vec3(0, 0, 10), 360.0f, (float)WIN_X / WIN_Y, 0.01f, 500.0f);
  Transform transform;
  int		fps = 0;
  int		t = time(NULL);
  unsigned char	tt[] = {255, 255, 255, 255};
  Texture text(tt, 1, 1, false);
  int	i;
  int	count(1), tot(0);
  vec2	lastPos[10] = {vec2(0, 0)};

  // float		lights[120] =
  //   {2, 0, 0, 0,  5, 7, 4, 400.0,
  //    30, 40, 5, 10};

  i = 0;
  while (i < 10)
    {
      data->players[i].position = vec3(0, 0, 1);
      data->players[i].direction = vec3(0, 1, 0);
      i++;
    }

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
      transform.GetPos() = vec3(0, 0, 0);
      map.Draw();
      i = 0;
      while (i < 10)
      	{
      	  if (i != player.GetId() || player.GetThird())
      	    {
	      // transform.GetPos() = data->players[i].position;
     	      // shader.Update(transform, camera);
      	       text.Bind(0);
      	      // playerModel.Draw();
	       DrawPlayerModel(data->players[i].position, data->players[i].direction, length(vec2(data->players[i].position) - lastPos[i]) * 5, camera, shader);
	       lastPos[i] = vec2(data->players[i].position);
	    }
      	  i++;
	}
      transform.GetPos() = vec3(0, 0, 0);
      display.Update(camera, map, player, data);
      player.FillCPlayer(data->players + player.GetId(), camera.GetFor());
    }
  return (0);
}
