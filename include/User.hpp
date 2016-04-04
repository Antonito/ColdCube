#ifndef	USER_H_
# define USER_H_

# include "common_structs.hpp"

class User
{
public:
  User(t_player *player);
  ~User();

  void		getDamage();
  void		shoot();

private:
  t_player	*m_player;
};

#endif	/* !USER_H_ */
