#ifndef	MENU_H
# define MENU_H

typedef	struct		s_button
{
  int			id;
  int			posx;
  int			posy;
  char			*name;
  bool			display;
  struct s_button	*next;
  struct s_button	*prev;
}			t_button;

class Menu
{
public:
  int	initMenu(void);
  void	createButton(int posx, int posy, char *text);
  void	showButton(int id);
  void	deleteButton(int id);
  void	deleteAllButton(void);

private:
  t_button	*menuButton;
};

#endif
