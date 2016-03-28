#include "server.hpp"

void		tcps_send_to_all(t_tcps *tcp)
{
  int		i;

  i = -1;
  while (++i < 10)
    {
      if (tcp->cli_sock[i] != 0)
	write(tcp->cli_sock[i], tcp->buff, strlen(tcp->buff));
    }
}

void		tcps_sync_all(t_tcps *tcp)
{
  char		buff[20 * 10 + 10 + 1];
  int		i;

  i = -1;
  buff[0] = 0;
  strcpy(buff, "/s\n");
  while (++i < tcp->nb_actual)
    {
      strcat(buff, tcp->pseudo[i]);
      strcat(buff, "\n");
    }
  i = -1;
  while (++i < tcp->nb_actual)
    {
      write(tcp->cli_sock[i], buff, strlen(buff));
    }
}
