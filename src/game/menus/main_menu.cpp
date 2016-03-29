#include "Menu.h"

void	loginMenu(std::vector<menuItem> &items)
{
  items[0].text = "Pseudo";
  items[1].text = "Server IP";
  items[2].text = "Server port";
  items[3].text = "Play";
  items[4].text = "Return to main menu";
}

void	optionMenu(std::vector<menuItem> &items)
{
  items[0].text = "Volume Music";
  items[1].text = "Volume Effect";
  items[2].text = "AZERTY / QWERTY";
  items[3].text = "Return to main menu";
}

void	pauseMenu(std::vector<menuItem> &items)
{
  items[0].text = "Return to game";
  items[1].text = "Options";
  items[2].text = "Return to main menu";
}

void	mainMenu(std::vector<menuItem> &items)
{
  items[0].text = "Start";
  items[1].text = "Options";
  items[2].text = "Quit";
  items[3].text = "Server port";
  items[4].text = "Server IP";
  items[5].text = "Pseudo";
}
