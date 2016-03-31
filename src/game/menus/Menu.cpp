#include <SDL2/SDL.h>
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_image.h"
#include "Menu.h"
#include <vector>
#include <string>
#include "game.hpp"
#include <time.h>

Menu::Menu(SDL_Surface *screen, std::vector<menuItem> *items) {
  this->items = items;
  this->screen = screen;
  this->currentItem = 0;
  TTF_Init();
  this->font = TTF_OpenFont("assets/fonts/menu.ttf", 50);
  printf("Font = %p %s\n", this->font, TTF_GetError());
  this->holded = false;
}

Menu::~Menu() {
  SDL_FreeSurface(this->textSurface);
  TTF_CloseFont(this->font);
  TTF_Quit();
}

void Menu::hover(int x, int y) {
  int	focusedx;
  int	focusedy;

  focusedx = (WIN_X - 1408) / 2;
  focusedy = (WIN_Y - 540) / 2;
}

void Menu::moveUp() {
  switch (this->currentItem) {
    case 5:
      this->currentItem = 1;
      break;
    case 4:
      this->currentItem = 2;
      break;
    case 3:
      this->currentItem = 4;
      break;
    case 6:
      this->currentItem = 5;
      break;
  }
  if (!this->currentItem)
    this->currentItem = 1;
}

void Menu::moveDown() {
  switch (this->currentItem) {
    case 1:
      this->currentItem = 5;
      break;
    case 2:
      this->currentItem = 4;
      break;
    case 4:
      this->currentItem = 3;
      break;
    case 5:
      this->currentItem = 6;
      break;
  }
  if (!this->currentItem)
    this->currentItem = 1;
}

void Menu::moveRight() {
  switch (this->currentItem) {
    case 1:
      this->currentItem = 2;
      break;
    case 5:
      this->currentItem = 4;
      break;
    case 6:
      this->currentItem = 3;
      break;
  }
  if (!this->currentItem)
    this->currentItem = 1;
}

void Menu::moveLeft() {
  switch (this->currentItem) {
    case 2:
      this->currentItem = 1;
      break;
    case 4:
      this->currentItem = 5;
      break;
    case 3:
      this->currentItem = 6;
      break;
  }
  if (!this->currentItem)
    this->currentItem = 1;
}

void Menu::moveNext() {
  if (this->currentItem < 7)
    ++this->currentItem;
}

void Menu::draw() {
  SDL_Rect pos;
  char path[32],
       curr[32];
  SDL_Surface *text;
  SDL_Color color = {8, 93, 163, 0};
  SDL_Color light = {243, 237, 211, 0};
  SDL_Color selected = {1, 4, 45, 0};
  SDL_Color selected2 = {191, 178, 175, 0};

  sprintf(curr, "selected-%d", this->currentItem);
  sprintf(path, "assets/imgs/menu/%s.bmp", this->holded && this->currentItem ? curr : "base");
  SDL_Surface *menu = IMG_Load(path);

  if ((*this->items)[1].text == " " || (*this->items)[1].text == "|" || (*this->items)[1].text == "")
    (*this->items)[1].text = "   Pseudo";
  if ((*this->items)[2].text == " " || (*this->items)[2].text == "|" || (*this->items)[2].text == "")
    (*this->items)[2].text = "Server IP";
  if ((*this->items)[3].text == " " || (*this->items)[3].text == "|" || (*this->items)[3].text == "")
    (*this->items)[3].text = "Port";
  pos.x = (WIN_X - 1408) / 2;
  pos.y = (WIN_Y - 540) / 2;
  SDL_FillRect(this->screen, NULL, SDL_MapRGB(this->screen->format, 143, 45, 42));
  SDL_BlitSurface(menu, NULL, this->screen, &pos);
  pos.y += 60;
  pos.x += 260;
  text = TTF_RenderUTF8_Blended(this->font, (*this->items)[1].text.c_str(), color);
  SDL_BlitSurface(text, NULL, this->screen, &pos);
  SDL_FreeSurface(text);
  pos.x += 630 + (7 - (*this->items)[2].text.length()) * 15;
  text = TTF_RenderUTF8_Blended(this->font, (*this->items)[2].text.c_str(), color);
  SDL_BlitSurface(text, NULL, this->screen, &pos);
  SDL_FreeSurface(text);
  pos.x -= (7 - (*this->items)[2].text.length()) * 15 - (7 - (*this->items)[3].text.length()) * 15;
  pos.y += 350;
  text = TTF_RenderUTF8_Blended(this->font, (*this->items)[3].text.c_str(), color);
  SDL_BlitSurface(text, NULL, this->screen, &pos);
  SDL_FreeSurface(text);
  pos.x -= (7 - (*this->items)[3].text.length()) * 15 - 50;
  pos.y -= 170;
  text = TTF_RenderUTF8_Blended(this->font, "Play !", this->currentItem == 4 ? selected : light);
  SDL_BlitSurface(text, NULL, this->screen, &pos);
  SDL_FreeSurface(text);
  pos.x -= 700;
  text = TTF_RenderUTF8_Blended(this->font, "Options", this->currentItem == 5 ? selected : light);
  SDL_BlitSurface(text, NULL, this->screen, &pos);
  SDL_FreeSurface(text);
  pos.x += 100;
  pos.y += 170;
  text = TTF_RenderUTF8_Blended(this->font, "Quit", this->currentItem == 6 ? selected2 : color);
  SDL_BlitSurface(text, NULL, this->screen, &pos);
  SDL_FreeSurface(text);
  SDL_FreeSurface(menu);
  if ((*this->items)[1].text == "   Pseudo")
    (*this->items)[1].text = " ";
  if ((*this->items)[2].text == "Server IP")
    (*this->items)[2].text = " ";
  if ((*this->items)[3].text == "Port")
    (*this->items)[3].text = " ";
  //for (int i = 0; i < (int)this->items->size(); ++i) {
  //  SDL_FillRect(bg, NULL, SDL_MapRGB(bg->format, 255, i == this->currentItem ? 100 : 255, 0));
  //  positionZozor.y += 80;
  //}
}

void Menu::selectCurrentItem() {
  printf("Selecting item %d\n", this->currentItem);
}

void Menu::hold() {
  this->holded = true;
}

void Menu::unhold() {
  usleep(120000);
  this->holded = false;
}
