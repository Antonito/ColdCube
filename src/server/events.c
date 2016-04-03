#include "events.hpp"
#include <unistd.h>

void		setEvent(uint32_t *value, int event, bool stat)
{
  t_uevent	set;

  set.value = *value;
  if (event == CONNECTED)
    set.event.connected = stat;
#ifdef	DEBUG
  else
    write(2, "Event doesn't exist\n", 20);
#endif
  *value = set.value;
}

bool		getEvent(uint32_t value, int event)
{
  t_uevent	set;

  set.value = value;
  if (event == CONNECTED)
    return (set.event.connected);
#ifdef	DEBUG
  write(2, "Event doesn't exist\n", 20);
#endif
  return (false);
}
