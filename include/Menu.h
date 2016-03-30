#ifndef	MENU_H_
# define MENU_H_

#include <SDL2/SDL.h>
#include "SDL2/SDL_ttf.h"
#include <vector>
#include <string>

typedef struct	s_Point
{
  int	x;
  int	y;
}		Point;

struct menuItem
{
  std::string text;
  Point box[4];
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
  void draw();
  void selectCurrentItem();
  int currentItem;
 private:
  TTF_Font *font;
  SDL_Surface *screen;
  Point menuLocation;
  std::vector<menuItem> *items;
  SDL_Surface *textSurface;
  SDL_Rect cursor;
};

void	loginMenu(std::vector<menuItem> &items);
void	optionMenu(std::vector<menuItem> &items);
void	pauseMenu(std::vector<menuItem> &items);
void	mainMenu(std::vector<menuItem> &items);

#endif // MENU_H_
