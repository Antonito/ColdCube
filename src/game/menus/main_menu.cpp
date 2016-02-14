#include "game.hpp"

int	main_menu(t_data *data)
{
  glClear(GL_COLOR_BUFFER_BIT);
  glBegin(GL_QUADS);
  glColor3ub(0,0,255);
  glVertex2d(-0.75,-0.75);
  glVertex2d(-0.75,0.75);
  glColor3ub(255,0,0);
  glVertex2d(0.75,0.75);
  glVertex2d(0.75,-0.75);
  glEnd();
  return (0);
}
