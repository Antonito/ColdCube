#include <stdbool.h>
#include "events.hpp"
#include "server.hpp"

void		udps_send_to_all(t_all *all)
{
  int		i;
  int		j;

  i = -1;
  while (++i < 10)
    {
      if (all->isPackage[i] == 0)
	continue;
      j = -1;
      while (++j < 10)
	{
	  if (all->isPackage[j] == 0)
	    continue;
	  sendto(all->udp->main_sock, all->udp->cli_buff[i], 42, 0,
		 (struct sockaddr *)&all->udp->cli_sock[j],
		 all->udp->cli_addrl);
	}
    }
  memset(all->isPackage, 0, sizeof(int) * 10);
}

void		set_cli_buff(t_all *all, int index)
{
  int		i;

  i = -1;
  while (++i < 42)
    all->udp->cli_buff[index][i] = all->udp->buff[i];
  all->timeout[index] = 1;
  all->isPackage[index] = 1;
}

void		udps_check_timeout(t_all *all)
{
  int		i;

  i = -1;
  while (++i < 10)
    {
      if (all->timeout[i] == 0 && all->connected[i] == 1)
	{
	  fprintf(stdout, "Client %s timed out\n", all->pseudo[i]);
	  udp_send_disconnect(all, (char)i);
	  all->connected[i] = 0;
	  close(all->tcp->cli_sock[i]);
	  all->tcp->cli_sock[i] = 0;
	  all->nb_actual -= 1;
	}
      else
	all->timeout[i] = 0;
    }
}

void		udp_send_disconnect(t_all *all, char id)
{
  uint32_t	events;
  char		packet[42];
  int		i;
  int		j;
  int		n;
  char		*tmp;

  setEvent(&events, IS_CONNECTED, false);
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
#ifdef	DEBUG
  printf("SEND DISCONNECT\n");
#endif
  i = -1;
  while (++i < 10)
    {
      if (all->connected[i] == 0)
	continue;
      j = -1;
      while (++j < 10)
	{
	  if (all->connected[j] == 0)
	    continue;
	  sendto(all->udp->main_sock, packet, 42, 0,
		 (struct sockaddr *)&all->udp->cli_sock[(int)id], all->udp->cli_addrl);
	}
    }
}
