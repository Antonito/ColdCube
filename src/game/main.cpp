#include <stdio.h>

int	main(int ac, char **av, char **env)
{
  if (!*env)
    {
      printf("Environment variable are missing\n");
#ifdef DEBUG
      printf("[INFOS] Game exited with status error 1");
#endif
      return (1);
    }
#ifdef DEBUG
  printf("[INFOS] Game exited correctly\n");
#endif
  return (0);
}
