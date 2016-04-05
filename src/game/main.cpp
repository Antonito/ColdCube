#include <SDL2/SDL.h>
#include "engine/display.hpp"
#include "game.hpp"
#include "Menu.h"
#include <GL/glut.h>
#include "SDL2/SDL_image.h"

#ifdef	CHEAT
# include "cheat.hpp"
t_cheat	cheat;
#endif

void	setAzerty(t_keys *keys)
{
  keys->forward = KEY_Z;
  keys->backward = KEY_S;
  keys->left = KEY_Q;
  keys->right = KEY_D;
  keys->jump = KEY_SPACE;
}

void	setQwerty(t_keys *keys)
{
  keys->forward = KEY_W;
  keys->backward = KEY_S;
  keys->left = KEY_A;
  keys->right = KEY_D;
  keys->jump = KEY_SPACE;
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
#ifdef	CHEAT
  bzero(&cheat, sizeof(t_cheat));
  cheat.keys.ammo = KEY_I;
  cheat.keys.life = KEY_J;
  cheat.keys.fly = KEY_K;
  cheat.keys.collisions = KEY_L;
#endif
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
  //Macro definie dans game.hpp
  surface = IMG_Load(CURSOR_IMG);
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
