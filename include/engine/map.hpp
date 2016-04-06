#ifndef MAP_HPP_
# define MAP_HPP_

# include "mesh.hpp"
# include "chunk.hpp"
# include "shader.hpp"

class Map
{
 public:
  Map();
  Map(const std::string &dir);
  void PutCube(unsigned char cube, ivec3 pos);
  unsigned char GetBlock(vec3 pos);
  ~Map();
  bool IsLoaded(ivec3 pos);
  void Draw();
  void Save();
private:
  int	m_nbChunk;
  Chunk	*m_chunks[64];
};

#endif // !MAP_HPP_
