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
  unsigned short		score : 16;
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
