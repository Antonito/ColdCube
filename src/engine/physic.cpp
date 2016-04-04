#include "engine/misc.hpp"
#include "engine/map.hpp"

double	GetCollisionX(Map &map, vec3 start, vec3 move)
{
  if (move.x == 0.0)
    return (1.0);

  vec3	incr(1, move.y / move.x, move.z / move.x);
  vec3	pos;

  pos = start - incr * (start.x - (int)start.x + (move.x > 0.0));
  incr *= (GLfloat)((move.x > 0.0) ? 1 : -1);
  while (length(pos - start) < length(move))
    {
      if (map.GetBlock(pos))
	return ((pos - start).x / move.x);
      pos += incr;
    }
  return (1.0);
}

double	GetCollisionY(Map &map, vec3 start, vec3 move)
{
  if (move.y == 0.0)
    return (1.0);

  vec3	incr(move.x / move.y, 1, move.z / move.y);
  vec3	pos;

  pos = start - incr * (start.y - (int)start.y + (move.y > 0.0));
  incr *= (GLfloat)((move.y > 0.0) ? 1 : -1);
  while (length(pos - start) < length(move))
    {
      if (map.GetBlock(pos))
	return ((pos - start).y / move.y);
      pos += incr;
    }
  return (1.0);
}

double	GetCollisionZ(Map &map, vec3 start, vec3 move)
{
  if (move.z == 0.0)
    return (1.0);

  vec3	incr(move.x / move.z, move.y / move.z, 1);
  vec3	pos;

  pos = start - incr * (start.z - (int)start.z + (move.z > 0.0));
  incr *= (GLfloat)((move.z > 0.0) ? 1 : -1);
  while (length(pos - start) < length(move))
    {
      if (map.GetBlock(pos))
	return ((pos - start).z / move.z);
      pos += incr;
    }
  return (1.0);
}

double	GetFullCollisionX(Map &map, vec3 pos, vec3 move)
{
  double	r = 1.0;
  double	tmp;
  double	x;

  x = (move.x > 0.0) ? 0.8 : 0.0;
  r = (r > (tmp = GetCollisionX(map, pos + vec3(x, 0, 0), move))) ? tmp : r;
  r = (r > (tmp = GetCollisionX(map, pos + vec3(x, 0.8, 0), move))) ? tmp : r;
  r = (r > (tmp = GetCollisionX(map, pos + vec3(x, 0, 1), move))) ? tmp : r;
  r = (r > (tmp = GetCollisionX(map, pos + vec3(x, 0.8, 1), move))) ? tmp : r;
  r = (r > (tmp = GetCollisionX(map, pos + vec3(x, 0, 1.8), move))) ? tmp : r;
  r = (r > (tmp = GetCollisionX(map, pos + vec3(x, 0.8, 1.8), move))) ? tmp : r;
  return (r);
}

double	GetFullCollisionY(Map &map, vec3 pos, vec3 move)
{
  double	r = 1.0;
  double	tmp;
  double	y;

  y = (move.y > 0.0) ? 0.8 : 0.0;
  r = (r > (tmp = GetCollisionY(map, pos + vec3(0, y, 0), move))) ? tmp : r;
  r = (r > (tmp = GetCollisionY(map, pos + vec3(0.8, y, 0), move))) ? tmp : r;
  r = (r > (tmp = GetCollisionY(map, pos + vec3(0, y, 1), move))) ? tmp : r;
  r = (r > (tmp = GetCollisionY(map, pos + vec3(0.8, y, 1), move))) ? tmp : r;
  r = (r > (tmp = GetCollisionY(map, pos + vec3(0, y, 1.8), move))) ? tmp : r;
  r = (r > (tmp = GetCollisionY(map, pos + vec3(0.8, y, 1.8), move))) ? tmp : r;
  return (r);
}

double	GetFullCollisionZ(Map &map, vec3 pos, vec3 move)
{
  double	r = 1.0;
  double	tmp;
  double	z;

  z = (move.z > 0.0) ? 1.8 : 0.0;
  r = (r > (tmp = GetCollisionZ(map, pos + vec3(0, 0, z), move))) ? tmp : r;
  r = (r > (tmp = GetCollisionZ(map, pos + vec3(0, 0.8, z), move))) ? tmp : r;
  r = (r > (tmp = GetCollisionZ(map, pos + vec3(0.8, 0, z), move))) ? tmp : r;
  r = (r > (tmp = GetCollisionZ(map, pos + vec3(0.8, 0.8, z), move))) ? tmp : r;
  return (r);
}

vec3	GetFullCollision(Map &map, vec3 pos, vec3 move)
{
  int	i = 0;
  vec3	res;
  bvec3	lock(true, true, true);

  while (i < 3)
    {
      res.x = GetFullCollisionX(map, pos, move);
      res.y = GetFullCollisionY(map, pos, move);
      res.z = GetFullCollisionZ(map, pos, move);

      if (res.x < res.y && res.x < res.z)
	{
	  pos += res.x * move;
	  move -= res.x * move;
	  move.x = 0;
	}
      else if (res.y < res.x && res.y < res.z)
	{
	  pos += res.y * move;
	  move -= res.y * move;
	  move.y = 0;
	}
      else
	{
	  pos += res.z * move;
	  move -= res.z * move;
	  move.z = 0;
	}
      i++;
    }
  return (pos);
}
