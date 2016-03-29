#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

intmain(int ac, char **av)
{
  intnb;
  inti = 0;
  charfilename[14] = {0};
  intfd;
  intheight;
  intj;
  inttemp = 0;
  unsigned charcol = 0;
  inttotal = 0;

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
      height = (i < 4) ? 32 : 1;
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
      temp = 1;
      write(fd, &temp, 4);
      total += 4;
      j = 0;
      height *= 256;
      while (j < height)
	{
	  if (j / 256 == 0)
	    col = 1;
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
