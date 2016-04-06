#include "AI.hpp"

//Retarded AI version 1.0

AI::AI()
{
}

AI::AI(t_player *player)
{
  m_player = player;
}

AI::~AI()
{
}

void		AI::setPlayer(t_player *player)
{
  m_player = player;
}

void		AI::shootPlayer(void)
{
}

void		AI::findPlayer(t_player *player, int *isConnected)
{
  glm::vec3	tmp3;
  int		i;

  i = 0;
  if (isConnected[i])
    m_closestPlayer = player[i].position - m_player->position;
  else
    m_closestPlayer = vec3(0, 0, 0);
  while (++i < 10)
    {
      tmp3 = player[i].position;
      if (i != m_id &&
	  glm::length(tmp3) <= glm::length(m_closestPlayer) &&
       	  isConnected[i])
	m_closestPlayer = tmp3;
    }
}

void		AI::moveToPlayer(void)
{
  //  m_model.Move(glm::normalize(glm::vec2(m_closestPlayer.x, m_closestPlayer.y)));
  m_model.GetPos() += m_closestPlayer;
  m_player->position = m_model.GetPos();
  printf("%f %f %f\n", m_player->position.x, m_player->position.y, m_player->position.z);
}

void		AI::updateAI(t_player *player, int *isConnected)
{
  findPlayer(player, isConnected);
  moveToPlayer();
}
