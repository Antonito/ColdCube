#include <iostream>
#include <string>
#include "engine/map.hpp"
#include "engine/camera.hpp"
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
      m_chunks[i] = new Chunk(dir, i);
      isLoaded = m_chunks[i]->IsLoaded();
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
      if (m_chunks[i]->IsLoaded())
	m_chunks[i]->Draw();
      i++;
    }
}

Map::~Map()
{
  int	i = 0;

  while (i < m_nbChunk)
    {
      delete m_chunks[i];
      i++;
    }
}

void Map::PutCube(unsigned char cube, ivec3 pos)
{
  int chunk = pos.x / 16 + pos.y / 16 * 8;
  ivec3 chunk_pos = ivec3(pos.x % 16, pos.y % 16, pos.z);

  if (m_chunks[chunk]->IsLoaded())
    m_chunks[chunk]->PutCube(cube, chunk_pos);
}

unsigned char	Map::GetBlock(vec3 pos)
{
  ivec3 p(pos);
  int	x;
  int	y;
  int	c;

  if (p.x < 0 || p.y < 0)
    return (0);
  x = p.x / 16;
  y = p.y / 16;
  if (x < 0 || x > 7 || y < 0 || y > 7 || p.z < 0.0f || p.z > 16.0f)
    return (0);
  c = x + 8 * y;
  unsigned char a = m_chunks[c]->GetBlock(p.x % 16, p.y % 16, p.z);
  return (a);
}

void Map::Save()
{
  int	i = 0;
  char  name[14] = {0};

  while (i < m_nbChunk && m_chunks[i]->IsLoaded())
    {
      sprintf(name, "map/chunk_%03d", i);
      m_chunks[i]->Save(name);
      i++;
    }
  printf("\nMap Saved !\n");
}

bool	Map::IsLoaded(ivec3 pos)
{
  int	x;
  int	y;
  int	c;

  x = pos.x / 16;
  y = pos.y / 16;
  if (x < 0 || x > 7 || y < 0 || y > 7)
    return (0);
  c = x + 8 * y;
  return (m_chunks[c]->IsLoaded());
}
