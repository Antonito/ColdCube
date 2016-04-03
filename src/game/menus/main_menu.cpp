#include "Menu.h"

static void	swap(menuItem *item1, menuItem *item2) {
  menuItem	tmp;

  tmp = *item1;
  *item1 = *item2;
  *item2 = tmp;
}

void	loginMenu(std::vector<menuItem> &items)
{
  if (items[0].type == 1) {
    swap(&items[7], &items[0]);
    swap(&items[8], &items[1]);
    swap(&items[9], &items[2]);
    swap(&items[10], &items[3]);
    swap(&items[11], &items[4]);
    swap(&items[12], &items[5]);
    swap(&items[13], &items[6]);
    return;
  }
  items[0].type = 0;
  items[1].text = "";
  items[1].type = MENU_TEXTINPUT;
  items[2].text = "";
  items[2].type = MENU_TEXTINPUT;
  items[3].text = "";
  items[3].type = MENU_TEXTINPUT;
  items[4].text = "   Play !";
  items[4].type = MENU_TEXT;
  items[5].text = "Options";
  items[5].type = MENU_TEXT;
  items[6].text = "Quit";
  items[6].type = MENU_TEXT;
  items[7].type = 1;
  items[8].text = "Music vol.";
  items[8].type = MENU_SLIDER;
  items[8].value = 50;
  items[9].text = "Effect vol.";
  items[9].type = MENU_SLIDER;
  items[9].value = 50;
  items[10].text = "Brightness";
  items[10].type = MENU_SLIDER;
  items[10].value = 50;
  items[11].text = "AZERTY mode";
  items[11].type = MENU_CHECKBOX;
  items[12].text = " Set Oculus";
  items[12].type = MENU_CHECKBOX;
  items[13].text = "Back";
  items[13].type = MENU_TEXT;

}

void	optionMenu(std::vector<menuItem> &items)
{
  if (items[0].type == 0) {
    swap(&items[7], &items[0]);
    swap(&items[8], &items[1]);
    swap(&items[9], &items[2]);
    swap(&items[10], &items[3]);
    swap(&items[11], &items[4]);
    swap(&items[12], &items[5]);
    swap(&items[13], &items[6]);
    return;
  }
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
