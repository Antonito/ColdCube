#include <stdlib.h>
#include "common_structs.hpp"

void	free_game(t_data *data)
{
  delete data;
}
