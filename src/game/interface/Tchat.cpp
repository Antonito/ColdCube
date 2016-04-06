#include <SDL2/SDL.h>
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_image.h"
#include "game.hpp"
#include "Tchat.hpp"
#include <vector>
#include <string>
#include <time.h>
#include <iostream>


Tchat::Tchat()
{
  Tchat(0);
}
Tchat::Tchat(unsigned char transparency)
{
  this->messages = new std::vector<std::string>;
  this->messages->push_back("You are now connected");
  this->maxlen = 20;
  this->background = IMG_Load(TCHAT_BACKGROUND);
  this->header = IMG_Load(TCHAT_HEADER);
  this->footer = IMG_Load(TCHAT_FOOTER);
  this->name_font = TTF_OpenFont(TCHAT_FONT_NAME, (int)(50 / WIN_RATIO));
  this->text_font = TTF_OpenFont(TCHAT_FONT_TEXT, (int)(50 / WIN_RATIO));
  this->isFocused = false;
  this->input = "";
  this->transparency = transparency;
}

Tchat::~Tchat()
{
  delete this->messages;
  TTF_CloseFont(this->name_font);
  TTF_CloseFont(this->text_font);
  SDL_FreeSurface(this->background);
  SDL_FreeSurface(this->header);
  SDL_FreeSurface(this->footer);
}

void Tchat::display(SDL_Rect pos, SDL_Surface *to)
{
  display(pos, to, WIN_Y);
}

void Tchat::display(SDL_Rect pos, SDL_Surface *to, int height)
{
  SDL_BlitSurface(this->background, NULL, to, &pos);
}

void Tchat::focus()
{
  this->isFocused = !this->isFocused;
  if (this->isFocused)
    this->cursor = this->input.length();
}

void Tchat::moveRight()
{
  if (this->cursor < this->input.length())
    ++this->cursor;
}

void Tchat::moveLeft()
{
  if (this->cursor)
    --this->cursor;
}

void Tchat::backspace()
{
  if (!isprint(this->input[this->input.length() - 1]))
    this->input.erase(this->input.length() - 2);
  else
    this->input.erase(this->input.length() - 1);
}

void Tchat::write_text(char *text)
{
  std::string backup = this->input;

  this->input += text;
  if (this->input.length() >= this->maxlen)
    this->input = backup;
}

void Tchat::send()
{
  std::cout << "SENDING : " << this->input << std::endl;
  this->input = "";
}

void Tchat::setTransparency(int transparency)
{
  this->transparency = transparency;
}
