#include <SDL2/SDL.h>
#include "engine/display.hpp"
#include "game.hpp"
#include "Menu.h"
#include <GL/glut.h>
#include "SDL2/SDL_image.h"

void	setAzerty(t_keys *keys)
{
  keys->forward = SDLK_z;
  keys->backward = SDLK_s;
  keys->left = SDLK_q;
  keys->right = SDLK_d;
  keys->jump = SDLK_SPACE;
}

void	setQwerty(t_keys *keys)
{
  keys->forward = SDLK_w;
  keys->backward = SDLK_s;
  keys->left = SDLK_a;
  keys->right = SDLK_d;
  keys->jump = SDLK_SPACE;
}

void	initData(t_data *data)
{
  memset(data, 0, sizeof(t_data));
  data->game.running = true;
  data->config.oculus = false;
  data->config.keyboard = AZERTY_MODE;
  data->config.musicVolume = 50;
  data->config.effectsVolume = 50;
  setAzerty(&data->config.keys);
}

int	game()
{
  t_data		*data = new t_data;
  Display		display(WIN_X, WIN_Y, "ColdCube");
  std::vector<menuItem>	items(14);
  std::string		inputText = "Some text";
  SDL_Rect		pos;
  SDL_Surface		*screen = SDL_GetWindowSurface(display.GetWin());
  SDL_Surface		*surface = NULL;
  Menu			*menu = new Menu(screen, &items);

  loginMenu(items);
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
