#ifndef COMMON_STRUCTS_H_
# define COMMON_STRUCTS_H_

# include <stdint.h>
# include <pthread.h>
# include <arpa/inet.h>


/*
** Network
*/

typedef	struct		s_udpc
{
  int			sock;
  struct sockaddr_in	to_serv;
  int			run;
  pthread_t		thread;
}			t_udpc;

typedef	struct		s_tcpc
{
  int			sock;
  struct sockaddr_in	to_serv;
  pthread_t		thread;
  int			run;
}			t_tcpc;

typedef	struct		s_network
{
  t_tcpc       		tcp;
  t_udpc       		udp;
}			t_network;

/*
** Map
*/

typedef	struct		s_map
{

}			t_map;

/*
** Weapons
*/


typedef struct		s_weapon
{
  int			id; /* Id de l'arme */
  int			loaded;
  int			ammo; /* Total de munitions */
  int			power;
  int			sound_fire;
  int			sound_reload;
  int			sound_empty;
}			t_weapon;

/*
** Interface
*/

typedef	struct		s_interface
{
  bool			chat_toggle;
}			t_interface;

/*
** Player_Local eventuellement useless
*/

typedef struct		s_player_local
{
  vector3		move;
}			t_player_local;

typedef	struct		s_player
{
  int			id; /* Le serveur defini l'id du joueur*/
  char			*pseudo;
  char			life;
  int			selected_weapon; /* Index du t_weapon */
  t_weapon		weapons[3];
  vector3		position;
  vector3		direction;
  uint32_t		events;
  t_player_local	local;
}			t_player;

typedef	struct		s_data
{
  t_player		players[10];
  t_map			map;
  t_objects		*obj;
  t_interface		interface;
  char			sounds[];
}			t_data;

#endif /* !COMMON_STRUCTS_H_ */
