#ifndef	EVENTS_HPP
# define EVENTS_HPP

# include <stdint.h>
# include <stdbool.h>

typedef enum			e_event
  {
    IS_CONNECTED	       	= 1,
    SHOOT			= 2
  }				e_event;

typedef	struct			s_event
{
  unsigned char			connected : 1;
  unsigned char			shoot : 1;

  // 16 bits score
  unsigned char			score1 : 1;
  unsigned char			score2 : 1;
  unsigned char			score3 : 1;
  unsigned char			score4 : 1;
  unsigned char			score5 : 1;
  unsigned char			score6 : 1;
  unsigned char			score7 : 1;
  unsigned char			score8 : 1;
  unsigned char			score9 : 1;
  unsigned char			score10 : 1;
  unsigned char			score11 : 1;
  unsigned char			score12 : 1;
  unsigned char			score13 : 1;
  unsigned char			score14 : 1;
  unsigned char			score15 : 1;
  unsigned char			score16 : 1;

  unsigned int			others : 14;
}				t_event;

typedef union			u_uevent
{
  t_event			event;
  uint32_t			value;
}				t_uevent;

void				setEvent(uint32_t *, int, bool);
bool				getEvent(uint32_t, int);

// The score may be reversed
void				setScore(uint32_t *, int);
short				getScore(uint32_t);

#endif //EVENTS_HPP
