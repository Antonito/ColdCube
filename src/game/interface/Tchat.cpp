#include <SDL2/SDL.h>
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_image.h"
#include "game.hpp"
#include "Tchat.hpp"
#include <vector>
#include <string>
#include <time.h>
#include <iostream>
#include <sys/time.h>


Tchat::Tchat()
{
  Tchat(0);
}

Tchat::Tchat(unsigned char transparency)
{
  this->messages = std::vector<std::string>(4);
  this->messages[0] = "toto";
  this->messages[1] = "toto";
  this->maxlen = 640;
  this->header = IMG_Load(TCHAT_HEADER);
  this->footer = IMG_Load(TCHAT_FOOTER);
  this->background = IMG_Load(TCHAT_BACKGROUND);
  this->name_font = TTF_OpenFont(TCHAT_FONT_NAME, (int)(50 / WIN_RATIO));
  this->text_font = TTF_OpenFont(TCHAT_FONT_TEXT, (int)(50 / WIN_RATIO));
  this->isFocused = false;
  this->transparency = transparency;
}

void Tchat::constructor()
{
  this->messages = std::vector<std::string>();
  this->messages.push_back("Server: Hello there!");
  this->messages.push_back("I'm a barbie girl");
  this->messages.push_back("in a barbie woooorld");
  this->messages.push_back("life in plastic");
  this->messages.push_back("is fantastic");
  this->maxlen = 640;
  this->header = IMG_Load(TCHAT_HEADER);
  this->footer = IMG_Load(TCHAT_FOOTER);
  this->background = IMG_Load(TCHAT_BACKGROUND);
  this->name_font = TTF_OpenFont(TCHAT_FONT_TEXT, (int)(30 / WIN_RATIO));
  this->text_font = TTF_OpenFont(TCHAT_FONT_TEXT, (int)(30 / WIN_RATIO));
  this->isFocused = false;
  this->cursor_img = SDL_CreateRGBSurface(0, 2, (int)(40 / WIN_RATIO), 32, 0, 0, 0, 0);
  this->input = new std::string();
  SDL_FillRect(this->cursor_img, NULL, SDL_MapRGB(this->cursor_img->format, 0, 0, 0));
  this->cursor_pos = 0;
  this->cursor = 0;
}

Tchat::~Tchat()
{
  TTF_CloseFont(this->name_font);
  TTF_CloseFont(this->text_font);
  SDL_FreeSurface(this->background);
  SDL_FreeSurface(this->header);
  SDL_FreeSurface(this->footer);
}

void Tchat::display(SDL_Rect pos, SDL_Surface *to)
{
  SDL_Rect base = pos;
  SDL_Rect text_pos = {42, pos.h - this->footer->h - 50, pos.w, pos.h};
  SDL_Surface *background = IMG_Load(TCHAT_BACKGROUND);
  SDL_Surface *text, *pseudo;
  SDL_Color grey = {82, 82, 82, 0},
	    black = {0, 0, 0, 0};
  std::string pseudonym, msg;
  size_t position;
  struct timeval tv;

  for (long i = this->messages.size() ; i-- ;)
  {
    msg = this->messages[i];
    position = this->messages[i].find(":");
    pseudo = NULL;
    if (position != std::string::npos)
      {
	pseudonym = this->messages[i].substr(0, position + 1);
	msg = this->messages[i].substr(position + 1);
	pseudo = TTF_RenderUTF8_Blended(this->name_font, pseudonym.c_str(), black);
	SDL_BlitSurface(pseudo, NULL, background, &text_pos);
	text_pos.x += pseudo->w + 10;
      }
    text = TTF_RenderUTF8_Blended(this->text_font, msg.c_str(), grey);
    SDL_BlitSurface(text, NULL, background, &text_pos);
    text_pos.x = 42;
    text_pos.y -= 35;
    SDL_FreeSurface(text);
    if (pseudo)
      SDL_FreeSurface(pseudo);
  }
  SDL_BlitSurface(background, NULL, to, &pos);
  pos = base;
  SDL_BlitSurface(header, NULL, to, &pos);
  pos = base;
  pos.y = base.h - footer->h;
  SDL_BlitSurface(footer, NULL, to, &pos);
  pos.y += 2 * footer->h / 3 - 12;
  pos.x += 54;
  gettimeofday(&tv, NULL);
  text = TTF_RenderUTF8_Blended(this->text_font, this->input->c_str(), black);
  SDL_BlitSurface(text, NULL, to, &pos);
  pos.x += this->cursor_pos;
  if (!this->isFocused && (tv.tv_usec > 500000))
    SDL_BlitSurface(cursor_img, NULL, to, &pos);
  SDL_FreeSurface(background);
  SDL_FreeSurface(text);
}

void Tchat::focus()
{
  this->isFocused = !this->isFocused;
  if (this->isFocused)
    this->cursor_pos = this->input->length();
}

void Tchat::moveRight()
{
  if ((this->cursor + 1) > this->input->length())
    return;
  do
    ++this->cursor, std::cout << "gone left : " << (int)((*this->input)[this->cursor - 1]) << std::endl;
  while ((char)((*this->input)[this->cursor]) < -64);
  std::cout << (int)((*this->input)[this->cursor]) << std::endl << std::endl;
  write_text("");
}

void Tchat::moveLeft()
{
  if (!this->cursor)
    return;
  do
    --this->cursor;
  while ((char)((*this->input)[this->cursor]) < -64);
  write_text("");
}

void Tchat::backspace()
{
  if (!this->cursor)
    return;
  do
    this->input->erase(--this->cursor, 1);
  while (this->cursor &&
	 (char)((*this->input)[this->cursor - 1]) < 0 &&
	 (char)((*this->input)[this->cursor - 1]) > -64);
  if (!this->cursor)
    this->cursor = this->cursor_pos = 0;
  else
    write_text("");
}

void Tchat::write_text(const char *text)
{
  std::string backup = *(this->input);
  SDL_Surface *bef_cur, *tot;
  SDL_Color black = {0, 0, 0, 0};
  std::string before;

  if (*text)
    this->input->replace(this->cursor, 0, text);
  this->cursor += strlen(text);
  before = this->input->substr(0, this->cursor);
  bef_cur = TTF_RenderUTF8_Blended(this->text_font, before.c_str(), black);
  tot = TTF_RenderUTF8_Blended(this->text_font, this->input->c_str(), black);
  if ((unsigned long)tot->w >= this->maxlen)
    *(this->input) = backup, this->cursor -= strlen(text);
  else
    this->cursor_pos = bef_cur ? bef_cur->w : 0;
  SDL_FreeSurface(bef_cur);
  SDL_FreeSurface(tot);
}

void Tchat::send()
{
  std::cout << "SENDING : " << this->input << std::endl;
  this->messages.push_back(*this->input);
  *(this->input) = "";
  this->cursor = this->cursor_pos = 0;
}

void Tchat::setTransparency(int transparency)
{
  this->transparency = transparency;
}
