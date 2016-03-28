#include "chunk.h"
#include <stdlib.h>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

Chunk::Chunk(const std::string &name)
{
  int	fd;
  int	size;

  fd = open(name.c_str(), O_RDONLY)
  if (fd == -1)
    {
      m_blocs = NULL;
      return ;
    }
  if (read(fd, &m_height, 4) < 4)
    {
      m_blocs = NULL;
      close(fd);
      return ;
    }
  size = m_height * 256;
  m_blocs = malloc(size);
  if (m_blocs == NULL)
    {
      close(fd);
      return ;
    }
  if (read(fd, m_blocs, size) < size)
    {
      free(m_blocs);
      close(fd);
      m_blocs = NULL;
      return ;
    }
  close(fd);
}

Chunk::~Chunk()
{
  free(m_blocs);
}

void	Chunk::DrawChunk()
{
  int	i = 0;
  int	size = m_height * 256;

  while (i < size)
    {

      i++;
    }
}
