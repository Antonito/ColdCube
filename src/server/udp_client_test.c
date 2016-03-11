/*
** udp_client_test.c for udp client test for server in /home/lokoum/prog
** 
** Made by Lucas Troncy
** Login   <troncy_l@epitech.net>
** 
** Started on  Mon Mar 07 16:48:42 2016 Lucas Troncy
** Last update Fri Mar 11 10:59:59 2016 Lucas Troncy
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <pthread.h>

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
  str[70] = 0;
  return (str);
}

void		*udp_thread(void *data)
{
  char		buff[70];
  struct sockaddr_in tserv;
  int		len;

  tserv = *((struct sockaddr_in *)data);
  len = sizeof(tserv);
  while (run)
    {
      recvfrom(sock, buff, 70, 0, (struct sockaddr *)&tserv, (socklen_t *)&len);
      write(1, buff, 70);
      write(1, "A\n", 2);
    }
}

int		main(int argc, char **argv)
{
  struct sockaddr_in server;
  int lenght;
  char		*buff;
  int		i;
  char		buff2[71];
  pthread_t	tudp;

  if (argc < 2)
    {
      fprintf(stderr, "enter valid ip address\n");
      return (1);
    }
  if ((sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
      fprintf(stderr, "socket creation failed\n");
      return (1);
    }
  server.sin_family = AF_INET;
  server.sin_port = htons(12345);
  server.sin_addr.s_addr = inet_addr(argv[1]);
  lenght = sizeof(server);
  buff = prepare_buffer(buff);
  if (sendto(sock, "/add tato", 9, 0, (struct sockaddr *)&server, lenght) < 1)
    {
      fprintf(stderr, "msg failed\n");
      return (1);
    }
  pthread_create(&tudp, NULL, udp_thread, (void *)&sock);
  while (42)
    {
      if (sendto(sock, buff, 70, 0, (struct sockaddr *)&server, lenght) < 1)
	{
	  fprintf(stderr, "msg failed\n");
	  return (1);
	}
    }
  return (0);
}
