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
// # include <GL/glu.h>
// # include <GL/glext.h>
# include <GL/gl.h>
# include <arpa/inet.h>
# include <glm/glm.hpp>
# include <OVR.h>
# include "events.hpp"
# include "Score.hpp"
# include "Tchat.hpp"
# include "engine/keys.hpp"

typedef enum		e_state
  {
    PRESSED,
    UNPRESSED
  }			e_state;

typedef enum		e_bodyHit
  {
    HEAD_HIT,
    BODY_HIT,
    ARM_HIT,
    LEG_HIT
  }			t_bodyHit;

/*
** Network
*/
typedef	struct		s_udpc
{
  int			sock;
  struct sockaddr_in	to_serv;
  int			run;
  int			run_send;
  char			buff[70];
  pthread_t		thread;
  pthread_t		thread_send;
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
  char			purIp[16];
  int			port;
  int			playerIndexTcp;
  int			playerIndexUdp;
  int			isPackage[10];
}			t_network;

/*
** Map
*/
typedef glm::vec3	vector3;

/*
** Weapons
*/
typedef enum		e_weapon
  {
    RIFLE_WEAPON,
    PISTOL_WEAPON,
    KNIFE_WEAPON
  }			t_eweapon;

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
typedef	struct		s_player
{
  int			id; /* Le serveur defini l'id du joueur*/
  char			*pseudo;
  char			life;
  uint32_t		selected_weapon; /* Index du t_weapon */
  t_weapon		weapons[3];
  vector3		position;
  vector3		direction;
  uint32_t		events;
}			t_player;

/*
** Game structure, containing basics infos (such as "is the game running ?")
*/
typedef struct		s_game
{
  Score			Team1;
  Score			Team2;
  bool			running;
  SDL_Surface		*screen;
}			t_game;

typedef struct		s_keys
{
  e_eventKey		forward;
  e_eventKey		backward;
  e_eventKey		left;
  e_eventKey		right;
  e_eventKey		jump;
}			t_keys;

typedef struct		s_config
{
  ovrHmd		oculusHmd;
  bool			oculus;
  int			keyboard;
  unsigned char		musicVolume;
  unsigned char		effectsVolume;
  t_keys		keys;
}			t_config;

typedef	struct		s_data
{
  t_player		players[10];
  t_game		game;
  t_network		net;
  t_config		config;
  SDL_Surface		*screen;
  Tchat			tchat;
  char			sounds[];
}			t_data;

#endif // !COMMON_STRUCTS_H_
