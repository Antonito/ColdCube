//#include <GL/glew.h>
#include <ctime>
#include "game.hpp"
#include "common_structs.hpp"
#include "engine/displayer.hpp"
#include "engine/shader.hpp"
#include "engine/mesh.hpp"
#include "engine/player.hpp"
#include "engine/texture.hpp"
#include "engine/transform.hpp"
#include "engine/camera.hpp"
#include "engine/map.hpp"
#include "engine/animation_player.hpp"
#include "User.hpp"
#include <time.h>

using namespace glm;

Mesh	SetPlanes(int, vec3);

int	engineMain(Displayer &display, t_data *data)
{
  Shader	shader("shaders/test1");
  Map		map("map");
  Player	player(vec3(10, 10, 5), 90, &map, data->net.playerIndexUdp);
  User		user(data->players + player.GetId());
  Camera	camera(vec3(10, 5, 10), 70.0f, (float)WIN_X / WIN_Y, 0.01f, 500.0f,
		       data->config.oculusHmd, data->config.oculus);
  Transform	transform;
  int		i;
  vec2		lastPos[10] = {vec2(0, 0)};
  vec3		lastPredict[10] = {vec3(0, 0, 0)};
  vec3		light(15, 15, 5);
  int		render;

  i = 0;
  while (i < 10)
    {
      data->players[i].position = vec3(2, 2 + i, 2);
      data->players[i].direction = vec3(0, 1, 0);
      i++;
    }
  shader.Bind();

  while (!display.IsClosed())
    {
      render = 0;
      display.Clear(0.0f, 0.3f, 0.8f, 1.0f);
      transform.GetPos() = vec3(0, 0, 0);
      while (render < data->config.oculus + 1)
	{
	  if (data->config.oculus)
	    glViewport((render == 0) ? 0 : WIN_X / 2, 0, WIN_X / 2, WIN_Y);
	  if (render == 1)
	    camera.GetPos() += normalize(cross(camera.GetFor(), vec3(0, 0, 1))) * (GLfloat)0.32;
	  shader.Update(transform, camera, &light);
	  map.Draw();
	  i = 0;
	  while (i < 10)
	    {
	      PredictPosition(data->players + i, lastPredict + i, data->net.isPackage + i);
	      DrawPlayerModel(data->players[i].position, data->players[i].direction,
			      length(vec2(data->players[i].position) - lastPos[i]) * 5,
			      camera, shader, i, player.GetId(), player.GetThird());
	      if (render == 0 && !data->config.oculus)
		lastPos[i] = vec2(data->players[i].position);
	      else if (render == 1 && data->config.oculus)
		lastPos[i] = vec2(data->players[i].position);
	      i++;
	    }
	  render++;
	}
      user.IsShooted(data->players, data->game.Team2, map);
      display.Update(camera, map, player, data, user);
      player.FillCPlayer(data->players + player.GetId(), camera.GetFor());
    }
  return (0);
}
