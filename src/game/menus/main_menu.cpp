#include "game.hpp"
#include "class/menu.hpp"

void	createMainMenu(Menu *mainMenu)
{
  mainMenu->selected_id = 0;
  mainMenu->initMenu(0, 0, (char *)"Mon premier bouton");
  mainMenu->createButton(0, 0, (char *)"Mon deuxieme boutooooon");
}
