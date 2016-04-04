#include "common_structs.hpp"

unsigned char	getDamage(int weapon, int part)
{
  switch(weapon)
    {
    case (RIFLE_WEAPON):
      {
	switch(part)
	  {
	  case (HEAD_HIT):
	    return (60);
	  case (BODY_HIT):
	    return (25);
	  case (ARM_HIT):
	    return (5);
	  case (LEG_HIT):
	    return (15);
	  default:
	    return (0);
	  }
      }
    case (PISTOL_WEAPON):
      {
	switch(part)
	  {
	  case (HEAD_HIT):
	    return (80);
	  case (BODY_HIT):
	    return (30);
	  case (ARM_HIT):
	    return (20);
	  case (LEG_HIT):
	    return (5);
	  default:
	    return (0);
	  }
      }
    case (KNIFE_WEAPON):
      {
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
