#include "server.hpp"

void		send_to_all(t_udps *udp)
{
  int		i;

  i = -1;
  while (++i < udp->nb_actual)
    {
      sendto(udp->main_sock, udp->cli_buff[i], 120, 0, (struct sockaddr *)&udp->cli_sock[i], udp->cli_addrl);
    }
}

void		set_cli_buff(t_udps *udp, int index)
{
  memcpy(udp->cli_buff[index], udp->buff, 120); /* same here, it depends on the UDP MSG size */
}
