#ifndef	EVENTS_HPP
# define EVENTS_HPP

# include <stdint.h>
# include <stdbool.h>

typedef enum			e_event
  {
    CONNECTED			= 1
  }				e_event;

typedef	struct			s_event
{
  unsigned int			connected : 1;
  unsigned int			other : 31;
}				t_event;

typedef union			u_uevent
{
  t_event			event;
  uint32_t			value;
}				t_uevent;

void				setEvent(uint32_t *, int, bool);
bool				getEvent(uint32_t, int);

#endif //EVENTS_HPP
