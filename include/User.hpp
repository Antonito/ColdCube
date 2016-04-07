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

  int		getSpeed(void){return (m_speed);};
  void		sprint(int state);
  //  void		getDamage();
  void		shoot();
  int		IsShooted(t_player *p, Score &advTeam, Map &map);
  vec4		IsHit(t_player *p, Map &map);

private:
  t_player	*m_player;
  int		m_speed;
};

#endif	/* !USER_H_ */
