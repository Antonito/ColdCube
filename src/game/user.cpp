#include "User.hpp"
#ifdef	CHEAT
# include "cheat.hpp"
#endif

User::User(t_player *player)
{
  m_player = player;
  m_speed = 1;
  m_player->life = 100;
}

User::~User()
{
}

void	User::sprint(int state)
{
  switch(state)
    {
    case(PRESSED):
      m_speed = 2;;
    case(UNPRESSED):
      m_speed = 1;
    }
}

void	User::getDamage()
{
#ifdef	CHEAT
  if (cheat.selected.life)
    m_player->life = 100;
#endif
  ;
}

void	User::shoot()
{
  ;
}
