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
    TTF_Font *name_font;
    TTF_Font *text_font;
    bool isFocused;
    int cursor;
    int maxlen;
    std::string input;
    std::vector<std::string> messages;
    unsigned char transparency;
  public:
    Tchat();
    Tchat(unsigned char transparency);
    ~Tchat();
    void getTchat();
    void backspace();
    void display(SDL_Rect, SDL_Surface *);
    void focus();
    void moveLeft();
    void moveRight();
    void send();
    void setTransparency(int);
    void write_text(char *);
    void scroll(int);
};

#endif /* !TCHAT_HPP */
