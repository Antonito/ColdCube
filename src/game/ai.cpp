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
    {
      m_closestPlayer = player[i].position;
      std::cout << "Id = " << i << "\n";
      dprintf(2, "Closest player is at %f %f %f\n", m_closestPlayer.x, m_closestPlayer.y, m_closestPlayer.z);
    }
  else
    m_closestPlayer = vec3(0, 0, 0);
  while (++i < 10)
    {
      tmp3 = player[i].position;
      // if (glm::length(tmp3) <= glm::length(m_closestPlayer) &&
      // 	  getEvent(player[i].events, CONNECTED))
      if (isConnected[i])
	{
	  std::cout << "Id = " << i << "\n";
	  m_closestPlayer = tmp3;
	  dprintf(2, "Closest player is at %f %f %f\n", m_closestPlayer.x, m_closestPlayer.y, m_closestPlayer.z);
	}
    }
}

void		AI::moveToPlayer(void)
{
  m_model.Move(glm::normalize(glm::vec2(m_closestPlayer.x, m_closestPlayer.y)));
}

void		AI::updateAI(t_player *player, int *isConnected)
{
  findPlayer(player, isConnected);
  //Si joueur visible -> tirer
  //shootPlayer();
  //Sinon
  moveToPlayer();
}
