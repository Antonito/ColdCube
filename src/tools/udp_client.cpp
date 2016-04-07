#ifdef _WIN32
# include <windows.h>
# include <winsock2.h>
# pragma comment(lib,"ws2_32.lib")
#else
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <sys/types.h>
# include <pthread.h>
# include <sys/time.h>
# include <iostream>
#endif
#include "tools.hpp"
#include "common_structs.hpp"

void			*udp_send_thread(void *data)
{
  t_data		*_data;
  long			timestamp;
  long			last_packet;
  struct timeval	t1;
  struct timeval	t2;

  _data = (t_data *)data;
  gettimeofday(&t1, NULL);
  last_packet = t1.tv_sec * 1000 + t1.tv_usec / 1000;
  while (_data->net.udp.run_send)
    {
      gettimeofday(&t2, NULL);
      timestamp = t2.tv_sec * 1000 + t2.tv_usec / 1000;
      if ((timestamp - last_packet) >= 16)
	{
	  createUdpPacket(_data, &_data->players[_data->net.playerIndexUdp]);
	  gettimeofday(&t1, NULL);
	  last_packet = t1.tv_sec * 1000 + t1.tv_usec / 1000;
	}
      usleep(200);
    }
  return (NULL);
}

void			*udp_thread(void *data)
{
  int			len;
  t_data		*_data;

  _data = (t_data *)data;
  len = sizeof(_data->net.udp.to_serv);
  while (_data->net.udp.run)
    {
      if (recvfrom(_data->net.udp.sock, _data->net.udp.buff, 42, 0,
		   (struct sockaddr *)&_data->net.tcp.to_serv, (socklen_t *)&len) == 42)
	{
	  if (!checkPacket(_data->net.udp.buff))
	    {
	      fprintf(stderr, "Wrong package output");
	      fflush(stderr);
	    }
	  readUdpPacket(_data);
	}
      usleep(200);
    }
  close(_data->net.udp.sock);
  return (NULL);
}

int			clientLaunchUdpc(t_data *data)
{
  int			len;
  char			tmp[30] = {0};
  struct timeval	tv;
#if _WIN32
  WSADATA		wsa;

  if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        printf("Failed. Error Code : %d",WSAGetLastError());
        exit(EXIT_FAILURE);
    }
#endif
  if ((data->net.udp.sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
      fprintf(stderr, "Socket creation failed\n");
      return (-1);
    }
  data->net.udp.to_serv.sin_family = AF_INET;
  data->net.udp.to_serv.sin_port = htons(data->net.port + 1);
  data->net.udp.to_serv.sin_addr.s_addr = inet_addr(data->net.purIp);
  len = sizeof(data->net.udp.to_serv);
  tv.tv_sec = 2;
  tv.tv_usec = 0;
  if (setsockopt(data->net.udp.sock, SOL_SOCKET, SO_RCVTIMEO,&tv,sizeof(tv)) < 0)
    return (-1);
  snprintf(tmp, 24, "/add %s", data->net.pseudo);
  if (sendto(data->net.udp.sock, tmp, strlen(tmp), 0,
	     (struct sockaddr *)&data->net.udp.to_serv, len) < 1)
    {
      close(data->net.udp.sock);
      fprintf(stderr, "Error sending pseudo (udp)\n");
      return (-1);
    }
#ifdef	DEBUG
  printf("before recv ID\n");
#endif
  tmp[0] = -1;
  recvfrom(data->net.udp.sock, tmp, 3, 0,
	  (struct sockaddr *)&data->net.udp.to_serv, (socklen_t *)&len);
  if (tmp[0] < 0 || tmp[0] > 9)
    {
      fprintf(stderr, "Receving Id timedOut or wrong Id = %d\n", (int)tmp[0]);
      close(data->net.udp.sock);
      return (-1);
    }
#ifdef	DEBUG
  printf("After recv ID\n");
#endif
  data->net.playerIndexUdp = (int)tmp[0];
#ifdef	DEBUG
  printf("Id = %d\n", data->net.playerIndexUdp);
#endif
  data->net.udp.run = 1;
  data->net.udp.run_send = 1;
#ifdef	DEBUG
  printf("creating thread UDP\n");
#endif
  memset(data->net.isPackage, 0, sizeof(int) * 10);
  pthread_create(&data->net.udp.thread, NULL, udp_thread, (void *)data);
  pthread_create(&data->net.udp.thread_send, NULL, udp_send_thread, (void *)data);
#ifdef	DEBUG
  printf("thread created\n");
#endif
#if _WIN32
  WSACleanup();
#endif
  return (0);
}
