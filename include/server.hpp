#ifndef SERVER_H_
# define SERVER_H_

# include <arpa/inet.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <sys/select.h>
# include <netinet/in.h>
# include <sys/time.h>
# include "tekdoom.h"

/*
** s_socket pour le server, il gere le tchate est la sync des clients
** avec le lancement des games
*/

typedef struct	s_socket
{
  int		main_sock;
  int		tmp_sock;
  int		cli_sock[MAX_CLIENTS];
  int		cli_nb;
  int		action;
  char		*port;
  char		**pseudo;
  bool		status[8];
  unsigned char	*seed;
  pthread_t	thread;
}		t_socket;

/*
** s_udp pour le server, il gere toutes les postions des clients
*/

typedef struct		s_udps
{
  int			main_sock;
  struct sockaddr_in	tmp_sock;
  int			my_addrl;
  int			cli_addrl;
  int			action;
  struct sockaddr_in	cli_sock[MAX_CLIENTS];
  char			**pseudo;
  char			cli_buff[8][109];
  char			buff[120];
  struct sockaddr_in	my_addr;
  fd_set		readfds;
  struct timeval	ms;
}			t_udps;

#endif /* !SERVER_H_ */
