#include "class/menu.hpp"
#include <iostream>
#include <stdlib.h>
#include "tools.hpp"

int		Menu::initMenu(int posx, int posy, char *text)
{
  t_button	*node;

  if (!(node = new t_button))
    {
      std::cerr << "Can't create new menu\n";
      return (1);
    }
  menuButton = node;
  menuButton->id = 0;
  menuButton->posx = posx;
  menuButton->posy = posy;
  menuButton->name = text;
  menuButton->display = false;
  menuButton->prev = NULL;
  menuButton->next = NULL;
  return (0);
#ifdef	DEBUG
  std::clog << "[Success] Created new Menu\n";
#endif
}

void		Menu::createButton(int posx, int posy, char *text)
{
  t_button	*node;
  t_button	*tmp;

  if (!menuButton)
    {
      std::cerr << "Please use initMenu first\n";
      return ;
    }
  if (!(node = new t_button))
    {
      std::cerr << "Can't create new button\n";
      return ;
    }
  tmp = menuButton;
  node->posx = posx;
  node->posy = posy;
  node->name = text;
  node->display = false;
  node->next = NULL;
  while (tmp->next)
    tmp = tmp->next;
  tmp->next = node;
  node->prev = tmp;
  node->id = node->prev->id + 1;
#ifdef	DEBUG
  std::clog << "[Success] Created node " << node->id << "\n";
#endif
}

void		Menu::hideAllButton(void)
{
  t_button	*tmp;

  tmp = menuButton;
  while (tmp)
    {
      tmp->display = false;
      tmp = tmp->next;
    }
}

void		Menu::hideButton(int id)
{
  t_button	*tmp;

  tmp = menuButton;
  while (tmp && tmp->id != id)
    {
      tmp = tmp->next;
    }
  if (tmp)
    {
      tmp->display = false;
    }
  else
    {
      std::cerr << "Button " << id << " doesn't exists\n";
    }
}

void		Menu::showAllButton(void)
{
  t_button	*tmp;

  tmp = menuButton;
  while (tmp)
    {
      tmp->display = true;
      tmp = tmp->next;
    }
}

void		Menu::showButton(int id)
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

void		Menu::printList(void)
{
  t_button	*tmp;

  tmp = menuButton;
  while (tmp)
    {
      std::clog << "Id : " << tmp->id << "\n";
      std::clog << "Pos : " << tmp->posx << ":" << tmp->posy<< "\n";
      std::clog << "Name : " << tmp->name << "\n";
      std::clog << "Display : " << tmp->display << "\n";
      tmp = tmp->next;
    }
}

void		Menu::deleteButton(int id)
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

void		Menu::deleteAllButton(void)
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

void		Menu::display(void)
{
  t_button	*tmp;

  tmp = menuButton;
  while (tmp)
    {
      if (tmp->display)
	{
	  drawText(tmp->name, tmp->posx, tmp->posy, 0.0, 1.0, 0.0);
#ifdef	DEBUG
	  std::clog << "Displayed button " << tmp->id << "\n";
#endif
	}
      tmp = tmp->next;
    }
}
