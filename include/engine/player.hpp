#ifndef PLAYER_HPP_
# define PLAYER_HPP_

# include <glm/glm.hpp>
# include "common_structs.hpp"
# include "engine/camera.hpp"

using namespace glm;

class Player
{
 public:
  Player();
  Player(vec3 pos, float rot, Map *map, int id);
  void Move(vec2 dir);
  void Jump();
  void Fall(float time);
  void Update(float time);
  void	SetCam(Camera &cam);
  void Draw();
  ~Player();
  vec3 GetCollisionMove(vec3 pos, vec3 move);
  vec3 &GetPos() {return m_pos;};
  vec2 &GetRot() {return m_rot;};

  int	GetId() {return m_id;};
  void	FillCPlayer(t_player *p, vec3 dir);

 private:
  vec3		m_pos;
  vec2		m_rot;
  float		m_speed;
  vec2		m_move;
  float		m_fall;
  Map		*m_map;
  Mesh		m_model;
  int		m_id;
};

#endif // !PLAYER_HPP_
