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
#include "engine/renderer.hpp"
#include "User.hpp"
#include <time.h>

using namespace glm;

Mesh	SetPlanes(int, vec3);
void	DrawUI(t_data *data, bool oculus);

//
// Timer -> getMinuts and getSeconds in data->game.Team1
//

int	engineMain(Displayer &display, t_data *data)
{
  Shader	shader("shaders/test1");
  Shader	barrel("shaders/barrel_roll");
  Map		map("map");
  data->players[data->net.playerIndexTcp].id = data->net.playerIndexTcp;
  Player	player(map.GetSpawn(), 90, &map, data->net.playerIndexTcp);
  User		user(&data->players[data->net.playerIndexTcp]);
  float		zoom = FOV_NORMAL;
  Camera	camera(vec3(10, 5, 10), zoom, (float)WIN_X / WIN_Y, 0.01f, 500.0f,
		       data->config.oculusHmd, data->config.oculus);
  Transform	transform;
  int		i;
  vec2		lastPos[10] = {vec2(0, 0)};
  vec3		lastPredict[10] = {vec3(0, 0, 0)};
  vec3		light(15, 15, 5);
  int		render;
  Renderer	rightEye(GAME_X, GAME_Y);
  Renderer	leftEye(GAME_X, GAME_Y);
  vec3		decal(0, 0, 0);

  i = 0;
  while (i < 10)
    {
      data->players[i].position = vec3(2, 2 + i, 2);
      data->players[i].direction = vec3(0, 1, 0);
      i++;
    }
  glViewport(0, 0, WIN_X, WIN_Y);
  while (!display.IsClosed())
    {
      if (player.IsAiming() && zoom > FOV_ZOOM && data->players[player.GetId()].selected_weapon != KNIFE_WEAPON)
	{
	  zoom -= ((FOV_ZOOM - 1) + zoom) / 7;
	  camera.SetFov(zoom);
	}
      else if (!player.IsAiming() && zoom < FOV_NORMAL)
	{
	  zoom += ((FOV_NORMAL + 1) - zoom) / 3;
	  camera.SetFov(zoom);
	}
            render = 0;
      transform.GetPos() = vec3(0, 0, 0);
      display.Clear(0.0f, 0.3f, 0.8f, 1.0f);
      while (render < data->config.oculus + 1)
	{
	  if (data->config.oculus && render == 0)
	    leftEye.Bind();
	  if (render == 1)
	    {
	      rightEye.Bind();
	      decal = normalize(cross(normalize(vec3(camera.GetFor().x, camera.GetFor().y, 0)), vec3(0, 0, 1))) * (GLfloat)0.16;
	      camera.GetPos() += decal;
	    }
	  shader.Bind();
	  if (data->config.oculus)
	    glViewport(0, 0, GAME_X, GAME_Y);
	  shader.Update(transform, camera, &light);
	  map.Draw();
	  i = 0;
	  while (i < 10)
	    {
	      if (getEvent(data->players[i].events, IS_CONNECTED))
	      	{
		  if (i != player.GetId() && ((render == 0 && !data->config.oculus) || (render == 1 && data->config.oculus)))
		    PredictPosition(data->players + i, lastPredict + i, data->net.isPackage + i);
		  DrawPlayerModel(data->players[i].position, data->players[i].direction,
				  length(vec2(data->players[i].position) - lastPos[i]) * 5,
				  camera, shader, i, player.GetId(), player.GetThird(), (render) ? decal / 2.0f : -decal / 2.0f);
		  if (render == 0 && !data->config.oculus)
		    lastPos[i] = vec2(data->players[i].position);
		  else if (render == 1 && data->config.oculus)
		    lastPos[i] = vec2(data->players[i].position);
		}
	      i++;
	    }
	  DrawUI(data, data->config.oculus);
	  render++;
	}
      if (data->config.oculus)
      	{
	  glBindFramebuffer(GL_FRAMEBUFFER, 0);
	  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	  barrel.Bind();
      	  glViewport(0, 0, WIN_X / 2, WIN_Y);
      	  leftEye.Draw();
      	  glViewport(WIN_X / 2, 0, WIN_X / 2, WIN_Y);
      	  rightEye.Draw();
      	}
      user.IsShooted(data->players, data->game.Team2, map, data);
      if (player.GetPos().z < -200.0f)
	data->players[player.GetId()].life = 0;
      if (data->players[player.GetId()].life <= 0)
	{
	  data->game.Team2.resetStreak();
	  data->players[player.GetId()].life = 100;
	  player.GetPos() = map.GetSpawn();
	}
      display.Update(camera, map, player, data, user);
      player.FillCPlayer(data->players + player.GetId(), camera.GetFor());
      data->game.Team2.updateTime();

      // if (data->game.Team2.checkWin())
      // 	{
      // 	  std::string	msg = LOOSE_MSG;
      // 	  std::string	bye = BYE_MSG;

      // 	  data->tchat.pushBack(msg);
      // 	  data->tchat.pushBack(bye);
      // 	  display.Update(camera, map, player, data, user);
      // 	  display.setClosed(true);
      // 	  sleep(4);
      // 	  data->game.Team1.setScore(0);
      // 	  data->game.Team2.setScore(0);
      // 	  return (0);
      // 	}
      // if (data->game.Team1.checkWin())
      // 	{
      // 	  std::string	msg = WIN_MSG;
      // 	  std::string	bye = BYE_MSG;

      // 	  data->tchat.pushBack(msg);
      // 	  data->tchat.pushBack(bye);
      // 	  display.Update(camera, map, player, data, user);
      // 	  display.setClosed(true);
      // 	  sleep(4);
      // 	  data->game.Team1.setScore(0);
      // 	  data->game.Team2.setScore(0);
      // 	  return (0);
      // 	}
    }
  return (0);
}

