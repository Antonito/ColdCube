#include <GL/gl.h>
#ifdef _WIN32
#else
# include <stdbool.h>
# include <stdint.h>
#endif

bool	checkPacket(char *str)
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
