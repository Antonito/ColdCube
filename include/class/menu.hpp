#ifndef	MENU_H
# define MENU_H

/*
** Pas de liste de chainee homemade
** Classe "Bouton" (hover et click)
** Classe menu
**
*/

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
  int	initMenu(int posx, int posy, char *text);
  void	createButton(int posx, int posy, char *text);
  void	hideAllButton(void);
  void  hideButton(int id);
  void	showAllButton(void);
  void	showButton(int id);
  void	printList(void);
  void	deleteButton(int id);
  void	deleteAllButton(void);
  void	display(void);

  int	selected_id;

private:
  t_button	*menuButton;
};

#endif
