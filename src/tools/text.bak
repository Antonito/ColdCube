#include <string.h>
#include <GL/gl.h>
#include <GL/glut.h>

void	drawText(char *str, int posx, int posy,
		 GLfloat red, GLfloat green, GLfloat blue)
{
  int	len;
  int	i;

  glColor3f(red, green, blue);
  glRasterPos2f(posx, posy);
  len = strlen(str);
  i = 0;
  while (i < len)
    {
      glutBitmapCharacter(GLUT_BITMAP_9_BY_15, str[i]);
      ++i;
    }
}
