#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

int		main()
{
  struct sockaddr_in server;
  int		sock;
  int		len;
  char		buff[2048];
  int		len2;
  char		buff2[200];

  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
      fprintf(stderr, "socket creation failed\n");
      return (1);
    }
  server.sin_addr.s_addr = inet_addr("127.0.0.1");
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
  if ((len = read(sock, buff, 1024)) == 0)
    {
      fprintf(stderr, "server closed stream :(\n");
      return (1);
    }
  buff[len] = 0;
  fprintf(stdout, "recv : %s\n", buff);
  while ((len2 = read(0, buff2, 199)) > 0)
    {
      buff2[len2] = 0;
      write(sock, buff2, strlen(buff2));
      if ((len = read(sock, buff, 1024)) == 0)
	{
          fprintf(stderr, "server closed stream :(\n");
         return (1);
	}
      buff[len] = 0;
      fprintf(stdout, "recv : %s\n", buff);
    }
  return (0);
}
