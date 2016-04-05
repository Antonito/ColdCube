#include "server.hpp"

void		tcps_send_to_all(t_all *all)
{
  int		i;

  i = -1;
  while (++i < 10)
    {
      if (all->connected[i] == 0)
	continue;
      if (all->tcp->cli_sock[i] != 0)
	write(all->tcp->cli_sock[i], all->tcp->buff, strlen(all->tcp->buff));
    }
}

void		tcps_sync_all(t_all *all)
{
  char		buff[20 * 10 + 10 + 1];
  int		i;

  i = -1;
  buff[0] = 0;
  strcpy(buff, "/s\n");
  while (++i < 10)
    {
      if (all->connected[i] == 0)
	continue;
      strcat(buff, all->pseudo[i]);
      strcat(buff, "\n");
    }
  i = -1;
  while (++i < 10)
    {
      if (all->connected[i] == 0)
	continue;
      write(all->tcp->cli_sock[i], buff, strlen(buff));
    }
}
