#include "engine/chunk.hpp"
#include <string.h>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>

#ifdef _WIN32
#else
# include <fcntl.h>
# include <unistd.h>
#endif

static Texture SetTex(char *, int);
 Mesh SetPlanes(int, vec3);
static unsigned int GetFullColor(unsigned char);

Chunk::Chunk()
{
  m_isLoaded = false;
  m_height = 0;
  m_pos = ivec3(0, 0, 0);
  m_chunk = NULL;
  m_texture = Texture();
  m_planes = Mesh();
}

Chunk::Chunk(const std::string &path, int chunk)
{
  m_isLoaded = false;
  int	p[3];
  m_chunk = LoadChunk(strdup(path.c_str()), chunk, &m_height, p);
  m_pos.x = p[0];
  m_pos.y = p[1];
  m_pos.z = p[2];
  if (m_chunk != NULL)
    {
      ClearChunk(m_chunk, m_height);
      m_texture = SetTex(m_chunk, m_height);
      vec3 pos(m_pos.x, m_pos.y, m_pos.z);
      m_planes = SetPlanes(m_height, pos);
      if (m_texture.GetTexture() != 0)
	m_isLoaded = true;
    }
}

Chunk::~Chunk()
{
  m_isLoaded = false;
}

void Chunk::Draw()
{
  m_texture.Bind(0);
  m_planes.Draw();
}

static Texture SetTex(char *chunk, int height)
{
  int	i, j, k, coord, coord2;
  int	size = 48 * height * 2;
  unsigned int	*imgData = new unsigned int[16 * size];
  int		h = 16 * height;

  i = j = k = 0;
  size = 256 * height;
  while (i < size)
    {
      coord = i / h + i % 16 * 16 + i % h / 16 * 256;

      coord2 = (i / h - 1) + i % 16 * 16 + i % h / 16 * 256;
      if (i / h == 0 || chunk[coord2] == 0)
	imgData[i] = GetFullColor(chunk[coord]);
      else
	imgData[i] = 0;

      coord2 = (i / h + 1) + i % 16 * 16 + i % h / 16 * 256;
      if (i / h == 15 || chunk[coord2] == 0)
	imgData[i + size] = GetFullColor(chunk[coord]);
      else
	imgData[i + size] = 0;
      i++;
    }
  while (j < size)
    {
      coord = j % 16 + j / h * 16 + j % h / 16 * 256;

      coord2 = j % 16 + (j / h - 1) * 16 + j % h / 16 * 256;
      if (j / h == 0 || chunk[coord2] == 0)
	imgData[2 * size + j] = GetFullColor(chunk[coord]);
      else
	imgData[2 * size + j] = 0;

      coord2 = j % 16 + (j / h + 1) * 16 + j % h / 16 * 256;
      if (j / h == 15 || chunk[coord2] == 0)
	imgData[3 * size + j] = GetFullColor(chunk[coord]);
      else
	imgData[3 * size + j] = 0;
      j++;
    }
  while (k < size)
    {
      if (k / 256 == 0 || chunk[k - 256] == 0)
	imgData[4 * size + k] = GetFullColor(chunk[k]);
      else
      	imgData[4 * size + k] = 0;
      if (k / 256 == height - 1 || chunk[k + 256] == 0)
	imgData[5 * size + k] = GetFullColor(chunk[k]);
      else
      	imgData[5 * size + k] = 0;
      k++;
    }
  Texture tex((const unsigned char*)imgData, 16, 2 * 48 * height, true);
  return (tex);
}

 Mesh SetPlanes(int height, vec3 pos)
{
  int	i, j;
  unsigned int	nbVertices = (4 * 16 * 2 + 4 * height) * 2;
  unsigned int	nbIndices = nbVertices / 2 * 3;
  Vertex	*vertices = new Vertex[nbVertices];
  unsigned int	indices[nbIndices];
  double		texSize = 48 * height * 2;

  i = j = 0;

  // Set the X planes
  while (j < 16)
    {
      vertices[4 * i] = Vertex(vec3(j, 0, 0) + pos, vec2(0, j * height / texSize));
      vertices[4 * i + 1] = Vertex(vec3(j, 0, height) + pos, vec2(0, (j + 1) * height / texSize));
      vertices[4 * i + 2] = Vertex(vec3(j, 16, height) + pos, vec2(1, (j + 1) * height / texSize));
      vertices[4 * i + 3] = Vertex(vec3(j, 16, 0) + pos, vec2(1, j * height / texSize));
      i++;
      j++;
    }
  j = 0;
  while (j < 16)
    {
      vertices[4 * i] = Vertex(vec3(j + 1, 0, 0) + pos, vec2(0, (j + 16) * height / texSize));
      vertices[4 * i + 1] = Vertex(vec3(j + 1, 16, 0) + pos, vec2(1, (j + 16) * height / texSize));
      vertices[4 * i + 2] = Vertex(vec3(j + 1, 16, height) + pos, vec2(1, (j + 17) * height / texSize));
      vertices[4 * i + 3] = Vertex(vec3(j + 1, 0, height) + pos, vec2(0, (j + 17) * height / texSize));
      i++;
      j++;
    }
  j = 0;

  // Set the Y planes
  while (j < 16)
    {
      vertices[4 * i] = Vertex(vec3(0, j, 0) + pos, vec2(0, (j + 32) * height / texSize));
      vertices[4 * i + 1] = Vertex(vec3(16, j, 0) + pos, vec2(1, (j + 32) * height / texSize));
      vertices[4 * i + 2] = Vertex(vec3(16, j, height) + pos, vec2(1, (j + 33) * height / texSize));
      vertices[4 * i + 3] = Vertex(vec3(0, j, height) + pos, vec2(0, (j + 33) * height / texSize));
      i++;
      j++;
    }
  j = 0;
  while (j < 16)
    {
      vertices[4 * i] = Vertex(vec3(0, j + 1, 0) + pos, vec2(0, (j + 48) * height / texSize));
      vertices[4 * i + 1] = Vertex(vec3(0, j + 1, height) + pos, vec2(0, (j + 49) * height / texSize));
      vertices[4 * i + 2] = Vertex(vec3(16, j + 1, height) + pos, vec2(1, (j + 49) * height / texSize));
      vertices[4 * i + 3] = Vertex(vec3(16, j + 1, 0) + pos, vec2(1, (j + 48) * height / texSize));
      i++;
      j++;
    }

  j = 0;
  // Set the Z planes
  while (j < height)
    {
      vertices[4 * i] = Vertex(vec3(0, 0, j) + pos, vec2(0, (j * 16 + 64 * height) / texSize));
      vertices[4 * i + 1] = Vertex(vec3(0, 16, j) + pos, vec2(0, ((j + 1) * 16 + 64 * height) / texSize));
      vertices[4 * i + 2] = Vertex(vec3(16, 16, j) + pos, vec2(1, ((j + 1) * 16 + 64 * height) / texSize));
      vertices[4 * i + 3] = Vertex(vec3(16, 0, j) + pos, vec2(1, (j * 16 + 64 * height) / texSize));
      i++;
      j++;
    }

  j = 0;
  while (j < height)
    {
      vertices[4 * i] = Vertex(vec3(0, 0, j + 1) + pos, vec2(0, ((j + height) * 16 + 64 * height) / texSize));
      vertices[4 * i + 1] = Vertex(vec3(16, 0, j + 1) + pos, vec2(1, ((j + height) * 16 + 64 * height) / texSize));
      vertices[4 * i + 2] = Vertex(vec3(16, 16, j + 1) + pos, vec2(1, ((j + height + 1) * 16 + 64 * height) / texSize));
      vertices[4 * i + 3] = Vertex(vec3(0, 16, j + 1) + pos, vec2(0, ((j + height + 1) * 16 + 64 * height) / texSize));
      i++;
      j++;
    }
  j = 0;
  while ((unsigned int)j < nbIndices / 6)
    {
      indices[6 * j] = 4 * j;
      indices[6 * j + 1] = 4 * j + 1;
      indices[6 * j + 2] = 4 * j + 2;
      indices[6 * j + 3] = 4 * j;
      indices[6 * j + 4] = 4 * j + 2;
      indices[6 * j + 5] = 4 * j + 3;
      j++;
    }

  Mesh mesh(vertices, nbVertices, indices, nbIndices, true);
  delete [] vertices;
  return (mesh);
}

