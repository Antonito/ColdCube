#include "common_structs.hpp"
#include <iostream>

void printBits(size_t const size, void const * const ptr)
{
  unsigned char *b = (unsigned char*) ptr;
  unsigned char byte;
  int i, j;

  for (i=size-1;i>=0;i--)
    {
      for (j=7;j>=0;j--)
	{
	  byte = b[i] & (1<<j);
	  byte >>= j;
	  printf("%u", byte);
	}
    }
  puts("");
}

void		setEvent(uint32_t *value, int event, bool stat)
{
  t_uevent	set;

  printBits(sizeof(uint32_t), value);
  set.value = *value;
  if (event == CONNECTED)
    set.event.connected = stat;
  else if (event == SHOOT)
    set.event.shoot = stat;
#ifdef	DEBUG
  else
    std::cerr << "Event doesn't exist\n";
#endif
  *value = set.value;
  printBits(sizeof(uint32_t), value);
}

bool		getEvent(uint32_t value, int event)
{
  t_uevent	set;

  set.value = value;
  if (event == CONNECTED)
    return (set.event.connected);
  else if (event == SHOOT)
    return (set.event.shoot);
#ifdef	DEBUG
  std::cerr << "Event doesn't exist\n";
#endif
  return (false);
}
