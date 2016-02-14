#include "game.hpp"
#include "main_menu.hpp"
#include "option_menu.hpp"

int		initSDL(t_data *data)
{
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
      fprintf(stderr, "SDL init error : %s\n", SDL_GetError());
      return (1);
    }
  data->game.screen = SDL_SetVideoMode(WIN_X, WIN_Y, 32, SDL_OPENGL);
  SDL_WM_SetCaption(WIN_TITLE, NULL);
  return (0);
}

/*
** Boucle (au debut sur le menu principal), jusqu'a ce qu'on quitte le jeu
*/

int		game_loop(t_data *data, SDL_Event event)
{
  while (data->game.running)
    {
      main_menu(data);
      SDL_WaitEvent(&event);
      if (event.type == SDL_QUIT)
	{
	  data->game.running = false;
	  break;
	}
      else if (event.type == SDL_KEYDOWN)
	{
	  if (1 && event.key.keysym.sym == SDLK_RETURN) // Mode menu
	    {
	      // if (mode_menu(data))
	      // return (1);
	      std::cout << "[INFOS] Displays the mode menu\n";
	    }
	  else if (1 && event.key.keysym.sym == SDLK_RETURN) // Option menu
	    {
	      // if (option_menu(data))
	      // return (1);
	      std::cout << "[INFOS] Displays the option menu\n";
	    }
	  else if (event.key.keysym.sym == SDLK_ESCAPE) //Quit, leaves game
	    {
	      data->game.running = false;
	      break;
	    }
	}
      glFlush();
      SDL_GL_SwapBuffers();
    }
  return (0);
}

int		game(void)
{
  t_data	*data;
  SDL_Event	event;

  if (!(data = new t_data))
    {
      write(2, "Malloc of t_data failed\n", 24);
      return (1);
    }
  if (initSDL(data))
    {
      free_game(data);
      return (1);
    }
  data->game.running = true;
  if (game_loop(data, event))
    {
      return (1);
    }
  free_game(data);
  SDL_Quit();
  return (0);
}

int		main(int ac, char **av, char **env)
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
