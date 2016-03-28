#include <boost/lexical_cast.hpp>
#include <iostream>
#include <string>
#include "map.hpp"
#include "camera.hpp"
#include <glm/gtc/type_ptr.hpp>

extern Camera g_Camera;
extern glm::quat g_Rotation;
extern GLint g_uniformMVP;

Map::Map()
{

}

Map::Map(const std::string &dir)
{
  int		i = 0;
  bool		isLoaded = true;

  while (i < 64 && isLoaded)
    {
      m_chunks[i] = Chunk(dir, i);
      m_chunks[i].Temp(false);
      isLoaded = m_chunks[i].IsLoaded();
      i++;
    }
  m_nbChunk = i;
}

void Map::Draw()
{
  int	i;

  i = 0;
  while (i < m_nbChunk)
    {
      if (m_chunks[i].IsLoaded())
	m_chunks[i].Draw();
      i++;
    }
}

Map::~Map()
{
}

void Map::PutCube(unsigned char cube, ivec3 pos)
{
  int chunk = pos.x / 16 + pos.y / 16 * 8;
  ivec3 chunk_pos = ivec3(pos.x % 16, pos.y % 16, pos.z - 1);

  if (m_chunks[chunk].IsLoaded())
    m_chunks[chunk].PutCube(cube, chunk_pos);
}

void Map::Save()
{
  int	i = 0;
  char  name[14] = {0};

  while (i < m_nbChunk && m_chunks[i].IsLoaded())
    {
      sprintf(name, "map/chunk_%03d", i);
      m_chunks[i].Save(name);
      i++;
    }
  printf("\nMap Saved !\n");
}
