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
#ifdef	DEBUG
  printf("Font = %p %s\n", this->font, TTF_GetError());
#endif
  this->holded = false;
}

Menu::~Menu() {
  SDL_FreeSurface(this->textSurface);
  TTF_CloseFont(this->font);
  TTF_Quit();
}

void Menu::hover(int x, int y) {
  if (y > 290 && y < 465) {
    if (x > 450 && x < 880)
      this->currentItem = 1;
    else if (x > 1030 && x < 1510)
      this->currentItem = 2;
    else
      this->currentItem = 0;
  } else if (y > 465 && y < 650) {
    if (x > 295 && x < 880)
      this->currentItem = 5;
    else if (x > 1080 && x < 1660)
      this->currentItem = 4;
    else
      this->currentItem = 0;
  } else if (y > 650 && y < 830) {
    if (x > 450 && x < 880)
      this->currentItem = 6;
    else if (x  > 1030 && x < 1510)
      this->currentItem = 3;
    else
      this->currentItem = 0;
  } else
    this->currentItem = 0;
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
  SDL_Color selected_red = {213, 79, 88, 0};
  //SDL_Color selected2 = {191, 178, 175, 0};

  sprintf(curr, "selected-%d", this->currentItem);
  sprintf(path, "assets/imgs/menu/%s.bmp", this->holded && this->currentItem ? curr : "base");
  SDL_Surface *menu = IMG_Load(path);
  SDL_Surface *slider_cur = IMG_Load("./assets/imgs/menu/slider-cursor.png");
  SDL_Surface *slider_bar = IMG_Load("./assets/imgs/menu/slider-bar.png");

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
  pos.x += 230;
  text = TTF_RenderUTF8_Blended(this->font, (*this->items)[1].text.c_str(), this->currentItem == 1 ? selected : color);
  SDL_BlitSurface(text, NULL, this->screen, &pos);
  if ((*this->items)[1].type == MENU_SLIDER)
    {
      pos.y += 75;
      SDL_BlitSurface(slider_bar, NULL, this->screen, &pos);
      pos.y -= 12;
      pos.x += (float)(slider_bar->w - slider_cur->w) * (float)(*this->items)[1].value / 100.0;
      SDL_BlitSurface(slider_cur, NULL, this->screen, &pos);
      pos.x -= (float)(slider_bar->w - slider_cur->w) * (float)(*this->items)[1].value / 100.0;
      pos.y -= 75 - 12;
    }

  SDL_FreeSurface(text);
  pos.x += 660 + (7 - (*this->items)[2].text.length()) * 15;
  text = TTF_RenderUTF8_Blended(this->font, (*this->items)[2].text.c_str(), this->currentItem == 2 ? selected : color);
  SDL_BlitSurface(text, NULL, this->screen, &pos);
  SDL_FreeSurface(text);
  if ((*this->items)[2].type == MENU_SLIDER)
    {
      pos.y += 75;
      SDL_BlitSurface(slider_bar, NULL, this->screen, &pos);
      pos.y -= 12;
      pos.x += (float)(slider_bar->w - slider_cur->w) * (float)(*this->items)[2].value / 100.0;
      SDL_BlitSurface(slider_cur, NULL, this->screen, &pos);
      pos.x -= (float)(slider_bar->w - slider_cur->w) * (float)(*this->items)[2].value / 100.0;
      pos.y -= 75 - 12;
    }

  pos.x -= (7 - (*this->items)[2].text.length()) * 15 - (7 - (*this->items)[3].text.length()) * 15;
  pos.y += 350;
  text = TTF_RenderUTF8_Blended(this->font, (*this->items)[3].text.c_str(), this->currentItem == 3 ? selected : color);
  SDL_BlitSurface(text, NULL, this->screen, &pos);
  SDL_FreeSurface(text);
  if ((*this->items)[3].type == MENU_SLIDER)
    {
      pos.y += 75;
      SDL_BlitSurface(slider_bar, NULL, this->screen, &pos);
      pos.y -= 12;
      pos.x += (float)(slider_bar->w - slider_cur->w) * (float)(*this->items)[3].value / 100.0;
      SDL_BlitSurface(slider_cur, NULL, this->screen, &pos);
      pos.x -= (float)(slider_bar->w - slider_cur->w) * (float)(*this->items)[3].value / 100.0;
      pos.y -= 75 - 12;
    }

  pos.x -= (7 - (*this->items)[3].text.length()) * 15 - 20;
  pos.y -= 170;
  text = TTF_RenderUTF8_Blended(this->font, (*this->items)[4].text.c_str(), this->currentItem == 4 ? selected_red : light);
  SDL_BlitSurface(text, NULL, this->screen, &pos);
  SDL_FreeSurface(text);
  if ((*this->items)[4].type == MENU_SLIDER)
    {
      pos.y += 75;
      SDL_BlitSurface(slider_bar, NULL, this->screen, &pos);
      pos.y -= 12;
      pos.x += (float)(slider_bar->w - slider_cur->w) * (float)(*this->items)[4].value / 100.0;
      SDL_BlitSurface(slider_cur, NULL, this->screen, &pos);
      pos.x -= (float)(slider_bar->w - slider_cur->w) * (float)(*this->items)[4].value / 100.0;
      pos.y -= 75 - 12;
    }

  pos.x -= 700 + (*this->items)[0].type * 50;
  text = TTF_RenderUTF8_Blended(this->font, (*this->items)[5].text.c_str(), this->currentItem == 5 ? selected_red : light);
  SDL_BlitSurface(text, NULL, this->screen, &pos);
  SDL_FreeSurface(text);
  pos.x += 130 + (*this->items)[0].type * 50;
  pos.y += 170;
  text = TTF_RenderUTF8_Blended(this->font, (*this->items)[6].text.c_str(), this->currentItem == 6 ? selected : color);
  SDL_BlitSurface(text, NULL, this->screen, &pos);
  SDL_FreeSurface(text);
  SDL_FreeSurface(menu);
  SDL_FreeSurface(slider_cur);
  SDL_FreeSurface(slider_bar);
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
}

void Menu::hold() {
  this->holded = true;
}

void Menu::unhold() {
  usleep(120000);
  this->holded = false;
}
