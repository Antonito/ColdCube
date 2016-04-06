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
  std::cout << "caca" << std::endl;
  this->messages = std::vector<std::string>(4);
  this->messages[0] = "toto";
  this->messages[1] = "toto";
  std::cout << this->messages.size() << " <- size" << std::endl;
  this->maxlen = 20;
  this->header = IMG_Load(TCHAT_HEADER);
  this->footer = IMG_Load(TCHAT_FOOTER);
  this->background = IMG_Load(TCHAT_BACKGROUND);
  this->name_font = TTF_OpenFont(TCHAT_FONT_NAME, (int)(50 / WIN_RATIO));
  this->text_font = TTF_OpenFont(TCHAT_FONT_TEXT, (int)(50 / WIN_RATIO));
  this->isFocused = false;
  this->input = "";
  this->transparency = transparency;
}

void Tchat::constructor()
{
  std::cout << "caca" << std::endl;
  this->messages = std::vector<std::string>(4);
  this->messages[0] = "toto";
  std::cout << this->messages.size() << " <- size" << std::endl;
  this->maxlen = 20;
  this->header = IMG_Load(TCHAT_HEADER);
  this->footer = IMG_Load(TCHAT_FOOTER);
  this->background = IMG_Load(TCHAT_BACKGROUND);
  this->name_font = TTF_OpenFont(TCHAT_FONT_NAME, (int)(50 / WIN_RATIO));
  this->text_font = TTF_OpenFont(TCHAT_FONT_TEXT, (int)(50 / WIN_RATIO));
  this->isFocused = false;
  this->transparency = transparency;
}

Tchat::~Tchat()
{
  TTF_CloseFont(this->name_font);
  TTF_CloseFont(this->text_font);
  SDL_FreeSurface(this->background);
  SDL_FreeSurface(this->header);
  SDL_FreeSurface(this->footer);
}

void Tchat::getTchat()
{
  std::cout << "this = " << this << std::endl;
  std::cout << "this->messages = " << this->messages.size() << std::endl;
}

void Tchat::display(SDL_Rect pos, SDL_Surface *to)
{
  SDL_Rect base = pos;
  SDL_Rect text_pos = {42, 42, pos.w, pos.h};
  SDL_Surface *header = IMG_Load(TCHAT_HEADER);
  SDL_Surface *footer = IMG_Load(TCHAT_FOOTER);
  SDL_Surface *background = IMG_Load(TCHAT_BACKGROUND);
  SDL_Surface *text;
  SDL_Color grey = {42, 42, 42, 0};

  this->getTchat();
  for (int i = this->messages.size() ; i && 0 ; i--)
  {
    std::cout << "Printing : " << this->messages[i].c_str() << std::endl;
    text = TTF_RenderUTF8_Blended(this->text_font, this->messages[i].c_str(), grey);
    SDL_BlitSurface(text, NULL, background, &text_pos);
    SDL_FreeSurface(text);
  }
  SDL_BlitSurface(background, NULL, to, &pos);
  pos = base;
  SDL_BlitSurface(header, NULL, to, &pos);
  pos = base;
  pos.y = base.h - footer->h;
  SDL_BlitSurface(footer, NULL, to, &pos);
  SDL_FreeSurface(header);
  SDL_FreeSurface(footer);
  SDL_FreeSurface(background);
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
