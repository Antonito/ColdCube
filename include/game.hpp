#ifndef	GAME_H_
# define GAME_H_

# define WIN_X	        1920
# define WIN_Y		1080
# define WIN_TITLE	"ColdCube"
# define PLAYER_SIZE 0.9
# define PLAYER_HEIGHT 1.8
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

int	engineMain(Display &, t_data *);
void	free_game(t_data *);

#endif	/* !GAME_H_ */
