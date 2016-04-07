#include <SDL2/SDL.h>
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_image.h"
#include "game.hpp"
#include "Tchat.hpp"
#include "common_structs.hpp"
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
  this->messages.push_back("Server: Welcome to the room");
  this->maxlen = 640;
  this->header = IMG_Load(TCHAT_HEADER);
  this->footer = IMG_Load(TCHAT_FOOTER);
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
  SDL_FreeSurface(this->header);
  SDL_FreeSurface(this->footer);
}

void Tchat::display(SDL_Rect pos, SDL_Surface *to)
{
  SDL_Rect text_pos = {pos.x + 42, pos.h - this->footer->h - 40, pos.w, pos.h};
  SDL_Surface *text, *pseudo;
  SDL_Color grey = {82, 82, 82, 0},
	    black = {0, 0, 0, 0};
  std::string pseudonym, msg;
  this->background = IMG_Load(TCHAT_BACKGROUND);
  size_t position;
  struct timeval tv;

  for (long i = this->messages.size() ; i-- && text_pos.y > 0 ;)
  {
    msg = this->messages[i];
    position = this->messages[i].find(":");
    pseudo = NULL;
    if (position != std::string::npos)
      {
	pseudonym = this->messages[i].substr(0, position + 1);
	msg = this->messages[i].substr(position + 1);
	pseudo = TTF_RenderUTF8_Blended(this->name_font, pseudonym.c_str(), black);
	SDL_BlitSurface(pseudo, NULL, this->background, &text_pos);
	text_pos.x += pseudo->w + 10;
      }
    text = TTF_RenderUTF8_Blended(this->text_font, msg.c_str(), grey);
    SDL_BlitSurface(text, NULL, this->background, &text_pos);
    text_pos.x = 42;
    text_pos.y -= 35;
    SDL_FreeSurface(text);
    if (pseudo)
      SDL_FreeSurface(pseudo);
  }
  SDL_BlitSurface(this->background, NULL, to, &pos);
  if (!pos.y)
    SDL_BlitSurface(this->header, NULL, to, &pos);
  pos.y = this->background->h - this->footer->h;
  SDL_BlitSurface(this->footer, NULL, to, &pos);
  pos.y += 2 * this->footer->h / 3 - 12;
  pos.x += 54;
  gettimeofday(&tv, NULL);
  text = TTF_RenderUTF8_Blended(this->text_font, this->input->c_str(), black);
  SDL_BlitSurface(text, NULL, to, &pos);
  pos.x += this->cursor_pos;
  if (this->isFocused && (tv.tv_usec > 500000))
    SDL_BlitSurface(this->cursor_img, NULL, to, &pos);
  SDL_FreeSurface(text);
  SDL_FreeSurface(this->background);
}

bool Tchat::isFocus()
{
  return this->isFocused;
}

void Tchat::focus(bool value)
{
  this->isFocused = value;
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

  if (*text == '/')
    return;
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

void Tchat::send(void *all)
{
  t_data	*data;
  std::string	msg;

  if (!(*this->input->c_str()))
    return;
  data = (t_data *)all;
  msg = data->net.pseudo;
  msg += ": ";
  msg += *this->input;
#ifdef	DEBUG
  std::cout << "SENDING : " << msg << std::endl;
#endif
  write(data->net.tcp.sock, msg.c_str(), strlen(msg.c_str()));
  *(this->input) = "";
  this->cursor = this->cursor_pos = 0;
}

void Tchat::setTransparency(int transparency)
{
  this->transparency = transparency;
}

void Tchat::pushBack(std::string &message)
{
  this->messages.push_back(message);;
}
