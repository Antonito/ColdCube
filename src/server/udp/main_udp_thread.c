#include "server.h"

void		*main_udp_thread(void *data)
{
  t_udps	*udp;

  init_zero_pseudo(udp->pseudo);
  udp->nb_actual = 0;
  if ((udp->main_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    fprintf(stderr, "cannot create socket \n");
  udp->my_addr.sin_family = AF_INET;
  udp->my_addr.sin_port = htons(*(int)data);
  udp->my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  udp->my_addrl = sizeof(udp->my_addr);
  if (bind(udp->main_sock, (struct sockaddr*)&udp->my_addr, udp->my_addrl) == -1)
    fprintf(stderr, "cannot bind on main socket :(\n");
  udp_thread(udp);
  return ((void *)0);
}

void		udp_thread(t_udps *udp)
{
  int		len;
  int		go

  printf("ON main loop\n");
  udp->action = 1;
  udp->cli_addrl = sizeof(udp->tmp_sock);
  while (udp->action)
  {
    udp->ms.tv_sec = 0;
    udp->ms.tv_usec = 1500;
    FD_ZERO(&udp->readfds);
    FD_SET(udp->main_sock, &udp->readfds);
    go = select(2, &udp->main_sock, NULL, NULL, &udp->ms);
    if (go == -1)
      {
	fprintf(stderr, "error select :(\n");
      }
    if (FD_ISSET(udp->main_sock, &udp->readfds))
      {
	fprintf(stdin, "message incoming :)\n");
	/*handle this : add client if not already connected, if connected, transfer his position to others */
	server_check_msg_udp(udp);
      }
    if ((len = recvfrom(udp->main_sock,
			upd->buff, 120, 0,
			(struct sockaddr *)&udp->tmp_addr, &udp->cli_addrl) == -1)
	{
	  fprintf(stderr, "To catch, a client disconnect/left\n");
	}
}

void		server_check_msg_udp(t_udps *udp)
{
  int		i;

  if ((len = recvfrom(udp->main_sock,
			upd->buff, 120, 0,
			(struct sockaddr *)&udp->tmp_addr, &udp->cli_addrl) == -1)
	{
	  fprintf(stderr, "To catch, a client disconnect/left\n");
	  /*server_remove_pseudo  + udp->n_actual -= 1*/
	}
  if (strncmp(udp->buff, "/add", 4) == 0)
    {
      server_add_pseudo(udp->pseudo, &udp->buff[5]);
      udp->cli_sock[udp->nb_actual] = udp->tmp_sock;
      udp->nb_actual += 1;
    }
  else
    {
      /*handle UDP tranfser */
      i = get_pseudo_index(udp->pseudo, udp->buff); /* buff is the whole message, need a parse */    
      set_cli_buff(udp, i);
    }
}
