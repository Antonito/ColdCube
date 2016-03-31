#include "server.hpp"

void		udps_send_to_all(t_udps *udp)
{
  int		i;
  int		j;

  i = -1;
  j = -1;
  while (++i < udp->nb_actual)
    {
      j = -1;
      while (++j < udp->nb_actual)
	{
	  sendto(udp->main_sock, udp->cli_buff[j], 42, 0,
		 (struct sockaddr *)&udp->cli_sock[i], udp->cli_addrl);
	  /* fprintf(stdout, "send buffer %d to cli %d ! ", j, i); */
	  /* fflush(stdout); */
	}
    }
}

void		set_cli_buff(t_udps *udp, int index)
{
  int		i;

  i = -1;
  while (++i < 42)
    udp->cli_buff[index][i] = udp->buff[i];
}
