#ifndef CHUNK_H_
# define CHUNK_H_

# include "GL/gl.h"
# include <glm/glm.hpp>
# include <glm/gtx/transform.hpp>
# include <glm/gtc/type_ptr.hpp>
# include <string>

class	Chunk
{
public:
  Chunk(const std::String &name);
  ~Chunk();
private:
  unsigned char	*m_blocs;
  int		m_height;
  glm::vec3	m_pos;
}

#endif /* !CHUNK_H_ */
