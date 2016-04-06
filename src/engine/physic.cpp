#include "engine/misc.hpp"
#include "engine/map.hpp"

#ifdef	CHEAT
# include "cheat.hpp"
#endif

#define ABS(A) (((double)(A) >= 0) ? (A) : -(A))
#define MAX(A, B) (((A) >= (B)) ? (A) : (B))
#define ROUND(A) (((A) - (int)(A) < 0.5f) ? (int)(A) : (int)(A) + 1)

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
  vec3	a(-1, 0, 0);
  vec3	t;
  double b = start.x - (int)start.x;

  pos = start - incr * (GLfloat)b;
  while (length(pos - start) < length(move))
    {
      t = pos + a;
      if (map.GetBlock(t))
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
  vec3	a(0, -1, 0);
  vec3	t;
  double b = start.y - (int)start.y;

  pos = start - incr * (GLfloat)b;
  while (length(pos - start) < length(move))
    {
      t = pos + a;
      if (map.GetBlock(t))
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
  vec3	a(0, 0, -1);
  vec3	t;
  double b = start.z - (int)start.z;

  pos = start - incr * (GLfloat)b;
  while (length(pos - start) < length(move))
    {
      t = pos + a;
      if (map.GetBlock(t))
	return ((pos - start).z / move.z);
      pos += incr;
    }
  return (1.0);
}

bool	GetFullCollisionX(Map &map, vec3 pos, double move)
{
  if ((move > 0.0 && (map.GetBlock(pos + vec3(0.8, 0, 0)) ||
		      map.GetBlock(pos + vec3(0.8, 0.8, 0)) ||
		      map.GetBlock(pos + vec3(0.8, 0, 1)) ||
		      map.GetBlock(pos + vec3(0.8, 0.8, 1)) ||
		      map.GetBlock(pos + vec3(0.8, 0, 1.8)) ||
		      map.GetBlock(pos + vec3(0.8, 0.8, 1.8)))) ||
      (move < 0.0 && (map.GetBlock(pos) ||
		      map.GetBlock(pos + vec3(0, 0.8, 0)) ||
		      map.GetBlock(pos + vec3(0, 0, 1)) ||
		      map.GetBlock(pos + vec3(0, 0.8, 1)) ||
		      map.GetBlock(pos + vec3(0, 0, 1.8)) ||
		      map.GetBlock(pos + vec3(0, 0.8, 1.8)))))
    return (true);
  return (false);
}

bool	GetFullCollisionY(Map &map, vec3 pos, double move)
{
  if ((move > 0.0 && (map.GetBlock(pos + vec3(0, 0.8, 0)) ||
		      map.GetBlock(pos + vec3(0.8, 0.8, 0)) ||
		      map.GetBlock(pos + vec3(0, 0.8, 1)) ||
		      map.GetBlock(pos + vec3(0.8, 0.8, 1)) ||
		      map.GetBlock(pos + vec3(0, 0.8, 1.8)) ||
		      map.GetBlock(pos + vec3(0.8, 0.8, 1.8)))) ||
      (move < 0.0 && (map.GetBlock(pos) ||
		      map.GetBlock(pos + vec3(0.8, 0, 0)) ||
		      map.GetBlock(pos + vec3(0, 0, 1)) ||
		      map.GetBlock(pos + vec3(0.8, 0, 1)) ||
		      map.GetBlock(pos + vec3(0, 0, 1.8)) ||
		      map.GetBlock(pos + vec3(0.8, 0, 1.8)))))
    return (true);
  return (false);}

bool	GetFullCollisionZ(Map &map, vec3 pos, double move)
{
  if ((move > 0.0 && (map.GetBlock(pos + vec3(0, 0, 1.8)) ||
		      map.GetBlock(pos + vec3(0.8, 0, 1.8)) ||
		      map.GetBlock(pos + vec3(0.8, 0.8, 1.8)) ||
		      map.GetBlock(pos + vec3(0, 0.8, 1.8)))) ||
      (move < 0.0 && (map.GetBlock(pos) ||
		      map.GetBlock(pos + vec3(0, 0.8, 0)) ||
		      map.GetBlock(pos + vec3(0.8, 0.8, 0)) ||
		      map.GetBlock(pos + vec3(0.8, 0, 0)))))
    return (true);
  return (false);
}

// vec3	GetFullCollision(Map &map, vec3 pos, vec3 move)
// {
//   int	i = 0;
//   vec3	res;
//   bvec3	lock(true, true, true);

//   while (i < 3)
//     {
//       res = vec3(1, 1, 1);
//       if (lock.x)
// 	res.x = GetFullCollisionX(map, pos, move);
//       if (lock.y)
// 	res.y = GetFullCollisionY(map, pos, move);
//       if (lock.z)
// 	res.z = GetFullCollisionZ(map, pos, move);

//       if (lock.x && res.x <= res.y && res.x <= res.z)
// 	{
// 	  pos += res.x * move;
// 	  move *= fabs(1 - res.x);
// 	  move.x = 0.0;
// 	  lock.x = false;
// 	}
//       else if (lock.y && res.y <= res.x && res.y <= res.z)
// 	{
// 	  pos += res.y * move;
// 	  move *= fabs(1 - res.y);
// 	  move.y = 0.0;
// 	  lock.y = false;
// 	}
//       else if (lock.z && res.z <= res.x && res.z <= res.y)
// 	{
// 	  pos += res.z * move;
// 	  move *= fabs(1 - res.z);
// 	  move.z = 0.0;
// 	  lock.z = false;
// 	}
//       i++;
//     }
//   return (pos);
// }

vec3	GetFullCollision(Map &map, vec3 pos, vec3 move)
{
  bvec3	lock(true, true, true);
  int	i = 0;
  vec3	incr = move / (GLfloat)1000.0;

  while (map.GetBlock(pos))
    {
      pos += vec3(0, 0, 1);
      pos.z = (int)pos.z;
    }
  while (i < 1000)
    {
      if (lock.x)
	pos += vec3(incr.x, 0, 0);
      if (GetFullCollisionX(map, pos, move.x) && !(lock.x = false))
	pos.x = round(pos.x) + (move.x > 0.0) * (0.2 - 0.0001);
      if (lock.y)
	pos += vec3(0, incr.y, 0);
      if (GetFullCollisionY(map, pos, move.y) && !(lock.y = false))
	pos.y = round(pos.y) + (move.y > 0.0) * (0.2 - 0.0001);
      if (lock.z)
	pos += vec3(0, 0, incr.z);
      if (GetFullCollisionZ(map, pos, move.z) && !(lock.z = false))
	pos.z = round(pos.z) + (move.z > 0.0) * 0.2;
      i++;
    }
  return (pos);
}
