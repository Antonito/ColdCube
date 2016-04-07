#include "Score.hpp"
#include "game.hpp"
#include "common_structs.hpp"

Score::Score()
{
  m_timeMult = 1;
  m_streakMult = 1.0;
  m_score = 0;
  m_begin = time(NULL);
}

Score::~Score()
{
}

void		Score::checkWin(int team)
{
  std::cout << "Team " << team << " wins !\n";
  exit(0);
}

void		Score::updateScore(int weapon, bool headShot, double dist)
{
  if (weapon == RIFLE_WEAPON)
    m_score += RIFLE_DMG * m_timeMult * m_streakMult * ((headShot) ? HEAD_RIFLE : 1) * ((dist >= FAR_DIST) ? FAR_RIFLE : 1);
  else if (weapon == PISTOL_WEAPON)
    m_score += PISTOL_DMG * m_timeMult * m_streakMult * ((headShot) ? HEAD_PISTOL : 1) * ((dist >= FAR_DIST) ? FAR_PISTOL : 1);
  else if (weapon == KNIFE_WEAPON)
    m_score += KNIFE_DMG * m_timeMult * m_streakMult * ((headShot) ? HEAD_KNIFE : 1);
  if (m_score > TOTAL_PTS)
    m_score = TOTAL_PTS;
};

void		Score::updateTime(void)
{
  time_t	shift;

  if (m_timeMult != END_TIMER)
    {
      shift = m_begin - time(NULL);
      if (m_timeMult == BEGIN_TIMER && shift / 60 == MIDDLE_TIMER)
	m_timeMult = MIDDLE_TIMER;
      else if (m_timeMult == MIDDLE_TIMER && shift / 60 == END_TIMER)
	m_timeMult = END_TIMER;
    }
}

void	Score::resetStreak(void)
{
  m_streakMult = 1.00;
}

void	Score::updateStreakMult(int weapon)
{
  if (weapon == RIFLE_WEAPON)
    m_streakMult += STREAK_RIFLE;
  else if (weapon == PISTOL_WEAPON)
    m_streakMult += STREAK_PISTOL;
  else if (weapon == KNIFE_WEAPON)
    m_streakMult += STREAK_KNIFE;
}

int	Score::getScore(void)
{
  return (m_score);
}
