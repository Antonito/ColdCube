#ifndef DISPLAY_HPP_
# define DISPLAY_HPP_

# include <SDL2/SDL.h>
# include <string>
# include "Menu.h"
# include "map.hpp"
# include "common_structs.hpp"

class Display
{
 public:
  Display(int width, int height, const std::string& title);

  void	Clear(float r, float g, float b, float a);
  void  Update(Camera &cam, Map &map);
  void  UpdateMenu(Menu *menu, std::vector<menuItem> &items, SDL_Rect *pos,
		   SDL_Surface *screen, SDL_Surface *surface, t_data *data);
  SDL_Window	*GetWin(){return m_window;};
  bool	IsClosed();

  virtual ~Display();
 protected:
 private:
  SDL_Window*	m_window;
  SDL_GLContext	m_glContext;
  bool		m_isClosed;
};

#endif // !DISPLAY_HPP_
