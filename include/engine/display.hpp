#ifndef DISPLAY_HPP_
# define DISPLAY_HPP_

# include <SDL2/SDL.h>
# include <string>
# include "engine/map.hpp"
# include "engine/player.hpp"

class Display
{
 public:
  Display(int width, int height, const std::string& title);

  void	Clear(float r, float g, float b, float a);
  void  Update(Camera &cam, Map &map, Player &player);
  bool	IsClosed();

  virtual ~Display();
 protected:
 private:
  SDL_Window*	m_window;
  SDL_GLContext	m_glContext;
  bool		m_isClosed;
};

#endif // !DISPLAY_HPP_
