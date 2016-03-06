#include "server.hpp"

void		udp_init_zero_pseudo(t_udps *udp)
{
  int		i = -1, j = -1;

  while (++i < 10)
    {
      j = -1;
      while (++j < 21)
	{
	  udp->pseudo[i][j] = 0;
	}
    }
}

int		udp_server_add_pseudo(t_udps *udp, char *str)
{
  if (udp_server_check_pseudo(udp, str) == -1)
    return (-1);
  strncpy(udp->pseudo[udp->nb_actual], str, strlen(str));
  return (0);
}

int		udp_server_check_pseudo(t_udps *udp, char *str)
{
  int		i;

  i = -1;
  while (++i < 10)
    {
      if (strncmp(udp->pseudo[i], str, 20) == 0)
	return (-1);
    }
  return (0);
}

void		udp_server_remove_pseudo_str(t_udps *udp, char *str)
{
  int		i;

  i = -1;
  while (strncmp(udp->pseudo[++i], str, 20) != 0 && i < 10);
  if (i == 10)
    return ;
  while (i + 1 < 10)
    {
      strncpy(udp->pseudo[i], udp->pseudo[i + 1], 20);
      ++i;
    }
  udp->nb_actual += 1;
}

int		udp_get_pseudo_index(t_udps *udp, char *str)
{
  int		i;

  i = -1;
  while (++i < 10)
    {
      if (strncmp(udp->pseudo[i], str, strlen(str)) == 0)
	return (i);
    }
  return (-1);
}
