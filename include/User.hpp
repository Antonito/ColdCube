#ifndef	USER_H_
# define USER_H_

# include "common_structs.hpp"

class User
{
public:
  User(t_player *player);
  ~User();

  int		getSpeed(void){return (m_speed);};
  void		sprint(int state);
  void		getDamage();
  void		shoot();

private:
  t_player	*m_player;
  int		m_speed;
};

#endif	/* !USER_H_ */
