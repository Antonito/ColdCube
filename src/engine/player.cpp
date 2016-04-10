#include "game.hpp"
#include "engine/misc.hpp"
#include "engine/player.hpp"

#ifdef	CHEAT
# include "cheat.hpp"
#endif

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
  m_third = false;
}

Player::~Player()
{
}

bool Player::IsOnBlock()
{
  if (m_pos.z == (int)m_pos.z && (m_map->GetBlock(m_pos + vec3(0, 0, -1)) ||
				  m_map->GetBlock(m_pos + vec3(0, 0.8, -1)) ||
				  m_map->GetBlock(m_pos + vec3(0.8, 0, -1)) ||
				  m_map->GetBlock(m_pos + vec3(0.8, 0.8, -1))))
    return (true);
  return (false);
}

void Player::Move(vec2 dir)
{
  if (this->IsOnBlock())
    m_move += normalize(dir);
  if (m_move.length() > 5.0)
    {
      m_move = normalize(m_move);
      m_move *= 4.5;
    }
}

void Player::MoveCheat(vec3 dir)
{
  m_pos += dir;
}

void Player::Jump()
{
  //  ivec3 p(m_pos);

#ifdef	CHEAT
  if (!cheat.selected.fly && this->IsOnBlock())
    m_fall = 8;
#else
  if (this->IsOnBlock())
    m_fall = 8;
#endif
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

  (void)time;
#ifdef	CHEAT
  if (!cheat.selected.fly)
    {
      if (!this->IsOnBlock())
	m_fall -= 0.5f;
    }
  else
    m_move *= 0.95;
#else
  if (!this->IsOnBlock())
    m_fall -= 0.5f;
#endif
  // else if (m_fall < 0.0)
  //   m_fall = 0.0f;
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
  // usleep(10000);
  //  pos += corner;
  temp = (pos.x - (int)pos.x) / move.x;

  pos += move;
  if (pos.z < 1)
    pos.z = 1;
  return (pos);
}

void Player::Update(Map &map, float time)
{
  this->Fall(time);

  vec3 move(m_move * m_speed * time, m_fall * time);
  double	z = m_pos.z;

  m_pos = GetFullCollision(map, m_pos, move);
  if (this->IsOnBlock())
    m_move *= 0.81;
  if (m_pos.z == z)
    m_fall = 0;
  // printf("(%.2f, %.2f, %.2f)             ", m_pos.x, m_pos.y, m_pos.z);
  // fflush(stdout);
}

void	Player::SetCam(Camera &cam, bool third, t_player *p)
{
  cam.GetPos() = m_pos + vec3(0.4, 0.4, 1.6) + vec3(p->direction.x, p->direction.y, 0) * (GLfloat)0.25;;
  cam.GetRot() = m_rot;
  if (third)
    cam.GetPos() -= p->direction * (GLfloat)3.0;
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

void	PredictPosition(t_player *p, vec3 *last, int *isPackage)
{
  vec3	tmp;

  tmp = p->position;
  if (!*isPackage)
    p->position += p->position - *last;
  else
    *isPackage = 0;
  *last = tmp;
}
