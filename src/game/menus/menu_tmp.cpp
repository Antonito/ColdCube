#include "class/menu_tmp.hpp"
#include <iostream>

Menu::Menu(int nb, std::string str)
{
  if (!(elems = new std::list<MenuItem>))
    {
      std::cerr << "Can't create new menu\n";
      return ;
    }
  id = nb;
  name = str;
}

Menu::~Menu(void)
{
  elems->clear();
  delete elems;
}

void	Menu::addMenuItem(void)
{
  MenuItem	item;

  elems->push_back(item);
}

void	Menu::deleteMenuItem(iterator index)
{
  elems->erase(index);
}

void	Menu::MenuItem::display(int type)
{
  if (type == BUTTON)
    {
      display_button();
    }
  else if (type == LABEL)
    {
      display_label();
    }
  else if (type == TEXTFIELD)
    {
      display_textfield();
    }
  else if (type == TOGGLE)
    {
      display_toggle();
    }
}

void	Menu::MenuItem::hide(int type)
{
  if (type == BUTTON)
    {
      hide_button();
    }
  else if (type == LABEL)
    {
      hide_label();
    }
  else if (type == TEXTFIELD)
    {
      hide_textfield();
    }
  else if (type == TOGGLE)
    {
      hide_toggle();
    }
}

void	Menu::MenuItem::Button::createButton(const int posx, const int posy,
					     const std::string name)
{
  x = posx;
  y = posy;
  text = name;
}

void	Menu::MenuItem::Label::setText(const std::string str)
{
  text = str;
}

void	Menu::MenuItem::Label::setSize(const int textSize)
{
  size = textSize;
}

void	Menu::MenuItem::TextField::getText(void)
{
  // WaitForInput and stock it to "input"
}

void	Menu::MenuItem::Toggle::setText(const std::string str)
{
  text = str;
}

void	Menu::MenuItem::Toggle::setStatus(const bool stat)
{
  status = stat;
}
