#ifndef PLAYER_HPP_
# define PLAYER_HPP_

# include <glm/glm.hpp>
# include "chunk.hpp"

using namespace glm;

class Player
{
 public:
  Player();
  Player(vec3 pos, float rot);
  void Move(vec2 dir);
  void Jump();
  void Fall(float time);
  void Update(float time);
  ~Player();
  vec3 GetCollisionMove(vec3 pos, vec3 move, bvec3 lock);
 private:
  vec3		m_pos;
  vec2		m_rot;
  float		m_speed;
  vec2		m_move;
  float		m_fall;
  Chunk		*m_chunks;
};

#endif // !PLAYER_HPP_
