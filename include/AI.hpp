#ifndef	AI_H_
# define AI_H_

# include "engine/player.hpp"

class AI
{
public:
  AI(t_player *player);
  ~AI();

  void		shootPlayer(void);
  void		findPlayer(t_player *player);
  void		moveToPlayer(void);
  void		updateAI(t_player *player);

private:
  Player	m_model;
  t_player	*m_player;
  glm::vec3	m_closestPlayer;
};

#endif	/* !AI_H_ */
