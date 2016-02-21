#ifndef SERVER_H_
# define SERVER_H_

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <pthread.h>
# include <arpa/inet.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <sys/select.h>
# include <netinet/in.h>
# include <sys/time.h>

/*
** s_tcps pour le server, il gere le tchate est la sync des clients
** avec le lancement des games
*/

typedef struct		s_tcps
{
  int			main_sock;
  int			my_addrl;
  int			cli_addrl;
  int			action;
  int			run;
  int			nb_actual;
  int			tmp_sock;
  int			cli_sock[10];
  int			max_fd;
  int			port;
  char			pseudo[10][21];
  char			buff[70];
  struct sockaddr_in	my_addr;
  fd_set		readfds;
}			t_tcps;

/*
** s_udps pour le server, il gere toutes les postions des clients
*/

typedef struct		s_udps
{
  int			main_sock;
  int			my_addrl;
  int			cli_addrl;
  int			action;
  int			run;
  int			nb_actual;
  struct sockaddr_in	tmp_sock;
  struct sockaddr_in	cli_sock[10];
  char			pseudo[10][21];
  char			cli_buff[8][200];
  char			buff[70];
  struct sockaddr_in	my_addr;
  fd_set		readfds;
  struct timeval	ms;
}			t_udps;

/* src/server/udp/server_udp_msg.c */
void		udps_send_to_all(t_udps *);
void		set_cli_buff(t_udps *, int);

/* src/server/server_pseudo.c */
void		init_zero_pseudo(t_udps *);
int		server_add_pseudo(t_udps *, char *);
int		server_check_pseudo(t_udps *, char *);
int		server_remve_pseudo_str(t_udps *, char *);
int		get_pseudo_index(t_udps *, char *);

/* src/server/udp/main_udp_thread.c */
void		*main_udp_thread(void *);
void		udp_thread(t_udps *);
void		server_check_msg_udp(t_udps *);

/* src/server/main.c */
int		main(int argc, char **argv);
void		cmd_loop(void);

/* src/server/tcp/main_tcp_thread.c */
void		*main_tcp_thread(void *);
void		tcp_thread(t_tcps *);
void		server_check_msg_tcp(t_tcps *);

/* src/server/tcp/server_tcp_functions.c */
void		init_tcps_cli(t_tcps *);
void		set_max_fd(t_tcps *);
void		tcps_cli_add(t_tcps *);

/* src/server/tcp/server_tcp_msg.c */
void		tcps_send_to_all(t_tcps *);

#endif /* !SERVER_H_ */
