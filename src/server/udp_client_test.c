/*
** udp_client_test.c for udp client test for server in /home/lokoum/prog
** 
** Made by Lucas Troncy
** Login   <troncy_l@epitech.net>
** 
** Started on  Mon Mar 07 16:48:42 2016 Lucas Troncy
** Last update Mon Mar 07 19:47:36 2016 Lucas Troncy
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>

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
  str[70] = 0;
  return (str);
}

int		main()
{
  struct sockaddr_in server;
  int		sock;
  int lenght;
  char		*buff;
  int		i;
  char		buff2[71];

  if ((sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
      fprintf(stderr, "socket creation failed\n");
      return (1);
    }
  server.sin_family = AF_INET;
  server.sin_port = htons(12345);
  server.sin_addr.s_addr = inet_addr("127.0.0.1");
  lenght = sizeof(server);
  buff = prepare_buffer(buff);
  if (sendto(sock, "/add tato", 9, 0, (struct sockaddr *)&server, lenght) < 1)
    {
      fprintf(stderr, "msg failed\n");
      return (1);
    }
  while (42)
    {
      if (recvfrom(sock, buff2, 70, 0, (struct sockaddr *)&server, (socklen_t *)&lenght) < 1)
	{
	  fprintf(stderr, "recv failed :(\n");
	  return (1);
	}
      write(1, buff2, 69);
      if (sendto(sock, buff, 70, 0, (struct sockaddr *)&server, lenght) < 1)
	{
	  fprintf(stderr, "msg failed\n");
	  return (1);
	}
    }
  return (0);
}
