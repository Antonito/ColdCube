#include "server.hpp"

void		init_tcps_cli(t_tcps *tcp)
{
  int		i;

  i = -1;
  while (++i < 10)
    tcp->cli_sock[i] = 0;
}

void		set_max_fd(t_tcps *tcp)
{
  int		i;

  i = -1;
  while (++i < 10)
    {
      if (tcp->cli_sock[i] != 0)
	FD_SET(tcp->cli_sock[i], &tcp->readfds);
      if (tcp->cli_sock[i] > tcp->max_fd)
	tcp->max_fd = tcp->cli_sock[i];
    }
}

void		tcps_cli_add(t_tcps *tcp)
{
  int		i;

  i = -1;
  while (++i < 10)
    {
      if (tcp->cli_sock[i] == 0)
	{
	  tcp->cli_sock[i] = tcp->tmp_sock;
	  break;
	}
    }
}

