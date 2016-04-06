#include <ctime>
#include "game.hpp"
#include "common_structs.hpp"
#include "engine/display.hpp"
#include <time.h>
#include "SDL2/SDL_image.h"

using namespace glm;

Mesh	SetPlanes(int, vec3);

int		room(Display &display, t_data *data)
{
  SDL_Surface		*bg,
			*surface;
  SDL_Rect	pos = {WIN_X / 2, WIN_Y / 2, WIN_X, WIN_Y};

  surface = IMG_Load(CURSOR_IMG);

  while (!display.IsClosed() && data->game.running)
    {
      bg = IMG_Load(ROOM_BACKGROUND);
      display.UpdateRoom(data, &pos, bg, surface);
      SDL_FreeSurface(bg);
    }
  if (!data->game.running)
    {
      data->game.running = true;

    }

  SDL_FreeSurface(surface);
  return (0);
}
