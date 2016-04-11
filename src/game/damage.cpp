#include "common_structs.hpp"

unsigned char	getDamage(int weapon, int part, double dist)
{
  unsigned char	tmp;
  switch(weapon)
    {
    case (RIFLE_WEAPON):
      {
	switch(part)
	  {
	  case (HEAD_HIT):
	    return (((tmp = 60 / dist * 4) > 30) ? tmp : 30);
	  case (BODY_HIT):
	    return (((tmp = 25 / dist * 4) > 12) ? tmp : 12);
	  case (ARM_HIT):
	    return (((tmp = 5 / dist * 4)  > 2) ? tmp : 2);
	  case (LEG_HIT):
	    return (((tmp = 15 / dist * 4)  > 7) ? tmp : 7);
	  default:
	    return (0);
	  }
      }
    case (PISTOL_WEAPON):
      {
	switch(part)
	  {
	  case (HEAD_HIT):
	    return ((((tmp = 80 / dist) * 4) > 40) ? tmp : 40);
	  case (BODY_HIT):
	    return (((tmp = 30 / dist * 4) > 15) ? tmp : 15);
	  case (ARM_HIT):
	    return (((tmp = 20 / dist * 4) > 10) ? tmp : 10);
	  case (LEG_HIT):
	    return (((tmp = 5 / dist * 4) > 2) ? tmp : 2);
	  default:
	    return (0);
	  }
      }
    case (KNIFE_WEAPON):
      {
	if (dist >= 1.2)
	  return (0);
	switch(part)
	  {
	  case (HEAD_HIT):
	    return (99);
	  case (BODY_HIT):
	    return (50);
	  case (ARM_HIT):
	    return (10);
	  case (LEG_HIT):
	    return (30);
	  default:
	    return (0);
	  }
      }
    default:
      return (0);
    }
  return (0);
}
