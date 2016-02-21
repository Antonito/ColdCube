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
