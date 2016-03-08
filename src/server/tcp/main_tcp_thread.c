#include "server.hpp"

void		*main_tcp_thread(void *data)
{
  t_tcps	tcp;
  int		i;

  i = 1;
  if ((tcp.main_sock = socket(AF_INET, SOCK_STREAM, 0)) < 1)
    {
      fprintf(stderr, "cannot create socket\n");
      return ((void *)0);
    }
  if (setsockopt(tcp.main_sock, SOL_SOCKET, SO_REUSEADDR, (char *)&i, sizeof(i)) != 0)
    {
      fprintf(stderr, "cannot handle multiple client at the same time\n");
      return ((void *)0);
    }
  tcp.my_addr.sin_family = AF_INET;
  tcp.my_addr.sin_addr.s_addr = INADDR_ANY;
  tcp.port = (int)data;
  tcp.my_addr.sin_port = htons(tcp.port);
  if (bind(tcp.main_sock, (struct sockaddr *)&tcp.my_addr, sizeof(tcp.my_addr)) != 0)
    {
      fprintf(stderr, "Cannot bind socket :(\n");
      return ((void *)0);
    }
  if (listen(tcp.main_sock, 2) != 0)
    {
      fprintf(stderr, "error pending 2 client at the same time\n");
      return ((void *)0);
    }
  tcp.my_addrl = sizeof(tcp.my_addr);
  tcp.run = 1;
  init_tcps_cli(&tcp);
  tcp.nb_actual = 0;
  tcp_thread(&tcp);
  return ((void *)0);
}

void		tcp_thread(t_tcps *tcp)
{
  fprintf(stdin, "init server done, waiting for client...\n");
  while (tcp->run)
    {
      FD_ZERO(&tcp->readfds);
      FD_SET(tcp->main_sock, &tcp->readfds);
      tcp->max_fd = tcp->main_sock;
      set_max_fd(tcp);
      if ((tcp->action = select(tcp->max_fd + 1, &tcp->readfds, NULL, NULL, NULL)) == -1)
	{
	  fprintf(stderr, "error with select:(\n");
	  return ;
	}
      if (FD_ISSET(tcp->main_sock, &tcp->readfds))
	{
	  if ((tcp->tmp_sock = accept(tcp->main_sock,
				      (struct sockaddr *)&tcp->my_addr,
				      (socklen_t *)&tcp->my_addrl)) == -1)
	    {
	      fprintf(stderr, "cannot accpet new client\n");
	    }
	  fprintf(stderr, "new client connected\n");
	  tcp->nb_actual += 1;
	  tcps_cli_add(tcp);
	}
      server_check_msg_tcp(tcp);
    }
}

void		server_check_msg_tcp(t_tcps *tcp)
{
  int		i;
  int		len;

  i = -1;
  while (++i < tcp->nb_actual)
    {
      if (FD_ISSET(tcp->cli_sock[i], &tcp->readfds))
	  {
	    if ((len = read(tcp->cli_sock[i], tcp->buff, TCP_READ)) == 0)
	      {
		fprintf(stdout, "client disconnected\n");
		close(tcp->cli_sock[i]);
		tcps_remove_sock(tcp, i);
		tcp_server_remove_pseudo_str(tcp, tcp->pseudo[i]);
	      }
	    else
	      {
		/*we got a MSG here */
		fprintf(stdout, "we got a massage here\n");
		tcp->buff[len] = '\0';
		tcps_check_received(tcp);
	      }
	  }
    }
}
