#include "class/menu.hpp"
#include <iostream>
#include <stdlib.h>

int	Menu::initMenu(void)
{
  t_button	*next;

  if (!(next = new t_button))
    return (1);
  return (0);
}

void	Menu::createButton(int posx, int posy, char *text)
{
  if (!menuButton->prev)
    {
      menuButton->id = 0;
    }
  else
    {
      menuButton->id = menuButton->prev->id + 1;
    }
  menuButton->posx = posx;
  menuButton->posy = posy;
  menuButton->name = text;
  menuButton->display = false;
  menuButton->next = NULL;
}

void	Menu::showButton(int id)
{
  t_button	*tmp;

  tmp = menuButton;
  while (tmp && tmp->id != id)
    {
      tmp = tmp->next;
    }
  if (tmp)
    {
      tmp->display = true;
    }
  else
    {
      std::cerr << "Button " << id << " doesn't exists\n";
    }
}

void	Menu::deleteButton(int id)
{
  t_button	*tmp;

  tmp = menuButton;
  while (tmp && id != tmp->id)
    {
      tmp = tmp->next;
    }
  if (tmp)
    {
      if (tmp->prev)
	{
	  tmp->prev->next = tmp->next;
	  if (tmp->next)
	    tmp->next->prev = tmp->prev;
	}
      else if (tmp->next)
	menuButton = tmp->next;
    }
}

void	Menu::deleteAllButton(void)
{
  t_button	*tmp;

  tmp = menuButton;
  while (tmp->next != NULL)
    {
      tmp = tmp->next;
      delete tmp->prev;
    }
  delete tmp;
}
