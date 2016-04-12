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
  time_t       	getMinuts(void){return ((m_begin - time(NULL)) / 60);};
  time_t       	getSeconds(void){return ((m_begin - time(NULL)) % 60);};
  void		updateTime(void);
  void		resetStreak(void);
  void		updateStreakMult(const int weapon);

  void		setScore(int score){m_score = score;};
  int		getScore(void);

private:
  double	m_streakMult;
  int		m_timeMult;
  int		m_score;
  time_t	m_begin;
};

#endif	/* !SCORE_H_ */
