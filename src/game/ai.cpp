#include "AI.hpp"

//Retarded AI version 1.0

AI::AI(t_player *player)
{
  m_player = player;
  m_model = Player();
}

AI::~AI()
{
}

void		AI::shootPlayer(void)
{
}

void		AI::findPlayer(t_player *player)
{
  glm::vec3	tmp3;
  int		i;

  i = 1;
  if (getEvent(player[i].events, CONNECTED))
    m_closestPlayer = player[i].position;
  while (++i < 10)
    {
      tmp3 = player[i].position;
      if (glm::length(tmp3) <= glm::length(m_closestPlayer) &&
	  getEvent(player[i].events, CONNECTED))
	m_closestPlayer = tmp3;
    }
}

void		AI::moveToPlayer(void)
{
  m_model.Move(glm::normalize(glm::vec2(m_closestPlayer.x, m_closestPlayer.y)));
}

void		AI::updateAI(t_player *player)
{
  findPlayer(player);
  //Si joueur visible -> tirer
  //shootPlayer();
  //Sinon
  moveToPlayer();
}
