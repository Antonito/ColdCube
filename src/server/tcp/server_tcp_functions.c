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

void		tcps_cli_add(t_all *all)
{
  int		i;

  i = -1;
  while (++i < 10)
    {
      if (all->connected[i] == 0)
	{
	  all->tcp->cli_sock[i] = all->tcp->tmp_sock;
	  all->connected[i] = 1;
	  all->timeout[i] = 1;
	  write(all->tcp->tmp_sock, "ok", 2);
	  fprintf(stdout, "tcp client tmp_sock added on index = %d\n", i);
	  break;
	}
    }
  all->nb_actual += 1;
}

void		tcps_check_received(t_all *all, int i)
{
  if (all->tcp->buff[0] == '/')
    {
      if (all->tcp->buff[1] == 'a')
	{
	  if (tcp_server_add_pseudo(all, &all->tcp->buff[3], i) == -1)
	    {
	      fprintf(stdout, "client rejected\n");
	      fprintf(stdout, ":%s:\n", &all->tcp->buff[3]);
	      write(all->tcp->tmp_sock, "sorry bad pseudo or server full\n", 33);
	    }
	  else
	    {
	      all->connected[i] = 1;
	      fprintf(stdout, ":%s:\n", &all->tcp->buff[3]);
	      fprintf(stdout, "pseudo: OK, client added, synced\n");
	      write(all->tcp->tmp_sock, "ok", 2);
	      tcps_sync_all(all);
	    }
	}
      if (all->tcp->buff[1] == 'r')
	{
	  fprintf(stdout, "client disconnected by /r\n");
	  close(all->tcp->cli_sock[i]);
	  all->tcp->cli_sock[i] = 0;
	  all->nb_actual -= 1;
	  all->connected[i] = 0;
	 }
    }
  else
    tcps_send_to_all(all);
}
