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
  short		mask = 1;
  short		scoreTmp;
  t_uevent	set;

  set.value = *value;
  scoreTmp = score;

  set.event.score1 = scoreTmp & mask;
  set.event.score2 = scoreTmp & (mask << 1);
  set.event.score3 = scoreTmp & (mask << 2);
  set.event.score4 = scoreTmp & (mask << 3);
  set.event.score5 = scoreTmp & (mask << 4);
  set.event.score6 = scoreTmp & (mask << 5);
  set.event.score7 = scoreTmp & (mask << 6);
  set.event.score8 = scoreTmp & (mask << 7);
  set.event.score9 = scoreTmp & (mask << 8);
  set.event.score10 = scoreTmp & (mask << 9);
  set.event.score11 = scoreTmp & (mask << 10);
  set.event.score12 = scoreTmp & (mask << 11);
  set.event.score13 = scoreTmp & (mask << 12);
  set.event.score14 = scoreTmp & (mask << 13);
  set.event.score15 = scoreTmp & (mask << 14);
  set.event.score16 = scoreTmp & (mask << 15);

  *value = set.value;
  printf("Event = %d | Score = %d\n", *value, score);
}

short		getScore(uint32_t value)
{
  short		score = 0;
  t_uevent	set;

  set.value = value;

  score |= set.event.score1;
  score |= set.event.score2 << 1;
  score |= set.event.score3 << 2;
  score |= set.event.score4 << 3;
  score |= set.event.score5 << 4;
  score |= set.event.score6 << 5;
  score |= set.event.score7 << 6;
  score |= set.event.score8 << 7;
  score |= set.event.score9 << 8;
  score |= set.event.score10 << 9;
  score |= set.event.score11 << 10;
  score |= set.event.score12 << 11;
  score |= set.event.score13 << 12;
  score |= set.event.score14 << 13;
  score |= set.event.score15 << 14;
  score |= set.event.score16 << 15;

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
