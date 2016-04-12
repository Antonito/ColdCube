#include "common_structs.hpp"
#include <iostream>

void		setEvent(uint32_t *value, int event, bool stat)
{
  t_uevent	set;

  set.value = *value;
  if (event == IS_CONNECTED)
    set.event.connected = stat;
  else if (event == SHOOT)
    set.event.shoot = stat;
#ifdef	DEBUG
  else
    std::cerr << "Event doesn't exist\n";
#endif
  *value = set.value;
}

void		setScore(uint32_t *value, int score)
{
  short		scoreTmp;
  t_uevent	set;

  set.value = *value;
  scoreTmp = score;
  set.event.score = scoreTmp;

  *value = set.value;
}

short		getScore(uint32_t value)
{
  short		score = 0;
  t_uevent	set;

  set.value = value;
  score = set.event.score;
  return (score);
}

bool		getEvent(uint32_t value, int event)
{
  t_uevent	set;

  set.value = value;
  if (event == IS_CONNECTED)
    return (set.event.connected);
  else if (event == SHOOT)
    return (set.event.shoot);
#ifdef	DEBUG
  std::cerr << "Event doesn't exist\n";
#endif
  return (false);
}
