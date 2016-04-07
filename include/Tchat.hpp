#ifndef TCHAT_HPP
# define TCHAT_HPP

# include <SDL2/SDL.h>
# include "SDL2/SDL_ttf.h"
# include "SDL2/SDL_image.h"
# include <vector>
# include <string>

class Tchat
{
  SDL_Surface *background;
  SDL_Surface *footer;
  SDL_Surface *header;
  SDL_Surface *cursor_img;
  TTF_Font *name_font;
  TTF_Font *text_font;
  bool isFocused;
  unsigned int cursor;
  unsigned int cursor_pos;
  unsigned long maxlen;
  std::string *input;
  std::vector<std::string> messages;
  unsigned char transparency;
public:
  Tchat();
  Tchat(unsigned char transparency);
  ~Tchat();
  bool isFocus();
  void constructor();
  void backspace();
  void display(SDL_Rect, SDL_Surface *);
  void focus();
  void moveLeft();
  void moveRight();
  void send(void *all);
  void setTransparency(int);
  void write_text(const char *);
  void scroll(int);
  void pushBack(std::string &message);
};

#endif /* !TCHAT_HPP */
