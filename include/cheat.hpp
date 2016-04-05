#ifndef	CHEAT_H_
# define CHEAT_H_

# include "engine/keys.hpp"

typedef struct			s_cheat
{
  struct	s_cheatSelected
  {
    bool	ammo;
    bool	life;
    bool	fly;
    bool	collisions;
  }				selected;
  struct	s_cheatKeys
  {
    e_eventKey	ammo;		// I key
    e_eventKey	life;		// J key
    e_eventKey	fly;		// K key
    e_eventKey	collisions;    	// L key
  }				keys;
}				t_cheat;

extern		t_cheat		cheat;

#endif	/* !CHEAT_H_ */
