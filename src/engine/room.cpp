#include <ctime>
#include "game.hpp"
#include "common_structs.hpp"
#include "engine/displayer.hpp"
#include <time.h>
#include "SDL2/SDL_image.h"

using namespace glm;

Mesh	SetPlanes(int, vec3);

int		room(Displayer &display, t_data *data)
{
  SDL_Surface		*bg,
			*surface;
  SDL_Rect		pos = {WIN_X / 2, WIN_Y / 2, 0, 0};

  surface = IMG_Load(CURSOR_IMG);
  bg = IMG_Load(ROOM_BACKGROUND);

  while (!display.IsClosed() && data->game.running && strcmp(data->net.tcp.buff, "/g"))
    {
      printf("This is WTF\n");
      display.UpdateRoom(data, &pos, bg, surface);
    }
  if (!data->game.running)
    data->game.running = true;
  data->tchat.focus(false);

  SDL_FreeSurface(surface);
  SDL_FreeSurface(bg);
  return (!strcmp(data->net.tcp.buff, "/g"));
}
