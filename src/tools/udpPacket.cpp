#include "common_structs.hpp"

int		createUdpPacket(t_player *player)
{
  char		packet[70];
  char		*tmp;
  int		n;
  unsigned int	i;

  packet[0] = (char)player->id;
  n = 1;
  i = 0;
  tmp = (char *)&player->position.x;
  while (i < sizeof(GLfloat))
    {
      packet[n + i] = tmp[i];
      ++i;
    }
  n += i;
  i = 0;
  tmp = (char *)&player->position.y;
  while (i < sizeof(GLfloat))
    {
      packet[n + i] = tmp[i];
      ++i;
    }
  n += i;
  i = 0;
  tmp = (char *)&player->position.z;
  while (i < sizeof(GLfloat))
    {
      packet[n + i] = tmp[i];
      ++i;
    }
  n += i;
  i = 0;
  tmp = (char *)&player->direction.x;
  while (i < sizeof(GLfloat))
    {
      packet[n + i] = tmp[i];
      ++i;
    }
  n += i;
  i = 0;
  tmp = (char *)&player->direction.y;
  while (i < sizeof(GLfloat))
    {
      packet[n + i] = tmp[i];
      ++i;
    }
  n += i;
  i = 0;
  tmp = (char *)&player->direction.z;
  while (i < sizeof(GLfloat))
    {
      packet[n + i] = tmp[i];
      ++i;
    }
  n += i;
  i = 0;
  tmp = (char *)&player->selected_weapon;
  while (i < 4)
    {
      packet[n + i] = tmp[i];
      ++i;
    }
  n += i;
  i = 0;
  tmp = (char *)&player->events;
  while (i < 4)
    {
      packet[n + i] = tmp[i];
      ++i;
    }
  return (0);
}
