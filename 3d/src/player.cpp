#include "player.hpp"
#include "misc.hpp"

static bool IsColinear(vec3 u, vec3 v)

Player::Player()
{
  m_pos = vec3(0, 0, 0);
  m_rot = vec2(0, 0);
  m_speed = 1.0f;
  m_move = vec2(0, 0);
  m_fall = 0.0f;
}

Player::Player(vec3 pos, float rot)
{
  m_pos = pos;
  m_rot = vec2(rot, 0);
  m_speed = 1.0f;
  m_move = vec2(0, 0);
  m_fall = 0.0f;
}

Player::~Player()
{
}

void Player::Move(vec2 dir)
{
  m_move += dir;
  m_move = normalize(m_move);
  if ((m_move - dir).length() < 0.1)
    m_move = dir;
}

void Player::Jump()
{
  int	x, y, z;

  if (m_pos.z != (int)m_pos.z)
    {
      x = (int)m_pos.x;
      y = (int)m_pos.y;
      z = (int)m_pos.z;
      if (m_chunks[(x >> 5) + ((y >> 5) << 5)].IsLoaded())
	{
	  if (m_chunks[(x >> 5) + ((y >> 5) << 5)].GetBlock(x, y ,z))
	    m_fall = JUMP_SPEED;
	}
    }
}

void Player::Fall(float time)
{
  int	x, y, z;

  if (m_pos.z != (int)m_pos.z)
    m_fall -= FALL_SPEED * time;
  else
    {
      x = (int)m_pos.x;
      y = (int)m_pos.y;
      z = (int)m_pos.z;
      if (!m_chunks[(x >> 5) + ((y >> 5) << 5)].IsLoaded() ||
	  !m_chunks[(x >> 5) + ((y >> 5) << 5)].GetBlock(x, y ,z))
	    m_fall -= FALL_SPEED * time;
      else
	m_fall = 0.0f;
    }
}

vec3 GetCollisionMove(vec3 pos, vec3 move, bvec3 lock)
{
  vec3	u(0, 0, 0);
  vec3	v(0, 0, 0);
  vec3	posT, moveT;

  if (!lock.x)
    {
      posT = pos + vec3(move.x, 0, 0);
      moveT = vec3(0, move.y, move.z);
      v = GetCollisionMove(posT, moveT, bvec3(true, lock.y, lock.z));
      if (IsColinear(u, v) && u.length() > v.length())
	u = v;
    }
  if (!lock.y)
    {
      posT = pos + vec3(0, move.y, 0);
      moveT = vec3(move.x, 0, move.z);
      v = GetCollisionMove(posT, moveT, bvec3(lock.x, true, lock.z));
      if (IsColinear(u, v) && u.length() > v.length())
	u = v;
    }
  if (!lock.z)
    {
      posT = pos + vec3(0, 0, move.z);
      moveT = vec3(move.x, move.y, 0);
      v = GetCollisionMove(posT, moveT, bvec3(lock.x, lock.y, true));
      if (IsColinear(u, v) && u.length() > v.length())
	u = v;
    }
  return (u);
}

void Player::Update(float time)
{
  this->Fall(time);

  vec3 move(m_move * m_speed * time, m_fall * time);
  m_pos += GetCollisionMove(m_pos, move, bvec3(false, false, false));
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
  if (k.x == k.y && k.y == k.z)
    return (true);
  return (false);
}
