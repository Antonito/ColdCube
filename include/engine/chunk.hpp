#ifndef CHUNK_HPP_
# define CHUNK_HPP_

# include "misc.hpp"
# include "texture.hpp"
# include "mesh.hpp"

using namespace glm;

extern "C" {
  char *LoadChunk(char *dir, int chunk, int *height, int *pos);
  void	ClearChunk(char *blocks, int height);
}

class Chunk
{
public:
  Chunk();
  Chunk(const std::string &path, int chunk);
  void Draw();
  void PutCube(unsigned char cube, ivec3 pos);
  ~Chunk();
  bool IsLoaded() {return m_isLoaded;}
  void Save(char *file);
  unsigned char GetBlock(int x, int y, int z);

private:
  Mesh		*m_planes;
  ivec3		m_pos;
  int		m_height;
  char		*m_chunk;
  Texture	*m_texture;
  bool		m_isLoaded;
};

#endif // !CHUNK_HPP_
