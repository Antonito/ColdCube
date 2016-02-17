#include "server.h"

void		send_to_all(t_udps *udp, char *str)
{
  int		i;

  i = -1;
  while (++i < udp->nb_actual)
    {
      udp_send(udp->main_sock, str, udp->cli_sock[i]);
    }
}

void		set_cli_buff(t_udps *udp, int index)
{
  memcpy(udp->cli_buff[i], udp->buff, 120); /* same here, it depends on the UDP MSG size */
}
