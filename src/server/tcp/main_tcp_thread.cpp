#include "server.hpp"

void		*main_tcp_thread(void *data)
{
  t_all		*all;
  int		i;

  all = (t_all *)data;
  all->tcp = new t_tcps;
  memset(all->tcp, 0, sizeof(t_tcps));
  i = 1;
  if ((all->tcp->main_sock = socket(AF_INET, SOCK_STREAM, 0)) < 1)
    {
      fprintf(stderr, "cannot create socket\n");
      return ((void *)0);
    }
  if (setsockopt(all->tcp->main_sock, SOL_SOCKET, SO_REUSEADDR, (char *)&i, sizeof(i)) != 0)
    {
      fprintf(stderr, "cannot handle multiple client at the same time\n");
      return ((void *)0);
    }
  all->tcp->my_addr.sin_family = AF_INET;
  all->tcp->my_addr.sin_addr.s_addr = INADDR_ANY;
  if ((all->tcp->port = all->port) < 1024)
    return ((void *)0);
  all->tcp->my_addr.sin_port = htons(all->tcp->port);
  if (bind(all->tcp->main_sock, (struct sockaddr *)&all->tcp->my_addr, sizeof(all->tcp->my_addr)) != 0)
    {
      fprintf(stderr, "Cannot bind socket :(\n");
      return ((void *)0);
    }
  if (listen(all->tcp->main_sock, 2) != 0)
    {
      fprintf(stderr, "error pending 2 client at the same time\n");
      return ((void *)0);
    }
  all->tcp->my_addrl = sizeof(all->tcp->my_addr);
  all->tcp->run = 1;
  init_tcps_cli(all->tcp);
  all->nb_actual = 0;
  tcp_thread(all);
  return ((void *)0);
}

void		tcp_thread(t_all *all)
{
  fprintf(stdout, "init server done, waiting for client...\n");
  while (all->tcp->run)
    {
      FD_ZERO(&all->tcp->readfds);
      FD_SET(all->tcp->main_sock, &all->tcp->readfds);
      all->tcp->max_fd = all->tcp->main_sock;
      set_max_fd(all->tcp);
      if ((all->tcp->action = select(all->tcp->max_fd + 1, &all->tcp->readfds, NULL, NULL, NULL)) == -1)
	{
	  fprintf(stderr, "error with select:(\n");
	  return ;
	}
      if (FD_ISSET(all->tcp->main_sock, &all->tcp->readfds))
	{
	  if ((all->tcp->tmp_sock = accept(all->tcp->main_sock,
				      (struct sockaddr *)&all->tcp->my_addr,
				      (socklen_t *)&all->tcp->my_addrl)) == -1)
	    {
	      fprintf(stderr, "error accpet new client\n");
	      continue;
	    }
	  fprintf(stderr, "new client incomming\n");
	  tcps_cli_add(all);
	}
      server_check_msg_tcp(all);
      memset(all->tcp->buff, 0, 210);
    }
  fprintf(stdout, "QUITTING\n");
}

void		server_check_msg_tcp(t_all *all)
{
  int		i;
  int		len;

  i = -1;
  while (++i < 10)
    {
      if (all->connected[i] == 0)
	continue;
      if (FD_ISSET(all->tcp->cli_sock[i], &all->tcp->readfds))
	  {
	    if ((len = read(all->tcp->cli_sock[i], all->tcp->buff, TCP_READ)) == 0)
	      {
		fprintf(stdout, "client disconnected\n");
		close(all->tcp->cli_sock[i]);
		all->tcp->cli_sock[i] = 0;
		all->nb_actual -= 1;
		all->connected[i] = 0;
	      }
	    else
	      {
		fprintf(stdout, "[TCP] MSG\n");
		all->tcp->buff[len] = '\0';
		fprintf(stdout, ":%s:\n", all->tcp->buff);
		tcps_check_received(all, i);
	      }
	  }
    }
}
