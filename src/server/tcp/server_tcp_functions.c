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
  tcps_sync_all(tcp);
}

void		tcps_check_received(t_tcps *tcp, int i)
{
  if (tcp->buff[0] == '/')
    {
      if (tcp->buff[1] == 'a')
	{
	  if (tcp_server_add_pseudo(tcp, &tcp->buff[3]) == -1)
	    {
	      fprintf(stdout, "client rejected\n");
	      write(tcp->tmp_sock, "sorry bad pseudo or server full\n", 33);
	    }
	  else
	    {
	      fprintf(stdout, "pseudo: OK, client added\n");
	    }
	}
      if (tcp->buff[1] == 'r')
	{
	  fprintf(stdout, "client disconnected\n");
	  close(tcp->cli_sock[i]);
	  tcps_remove_sock(tcp, i);
	  tcp_server_remove_pseudo_str(tcp, tcp->pseudo[i]);
	 }
    }
  else
    tcps_send_to_all(tcp);
}

void		tcps_remove_sock(t_tcps *tcp, int index)
{
  tcp->nb_actual -= 1;
  while (index + 1 < 10)
    {
      tcp->cli_sock[index] = tcp->cli_sock[index + 1];
      if (tcp->cli_sock[index + 1] == 0)
	break;
    }
}
