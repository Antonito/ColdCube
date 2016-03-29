#include "server.hpp"

int		main(int argc, char **argv)
{
  pthread_t	tcpt;
  /*pthread_t	tudp;*/
  int		tmp;
  int		port;

  if (argc < 2)
    {
      fprintf(stderr, "Usage:\n./server_game port\n");
      return (1);
    }
  port = atoi(argv[1]);
  if (pthread_create(&tcpt, NULL, main_tcp_thread, (void *)&port) != 0)
    {
      fprintf(stderr, "error creating the tcp thread :(\n");
      return (1);
    }
  /*tmp = atoi(argv[1]);
  if (pthread_create(&tudp, NULL, main_udp_thread, (void *)&tmp) != 0)
    {
      fprintf(stderr, "error creating the udp thread :(\n");
      return (1);
    }*/
  cmd_loop();
  return (0);
}

void		cmd_loop(void)
{
  int		run;
  char		str[20];

  run = 1;
  printf("\n>>");
  while ((run = read(0, &str, 19)) > 0)
    {
      str[run] = '\0';
      printf("\n>>");
      if (strncmp("exit", str, strlen(str) - 1) == 0)
	{
	  run = 0;
	  exit(0);
	}
    }
  }
