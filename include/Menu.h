#ifndef	MENU_H_
# define MENU_H_

#include <SDL2/SDL.h>
#include "SDL2/SDL_ttf.h"
#include <vector>
#include <string>

#ifndef MENU_TEXT
# define MENU_TEXT 0
# define MENU_TEXTINPUT 1
# define MENU_CHECKBOX 3
# define MENU_SLIDER 4
#endif /* !MENU_TEXT */

typedef enum	e_menuElem
  {
    RIGHT_MIDDLE	= 4,
    LEFT_MIDDLE		= 5,
    LEFT_BOTTOM		= 6
  }		e_menuElem;

typedef struct	s_Point
{
  int	x;
  int	y;
}		Point;

struct menuItem
{
  std::string text;
  int type;
  short value;
  void (*ptToFunc)();
};

void	mainMenu(std::vector<menuItem> &items);

class Menu
{
 public:
  Menu(SDL_Surface *, std::vector<menuItem> *);
  ~Menu();
  void hover(int, int);
  void moveUp();
  void moveDown();
  void moveLeft();
  void moveRight();
  void moveNext();
  void draw();
  void selectCurrentItem();
  void hold();
  void unhold();
  int currentItem;
  bool holded;
 private:
  TTF_Font *font;
  SDL_Surface *screen;
  std::vector<menuItem> *items;
  SDL_Surface *textSurface;
};

void	loginMenu(std::vector<menuItem> &items);
void	optionMenu(std::vector<menuItem> &items);
void	pauseMenu(std::vector<menuItem> &items);
void	mainMenu(std::vector<menuItem> &items);

#endif // MENU_H_
