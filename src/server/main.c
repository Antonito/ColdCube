#include "server.hpp"

int		main(int argc, char **argv)
{
  pthread_t	tcpt;
  pthread_t	tudp;
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
  tmp = atoi(argv[1]);
  ++tmp;
  if (pthread_create(&tudp, NULL, main_udp_thread, (void *)&tmp) != 0)
    {
      fprintf(stderr, "error creating the udp thread :(\n");
      return (1);
    }
  pthread_join(tcpt, NULL);
  pthread_join(tudp, NULL);
  return (0);
}
