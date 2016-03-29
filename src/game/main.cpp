#include <SDL2/SDL.h>
#include "engine/display.hpp"
#include "game.hpp"
#include "Menu.h"
#include <GL/glut.h>

int	game()
{
  t_data		*data;
  Display		display(WIN_X, WIN_Y, "Coldcube");
  std::vector<menuItem>	items(5);
  std::string		inputText = "Some text";
  SDL_Rect		pos;
  SDL_Surface		*screen = SDL_GetWindowSurface(display.GetWin());
  SDL_Surface		*surface = NULL;
  Menu			*menu = new Menu(screen, &items);

  if (!(data = malloc(sizeof(t_data))))
    return (write(2, "[Err] Malloc failed\n", 20), 1);
  surface = SDL_LoadBMP("asets/imgs/cursor.bmp");
  SDL_SetColorKey(surface, 0, SDL_MapRGB(surface->format, 0, 0, 0));
  SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));
  pos.x = (screen->w >> 1)- (surface->w >> 1);
  pos.y = (screen->h >> 1)- (surface->h >> 1);
  SDL_StartTextInput();
  while (data->game.running)
    {
      // SDL_WaitEvent(&event);
      // if (engineMain(display))
      // 	return (1);
      display.UpdateMenu(menu, items, &data->game.running, &pos, screen,
			 surface, data);
    }
  free(data);
  return (0);
}

int	main(int ac, char **av, char **env)
{
  if (!*env)
    {
      write(2, "Environment variable are missing\n", 33);
#ifdef DEBUG
      write(2, "[INFOS] Game exited with status error 1\n", 40);
#endif
      return (1);
    }
  if (game())
    {
      write(2, "An error occured.\n", 18);
#ifdef DEBUG
      write(2, "[INFOS] Game exited with status error 1\n", 40);
#endif
      return (1);
    }
#ifdef DEBUG
  write(2, "[INFOS] Game exited correctly\n", 30);
#endif
  return (0);
}
