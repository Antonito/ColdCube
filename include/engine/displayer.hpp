#ifndef DISPLAYER_HPP_
# define DISPLAYER_HPP_

//# include <SFML/Audio.hpp>
# include <SDL2/SDL.h>
# include <string>
# include "engine/map.hpp"
# include "engine/player.hpp"
# include "Menu.h"
# include "User.hpp"
# include "common_structs.hpp"

class Displayer
{
 public:
  Displayer(int width, int height, const std::string& title);

  void	Clear(float r, float g, float b, float a);
  void  Update(Camera &cam, Map &map, Player &player, t_data *data, User &user);
  void  UpdateRoom(t_data *data, SDL_Rect *, SDL_Surface *, SDL_Surface *);
  void  UpdateMenu(Menu *menu, std::vector<menuItem> &items, SDL_Rect *pos,
		   SDL_Surface *screen, SDL_Surface *surface, t_data *data);
  SDL_Window	*GetWin()const{return m_window;};
  bool	IsClosed();
  void	setClosed(bool state){m_isClosed = state;};

  virtual ~Displayer();
 protected:
 private:
  SDL_Window*	m_window;
  TTF_Font	*name_font;
  SDL_GLContext	m_glContext;
  bool		m_isClosed;
  SDL_Surface*	m_windowSurface;
};

int	room(Displayer &, t_data *);

#endif // !DISPLAYER_HPP_
