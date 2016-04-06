#include "AI.hpp"
#include "server.hpp"
#include "tools.hpp"
#include <unistd.h>
#include <string.h>

int		createUdpPacketAI(int id, t_player *player, char *buff)
{
  char		packet[42];
  char		*tmp;
  int		n;
  unsigned int	i;

  memset(packet, 0, 42);
  packet[0] = (char)id;
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
  strncpy(buff, packet, 42);
  return (0);
}

int		readUdpPacketAI(char *pack, t_player *players, int *isPackage)
{
  GLfloat	flo;
  char *	tmp;
  int		all;
  unsigned int	i;
  uint32_t	tlo;

  if (!checkPacket(pack))
    {
      /*fprintf(stderr, "package wrong");
      fflush(stderr);*/
      return (1);
    }
  i = 0;
  flo = 0.0f;
  all = 2;
  tlo = 0;
  isPackage[(int)pack[0]] = 1;
  tmp = (char *)&flo;
  while (i < sizeof(GLfloat))
    {
      tmp[i] = pack[all + i];
      ++i;
    }
  players[(int)pack[0]].position.x = flo;
  flo = 0.0f;
  all += i + 1;
  i = 0;
  while (i < sizeof(GLfloat))
    {
      tmp[i] = pack[all + i];
      ++i;
    }
  players[(int)pack[0]].position.y = flo;
  flo = 0.0f;
  all += i + 1;
  i = 0;
  while (i < sizeof(GLfloat))
    {
      tmp[i] = pack[all + i];
      ++i;
    }
  players[(int)pack[0]].position.z = flo;
  flo = 0.0f;
  all += i + 1;
  i = 0;
  while (i < sizeof(GLfloat))
    {
      tmp[i] = pack[all + i];
      ++i;
    }
  players[(int)pack[0]].direction.x = flo;
  flo = 0.0f;
  all += i + 1;
  i = 0;
  while (i < sizeof(GLfloat))
    {
      tmp[i] = pack[all + i];
      ++i;
    }
  players[(int)pack[0]].direction.y = flo;
  flo = 0.0f;
  all += i + 1;
  i = 0;
  while (i < sizeof(GLfloat))
    {
      tmp[i] = pack[all + i];
      ++i;
    }
  players[(int)pack[0]].direction.z = flo;
  tmp = (char *)&tlo;
  all = i + 1;
  i = 0;
  while (i < sizeof(uint32_t))
    {
      tmp[i] = pack[all + i];
      ++i;
    }
  players[(int)pack[0]].selected_weapon = tlo;
  all = i + 1;
  i = 0;
  while (i < sizeof(uint32_t))
    {
      tmp[i] = pack[all + i];
      ++i;
    }
  players[(int)pack[0]].events = tlo;
  return (0);
}

int	initAI(t_player *player)
{
  int		i;
  glm::vec3	pos;
  glm::vec3	direction;

  i = -1;
  direction.x = 1;
  direction.y = 0;
  direction.z = 0;
  pos.x = 0;
  pos.y = 0;
  pos.z = 1;
  while (++i < 10)
    {
      memset(&player[i], 0, sizeof(t_player));
      player[i].id = i;
      if (!(player[i].pseudo = strndup("Bot\0", 4)))
	return (1);
      player[i].life = 100;
      player[i].selected_weapon = RIFLE_WEAPON;
      player[i].position = pos;
      player[i].direction = direction;
      pos.x++;
    }
  return (0);
}

void	*main_ai_thread(void *all)
{
  int	i;
  AI	*AIs= new AI[10];
  t_all	*data;

  data = (t_all *)all;
  data->ai = new t_player[10];
  if (initAI(data->ai))
    {
      write(2, "Error during AI init\n", 21);
      return (NULL);
    }
  i = -1;
  while (++i < 10)
    {
      AIs[i].setPlayer(&data->ai[i]);
      AIs[i].setId(i);
    }
  while (1)
    {
      i = -1;
      while (++i < 10)
	{
	  if (data->isPackage[i] && data->connected[i])
	    readUdpPacketAI(data->udp->cli_buff[i], &data->ai[i],
			    data->isPackage);
	}
      i = -1;
      while (++i < 10)
  	{
  	  if (!data->connected[i])
  	    {
  	      AIs[i].updateAI(data->ai, data->connected);
  	      createUdpPacketAI(i, &data->ai[i], data->udp->cli_buff[i]);
  	    }
  	}
      usleep(1000);
    }
  return (NULL);
}
