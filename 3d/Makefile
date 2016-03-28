NAME=		coldcube

CPPFILES=	chunk.cpp		\
		display.cpp		\
		load_shader.cpp		\
		main.cpp		\
		map.cpp			\
		mesh.cpp		\
		shader.cpp		\
		texture.cpp

CFILES=		cload_chunk.c

PREFIX=		src/

CPPSRC=		$(addprefix $(PREFIX), $(CPPFILES))

CSRC=		$(addprefix $(PREFIX), $(CFILES))

OBJ=		$(CPPSRC:.cpp=.o)

OBJ+=		$(CSRC:.c=.o)

LIB=		-lSDL2 -lGL -lm -lGLEW -lglut

INCDIR=		-Iinclude

CFLAGS=		-W -Wall -Wextra -g

CXX=		g++

CC=		gcc

%.o:		%.c
		@$(CC) -c $< -o $@ $(INCDIR) $(LIB) $(CFLAGS)
		@echo -e '\e[1m\e[92m[OK]\e[0m $@'


%.o:		%.cpp
		@$(CXX) -c $< -o $@ $(INCDIR) $(LIB) $(CFLAGS)
		@echo -e '\e[1m\e[92m[OK]\e[0m $@'

$(NAME):	$(OBJ)
		@$(CXX) -o $(NAME) $(OBJ) $(INCDIR) $(LIB) $(CFLAGS)
		@echo -e '\e[1m\e[92m[OK] \e[34mLinking\e[0m'

all:		$(NAME)

clean:
		@rm -rf $(OBJ)
		@echo -e '\e[1m\e[91m[RM]\e[0m $(OBJ)'

fclean:		clean
		@rm -rf $(NAME)
		@echo -e '\e[1m\e[91m[RM]\e[0m $(NAME)'

re:		fclean $(NAME)

.PHONY:		$(NAME) all clean fclean re
