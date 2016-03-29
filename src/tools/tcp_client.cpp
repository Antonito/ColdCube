#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <iostream>
#include "common_structs.hpp"

void		*tcp_thread(void *data)
{
  int		len;
  t_data	*_data = (t_data *) data;

  while (_data->net.tcp.run)
    {
      std::clog << "Run = " << _data->net.tcp.run << "\n";
      len = read(_data->net.tcp.sock, _data->net.tcp.buff, 199);
      _data->net.tcp.buff[len] = 0;
      fprintf(stderr, ":%s:", _data->net.tcp.buff);
      fflush(stderr);
    }
  fprintf(stdout, "stoped tcp thread\n");
  return (NULL);
}

int		clientLaunchTcpc(t_data *data)
{
  char		tmp[30];

  if ((data->net.tcp.sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
      fprintf(stderr, "socket creation failed\n");
      return (-1);
    }
  data->net.tcp.to_serv.sin_addr.s_addr = inet_addr(data->net.ip);
  data->net.tcp.to_serv.sin_family = AF_INET;
  data->net.tcp.to_serv.sin_port = htons(data->net.port);
  if (connect(data->net.tcp.sock, (struct sockaddr *)&data->net.tcp.to_serv,
	      sizeof(data->net.tcp.to_serv)) < 0)
    {
      fprintf(stderr, "cannot connect\n");
      return (-1);
    }
  snprintf(tmp, 24, "/a %s", data->net.pseudo);
  if (write(data->net.tcp.sock, tmp, strlen(tmp)) != (int)strlen(tmp))
    {
      fprintf(stderr, "error sending pseudo\n");
      return (-1);
    }
  data->net.tcp.run = 1;
  data->net.playerIndexTcp = atoi(tmp);
  pthread_create(&data->net.tcp.thread, NULL, tcp_thread, (void *)data);
  return (0);
}
