#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

char	*LoadChunk(char *dir, int chunk, int *height, int *pos)
{
  char	*blocks;
  int	fd;
  char	*file;

  if (dir == NULL)
    {
      dprintf(2, "Error: Invalid mapname (NULL pointer)\n");
      exit(1);
    }
  if ((file = calloc(strlen(dir) + 11, 1)) == NULL)
    {
      dprintf(2, "Error: Memory allocation failed\n");
      exit(1);
    }
  sprintf(file, "%s/chunk_%03d", dir, chunk);
  if ((fd = open(file, O_RDONLY)) == -1)
    {
      exit(1);
    }
  if (read(fd, height, 4) < 4 || read(fd, pos, 12) < 12)
    {
      dprintf(2, "Error: Failed to read [height] and [pos] in '%s'\n", file);
      exit(1);
    }
  if ((blocks = malloc(256 * *height)) == NULL)
    {
      dprintf(2, "Error: Memory allocation for the %s failed (%d bytes)\n",
	      file, 256 * *height);
      exit(1);
    }
  if (read(fd, blocks, 256 * *height) < 256 * *height)
    {
      dprintf(2, "Error: Failed to read the %s (%d bytes)\n",
	      file, 256 * *height);
      exit(1);
    }
  close(fd);
  return (blocks);
}

void	ClearChunk(char *blocks, int height)
{
  int	x, y, z;
  char	*temp;

  if ((temp = calloc(256 * height, 1)) == NULL)
    return ;
  z = 0;
  while (z < height - 1)
    {
      y = 0;
      while (y < 15)
	{
	  x = 0;
	  while (x < 15)
	    {
	      if (x && y && z && blocks[z * 256 + y * 16 + x] &&
		  blocks[z * 256 + y * 16 + x - 1] && blocks[z * 256 + y * 16 + x + 1] &&
		  blocks[z * 256 + (y + 1) * 16 + x] && blocks[z * 256 + (y - 1) * 16 + x]
		  && blocks[(z + 1) * 256 + y * 16 + x] && blocks[(z - 1) * 256 + y * 16 + x])
		temp[z * 256 + y * 16 + x] = 1;
	      x++;
	    }
	  y++;
	}
      z++;
    }
  x = 0;
  y = 256 * height;
  while (x < y)
    {
      if (temp[x])
	blocks[x] = 0;
      x++;
    }
  free(temp);
}
