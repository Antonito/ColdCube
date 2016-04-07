#include "server.hpp"

void		*send_time(void *_data)
{
  t_all		*all = (t_all *)_data;
  int		i;
  char		msg[30];

  i = 6;
  memset(msg, 0, 30);
  sprintf(msg, " ");
  tcps_send_to_all_c(all, msg);
  usleep(200);
  memset(msg, 0, 30);
  sprintf(msg, "Game starting !");
  tcps_send_to_all_c(all, msg);
  usleep(200);
  while (--i > 0)
    {
      memset(msg, 0, 30);
      sprintf(msg, "     %d", i);
      tcps_send_to_all_c(all, msg);
      sleep(1);
    }
      memset(msg, 0, 30);
      sprintf(msg, "/g");
      tcps_send_to_all_c(all, msg);
      return (NULL);
}

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
	  all->tmpIndex = i;
	  break;
	}
    }
  all->nb_actual += 1;
}

void		tcps_check_received(t_all *all, int i)
{
  char		tmp[3] = {0};
  pthread_t	timer;
  static int	game = 0;

  if (all->tcp->buff[0] == '/')
    {
      if (all->tcp->buff[1] == 'a')
	{
	  if (tcp_server_add_pseudo(all, &all->tcp->buff[3], i) == -1)
	    {
	      fprintf(stdout, "[WARN]client already connected, bye\n");
	      fprintf(stdout, ":%s:\n", &all->tcp->buff[3]);
	      write(all->tcp->tmp_sock, "sorry bad pseudo or server full\n", 33);
	      all->connected[all->tmpIndex] = 0;
	      close(all->tcp->cli_sock[all->tmpIndex]);
	      all->tcp->cli_sock[all->tmpIndex] = 0;
	    }
	  else
	    {
	      fprintf(stdout, "[TCP] added :%s:\n", all->pseudo[i]);
	      tmp[0] = (char)i;
	      write(all->tcp->tmp_sock, tmp, 2);
	      usleep(1000);
	      tcps_sync_all(all);
	    }
	}
      if (all->tcp->buff[1] == 'r')
	{
	  fprintf(stdout, "[WARN]client disconnected by /r\n");
	  close(all->tcp->cli_sock[i]);
	  all->tcp->cli_sock[i] = 0;
	  all->nb_actual -= 1;
	  all->connected[i] = 0;
	  memset(all->pseudo[i], 0, 21);
	  tcps_sync_all(all);
	 }
      if (all->tcp->buff[1] == 'k' && !game)
	{
	  game = 1;
	  if (pthread_create(&timer, NULL, send_time, (void *)all) != 0)
	    {
	      fprintf(stderr, "Error: Creating the timer thread\n");
	      return ;
	    }
	}
    }
  else
    tcps_send_to_all(all);
}