void	DrawUI(t_data *data, bool oculus)
{
  SDL_Rect		tchat_pos = {0, data->tchat.isFocus() ? (WIN_Y / 2) : (3 * WIN_Y / 4), 854, data->tchat.isFocus() ? (WIN_Y / 2) : (WIN_Y / 4)};
  SDL_Rect		origin = {42, 10, WIN_X, WIN_Y};
  SDL_Rect		center = {(WIN_X - 50) / 2, (WIN_Y - 50) / 2, 50, 50};
  SDL_Surface		*life;
  char			lifebar[32];
  SDL_Color		black = {0, 0, 0, 255};
  static TTF_Font	*font = TTF_OpenFont(TCHAT_FONT_NAME, (int)(40 / WIN_RATIO));
  static SDL_Surface	*crosshair = IMG_Load("./assets/imgs/crosshair.png");
  static SDL_Surface	*ui = SDL_CreateRGBSurface(0, WIN_X, WIN_Y, 32, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);

  glFlush();

  SDL_FillRect(ui, NULL, SDL_MapRGBA(ui->format, 0, 0, 0, 0));
  if (!oculus)
    SDL_BlitScaled(crosshair, NULL, ui, &center);
  sprintf(lifebar, "./assets/imgs/lifebar/%03d.png", data->players[data->net.playerIndexUdp].life);
  life = IMG_Load(lifebar);
  SDL_BlitSurface(life, NULL, ui, &origin);
  if (!oculus)
    data->tchat.display(tchat_pos, ui, (SDL_Color){210, 210, 210, 255});
  SDL_FreeSurface(life);
  life = TTF_RenderUTF8_Blended(font, data->players[data->net.playerIndexUdp].pseudo, black);
  origin.x = 470;
  origin.y = 105;
  SDL_BlitSurface(life, NULL, ui, &origin);
  SDL_FreeSurface(life);
  Texture uiTex(ui);
  // SDL_FreeSurface(ui);

  glDisable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);
  glDisable(GL_LIGHTING);
  glUseProgram(0);
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);
  glBlendEquation(GL_FUNC_ADD);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  if (!oculus)
    {
      glBegin(GL_QUADS);
      uiTex.Bind(0);
      glTexCoord2i(0, 0);
      glVertex3f(-1, 1, 0);
      glTexCoord2i(0, 1);
      glVertex3f(-1, -1, 0);
      glTexCoord2i(1, 1);
      glVertex3f(1, -1, 0);
      glTexCoord2i(1, 0);
      glVertex3f(1, 1, 0);
      glEnd();
    }
  else
    {
      glBegin(GL_QUADS);
      uiTex.Bind(0);
      glTexCoord2i(0, 0);
      glVertex3f(-0.8, 0.6, 0);
      glTexCoord2i(0, 1);
      glVertex3f(-0.8, -0.6, 0);
      glTexCoord2i(1, 1);
      glVertex3f(0.8, -0.6, 0);
      glTexCoord2i(1, 0);
      glVertex3f(0.8, 0.6, 0);
      glEnd();
    }

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glEnable(GL_LIGHTING);
  glCullFace(GL_BACK);
  glDisable(GL_BLEND);
}
