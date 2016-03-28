#include "server.hpp"

void		*main_udp_thread(void *data)
{
  t_udps	udp;

  udp_init_zero_pseudo(&udp);
  udp.nb_actual = 0;
  if ((udp.main_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
      fprintf(stderr, "cannot create socket \n");
      return ((void *)0);
    }
  udp.my_addr.sin_family = AF_INET;
  printf("the port used = %d\n", (int)data);
  udp.my_addr.sin_port = htons((int)data);
  udp.my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  udp.my_addrl = sizeof(udp.my_addr);
  if (bind(udp.main_sock, (struct sockaddr *)&udp.my_addr, udp.my_addrl) == -1)
    {
      fprintf(stderr, "cannot bind on main socket :(\n");
      return ((void *)0);
    }
  udp_thread(&udp);
  return ((void *)0);
}

void		udp_thread(t_udps *udp)
{
  int		len;
  int		go;

  udp->action = 1;
  udp->cli_addrl = sizeof(udp->tmp_sock);
  udp->ms.tv_sec = 0;
  udp->ms.tv_usec = 0;
  while (udp->action)
  {
    if (udp->ms.tv_usec == 0)
      {
	udp->ms.tv_sec = 0;
	udp->ms.tv_usec = 1500;
      }
    FD_ZERO(&udp->readfds);
    FD_SET(udp->main_sock, &udp->readfds);
    go = select(udp->main_sock + 1, &udp->readfds, NULL, NULL, &udp->ms);
    if (go == -1)
      {
	fprintf(stderr, "error select :(\n");
      }
    else if (go == 0 && udp->nb_actual > 0)
      {
	udps_send_to_all(udp);
	continue;
      }
    if (FD_ISSET(udp->main_sock, &udp->readfds))
      {
	FD_CLR(udp->main_sock, &udp->readfds);
	if ((len = recvfrom(udp->main_sock,
			udp->buff, 70, 0,
			(struct sockaddr *)&udp->tmp_sock, (socklen_t *)&udp->cli_addrl)) > 0)
	  {
	    server_check_msg_udp(udp);
	  }
	else
	  {
	    fprintf(stdout, "nop\n");
	  }
      }
    }
  write(1, "CLOSED\n", 7);
}

void		server_check_msg_udp(t_udps *udp)
{
  int		i;
  char		tmp[2];

  if (strncmp(udp->buff, "/add", 4) == 0)
    {
      if (udp_server_add_pseudo(udp, &udp->buff[5]) == -1)
	return ;
      if ((i = udp_get_pseudo_index(udp, &udp->buff[5])) == -1)
	return ;
      udp->cli_sock[i] = udp->tmp_sock;
      sprintf(tmp, "%d", udp->nb_actual);
      udp->nb_actual += 1;
      sendto(udp->main_sock, tmp, 1, 0, (struct sockaddr *)&udp->tmp_sock, udp->cli_addrl);
    }
  else
    {
      i = udp->buff[0];
      set_cli_buff(udp, i);
    }
}
