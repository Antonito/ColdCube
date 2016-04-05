#include <sys/time.h>
#include "server.hpp"

void		*main_udp_thread(void *data)
{
  t_all		*all;

  all = (t_all *)data;
  if ((all->udp = malloc(sizeof(t_udps))) == NULL)
    return (NULL);
  if ((all->udp->port = all->port + 1) < 1024)
    return ((void *)0);
  if ((all->udp->main_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
      fprintf(stderr, "Cannot create socket\n");
      return ((void *)0);
    }
  all->udp->my_addr.sin_family = AF_INET;
  printf("The port used = %d\n", all->udp->port);
  all->udp->my_addr.sin_port = htons(all->udp->port);
  all->udp->my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  all->udp->my_addrl = sizeof(all->udp->my_addr);
  if (bind(all->udp->main_sock, (struct sockaddr *)&all->udp->my_addr, all->udp->my_addrl) == -1)
    {
      fprintf(stderr, "Cannot bind on main socket\n");
      return ((void *)0);
    }
  udp_thread(all);
  return ((void *)0);
}

void			udp_thread(t_all *all)
{
  int			len;
  int			go;
  time_t		z1, z2;
  time_t		diffout;
  struct timeval	t1;

  all->udp->action = 1;
  all->udp->cli_addrl = sizeof(all->udp->tmp_sock);
  z1 = time(NULL);
  while (all->udp->action)
  {
    FD_ZERO(&all->udp->readfds);
    FD_SET(all->udp->main_sock, &all->udp->readfds);
    z2 = time(NULL);
    diffout = z2 - z1;
    go = select(all->udp->main_sock + 1, &all->udp->readfds, NULL, NULL, NULL);
    if (go == -1)
      {
	fprintf(stderr, "Error select\n");
      }
    gettimeofday(&t1, NULL);
    if (t1.tv_usec % 15000)
      {
	udps_send_to_all(all);
	gettimeofday(&t1, NULL);
      }
    if (diffout >= 5)
      {
	udps_check_timeout(all);
	z1 = time(NULL);
      }
    if (FD_ISSET(all->udp->main_sock, &all->udp->readfds))
      {
	FD_CLR(all->udp->main_sock, &all->udp->readfds);
	memset(all->udp->buff, 0, 42);
	if ((len = recvfrom(all->udp->main_sock,
			    all->udp->buff, 42, 0,
			    (struct sockaddr *)&all->udp->tmp_sock, (socklen_t *)&all->udp->cli_addrl)) > 0)
	  {
	    server_check_msg_udp(all);
	  }
	else
	  {
	    fprintf(stdout, "Error\n");
	  }
      }
    }
  write(1, "CLOSED\n", 7);
}

void		server_check_msg_udp(t_all *all)
{
  int		i;
  char		tmp[30] = {0};

  if (strncmp(all->udp->buff, "/add", 4) == 0)
    {
      if ((i = tcp_get_pseudo_index(all, &all->udp->buff[5])) == -1)
	{
	  sendto(all->udp->main_sock, "/r", 2, 0,
		(struct sockaddr *)&all->udp->tmp_sock, all->udp->cli_addrl);
	  printf("\nwe cannot find him to pseudo DB\nwith %s\n", &all->udp->buff[5]);
	  return ;
	}
      sprintf(tmp, "%c", (char)i);
      sendto(all->udp->main_sock, tmp, 2, 0,
	     (struct sockaddr *)&all->udp->tmp_sock, all->udp->cli_addrl);
      all->udp->cli_sock[i] = all->udp->tmp_sock;
      all->timeout[i] = 1;
      printf("all functionnal with id = %d\n", i);
    }
  else
    {
      i = all->udp->buff[0];
      set_cli_buff(all, i);
    }
}
