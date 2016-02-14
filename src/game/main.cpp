#include "game.hpp"

int	initSDL(void)
{
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
      fprintf(stderr, "SDL init error : %s\n", SDL_GetError());
      return (1);
    }
  SDL_SetVideoMode(WIN_X, WIN_Y, 32, SDL_OPENGL);
  SDL_WM_SetCaption(WIN_TITLE, NULL);
  return (0);
}

/*
** Boucle (au debut sur le menu principal), jusqu'a ce qu'on quitte le jeu
*/

int		game(void)
{
  t_data	*data;

  if (!(data = new t_data))
    {
      write(2, "Malloc of t_data failed\n", 24);
      return (1);
    }
  if (initSDL())
    {
      free_game(data);
      return (1);
    }
  data->game.running = true;
  while (data->game.running)
    {
      //ShowMainMenu

      //If Play -> start, connection menu
      //else if -> Options, show options menu
      //else if -> Quit, leaves game
    }
  free_game(data);
  SDL_Quit();
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
  // Lancement du thread TCP
  if (game() == 1) //Lancement de la partie graphique
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
