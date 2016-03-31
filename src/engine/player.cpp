#include "game.hpp"
#include "engine/player.hpp"
#include "engine/misc.hpp"

static bool IsColinear(vec3 u, vec3 v);

Player::Player()
{
  m_pos = vec3(0, 0, 0);
  m_rot = vec2(0, 0);
  m_speed = 1.0f;
  m_move = vec2(0, 0);
  m_fall = 0.0f;
  m_map = NULL;
  m_id = 0;
}

Player::Player(vec3 pos, float rot, Map *map, int id)
{
  m_pos = pos;
  m_rot = vec2(rot, 0);
  m_speed = 1.0f;
  m_move = vec2(0, 0);
  m_fall = 0.0f;
  m_map = map;
  m_id = id;
}

Player::~Player()
{
}

void Player::Move(vec2 dir)
{
  m_move += normalize(dir);
  if (m_move.length() > 3.0)
    {
      m_move = normalize(m_move);
      m_move *= 2.5;
    }
}

void Player::Jump()
{
  //  ivec3 p(m_pos);

  m_fall = 10;
  // if (m_pos.z != (int)m_pos.z)
  //   {
  //     if (m_map->IsLoaded(p))
  // 	{
  // 	  if (m_map->GetBlock(m_pos))
  // 	    m_fall = 10;
  // 	}
  //   }
}

void Player::Fall(float time)
{
  ivec3	p(m_pos);

  if (m_pos.z != (int)m_pos.z)
    m_fall -= 0.4;
  else
    {
      if (!m_map->IsLoaded(p) ||
  	  !m_map->GetBlock(m_pos))
	m_fall -= 0.4f;
      else
	{
	  m_fall = 0.0f;
	  m_move *= 0.9;
	}
    }
}


bool	CheckPos(vec3 pos, Map *map)
{
  if (map->GetBlock(pos) ||
      map->GetBlock(pos + vec3(0, 0, 1)) ||
      map->GetBlock(pos + vec3(0, 0, 1.8)))
    return (true);
  return (false);
}

double	RoundPos(double pos, double dir, double size)
{
  if (dir > 0.0)
    return ((int)(pos - dir) + 1 - size / 2);
  return ((int)(pos - dir) + size / 2);
}

vec3 Player::GetCollisionMove(vec3 pos, vec3 move)
{
  bvec3	lock(true, true, true);
  vec3	corner;
  vec3	dist(0, 0, 0);
  vec3	final(0, 0, 0);
  double	temp;

  corner.x = ((move.x < 0) ? -PLAYER_SIZE : PLAYER_SIZE) / 2.0;
  corner.y = ((move.y < 0) ? -PLAYER_SIZE : PLAYER_SIZE) / 2.0;
  corner.z = (move.z < 0) ? 0 : PLAYER_HEIGHT;
  usleep(10000);
  //  pos += corner;
  temp = (pos.x - (int)pos.x) / move.x;

  pos += move;
  if (pos.z < 1)
    pos.z = 1;
  return (pos);
}

void Player::Update(float time)
{
  this->Fall(time);

  vec3 move(m_move * m_speed * time, m_fall * time);
  m_pos = GetCollisionMove(m_pos, move);
  m_move *= 0.93;
  //  printf("\r(%.2f, %.2f, %.2f)             ", m_pos.x, m_pos.y, m_pos.z);
  fflush(stdout);
}

static bool IsColinear(vec3 u, vec3 v)
{
  vec3	k(0, 0, 0);

  if ((u.x == 0.0f && u.y == 0.0f && u.z == 0.0f) ||
      (v.x == 0.0f && v.y == 0.0f && v.z == 0.0f))
    return (true);
  k.x = u.x / v.x;
  k.y = u.y / v.y;
  k.z = u.z / v.z;
  return (k.x == k.y && k.y == k.z);
}

void	Player::SetCam(Camera &cam)
{
      cam.GetPos() = m_pos + vec3(0, 0, 2.5);
  cam.GetRot() = m_rot;
}

void	Player::Draw()
{
  m_model.Draw();
}

void	Player::FillCPlayer(t_player *p, vec3 dir)
{
  p->position = m_pos;
  p->direction = dir;
}
