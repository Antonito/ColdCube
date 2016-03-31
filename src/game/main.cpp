#include <SDL2/SDL.h>
#include "engine/display.hpp"
#include "game.hpp"
#include "Menu.h"
#include <GL/glut.h>
#include "SDL2/SDL_image.h"

void	initData(t_data *data)
{
  memset(data, 0, sizeof(t_data));
  data->game.running = true;
}

int	game()
{
  t_data		*data = new t_data;
  Display		display(WIN_X, WIN_Y, "ColdCube");
  std::vector<menuItem>	items(6);
  std::string		inputText = "Some text";
  SDL_Rect		pos;
  SDL_Surface		*screen = SDL_GetWindowSurface(display.GetWin());
  SDL_Surface		*surface = NULL;
  Menu			*menu = new Menu(screen, &items);

  surface = IMG_Load("assets/imgs/cursor.bmp");
  pos.x = (screen->w >> 1)- (surface->w >> 1);
  pos.y = (screen->h >> 1)- (surface->h >> 1);
  SDL_StartTextInput();
  initData(data);
  while (data->game.running)
    {
      display.UpdateMenu(menu, items, &pos, screen, surface, data);
    }
  delete data;
  return (0);
}

int	main(int ac, char **av, char **env)
{
  (void) ac;
  (void) av;
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
