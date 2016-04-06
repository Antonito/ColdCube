/*
** my_str_to_wordtab.c for str wordtab in /home/lokoum/prog/PSU_2015_tetris/src/lib
** 
** Made by Lucas Troncy
** Login   <troncy_l@epitech.net>
** 
** Started on  Thu Feb 25 18:09:08 2016 Lucas Troncy
** Last update Wed Apr 06 12:31:02 2016 Lucas Troncy
*/

#include <stdlib.h>
#include <string.h>

int		splitter_counter(char *str, char splitter)
{
  int		count;
  int		i;

  count = 0;
  i = 0;
  while (str[i] != '\0')
    {
      if (str[i] == splitter)
	count++;
      i++;
    }
  return (count + 1);
}

char		**my_str_to_wordtab(char *str, char splitter)
{
  int		i;
  char		**table;
  int		nb;
  int		index;
  int		starter;

  i = -1;
  starter = 0;
  nb = splitter_counter(str, splitter);
  if ((table = (char **)malloc(sizeof(char *) * (nb + 1))) == NULL)
    return (NULL);
  while (++i < nb && (index = 0) == 0)
    {
      while (str[starter + index] != 0 && str[starter + index] != splitter)
	index++;
      index++;
      if ((table[i] = (char *)malloc(sizeof(char) * (index + 1))) == NULL)
	return (NULL);
      table[i][0] = '\0';
      table[i] = strncpy(table[i], &str[starter], index - 1);
      starter += index;
    }
  table[i] = NULL;
  return (table);
}
