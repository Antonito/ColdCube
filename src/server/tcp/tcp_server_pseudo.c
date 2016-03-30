#include "server.hpp"

void		tcp_init_zero_pseudo(t_tcps *tcp)
{
  int		i = -1, j = -1;

  while (++i < 10)
    {
      j = -1;
      while (++j < 21)
	{
	  tcp->pseudo[i][j] = 0;
	}
    }
}

int		tcp_server_add_pseudo(t_tcps *tcp, char *str)
{
  if (tcp_server_check_pseudo(tcp, str) == -1)
    return (-1);
  strncpy(tcp->pseudo[tcp->addIndex], str, strlen(str));
  return (0);
}

int		tcp_server_check_pseudo(t_tcps *tcp, char *str)
{
  int		i;

  i = -1;
  while (++i < 10)
    {
      if (strncmp(tcp->pseudo[i], str, 20) == 0)
	return (-1);
    }
  return (0);
}

void		tcp_server_remove_pseudo_str(t_tcps *tcp, char *str)
{
  int		i;

  i = -1;
  while (strncmp(tcp->pseudo[++i], str, 20) != 0 && i < 10);
  if (i == 10)
    return ;
  while (i + 1 < 10)
    {
      strncpy(tcp->pseudo[i], tcp->pseudo[i + 1], 20);
      ++i;
    }
}

int		tcp_get_pseudo_index(t_tcps *tcp, char *str)
{
  int		i;

  i = -1;
  while (++i < 10)
    {
      if (strncmp(tcp->pseudo[i], str, strlen(str)) == 0)
	return (i);
    }
  return (-1);
}
