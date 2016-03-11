#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

int		run = 42;

void		*tcp_thread(void *data)
{
  char		buff[200];
  int		len;
  int		tsock = *((int *) data);

  printf("socked WHILE is %d\n", tsock);
  while (run)
    {
      len = read(tsock, buff, 199);
      buff[len] = 0;
      fprintf(stdout, "%s\n", buff);
    }
}

int		main(int argc, char **argv)
{
  struct sockaddr_in server;
  int		sock;
  int		len2;
  char		buff2[200];
  pthread_t	ttcp;

  if (argc < 2)
    {
      fprintf(stderr, "please enter an ip address\n");
	return (1);
    }
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
      fprintf(stderr, "socket creation failed\n");
      return (1);
    }
  server.sin_addr.s_addr = inet_addr(argv[1]);
  server.sin_family = AF_INET;
  server.sin_port = htons(12345);
  if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
      fprintf(stderr, "cannot connect\n");
      return (1);
    }
  if (write(sock, "/a toto", 7) != 7)
    {
      fprintf(stderr, "error sending MSG\n");
      return (1);
    }
  pthread_create(&ttcp, NULL, tcp_thread, (void *)&sock);
  while ((len2 = read(0, buff2, 199)) > 0)
    {
      buff2[len2] = 0;
      write(sock, buff2, strlen(buff2));
    }
  run = 0;
  return (0);
}
