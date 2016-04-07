#ifndef	SCORE_H_
# define SCORE_H_

# include <time.h>

class Score
{
public:
  Score();
  ~Score();
  void		printScore(const int team);
  void		checkWin(const int team);
  void		updateScore(const int weapon, const bool headshot,
			    const double dist);
  void		updateTime(void);
  void		resetStreak(void);
  void		updateStreakMult(const int weapon);

  int		getScore(void);

private:
  double	m_streakMult;
  int		m_timeMult;
  int		m_score;
  time_t	m_begin;
};

#endif	/* !SCORE_H_ */
