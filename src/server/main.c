#include "server.hpp"

int		main(int argc, char **argv)
{
  t_all		all;
  int		i;
  int		j;

  if (argc < 2)
    {
      fprintf(stderr, "Usage:\n./server_game port\n");
      return (1);
    }
  i = -1;
  while (++i < 10)
    {
      all.connected[i] = 0;
      all.timeout[i] = 0;
      j = -1;
      while (++j < 21)
	all.pseudo[i][j] = 0;
    }
  all.port = atoi(argv[1]);
  if (pthread_create(&all.tcpt, NULL, main_tcp_thread, (void *)&all) != 0)
    {
      fprintf(stderr, "error creating the tcp thread :(\n");
      return (1);
    }
  if (pthread_create(&all.tudp, NULL, main_udp_thread, (void *)&all) != 0)
    {
      fprintf(stderr, "error creating the udp thread :(\n");
      return (1);
    }
  pthread_join(all.tcpt, NULL);
  pthread_join(all.tudp, NULL);
  return (0);
}
