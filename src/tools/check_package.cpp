#include <GL/gl.h>
#include <stdbool.h>
#include <stdint.h>

bool	checkPackage(char *str)
{
  int	i;

  i = 1;
  if (str[i++] || str[sizeof(GLfloat) + i++] ||
      str[(sizeof(GLfloat) << 1) + i++] ||
      str[(sizeof(GLfloat) * 3) + i++] ||
      str[((sizeof(GLfloat) << 2)) + i++] ||
      str[sizeof(GLfloat) * 5 + i++] ||
      str[sizeof(GLfloat) * 6 + i++] ||
      str[sizeof(GLfloat) * 6 + sizeof(uint32_t) + i++] ||
      str[sizeof(GLfloat) * 6 + (sizeof(uint32_t) << 1) + i])
    return (false);
  return (true);
}
