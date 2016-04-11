#include "common_structs.hpp"

unsigned char	getDamage(int weapon, int part, double dist)
{
  switch(weapon)
    {
    case (RIFLE_WEAPON):
      {
	switch(part)
	  {
	  case (HEAD_HIT):
	    return (60 / dist * 4);
	  case (BODY_HIT):
	    return (25 / dist * 4);
	  case (ARM_HIT):
	    return (5 / dist * 4);
	  case (LEG_HIT):
	    return (15 / dist * 4);
	  default:
	    return (0);
	  }
      }
    case (PISTOL_WEAPON):
      {
	switch(part)
	  {
	  case (HEAD_HIT):
	    return (80 / dist) * 4;
	  case (BODY_HIT):
	    return (30 / dist * 4);
	  case (ARM_HIT):
	    return (20 / dist * 4);
	  case (LEG_HIT):
	    return (5 / dist * 4);
	  default:
	    return (0);
	  }
      }
    case (KNIFE_WEAPON):
      {
	if (dist >= 0.8)
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
