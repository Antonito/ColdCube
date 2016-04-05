#include "engine/misc.hpp"
#include "engine/map.hpp"

#ifdef	CHEAT
# include "cheat.hpp"
#endif

#define ABS(A) (((double)(A) >= 0) ? (A) : -(A))
#define MAX(A, B) (((A) >= (B)) ? (A) : (B))

double	GetCollisionX(Map &map, vec3 start, vec3 move)
{
#ifdef	CHEAT
  if (cheat.selected.collisions)
    return (1.0);
#endif
  if (move.x == 0.0)
    return (1.0);

  vec3	incr(1, move.y / move.x, move.z / move.x);
  vec3	pos;
  vec3	a;
  double b = start.x - (int)start.x;

  if (move.x > 0.0 && map.GetBlock(start))
    return (0.0);
  // if (map.GetBlock(start) && b < 0.2)
  //   return (0);
  if (move.x > 0.0)
    pos += incr;
  // if (move.x > 0.0 && map.GetBlock(start))
  //   pos -= incr * (GLfloat)2.0;
  pos = start - incr * (GLfloat)b;
  // if (start.x > (int)start.x)
  //   printf("Oui1\n");
  // if (move.x > 0.0)
  //   pos += incr;
  incr *= (GLfloat)((move.x > 0.0) ? 1 : -1);
  a = vec3(-(move.x < 0), 0, 0);
  while (length(pos - start) < length(move))
    {
      if (map.GetBlock(pos + a))
	return ((pos - start).x / move.x);
      pos += incr;
    }
  return (1.0);
}

double	GetCollisionY(Map &map, vec3 start, vec3 move)
{
#ifdef	CHEAT
  if (cheat.selected.collisions)
    return (1.0);
#endif
  if (move.y == 0.0)
    return (1.0);

  vec3	incr(move.x / move.y, 1, move.z / move.y);
  vec3	pos;
  vec3	a;
  double b = start.y - (int)start.y;

  // if (map.GetBlock(start) && b < 0.2)
  //   return (0);
  if (move.y > 0.0 && map.GetBlock(start))
    return (0.0);
  if (move.y > 0.0)
    pos += incr;
  // if (move.y > 0.0 && map.GetBlock(start))
  //   pos -= incr * (GLfloat)2.0;
  pos = start - incr * (GLfloat)b;
  // if (start.y > (int)start.y)
  //   printf("Oui2\n");
  // if (move.y > 0.0)
  //   pos += incr;
  incr *= (GLfloat)((move.y > 0.0) ? 1 : -1);
  a = vec3(0, -(move.y < 0), 0);
  while (length(pos - start) < length(move))
    {
      if (map.GetBlock(pos + a))
	return ((pos - start).y / move.y);
      pos += incr;
    }
  return (1.0);
}

double	GetCollisionZ(Map &map, vec3 start, vec3 move)
{
#ifdef	CHEAT
  if (move.z > 0.0 && cheat.selected.collisions)
    return (1.0);
#endif
  if (move.z == 0.0)
    return (1.0);

  vec3	incr(move.x / move.z, move.y / move.z, 1);
  vec3	pos;
  vec3	a;
  double b = start.z - (int)start.z;

  // if (map.GetBlock(start) && b < 0.2)
  //   return (0);
  if (move.z > 0.0 && map.GetBlock(start))
    return (0.0);
  if (move.z > 0.0)
    pos += incr;
  // if (move.z > 0.0 && map.GetBlock(start))
  //   pos -= incr * (GLfloat)2.0;
  pos = start - incr * (GLfloat)b;
  // if (start.z > (int)start.z)
    // printf("Oui3\n");
  // if (move.x > 0.0)
  //   pos += incr;
  incr *= (GLfloat)((move.z > 0.0) ? 1 : -1);
  a = vec3(0, 0, -(move.z < 0));
  while (length(pos - start) < length(move))
    {
      if (map.GetBlock(pos + a))
	return ((pos - start).z / move.z);
      pos += incr;
    }
  return (1.0);
}

double	GetFullCollisionX(Map &map, vec3 pos, vec3 move)
{
  double	r = 1.0;
  double	tmp;

  if (move.x == 0.0)
    return (1.0);
  if (move.x > 0.0)
    {
      r = (r > (tmp = GetCollisionX(map, pos + vec3(0.8, 0, 0), move))) ? tmp : r;
      r = (r > (tmp = GetCollisionX(map, pos + vec3(0.8, 0.8, 0), move))) ? tmp : r;
      r = (r > (tmp = GetCollisionX(map, pos + vec3(0.8, 0, 1), move))) ? tmp : r;
      r = (r > (tmp = GetCollisionX(map, pos + vec3(0.8, 0.8, 1), move))) ? tmp : r;
      r = (r > (tmp = GetCollisionX(map, pos + vec3(0.8, 0, 1.8), move))) ? tmp : r;
      r = (r > (tmp = GetCollisionX(map, pos + vec3(0.8, 0.8, 1.8), move))) ? tmp : r;
    }
  else
    {
      r = (r > (tmp = GetCollisionX(map, pos + vec3(0, 0, 0), move))) ? tmp : r;
      r = (r > (tmp = GetCollisionX(map, pos + vec3(0, 0.8, 0), move))) ? tmp : r;
      r = (r > (tmp = GetCollisionX(map, pos + vec3(0, 0, 1), move))) ? tmp : r;
      r = (r > (tmp = GetCollisionX(map, pos + vec3(0, 0.8, 1), move))) ? tmp : r;
      r = (r > (tmp = GetCollisionX(map, pos + vec3(0, 0, 1.8), move))) ? tmp : r;
      r = (r > (tmp = GetCollisionX(map, pos + vec3(0, 0.8, 1.8), move))) ? tmp : r;
    }
  return (r);
}

