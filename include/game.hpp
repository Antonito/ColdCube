#ifndef	GAME_H_
# define GAME_H_

# define RES				108
# if (RES == 1080)
#  define WIN_X				1920
#  define WIN_Y				1080
# else
#  define WIN_X				1280
#  define WIN_Y				720
# endif

# define WIN_TITLE			"ColdCube"

# if (WIN_X == 1280)
#  define WIN_RATIO			1.50
#  define SLIDER_CURSOR			"./assets/imgs/menu/720/slider-cursor.png"
#  define SLIDER_BAR			"./assets/imgs/menu/720/slider-bar.png"
#  define MENU_BACKGROUND		"assets/imgs/menu/720/%s.bmp"
#  define CURSOR_IMG			"assets/imgs/cursor720.bmp"
# else
#  define WIN_RATIO			1
#  define SLIDER_CURSOR			"./assets/imgs/menu/slider-cursor.png"
#  define SLIDER_BAR			"./assets/imgs/menu/slider-bar.png"
#  define MENU_BACKGROUND		"assets/imgs/menu/%s.bmp"
#  define CURSOR_IMG			"assets/imgs/cursor.bmp"
# endif

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

# define FAR_DIST			100.0

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

int	engineMain(Display &, t_data *);
void	setAzerty(t_keys *);
void	setQwerty(t_keys *);
void	free_game(t_data *);

#endif	/* !GAME_H_ */
