# Useful variables
DEBUG=			no
CHEAT=			no

# Sources
GAME_PREFIX=		src/game/

GAME_FILES=		main.cpp			\
			free.cpp			\
			score.cpp			\
			damage.cpp			\
			user.cpp			\
			interface/Tchat.cpp 		\
			menus/main_menu.cpp		\
			menus/Menu.cpp

SERV_PREFIX=		src/server/

SERV_FILES=		main.cpp			\
			ai_thread.cpp			\
			udp/main_udp_thread.cpp		\
			udp/server_udp_msg.cpp		\
			tcp/main_tcp_thread.cpp		\
			tcp/server_tcp_functions.cpp	\
			tcp/server_tcp_msg.cpp		\
			server_pseudo.cpp

ENGINE_PREFIX=		src/engine/

ENGINE_FILES=		animation_player.cpp		\
			chunk.cpp			\
			displayer.cpp			\
			load_shader.cpp			\
			map.cpp				\
			mesh.cpp			\
			physic.cpp			\
			room.cpp			\
			player.cpp			\
			shader.cpp			\
			texture.cpp			\
			renderer.cpp			\
			engine.cpp

ENGINE_C_FILES=		cload_chunk.c

TOOLS_PREFIX=		src/tools/

TOOLS_FILES=		text.cpp			\
			udpPacket.cpp			\
			sendUdpPacket.cpp		\
			udp_client.cpp			\
			check_package.cpp		\
			tcp_client.cpp			\
			events.cpp			\
			str2tab.cpp

GENERATION_PREFIX=	src/generation/

GENERATION_FILES=	generate_map.c

# Adding prefixes
GAME=			$(addprefix $(GAME_PREFIX),$(GAME_FILES))
SERVER=			$(addprefix $(SERV_PREFIX),$(SERV_FILES))
ENGINE=			$(addprefix $(ENGINE_PREFIX),$(ENGINE_FILES))
TOOLS=			$(addprefix $(TOOLS_PREFIX),$(TOOLS_FILES))
ENGINE_C=		$(addprefix $(ENGINE_PREFIX),$(ENGINE_C_FILES))
TOOLS_C=		$(addprefix $(TOOLS_PREFIX),$(TOOLS_C_FILES))
GENERATION=		$(addprefix $(GENERATION_PREFIX),$(GENERATION_FILES))

GAME+=			$(TOOLS)
GAME+=			$(ENGINE)

SERVER+=		src/tools/events.cpp		\
			src/tools/check_package.cpp	\
			src/game/ai.cpp			\
			src/engine/player.cpp		\
			src/engine/mesh.cpp		\
			src/engine/map.cpp		\
			src/engine/chunk.cpp		\
			src/engine/texture.cpp		\
			src/engine/physic.cpp

NAME=			coldcube
NAMESERV=		server_coldcube
NAMEGEN=		generator_coldcube

HEAD=			-Iinclude			\
			-Ilib/lapin/include

# Flags

CXXFLAGS= $(HEAD) -W -Wall -Wextra
CFLAGS= $(HEAD) -W -Wall -Wextra

ifeq ($(DEBUG), yes)
CXXFLAGS+= -g -D DEBUG
CFLAGS+= -g -D DEBUG
endif

ifeq ($(CHEAT), yes)
CXXFLAGS+= -D CHEAT
CFLAGS+= -D CHEAT
endif

# Compiler

CC=			gcc

ifeq ($(DEBUG), yes)
CXX=			clang
else
CXX=			g++
endif

RM=			rm -f

LIB=			-Llib/lapin/lib			\
			-llapin 			\
			-lsfml-audio 			\
			-lsfml-graphics 		\
			-lsfml-window 			\
			-lsfml-system 			\
			-lstdc++			\
			-lpthread			\
			-lSDL2				\
			-lSDL2_ttf			\
			-lSDL2_image			\
			-lGL				\
			-lGLEW				\
			-lglut				\
			-lOVR				\
			-ldl				\
			-lm

LIB_SERVER=		-lstdc++			\
			-lpthread			\
			-lm				\
			-lGL				\
			-lGLEW

# Obj link

OBJ=			$(GAME:.cpp=.o)
OBJ+=			$(ENGINE_C:.c=.o)

OBJSERV=		$(SERVER:.cpp=.o)
OBJSERV+=		$(ENGINE_C:.c=.o)

OBJGEN=			$(GENERATION:.c=.o)

$(NAMESERV):	$(OBJSERV) $(NAME) $(NAMEGEN)
	@echo -n -e "[ \e[1m\e[92mOK\e[0m ]"
	@echo "Compiled server"
	@$(CC) $(OBJSERV) -o $(NAMESERV) $(LIB_SERVER)

$(NAMEGEN):	$(OBJGEN)
	@echo -n -e "[ \e[1m\e[92mOK\e[0m ]"
	@echo "Compiled generator"
	@$(CC) $(OBJGEN) -o $(NAMEGEN) $(LIB)

$(NAME):	$(OBJ)
ifeq ($(DEBUG), yes)
	@tput setaf 1; tput bold
	@echo "  ____  _____ ____  _   _  ____   __  __  ___  ____  _____ ";
	@echo " |  _ \| ____| __ )| | | |/ ___| |  \/  |/ _ \|  _ \| ____|";
	@echo " | | | |  _| |  _ \| | | | |  _  | |\/| | | | | | | |  _|  ";
	@echo " | |_| | |___| |_) | |_| | |_| | | |  | | |_| | |_| | |___ ";
	@echo " |____/|_____|____/ \___/ \____| |_|  |_|\___/|____/|_____|";
	@echo "                                                           ";
	@tput sgr0
endif
	@echo -n -e "[ \e[1m\e[92mOK\e[0m ]"
	@echo "Compiled game"
	@$(CXX) $(OBJ) -o $(NAME) $(LIB)

%.o:	%.c
	@echo -n -e "[ \e[1m\e[92mOK\e[0m ]"
	@echo "Compiling" $<
	@$(CC) $(CFLAGS) -c -o $@ $<

%.o:	%.cpp
	@echo -n -e "[ \e[1m\e[92mOK\e[0m ]"
	@echo "Compiling" $<
	@$(CXX) $(CXXFLAGS) -c -o $@ $<

all:	$(NAMESERV) $(NAME) $(NAMEGEN)

clean:
	@echo -n -e "[ \e[1m\e[92mOK\e[0m ]"
	@echo "Removing OBJ files ..."
	@$(RM) $(OBJ)
	@$(RM) $(OBJSERV)
	@$(RM) $(OBJGEN)

fclean:	clean
	@echo -n -e "[ \e[1m\e[92mOK\e[0m ]"
	@echo "Deleting binaries ..."
	@$(RM) $(NAME)
	@$(RM) $(NAMESERV)
	@$(RM) $(NAMEGEN)

re:	fclean all

.PHONY:	all clean fclean re