double	GetFullCollisionY(Map &map, vec3 pos, vec3 move)
{
  double	r = 1.0;
  double	tmp;

  if (move.y == 0.0)
    return (1.0);
  if (move.y > 0.0)
    {
      r = (r > (tmp = GetCollisionY(map, pos + vec3(0, 0.8, 0), move))) ? tmp : r;
      r = (r > (tmp = GetCollisionY(map, pos + vec3(0.8, 0.8, 0), move))) ? tmp : r;
      r = (r > (tmp = GetCollisionY(map, pos + vec3(0, 0.8, 1), move))) ? tmp : r;
      r = (r > (tmp = GetCollisionY(map, pos + vec3(0.8, 0.8, 1), move))) ? tmp : r;
      r = (r > (tmp = GetCollisionY(map, pos + vec3(0, 0.8, 1.8), move))) ? tmp : r;
      r = (r > (tmp = GetCollisionY(map, pos + vec3(0.8, 0.8, 1.8), move))) ? tmp : r;
    }
  else
    {
      r = (r > (tmp = GetCollisionY(map, pos + vec3(0, 0, 0), move))) ? tmp : r;
      r = (r > (tmp = GetCollisionY(map, pos + vec3(0.8, 0, 0), move))) ? tmp : r;
      r = (r > (tmp = GetCollisionY(map, pos + vec3(0, 0, 1), move))) ? tmp : r;
      r = (r > (tmp = GetCollisionY(map, pos + vec3(0.8, 0, 1), move))) ? tmp : r;
      r = (r > (tmp = GetCollisionY(map, pos + vec3(0, 0, 1.8), move))) ? tmp : r;
      r = (r > (tmp = GetCollisionY(map, pos + vec3(0.8, 0, 1.8), move))) ? tmp : r;
    }
  return (r);
}

double	GetFullCollisionZ(Map &map, vec3 pos, vec3 move)
{
  double	r = 1.0;
  double	tmp;
  double	z;

  z = (move.z > 0.0) ? 1.8 : 0.0;
  if (move.z == 0.0)
    return (1.0);
  if (move.z > 0.0)
    {
      r = (r > (tmp = GetCollisionZ(map, pos + vec3(0, 0, 1.8), move))) ? tmp : r;
      r = (r > (tmp = GetCollisionZ(map, pos + vec3(0, 0.8, 1.8), move))) ? tmp : r;
      r = (r > (tmp = GetCollisionZ(map, pos + vec3(0.8, 0, 1.8), move))) ? tmp : r;
      r = (r > (tmp = GetCollisionZ(map, pos + vec3(0.8, 0.8, 1.8), move))) ? tmp : r;
    }
  else
    {
      r = (r > (tmp = GetCollisionZ(map, pos + vec3(0, 0, 0), move))) ? tmp : r;
      r = (r > (tmp = GetCollisionZ(map, pos + vec3(0, 0.8, 0), move))) ? tmp : r;
      r = (r > (tmp = GetCollisionZ(map, pos + vec3(0.8, 0, 0), move))) ? tmp : r;
      r = (r > (tmp = GetCollisionZ(map, pos + vec3(0.8, 0.8, 0), move))) ? tmp : r;
    }
  return (r);
}

vec3	GetFullCollision(Map &map, vec3 pos, vec3 move)
{
  int	i = 0;
  vec3	res;
  bvec3	lock(true, true, true);

  while (i < 3)
    {
      res = vec3(1, 1, 1);
      if (lock.x)
	res.x = GetFullCollisionX(map, pos, move);
      if (lock.y)
	res.y = GetFullCollisionY(map, pos, move);
      if (lock.z)
	res.z = GetFullCollisionZ(map, pos, move);

      if (lock.x && res.x <= res.y && res.x <= res.z)
	{
	  pos += res.x * move;
	  move *= fabs(1 - res.x);
	  move.x = 0.0;
	  lock.x = false;
	  // printf("X:%.2f\t", res.x);
	}
      else if (lock.y && res.y <= res.x && res.y <= res.z)
	{
	  pos += res.y * move;
	  move *= fabs(1 - res.y);
	  move.y = 0.0;
	  lock.y = false;
	  // printf("Y:%.2f\t", res.y);
	}
      else if (lock.z && res.z <= res.x && res.z <= res.y)
	{
	  pos += res.z * move;
	  move *= fabs(1 - res.z);
	  move.z = 0.0;
	  lock.z = false;
	  // printf("Z:%.2f\t", res.z);
	}
      i++;
    }
  // printf("\n");
  return (pos);
}
