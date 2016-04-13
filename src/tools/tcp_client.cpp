#ifdef _WIN32
# include <windows.h>
# include <winsock2.h>
# pragma comment(lib,"ws2_32.lib")
#else
# include <stdlib.h>
# include <stdio.h>
# include <arpa/inet.h>
# include <sys/socket.h>
# include <netdb.h>
# include <unistd.h>
# include <pthread.h>
# include <string.h>
#endif
#include <iostream>
#include <string>
#include "common_structs.hpp"
#include "tools.hpp"

void		host_ip(char *ip, char *purIp)
{
  struct hostent *he;
    struct in_addr **addr_list;
    int i;

    if ( (he = gethostbyname(ip)) == NULL)
    {
        herror("gethostbyname");
        return ;
    }
    addr_list = (struct in_addr **) he->h_addr_list;
    for(i = 0; addr_list[i] != NULL; i++)
    {
        strcpy(purIp , inet_ntoa(*addr_list[i]) );
#ifdef	DEBUG
	fprintf(stdout, "%s was resolved in %s\n", ip, purIp);
#endif
        return ;
    }
    return ;
}

void		tcp_set_pseudo(t_data *data)
{
  int		i;
  char		**pseudo;

  if ((pseudo = my_str_to_wordtab(data->net.tcp.buff, '\n')) == NULL)
    return ;
  i = 0;
  while (pseudo[i] && pseudo[++i] && pseudo[i + 1])
    {
#ifdef	DEBUG
      fprintf(stdout, "#%s#\n", pseudo[i]);
#endif
      memset(data->players[i - 1].pseudo, 0, 21);
      if (strncmp(pseudo[i], "/no", 3) != 0)
	strncpy(data->players[i - 1].pseudo, pseudo[i], strlen(pseudo[i]));
    }
  i = -1;
  while (pseudo[++i] != NULL && i < 10)
    {
      free(pseudo[i]);
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
#ifdef	DEBUG
	  fprintf(stdout, "run thread = 0\n");
#endif
	}
      _data->net.tcp.buff[len] = 0;
      if (strncmp("/s", _data->net.tcp.buff, 2) == 0)
	tcp_set_pseudo(_data);
      else if (strncmp("/h", _data->net.tcp.buff, 2) == 0)
          _data->net.hitmarker = true;
      else if (strncmp("/f", _data->net.tcp.buff, 2) == 0)
      {
          _data->net.shoot[(int)_data->net.tcp.buff[3] - 48] = true;
          printf("received shoot from %d\n", (int)_data->net.tcp.buff[3]);
      }
#ifdef	DEBUG
      else if (strncmp("/g", _data->net.tcp.buff, 2) == 0)
	fprintf(stdout, "We launch the game Here\n");
#else
      else if (strncmp("/g", _data->net.tcp.buff, 2) == 0);
#endif
      else
	{
	  std::string str(_data->net.tcp.buff);
	  _data->tchat.pushBack(str);
	}
#ifdef	DEBUG
      fprintf(stderr, ":%s:", _data->net.tcp.buff);
      fflush(stderr);
#endif
    }
  close(_data->net.tcp.sock);
#ifdef	DEBUG
  fprintf(stdout, "stoped tcp thread\n");
#endif
  return (NULL);
}

int		clientLaunchTcpc(t_data *data)
{
  char		tmp[30] = {0};
#ifdef _WIN32
  WSADATA	wsa;

    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        printf("Failed. Error Code : %d", WSAGetLastError());
        return 1;
    }
#endif
    memset(data->net.purIp, 0, 16);
    host_ip(data->net.ip, data->net.purIp);
  if ((data->net.tcp.sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
      fprintf(stderr, "Socket creation failed\n");
      return (-1);
    }
  data->net.tcp.to_serv.sin_addr.s_addr = inet_addr(data->net.purIp);
  data->net.tcp.to_serv.sin_family = AF_INET;
  data->net.tcp.to_serv.sin_port = htons(data->net.port);
  if (connect(data->net.tcp.sock, (struct sockaddr *)&data->net.tcp.to_serv,
	      sizeof(data->net.tcp.to_serv)) < 0)
    {
      fprintf(stderr, "Cannot connect\n");
      return (-1);
    }
  snprintf(tmp, 24, "/a %s", data->net.pseudo);
  if (write(data->net.tcp.sock, tmp, strlen(tmp)) != (int)strlen(tmp))
    {
      close(data->net.tcp.sock);
      fprintf(stderr, "Error sending pseudo\n");
      return (-1);
    }
  read(data->net.tcp.sock, tmp, 3);
#ifdef	DEBUG
  fprintf(stdout, "the tcp index :%d:\n", (int)tmp[0]);
#endif
  if (tmp[0] == 's')
    {
      close(data->net.tcp.sock);
      return (-1);
    }
  data->net.playerIndexUdp = (int)tmp[0];
  data->net.tcp.run = 1;
  data->net.hitmarker = 0;
  data->net.playerIndexTcp = (int)tmp[0];
  pthread_create(&data->net.tcp.thread, NULL, tcp_thread, (void *)data);
#ifdef _WIN32
  WSACleanup();
#endif
  return (0);
}
