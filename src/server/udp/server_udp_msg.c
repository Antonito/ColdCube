#include <stdbool.h>
#include "server.hpp"

void		udps_send_to_all(t_udps *udp)
{
  int		i;
  int		j;

  i = -1;
  j = -1;
  while (++i < 10 && udp->connected[i] == 1)
    {
      j = -1;
      while (++j < 10 && udp->connected[i] == 1)
	{
	  sendto(udp->main_sock, udp->cli_buff[j], 42, 0,
		 (struct sockaddr *)&udp->cli_sock[i], udp->cli_addrl);
	}
    }
}

void		set_cli_buff(t_udps *udp, int index)
{
  int		i;

  i = -1;
  while (++i < 42)
    udp->cli_buff[index][i] = udp->buff[i];
  udp->timeout[index] = 1;
}

void		udps_check_timeout(t_udps *udp)
{
  int		i;

  i = -1;
  while (++i < 10)
    {
      if (udp->timeout[i] == 0 && udp->connected[i] == 1)
	{
	  fprintf(stdout, "client %s timedout !\n", udp->pseudo[i]);
	  udp_send_disconnect(udp, (char)i);
	  udp->connected[i] = 0;
	  udp->nb_actual -= 1;
	}
    }
}

void		udp_send_disconnect(t_udps *udp, char id)
{
  uint32_t	events;
  char		packet[42];
  int		i;
  int		n;
  char		*tmp;

  setEvent(&events, CONNECTED, false);
  memset(packet, 0, 42);
  packet[0] = id;
  n = 37;
  i = 0;
  tmp = (char *)&events;
  while (i < 4)
    {
      packet[n + i] = tmp[i];
      ++i;
    }
  sendto(udp->main_sock, packet, 42, 0,
                 (struct sockaddr *)&udp->cli_sock[(int)id], udp->cli_addrl);
}
