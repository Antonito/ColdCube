#include "User.hpp"
#ifdef	CHEAT
# include "cheat.hpp"
#endif

#include "game.hpp"
#include "tools.hpp"

vec3	GetSoundPos(Camera &cam, vec3 playerPos)
{
  vec4	pos(playerPos.x, playerPos.y, playerPos.z, 1.0);

  pos += vec4(0.4, 0.4, 1.6, 0.0);
  pos = cam.GetModelView() * pos;
  return (vec3(pos.x, pos.y, pos.z));
}

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

void			User::shoot(bool shoot, bool lock)
{
  static bool		isShooting = false;

  if (lock)
    return ;
  if (isShooting)
    {
      if (m_player->weapons[m_player->selected_weapon].shootSound &&
	  bunny_music_get_cursor(m_player->weapons[m_player->selected_weapon].shootSound) <= SOUND_WAIT)
	{
	  isShooting = false;
	  bunny_sound_stop(&m_player->weapons[m_player->selected_weapon].shootSound->sound);
	}
    }
  if (shoot && m_player->weapons[m_player->selected_weapon].loaded < 0)
    {
      if (!isShooting && m_player->weapons[m_player->selected_weapon].shootSound)
	{
	  bunny_sound_play(&m_player->weapons[m_player->selected_weapon].shootSound->sound);
	  isShooting = true;
	  setEvent(&m_player->events, SHOOT, true);
	}
      return ;
    }
  else if (shoot)
    {
      if (m_player->weapons[m_player->selected_weapon].loaded > 0)
	{
	  --m_player->weapons[m_player->selected_weapon].loaded;
	  if (!isShooting && m_player->weapons[m_player->selected_weapon].shootSound)
	    {
	      bunny_sound_play(&m_player->weapons[m_player->selected_weapon].shootSound->sound);
	      isShooting = true;
	      setEvent(&m_player->events, SHOOT, true);
	    }
	  return ;
	}
      else
	{
	  //Play no ammo sound
	  return ;
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

int     User::IsShooted(t_player *p, Score &advTeam, Map &map, t_data *data,
			Camera &cam)
{
  int		i = 0;
  vec4		hit;
  int		damage = 0;
  vec2		dist;
  int		id = m_player->id;
  int		weapon;
  bool		headshot;
  static bool	shooting[10] = {0};

  while (i < 10)
    {
      hit = vec4(0, 0, 0, -1);
      weapon = p[i].selected_weapon;
      headshot = false;
      if (getEvent(p[i].events, SHOOT))
	{
	  vec3	shootPos = normalize(GetSoundPos(cam, p[i].position));
	  if (shooting[i] &&
	      bunny_music_get_cursor(p[i].weapons[p[i].selected_weapon].shootSound) <= SOUND_WAIT)
	    shooting[i] = false;
	  if (i != id && !shooting[i] && p[i].weapons[p[i].selected_weapon].shootSound)
	    {
	      printf("%.2f %.2f %.2f\n", shootPos.x, shootPos.y, shootPos.z);
	      bunny_sound_play(&p[i].weapons[p[i].selected_weapon].shootSound->sound);
	      bunny_sound_position(&p[i].weapons[p[i].selected_weapon].shootSound->sound, (double)shootPos.x, (double)shootPos.y, (double)shootPos.z);
	      shooting[i] = true;
	    }
	}
      if (getEvent(p[i].events, SHOOT) && id % 2 != i % 2)
	{
	  hit = this->IsHit(p + i, map);
	}
      if (hit.w > 0.0)
  	{
	  //	  setShooter(&p[id].events, i);
          char tmp[30];
          memset(tmp, 0, 30);
          sprintf(tmp, "/h %d", i);
          write(data->net.tcp.sock, tmp, strlen(tmp));
  	  dist = vec2(hit.x - m_player->position.x - 0.4,
  		      hit.y - m_player->position.y - 0.4);
  	  if (hit.z > m_player->position.z + 1.4 && (headshot = true))
  	    damage = getDamage(weapon, HEAD_HIT, hit.w);
  	  else if (hit.z < m_player->position.z + 0.8)
  	    damage = getDamage(weapon, LEG_HIT, hit.w);
  	  else if (length(dist) < 0.2)
  	    damage = getDamage(weapon, BODY_HIT, hit.w);
  	  else
  	    damage = getDamage(weapon, ARM_HIT, hit.w);
  	  (m_player->life - damage <= 0) ? (m_player->life = 0) : (m_player->life -= damage);
  	  if (m_player->life <= 0)
	    {
	      advTeam.updateStreakMult(weapon);
	      advTeam.updateScore(weapon, headshot, length(vec3(hit) - p[i].position));
	      setScore(&m_player->events, advTeam.getScore());
              memset(tmp, 0, 30);
              sprintf(tmp, "/t %d %d", i, data->net.playerIndexTcp);
              write(data->net.tcp.sock, tmp, strlen(tmp));
	    }
  	}
      // if (getEvent(p[i].events, SHOOT))
      // 	setEvent(&p[i].events, SHOOT, false);
      i++;
    }
  return (0);
}
