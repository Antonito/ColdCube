#ifdef _WIN32
# include <windows.h>
# include <winsock2.h>
# pragma comment(lib,"ws2_32.lib")
#else
# include <stdlib.h>
# include <stdio.h>
# include <arpa/inet.h>
# include <sys/socket.h>
# include <unistd.h>
# include <pthread.h>
# include <string.h>
#endif
#include <iostream>
#include "common_structs.hpp"
#include "tools.hpp"

void		tcp_set_pseudo(t_data *data)
{
  int		i;
  char		**pseudo;

  i = -1;
  if ((pseudo = my_str_to_wordtab(data->net.tcp.buff, '\n')) == NULL)
    return ;
  write(1, "OOOOOOOOOO\n", 11);
  printf("DATA %p\n", data);
  while (pseudo[++i + 1] != NULL)
    {
      fprintf(stdout, "#%s#\n", pseudo[i + 1]);
      //strncpy(data->players[i].pseudo, pseudo[i + 1], strlen(pseudo[i + 1]));
      //data->players[i].pseudo[strlen(pseudo[i + 1])] = 0;
    }
}

void		*tcp_thread(void *data)
{
  int		len;
  t_data	*_data = (t_data *) data;

  while (_data->net.tcp.run)
    {
      if ((len = read(_data->net.tcp.sock, _data->net.tcp.buff, 199)) == 0)
	{
	  _data->net.tcp.run = 0;
	  fprintf(stdout, "run thread = 0\n");
	}
      _data->net.tcp.buff[len] = 0;
      if (strncmp("/s", _data->net.tcp.buff, 2) == 0)
	tcp_set_pseudo(_data);
      fprintf(stderr, ":%s:", _data->net.tcp.buff);
      fflush(stderr);
      usleep(3000);
    }
  close(_data->net.tcp.sock);
  fprintf(stdout, "stoped tcp thread\n");
  return (NULL);
}

int		clientLaunchTcpc(t_data *data)
{
  char		tmp[30] = {0};
#ifdef _WIN32
  WSADATA	wsa;

    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        printf("Failed. Error Code : %d",WSAGetLastError());
        return 1;
    }
#endif
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
      close(data->net.tcp.sock);
      fprintf(stderr, "error sending pseudo\n");
      return (-1);
    }
  read(data->net.tcp.sock, tmp, 29);
  fprintf(stdout, ":%s:\n", tmp);
  if (tmp[0] == 's')
    {
      close(data->net.tcp.sock);
      return (-1);
    }
  data->net.tcp.run = 1;
  data->net.playerIndexTcp = atoi(tmp);
  pthread_create(&data->net.tcp.thread, NULL, tcp_thread, (void *)data);
#ifdef _WIN32
  WSACleanup();
#endif
  return (0);
}
