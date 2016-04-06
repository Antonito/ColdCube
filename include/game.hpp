#ifndef	GAME_H_
# define GAME_H_

# define RES				1080
# if (RES == 1080)
#  define WIN_X				1920
#  define WIN_Y				1080
# else
#  define WIN_X				1280
#  define WIN_Y				720
# endif

# define WIN_TITLE			"ColdCube"
# define FONT_PATH			"assets/fonts/menu.ttf"

# if (WIN_X == 1280)
#  define CURSOR_IMG			"./assets/imgs/cursor720.bmp"
#  define MENU_BACKGROUND		"./assets/imgs/menu/720/%s.bmp"
#  define TCHAT_BACKGROUND		"./assets/imgs/tchat/background.png"
#  define TCHAT_HEADER			"./assets/imgs/tchat/header.png"
#  define TCHAT_FOOTER			"./assets/imgs/tchat/footer.png"
#  define TCHAT_FONT_NAME		"./assets/fonts/pseudo.ttf"
#  define TCHAT_FONT_TEXT		"./assets/fonts/chat.ttf"
#  define ROOM_BACKGROUND		"./assets/imgs/room/720/background.png"
#  define ROOM_ICON_PLAYER		"./assets/imgs/room/icon_connected.png"
#  define ROOM_ICON_IA			"./assets/imgs/room/icon_ia.png"
#  define SLIDER_BAR			"./assets/imgs/menu/720/slider-bar.png"
#  define SLIDER_CURSOR			"./assets/imgs/menu/720/slider-cursor.png"
#  define WIN_RATIO			1.50
# else
#  define CURSOR_IMG			"./assets/imgs/cursor.bmp"
#  define MENU_BACKGROUND		"./assets/imgs/menu/%s.bmp"
#  define TCHAT_BACKGROUND		"./assets/imgs/tchat/background.png"
#  define TCHAT_HEADER			"./assets/imgs/tchat/header.png"
#  define TCHAT_FOOTER			"./assets/imgs/tchat/footer.png"
#  define TCHAT_FONT_NAME		"./assets/fonts/pseudo.ttf"
#  define TCHAT_FONT_TEXT		"./assets/fonts/chat.ttf"
#  define ROOM_BACKGROUND		"./assets/imgs/room/background.png"
#  define ROOM_ICON_PLAYER		"./assets/imgs/room/icon_connected.png"
#  define ROOM_ICON_IA			"./assets/imgs/room/icon_ia.png"
#  define SLIDER_BAR			"./assets/imgs/menu/slider-bar.png"
#  define SLIDER_CURSOR			"./assets/imgs/menu/slider-cursor.png"
#  define WIN_RATIO			1
# endif

# define PLAYER_SIZE			0.9
# define PLAYER_HEIGHT			1.8
# define MAX_PSEUDO			20

//
// Game elements
//

# define TOTAL_PTS			10000

# define KNIFE_DMG			30
# define PISTOL_DMG			15
# define RIFLE_DMG			10

# define HEAD_KNIFE			10.00
# define HEAD_PISTOL			3.00
# define HEAD_RIFLE			2.50

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
#  include <unistd.h>
#  include <sys/types.h>
#  include <sys/stat.h>
# endif

# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <iostream>
# include <istream>
# include <math.h>
# include <fcntl.h>
# include <time.h>
# include <pthread.h>
# include <SDL2/SDL.h>
# include "engine/displayer.hpp"
# include "common_structs.hpp"

unsigned int	getDamage(int, int);
int		engineMain(Displayer &, t_data *);
void		setAzerty(t_keys *);
void		setQwerty(t_keys *);
void		free_game(t_data *);

#endif	/* !GAME_H_ */