static unsigned int GetFullColor(unsigned char color)
{
  static unsigned int colors[] =
    {0x00000000, 0xFFFFFFFF, 0xFF0000FF, 0xFF00FF00,
     0xFFFF0000, 0xFF222222, 0xFF777777};
  // static bool isSet = false;

  // if (!isSet)
  //   {
  //     int	i = 0;
  //     while (i < 256)
  // 	{
  // 	  // colors[i] = (((i >> 6) & 4) * 85) << 24;
  // 	  //colors[i] = i << 24;
  // 	  // colors[i] |= rand() % (256 * 256 * 256);
  // 	  //	  colors[i] = (rand() & 0x00FFFFFF) | (i << 24);
  // 	  colors[i] = (i << 24);
  // 	  colors[i] |= ((i >> 4) & 3) * 85;
  // 	  colors[i] |= (((i >> 2) & 3) * 85) << 8;
  // 	  colors[i] |= ((i & 3) * 85) << 16;
  // 	  // colors[i] |= i;
  // 	  // int	temp = rand() % 8;
  // 	  // // colors[i] = (i << 24);
  // 	  // colors[i] = (rand() % 100 + (((temp & 4) == 4) ? 155 : 0)) << 16;
  // 	  // colors[i] |= (rand() % 100 + (((temp & 2) == 2) ? 155 : 0)) << 8;
  // 	  // colors[i] |= rand() % 100 + (((temp & 1) == 1) ? 155 : 0);
  // 	  // // colors[i] = 256 * 256 * 256 - 1;
  // 	  // colors[i] |= i << 24;

  // 	  i++;
  // 	}
  //     isSet = true;
  //   }
  return (colors[(int)color]);
}

unsigned char Chunk::GetBlock(int x, int y, int z)
{
  return (m_chunk[x + (y << 4) + (z << 8)]);
}

void Chunk::PutCube(unsigned char cube, ivec3 pos)
{
  printf("[%d, %d] (%d, %d, %d)\n", m_pos.x, m_pos.y, pos.x, pos.y, pos.z);
  if (pos.z >= m_pos.z && pos.z <= m_pos.z + m_height &&
      (m_chunk[pos.x + 16 * pos.y + 256 * pos.z] == 0 || cube == 0))
    {
      m_chunk[pos.x + 16 * pos.y + 256 * pos.z] = cube;
      m_texture.~Texture();
      m_texture = SetTex(m_chunk, m_height);
    }
}

void	Chunk::Save(char *file)
{
  int	fd = open(file, O_RDWR);
  char  buf[16];
  int	size = 256 * m_height;

  if (fd != -1)
    {
      read(fd, buf, 16);
      write(fd, m_chunk, size);
    }
}
