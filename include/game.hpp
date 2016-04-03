#ifndef	GAME_H_
# define GAME_H_

# define WIN_X				1280
# define WIN_Y				720
# define WIN_TITLE			"ColdCube"
# define PLAYER_SIZE			0.9
# define PLAYER_HEIGHT			1.8
# define MAX_PSEUDO			20

//
// Game elements
//

# define TOTAL_PTS			10000

# define RIFLE_DMG			10
# define PISTOL_DMG			15
# define KNIFE_DMG			30

# define HEAD_RIFLE			2.50
# define HEAD_PISTOL			3.00
# define HEAD_KNIFE			10.00

# define FAR_RIFLE			5
# define FAR_PISTOL			7

# define BEGIN_TIMER			1
# define MIDDLE_TIMER			2
# define END_TIMER			3

# define STREAK_RIFLE			1.10
# define STREAK_PISTOL			1.25
# define STREAK_KNIFE			1.50

//
//
//

# ifdef _WIN32
#  include <windows.h>
# else
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdint.h>
# endif

# include <iostream>
# include <istream>
# include <math.h>
# include <fcntl.h>
# include <time.h>
# include <pthread.h>
# include <SDL2/SDL.h>
# include "engine/display.hpp"
# include "common_structs.hpp"

// class	Team
// {
// public:
//   Team();
//   ~Team();
// private:
//   int	m_score;
// };

// class	Game
// {
// public:
//   Game();
//   ~Game();

//   Team	team1;
//   Team	team2;

//   bool	isOver();
//   int	getScore();

// private:
//   int	m_score;
// };

int	engineMain(Display &, t_data *);
void	free_game(t_data *);

#endif	/* !GAME_H_ */
