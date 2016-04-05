#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int	main(int ac, char **av)
{
  int	nb;
  int	i = 0;
  char	filename[14] = {0};
  int	fd;
  int	height;
  int	j;
  int	temp = 0;
  unsigned char	col = 0;
  int	total = 0;

  srand(time(NULL));
  if (ac >= 2)
    nb = atoi(av[1]);
  else
    nb = rand() % 256;
  while (i < nb)
    {
      sprintf(filename, "map/chunk_%03d", i);
      if ((fd = creat(filename, 00644)) == -1)
	{
	  printf("Error: Failed to create the file '%s'\n", filename);
	  return (1);
	}
      /* height = rand() % 20 + 12; */
      /* height = 64; */
      height = 10;
      printf("%s %d\n", filename, height);
      write(fd, &height, 4);
      total += 4;
      temp = (i % 8) * 16;
      write(fd, &temp, 4);
      total += 4;
      temp = (i / 8) * 16;
      write(fd, &temp, 4);
      total += 4;
      //      temp = rand() % 10;
      temp = 0;
      write(fd, &temp, 4);
      total += 4;
      j = 0;
      height *= 256;
      while (j < height)
	{
	  /* if (j / 256 == 0) */
	  /*   col = rand() % 6 + 1; */
	  /* else */
	  if (j < 256)
	    col = rand() % 6 + 1;
	  /* else if (rand() % 100 && j % 16 == 0 && j % 256 != 0) */
	  /*   col = rand() % 7; */
	  else
	    col = 0;
	  /* if (rand() % 20) */
	  /* if (j < 3 * 256) */
	  /*   //    col = rand() % 55 + 200; */
	  /*   col = rand() % 7 + 1; */
	  /*   // col = j; */
	  /* else if (rand() % 20 == 0) */
	  /*   col = rand() % 7 + 1; */
	  /* else */
	  /* col = 0; */
	  write(fd, &col, 1);
	  total++;
	  j++;
	}
      close(fd);
      i++;
    }
  printf("TOTAL SIZE:\n%dB\n%.2fkB\n%.2fMB\n", total, total / 1000.0f, total / 1000000.0f);
  return (0);
}
