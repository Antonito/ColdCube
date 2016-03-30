#include <SDL2/SDL.h>
#include "SDL2/SDL_ttf.h"
#include "Menu.h"
#include <vector>
#include <string>

Menu::Menu(SDL_Surface *screen, std::vector<menuItem> *items) {
  this->items = items;
  this->screen = screen;
  this->currentItem = 0;
  TTF_Init();
  this->font = TTF_OpenFont("assets/fonts/menu.ttf", 15);
  printf("Font = %p %s\n", this->font, TTF_GetError());
}

Menu::~Menu() {
  SDL_FreeSurface(this->textSurface);
  TTF_CloseFont(this->font);
  TTF_Quit();
}

void Menu::hover(int x, int y) {
}

void Menu::moveDown() {
  if (this->currentItem < (int)(this->items->size() - 1))
    ++this->currentItem;
}

void Menu::moveUp() {
  if (this->currentItem)
    --this->currentItem;
}

void Menu::draw() {
  SDL_Rect positionZozor;
  SDL_Surface *text;
  SDL_Surface *bg = SDL_CreateRGBSurface(SDL_SWSURFACE, 300, 70, 32, 0, 0, 0, 0);
  SDL_Color color;

  color.r = 255;
  color.g = 0;
  color.b = 0;
  positionZozor.x = 10;
  positionZozor.y = 10;
  for (int i = 0; i < (int)this->items->size(); ++i) {
    SDL_SetColorKey(bg, 0, SDL_MapRGB(bg->format, 0, 0, 255));
    SDL_FillRect(bg, NULL, SDL_MapRGB(bg->format, 255, i == this->currentItem ? 100 : 255, 0));
    text = TTF_RenderText_Blended(this->font, (*this->items)[i].text.c_str(), color);
    SDL_BlitSurface(bg, NULL, this->screen, &positionZozor);
    SDL_BlitSurface(text, NULL, this->screen, &positionZozor);
    positionZozor.y += 80;
  }
  SDL_FreeSurface(bg);
}

void Menu::selectCurrentItem() {
  printf("Selecting item %d\n", this->currentItem);
}
