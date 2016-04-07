#include "server.hpp"
#include "common_structs.hpp"

#ifdef	CHEAT
# include "cheat.hpp"
t_cheat	cheat;
#endif

int		main(int argc, char **argv)
{
  t_all		all;
  int		i;
  int		j;

#ifdef	CHEAT
  memset(&cheat, 0, sizeof(t_cheat));
#endif
  memset(&all, 0, sizeof(t_all));
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
      fprintf(stderr, "Error: Creating the TCP thread\n");
      return (1);
    }
  if (pthread_create(&all.tudp, NULL, main_udp_thread, (void *)&all) != 0)
    {
      fprintf(stderr, "Error: Creating the UDP thread\n");
      return (1);
    }
  // if (pthread_create(&all.aiThread, NULL, main_ai_thread, (void *)&all) != 0)
  //   {
  //     fprintf(stderr, "Error: Creating the AI thread\n");
  //     return (1);
  //   }
  pthread_join(all.tcpt, NULL);
  pthread_join(all.tudp, NULL);
  //  pthread_join(all.aiThread, NULL);
  return (0);
}
