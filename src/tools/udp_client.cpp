/*
** udp_client_test.c for udp client test for server in /home/lokoum/prog
**
** Made by Lucas Troncy
** Login   <troncy_l@epitech.net>
**
** Started on  Mon Mar 07 16:48:42 2016 Lucas Troncy
// Last update Wed Mar 30 08:01:32 2016 Antoine Baché
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <pthread.h>
#include "tools.hpp"
#include "common_structs.hpp"

void		*udp_thread(void *data)
{
  int		len;
  t_data	*_data;

  _data = (t_data *) data;
  len = sizeof(_data->net.udp.to_serv);
  while (_data->net.udp.run)
    {
      if (recvfrom(_data->net.udp.sock, _data->net.udp.buff, 42, 0,
	       (struct sockaddr *)&_data->net.tcp.to_serv, (socklen_t *)&len) == 42)
	{
	  if (!checkPacket(_data->net.udp.buff))
	    {
	      fprintf(stderr, "wrong package output");
	      fflush(stderr);
	    }
	  readUdpPacket(_data);
	}
    }
  close(_data->net.udp.sock);
  return (NULL);
}

int		clientLaunchUdpc(t_data *data)
{
  int		len;
  char		tmp[30];

  if ((data->net.udp.sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
      fprintf(stderr, "socket creation failed\n");
      return (-1);
    }
  data->net.udp.to_serv.sin_family = AF_INET;
  data->net.udp.to_serv.sin_port = htons(data->net.port + 1);
  data->net.udp.to_serv.sin_addr.s_addr = inet_addr(data->net.ip);
  len = sizeof(data->net.udp.to_serv);
  snprintf(tmp, 24, "/add %s", data->net.pseudo);
  if (sendto(data->net.udp.sock, tmp, strlen(tmp), 0,
	     (struct sockaddr *)&data->net.udp.to_serv, len) < 1)
    {
      fprintf(stderr, "error sending pseudo (udp)\n");
      return (-1);
    }
  recvfrom(data->net.udp.sock, tmp, 10, 0,
	  (struct sockaddr *)&data->net.tcp.to_serv, (socklen_t *)&len);
  data->net.playerIndexUdp = atoi(tmp);
  printf("Id = %d\n", data->net.playerIndexUdp);
  data->net.udp.run = 1;
  pthread_create(&data->net.udp.thread, NULL, udp_thread, (void *)data);
  return (0);
}
