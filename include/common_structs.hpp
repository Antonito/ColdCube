#ifndef COMMON_STRUCTS_H_
# define COMMON_STRUCTS_H_

# if _WIN32
#  include <windows.h>
#  include <GL/glew.h>
# endif

# include <stdbool.h>
# include <stdint.h>
# include <pthread.h>
# include <SDL/SDL.h>
# include <GL/glu.h>
# include <GL/glext.h>
# include <GL/gl.h>
# include <arpa/inet.h>

/*
** Network
*/

typedef	struct		s_udpc
{
  int			sock;
  struct sockaddr_in	to_serv;
  int			run;
  char			buff[70];
  pthread_t		thread;
}			t_udpc;

typedef	struct		s_tcpc
{
  int			sock;
  struct sockaddr_in	to_serv;
  char			buff[140];
  pthread_t		thread;
  int			run;
}			t_tcpc;

typedef	struct		s_network
{
  t_tcpc		tcp;
  t_udpc		udp;
  char			*ip;
  char			*pseudo;
  int			port;
  int			playerIndexTcp;
  int			playerIndexUdp;
}			t_network;

/*
** Objects
*/

typedef struct		s_objects
{
  struct s_objects	*next;
  struct s_objects	*prev;
}			t_objects;

/*
** Map
*/

typedef	struct		vec3
{
  double		x;
  double		y;
  double		z;
}			vector3;

typedef	struct		s_cube
{
  unsigned int		r : 2;
  unsigned int		g : 2;
  unsigned int		b : 2;
  unsigned int		a : 2;
}			t_cube ;

typedef struct		s_block
{
  s_cube		cube;
  unsigned char		byte;
}			t_block;

typedef	struct		s_chunk
{
  t_block		block[16 * 16 * 16];
}			t_chunk;

typedef	struct		s_map
{
  t_chunk		chunks[256];
  vector3		spawn[16];
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
  vector3      		move;
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

/*
** Game structure, containing basics infos (such as "is the game running ?")
*/

typedef struct		s_game
{
  bool			running;
  SDL_Surface		*screen;
}			t_game;

typedef	struct		s_data
{
  t_player		players[10];
  t_map			map;
  t_objects		*obj;
  t_interface		interface;
  t_game		game;
  t_network		net;
  char			sounds[];
}			t_data;

#endif /* !COMMON_STRUCTS_H_ */
