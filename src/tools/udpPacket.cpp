#include <GL/gl.h>
#include "common_structs.hpp"
#include "tools.hpp"

int		createUdpPacket(t_data *data, t_player *player)
{
  char		packet[70];
  char		*tmp;
  int		n;
  unsigned int	i;

  memset(packet, 0, 70);
  packet[0] = (char)data->net.playerIndexUdp;
  n = 2;
  i = 0;
  tmp = (char *)&player->position.x;
  while (i < sizeof(GLfloat))
    {
      packet[n + i] = tmp[i];
      ++i;
    }
  n += i + 1;
  i = 0;
  tmp = (char *)&player->position.y;
  while (i < sizeof(GLfloat))
    {
      packet[n + i] = tmp[i];
      ++i;
    }
  n += i + 1;
  i = 0;
  tmp = (char *)&player->position.z;
  while (i < sizeof(GLfloat))
    {
      packet[n + i] = tmp[i];
      ++i;
    }
  n += i + 1;
  i = 0;
  tmp = (char *)&player->direction.x;
  while (i < sizeof(GLfloat))
    {
      packet[n + i] = tmp[i];
      ++i;
    }
  n += i + 1;
  i = 0;
  tmp = (char *)&player->direction.y;
  while (i < sizeof(GLfloat))
    {
      packet[n + i] = tmp[i];
      ++i;
    }
  n += i + 1;
  i = 0;
  tmp = (char *)&player->direction.z;
  while (i < sizeof(GLfloat))
    {
      packet[n + i] = tmp[i];
      ++i;
    }
  n += i + 1;
  i = 0;
  tmp = (char *)&player->selected_weapon;
  while (i < 4)
    {
      packet[n + i] = tmp[i];
      ++i;
    }
  n += i + 1;
  i = 0;
  tmp = (char *)&player->events;
  while (i < 4)
    {
      packet[n + i] = tmp[i];
      ++i;
    }
  if (sendUdpPacket(data, packet) != 0)
    return (1);
  return (0);
}

int		readUdpPacket(t_data *data)
{
  GLfloat	flo;
  char *	tmp;
  int		all;
  unsigned int	i;
  uint32_t	tlo;

  if (!checkPacket(data->net.udp.buff))
    {
      /*fprintf(stderr, "package wrong");
      fflush(stderr);*/
      return (1);
    }
  i = 0;
  flo = 0.0f;
  all = 1;
  tlo = 0;
  tmp = (char *)&flo;
  while (i < sizeof(GLfloat))
    {
      tmp[i] = data->net.udp.buff[all + i];
      ++i;
    }
  data->players[(int)data->net.udp.buff[0]].position.x = flo;
  flo = 0.0f;
  i = 0;
  all += i + 1;
  while (i < sizeof(GLfloat))
    {
      tmp[i] = data->net.udp.buff[all + i];
      ++i;
    }
  data->players[(int)data->net.udp.buff[0]].position.y = flo;
  flo = 0.0f;
  i = 0;
  all += i + 1;
  while (i < sizeof(GLfloat))
    {
      tmp[i] = data->net.udp.buff[all + i];
      ++i;
    }
  data->players[(int)data->net.udp.buff[0]].position.z = flo;
  flo = 0.0f;
  i = 0;
  all += i + 1;
  while (i < sizeof(GLfloat))
    {
      tmp[i] = data->net.udp.buff[all + i];
      ++i;
    }
  data->players[(int)data->net.udp.buff[0]].direction.x = flo;
  flo = 0.0f;
  i = 0;
  all += i + 1;
  while (i < sizeof(GLfloat))
    {
      tmp[i] = data->net.udp.buff[all + i];
      ++i;
    }
  data->players[(int)data->net.udp.buff[0]].direction.y = flo;
  flo = 0.0f;
  i = 0;
  all += i + 1;
  while (i < sizeof(GLfloat))
    {
      tmp[i] = data->net.udp.buff[all + i];
      ++i;
    }
  data->players[(int)data->net.udp.buff[0]].direction.z = flo;
  tmp = (char *)&tlo;
  i = 0;
  all = i + 1;
  while (i < sizeof(uint32_t))
    {
      tmp[i] = data->net.udp.buff[all + i];
      ++i;
    }
  data->players[(int)data->net.udp.buff[0]].selected_weapon = tlo;
  i = 0;
  all = i + 1;
  while (i < sizeof(uint32_t))
    {
      tmp[i] = data->net.udp.buff[all + i];
      ++i;
    }
  data->players[(int)data->net.udp.buff[0]].events = tlo;
  return (0);
}
