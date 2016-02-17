#include "server.h"

void		init_zero_pseudo(char pseudo[][])
{
  int		i = -1, j = -1;

  while (++i < 10)
    {
      j = -1;
      while (++j < 21)
	{
	  pseudo[i][j] = 0;
	}
    }
}

int		server_add_pseudo(char pseudo[][], char *str)
{
  if (server_check_pseudo(udp, str) == -1)
    return (-1);
  strncpy(udp->pseudo[udp->nb_actual], str);
  return (0);
}

int		server_check_pseudo(char pseudo[][], char *str)
{
  int		i;

  i = -1;
  while (++i < 10)
    {
      if (strncmp(udp->str[i], str, 20) == 0)
	return (-1);
    }
  return (0);
}

/* do NOT forget to  decrement udp->nb_actual after this call */
void		server_remove_pseudo_str(char pseudo[][], char *str)
{
  int		i;

  i = -1;
  while (strncmp(pseudo[++i], str, 20) != 0 && i < 10);
  if (i == 10)
    return ;
  while (i + 1 < 10)
    {
      strncpy(pseudo[i], pseudo [i + 1], 20);
      ++i;
    }
}

int		get_pseudo_index(char pseudo[][], char *str)
{
  int		i;

  i = -1;
  while (++i < 10)
    {
      if (strncmp(pseudo[i], str, strlen(str)) == 0)
	return (i);
    }
  return (-1);
}
