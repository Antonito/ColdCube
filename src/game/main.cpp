#include "game.hpp"

/*
** Boucle (au debut sur le menu principal), jusqu'a ce qu'on quitte le jeu
*/

int		game(void)
{
  t_data	*data;

  if (!(data = malloc(sizeof(t_data))))
    {
      printf("Malloc of t_data failed\n");
      return (1);
    }
  free_game(data);
  return (0);
}

int	main(int ac, char **av, char **env)
{
  if (!*env)
    {
      printf("Environment variable are missing\n");
#ifdef DEBUG
      printf("[INFOS] Game exited with status error 1\n");
#endif
      return (1);
    }
  // Lancement du thread TCP
  if (game() == 1) //Lancement de la partie graphique
    {
      printf("An error occured.\n");
#ifdef DEBUG
      printf("[INFOS] Game exited with status error 1\n");
#endif
      return (1);
    }
#ifdef DEBUG
  printf("[INFOS] Game exited correctly\n");
#endif
  return (0);
}
