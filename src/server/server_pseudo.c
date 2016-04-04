#include "server.hpp"

int		tcp_server_add_pseudo(t_all *all, char *str, int i)
{
  if (tcp_server_check_pseudo(all, str) == -1)
    return (-1);
  strncpy(all->pseudo[i], str, strlen(str));
  return (0);
}

int		tcp_server_check_pseudo(t_all *all, char *str)
{
  int		i;

  i = -1;
  while (++i < 10)
    {
      if (all->connected[i] == 0)
	continue;
      if (strncmp(all->pseudo[i], str, 20) == 0)
	return (-1);
    }
  return (0);
}

int		tcp_get_pseudo_index(t_all *all, char *str)
{
  int		i;

  i = -1;
  while (++i < 10)
    {
      if (all->connected[i] == 0)
	continue;
      if (strncmp(all->pseudo[i], str, strlen(str)) == 0)
	return (i);
    }
  return (-1);
}
