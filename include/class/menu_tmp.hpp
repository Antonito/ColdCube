#ifndef	MENU_H
# define MENU_H

# include <string>
# include <list>

typedef	enum	e_menuItems
  {
    BUTTON,
    LABEL,
    TEXTFIELD,
    TOGGLE
  }		menuItems;

class Menu
{
public:

  Menu(int nb, std::string str);
  ~Menu(void);

  void			displayAll(void);
  void			hideAll(void);
  void			addMenuItem(void);
  void			deleteMenuItem(const_iterator index);

  class			MenuItem
  {
  public:
    void		onHover(void);
    void		onClick();
    void		display(int type);
    void		hide(int type);
    class		Button
    {
    public:
      void		createButton(const int posx, const int posy,
				     const std::string name);

      int		x;
      int		y;
      std::string	text;
    }; // Button

    class		Label
    {
      void		setSize(const int textSize);
      void		setText(const std::string str);

      int		size;
      std::string	text;
    }; // Label

    class		TextField
    {
      void		getText(void);

      std::string	input;
      std::string	text;
    }; // TextField

    class		Toggle
    {
      void		setText(const std::string str);
      void		setStatus(const bool stat);

      std::string	text;
      bool		status;
    }; // Toggle

  private:
    void		display_button(void);
    void		display_label(void);
    void		display_textfield(void);
    void		display_toggle(void);
    void		hide_button(void);
    void		hide_label(void);
    void		hide_textfield(void);
    void		hide_toggle(void);
  }; // MenuItem

private:
  int			id;
  std::string		name;
  std::list<MenuItem>	*elems;
}; // Menu
#endif
