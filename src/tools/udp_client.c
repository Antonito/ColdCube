/*
** udp_client_test.c for udp client test for server in /home/lokoum/prog
** 
** Made by Lucas Troncy
** Login   <troncy_l@epitech.net>
** 
** Started on  Mon Mar 07 16:48:42 2016 Lucas Troncy
** Last update Mon Mar 28 16:43:33 2016 Lucas Troncy
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <pthread.h>
#include "common_struct.h"

int		run = 42;
int		sock;

char		*prepare_buffer(char *str)
{
  int		i;

  if ((str = malloc(sizeof(char) * (70 + 1))) == NULL)
    {
      fprintf(stderr, "malloc failed LAMO\n");
      exit(1);
    }
  i = -1;
  while (++i < 70)
    {
      str[i] = 50;
    }
  str[0] = 3;
  str[1] = 0;
  str[70] = 0;
  return (str);
}

void		*udp_thread(void *data)
{
  int		len;
  t_data	*_data;

  _data = (t_data *) data;
  len = sizeof(tserv);
  while (_data->net->udp->run)
    {
      recvfrom(_data->net->udp->sock, _data->net->udp->buff, 70, 0,
	       (struct sockaddr *)&_data->net->tcp->to_serv, (socklen_t *)&len);
    }
}

int		clientLaunchUdpc(t_data *data)
{
  int		len;
  char		tmp[30];

  if ((data->net->udp->sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
      fprintf(stderr, "socket creation failed\n");
      return (-1);
    }
  data->net->udp->to_serv.sin_family = AF_INET;
  data->net->udp->to_serv.sin_port = htons(data->net->port + 1);
  data->net->udp->to_serv.sin_addr.s_addr = inet_addr(data->net->ip);
  len = sizeof(data->net->udp->to_serv);
  snprintf(tmp, 24, "/add %s", data->net->pseudo);
  if (sendto(sock, tmp, strlen(tmp), 0,
	     (struct sockaddr *)&data->net->udp->to_serv, len) < 1)
    {
      fprintf(stderr, "error sending pseudo (udp)\n");
      return (-1);
    }
  recvfrom(_data->net->udp->sock, tmp, 10, 0,
	  (struct sockaddr *)&_data->net->tcp->to_serv, (socklen_t *)&len);
  _data->net->playerIndexUdp = atoi(tmp);
  pthread_create(&tudp, NULL, udp_thread, (void *)&sock);
  return (0);
}
