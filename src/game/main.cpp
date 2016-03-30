#include <SDL2/SDL.h>
#include "engine/display.hpp"
#include "game.hpp"
#include "main_menu.hpp"
#include "option_menu.hpp"
#include "class/menu.hpp"
#include <GL/glut.h>

int	main(int ac, char **av, char **env)
{
  Display	display(WIN_X, WIN_Y, "Coldcube");

  // while (!display.IsClosed())
  //   {
  engineMain(display);
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
