#ifndef	USER_H_
# define USER_H_

# include <GL/glew.h>
# include <SDL2/SDL.h>
# include "common_structs.hpp"
# include "engine/map.hpp"

class User
{
public:
  User(t_player *player);
  ~User();

  void		changeWeapon(e_weapon weapon)
  {
    m_player->selected_weapon = weapon;
  };
  void		changeWeaponWheel(e_movement wheel)
  {
    if (wheel == UP)
      switch (m_player->selected_weapon)
	{
	case (KNIFE_WEAPON):
	  m_player->selected_weapon = PISTOL_WEAPON;
	  break;
	case (PISTOL_WEAPON):
	  m_player->selected_weapon = RIFLE_WEAPON;
	  break;
	case (RIFLE_WEAPON):
	  m_player->selected_weapon = KNIFE_WEAPON;
	  break;
	}
    else
      switch (m_player->selected_weapon)
	{
	case (KNIFE_WEAPON):
	  m_player->selected_weapon = RIFLE_WEAPON;
	  break;
	case (PISTOL_WEAPON):
	  m_player->selected_weapon = KNIFE_WEAPON;
	  break;
	case (RIFLE_WEAPON):
	  m_player->selected_weapon = PISTOL_WEAPON;
	  break;
	}
  };
  int		getSpeed(void){return (m_speed);};
  void		sprint(int state);
  //  void		getDamage();
  void		shoot(bool shoot, bool lock);
  int		IsShooted(t_player *p, Score &advTeam, Map &map, t_data *data,
			  Camera &cam);
  vec4		IsHit(t_player *p, Map &map);

private:
  t_player	*m_player;
  int		m_speed;
};

#endif	/* !USER_H_ */
