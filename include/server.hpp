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
  int			my_addrl;
  int			cli_addrl;
  int			action;
  int			nb_actual;
  struct sockaddr_in	tmp_sock;
  struct sockaddr_in	cli_sock[10];
  char			pseudo[10][21];
  char			cli_buff[8][200];
  char			buff[120];
  struct sockaddr_in	my_addr;
  fd_set		readfds;
  struct timeval	ms;
}			t_udps;

/* src/server/udp/server_udp_msg.c */
void		send_to_all(t_udps *, char *);
void		set_cli_buff(t_udps *, int);

/* src/server/server_pseudo.c */
void		init_zero_pseudo(char [][]);
int		server_add_pseudo(char [][], char *);
int		server_check_pseudo(char [][], char *);
int		server_remve_pseudo_str(char [][], char *);
int		get_pseudo_index(char [][], char *);

/* src/server/udp/main_udp_thread.c */
void		*main_udp_thread(void *data);
void		udp_thread(t_udps *);
void		server_check_msg(t_udps *);

#endif /* !SERVER_H_ */
