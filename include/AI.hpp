#ifndef	AI_H_
# define AI_H_

# include <GL/glew.h>
# include "engine/player.hpp"
# include "events.hpp"

class AI
{
public:
  AI();
  AI(t_player *player);
  ~AI();

  int		getId()const{return (m_id);};
  void		setId(int id){m_id = id;};
  void		setPlayer(t_player *player);
  bool		isBot(uint32_t events) {return (!getEvent(events, IS_CONNECTED));};
  void		shootPlayer(void);
  void		findPlayer(t_player *player, int *isConnected);
  void		moveToPlayer(void);
  void		updateAI(t_player *player, int *isConnected);

private:
  Player	m_model;
  t_player	*m_player;
  glm::vec3	m_closestPlayer;
  int		m_id;
};

#endif	/* !AI_H_ */
