#include "User.hpp"
#ifdef	CHEAT
# include "cheat.hpp"
#endif

#include "game.hpp"

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

// void	User::getDamage()
// {
// #ifdef	CHEAT
//   if (cheat.selected.life)
//     m_player->life = 100;
// #endif
//   ;
// }

void	User::shoot(bool shoot)
{
  if (m_player->weapons[m_player->selected_weapon].loaded < 0)
    setEvent(&m_player->events, SHOOT, shoot);
  else
    {
      if (m_player->weapons[m_player->selected_weapon].loaded > 0)
	{
	  //Play shoot sound
	  --m_player->weapons[m_player->selected_weapon].loaded;
	  setEvent(&m_player->events, SHOOT, shoot);
	}
      else
	{
	  //Play no ammo sound
	  ;
	}
    }
}


vec4    User::IsHit(t_player *p, Map &map)
{
  vec3	start = p->position + vec3(0.4, 0.4, 1.6);
  vec3	pos = start;
  vec3	dir = normalize(p->direction) * (GLfloat)0.4;
  vec3	user = m_player->position;

  while (length(user - start) + 2 > length(pos - start))
    {
      if (map.GetBlock(pos))
	return (vec4(pos.x, pos.y, pos.z, -1.0));
      if (pos.x > user.x && pos.x < user.x + 0.8 &&
	  pos.y > user.y && pos.y < user.y + 0.8 &&
	  pos.z > user.z && pos.z < user.z + 1.8)
	return (vec4(pos.x, pos.y, pos.z, length(pos - start)));
      pos += dir;
    }
  return (vec4(pos.x, pos.y, pos.z, -1.0));
}

int     User::IsShooted(t_player *p, Score &advTeam, Map &map)
{
  int		i = 0;
  vec4		hit;
  int		damage = 0;
  vec2		dist;
  int		id = m_player->id;
  int		weapon;
  bool		headshot;

  while (i < 10)
    {
      hit = vec4(0, 0, 0, -1);
      weapon = p[i].selected_weapon;
      headshot = false;
      if (getEvent(p[i].events, SHOOT) && id % 2 != i % 2)
	{
  	hit = this->IsHit(p + i, map);
	}
      if (hit.w > 0.0)
  	{
	  printf("%.2f %.2f %.2f %.2f\n", hit.x, hit.y, hit.z, hit.w);
  	  dist = vec2(hit.x - m_player->position.x - 0.4,
  		      hit.y - m_player->position.y - 0.4);
  	  if (hit.z > m_player->position.z + 1.4 && (headshot = true))
  	    damage = getDamage(weapon, HEAD_HIT);
  	  else if (hit.z < m_player->position.z + 0.8)
  	    damage = getDamage(weapon, LEG_HIT);
  	  else if (length(dist) < 0.2)
  	    damage = getDamage(weapon, BODY_HIT);
  	  else
  	    damage = getDamage(weapon, ARM_HIT);
  	  m_player->life -= damage;
	  printf("LIFE %d\n", m_player->life);
  	  if (m_player->life <= 0)
  	    advTeam.updateScore(weapon, headshot, length(vec3(hit) - p[i].position));
  	}
      if (getEvent(p[i].events, SHOOT))
  	setEvent(&p[i].events, SHOOT, false);
      i++;
    }
  return (0);
}
