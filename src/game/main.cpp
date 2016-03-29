#include <SDL2/SDL.h>
#include "engine/display.hpp"
#include "game.hpp"
#include "main_menu.hpp"
#include "option_menu.hpp"
#include "class/menu.hpp"
#include <GL/glut.h>

// int	initSDL(int ac, char **av, t_data *data)
// {
//   if (SDL_Init(SDL_INIT_VIDEO) < 0)
//     {
//       fprintf(stderr, "SDL init error : %s\n", SDL_GetError());
//       return (1);
//     }
//   glutInit(&ac, av);
//   data->game.screen = SDL_SetVideoMode(WIN_X, WIN_Y, 32, SDL_OPENGL);
//   SDL_WM_SetCaption(WIN_TITLE, NULL);
//   return (0);
// }

/*
** Boucle (au debut sur le menu principal), jusqu'a ce qu'on quitte le jeu
*/
int	game_loop(t_data *data, SDL_Event event, Menu *mainMenu)
{
  Display	display(WIN_X, WIN_Y, "Coldcube - Best solution to cooling your computer");

  // while (!display.IsClosed())
  //   {
      engineMain(&display);
      //    }

  // while (data->game.running)
  //   {
  //     mainMenu->display();
  //     SDL_WaitEvent(&event);
  //     if (event.type == SDL_QUIT)
  // 	{
  // 	  data->game.running = false;
  // 	  break;
  // 	}
  //     else if (event.type == SDL_KEYDOWN)
  // 	{
  // 	  if (1 && event.key.keysym.sym == SDLK_RETURN) // Mode menu
  // 	    {
  // 	      mainMenu->deleteAllButton();
  // 	      engineMain();
  // 	      // if (mode_menu(data))
  // 	      // return (1);
  // 	      std::clog << "[INFOS] Displays the mode menu\n";
  // 	      createMainMenu(mainMenu);
  // 	    }
  // 	  else if (1 && event.key.keysym.sym == SDLK_RETURN) // Option menu
  // 	    {
  // 	      mainMenu->deleteAllButton();
  // 	      // if (option_menu(data))
  // 	      // return (1);
  // 	      std::clog << "[INFOS] Displays the option menu\n";
  // 	      createMainMenu(mainMenu);
  // 	    }
  // 	  else if (event.key.keysym.sym == SDLK_ESCAPE) //Quit
  // 	    {
  // 	      data->game.running = false;
  // 	      break;
  // 	    }
  // 	}
  //     glFlush();
  //     SDL_GL_SwapBuffers();
    // }
  return (0);
}

int		game(int ac, char **av)
{
  t_data	*data;
  SDL_Event	event;
  Menu		mainMenu;

  if (!(data = new t_data))
    {
      write(2, "Malloc of t_data failed\n", 24);
      return (1);
    }
  // createMainMenu(&mainMenu);
  // mainMenu.showAllButton();
  if (game_loop(data, event, &mainMenu))
    {
      // mainMenu.deleteAllButton();
      return (1);
    }
  // mainMenu.deleteAllButton();
  // free_game(data);
  // SDL_Quit();
  return (0);
}

int	main(int ac, char **av, char **env)
{
  Display	display(1280, 720, "Coldcube");

  // while (!display.IsClosed())
  //   {
      engineMain(&display);
//   if (!*env)
//     {
//       write(2, "Environment variable are missing\n", 33);
// #ifdef DEBUG
//       write(2, "[INFOS] Game exited with status error 1\n", 40);
// #endif
//       return (1);
//     }
//   // Lancement du thread TCP
//   if (game(ac, av) == 1) //Lancement de la partie graphique
//     {
//       write(2, "An error occured.\n", 18);
// #ifdef DEBUG
//       write(2, "[INFOS] Game exited with status error 1\n", 40);
// #endif
//       return (1);
//     }
// #ifdef DEBUG
//   write(2, "[INFOS] Game exited correctly\n", 30);
// #endif
  return (0);
}
