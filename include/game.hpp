#ifndef	GAME_H_
# define GAME_H_

# define WIN_X		1280
# define WIN_Y		720
# define WIN_TITLE	"ColdCube"

# define MAX_PSEUDO	20

# ifdef _WIN32
#  include <windows.h>
# endif

# include <iostream>
# include <istream>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <math.h>
# include <fcntl.h>
# include <time.h>
# include <pthread.h>
# include <SDL2/SDL.h>
# include "engine/display.hpp"
# include "common_structs.hpp"

int	engineMain(Display &);
void	free_game(t_data *);

#endif	/* !GAME_H_ */
