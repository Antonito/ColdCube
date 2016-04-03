#include "common_structs.hpp"
#include <iostream>

void		setEvent(uint32_t value, int event, bool stat)
{
  t_uevent	set;

  set.value = value;
  if (event == CONNECTED)
    set.event.connected = stat;
#ifdef	DEBUG
  else
    std::cerr << "Event doesn't exist\n";
#endif
}

bool		getEvent(uint32_t value, int event)
{
  t_uevent	set;

  set.value = value;
  if (event == CONNECTED)
    return (set.event.connected);
#ifdef	DEBUG
  std::cerr << "Event doesn't exist\n";
#endif
  return (false);
}
