#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include <vector>
#include <string>

typedef struct	Point
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
