#ifndef	TEKDOOM_H_
# define TEKDOOM_H_
# define UNUSED __attribute__((unused))
# define PACKED __attribute__((packed))
# ifndef WIN_X
#  define WIN_X 1280
# endif	/* !WIN_X */
# ifndef WIN_Y
#  define WIN_Y 720
# endif	/* !WIN_Y */
# define MOUSE_BUTTONS 6
# define KEY_BUTTONS 101
# define MAX_PLAYER 8
# define _DEFAULT_SOURCE_
# define STANDARD_RIGHTS S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH
# define NB_OBJ 8
# define ZNEAR 0
# define ZFAR 10000
# ifndef MAX_COUNT
#  define MAX_COUNT 510510
# endif
# ifndef FOV
#  define FOV 45
# endif /* !FOV */
# define MIN(A, B) (((A) <= (B)) ? (A) : (B))
# define MAX(A, B) (((A) >= (B)) ? (A) : (B))
# define ABS(A) (A >= 0 ? (A) : -(A))
# define ROUND(A) (((int)(A) - (A) < 0.5) ? (int)(A) : (int)(A) + 1)
# define SIZE_TRIGO_TAB 3600
# ifndef SKY_COLOR
#  define SKY_COLOR 0xFFFFDD00
# endif /* !SKY_COLOR */
# define PYTHA(A, B) (sqrt((A) * (A) + (B) * (B)))
# define POW2(N) ((N) * (N))
# define POW3(N) ((N) * (N) * (N))

typedef enum		e_area
  {
    CHATBOX		= 0,
    TEXTBOX		= 1,
    PLAYBUTTON		= 2,
    EXITBUTTON		= 3,
    OTHER		= 4
  }			t_area;

typedef struct s_player	t_player;
typedef struct s_vector	t_vector;
typedef struct s_pos	t_pos;

# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include <stdlib.h>
# include <stdint.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <time.h>
# include <pthread.h>

#endif	/* !TEKDOOM_H_ */
