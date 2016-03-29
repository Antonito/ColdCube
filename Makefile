DEBUG=			yes

GAME_PREFIX=		src/game/

GAME_FILES=		main.cpp			\
			free.cpp			\
			menus/menu.cpp			\
			menus/main_menu.cpp		\
			menus/options_menu.cpp

SERV_PREFIX=		src/server/

SERV_FILES=		main.c				\
			udp/udp_server_pseudo.c		\
			udp/main_udp_thread.c		\
			udp/server_udp_msg.c		\
			tcp/main_tcp_thread.c		\
			tcp/server_tcp_functions.c	\
			tcp/server_tcp_msg.c		\
			tcp/tcp_server_pseudo.c		\

ENGINE_PREFIX=		src/engine/

ENGINE_FILES=		chunk.cpp			\
			display.cpp			\
			load_shader.cpp			\
			map.cpp				\
			mesh.cpp			\
			shader.cpp			\
			texture.cpp			\
			engine.cpp

ENGINE_C_FILES=		cload_chunk.c

TOOLS_PREFIX=		src/tools/

TOOLS_FILES=		text.cpp			\
			udpPacket.cpp			\
			sendUdpPacket.cpp		\
			udp_client.cpp			\
			check_package.cpp		\
			tcp_client.cpp

GAME=			$(addprefix $(GAME_PREFIX),$(GAME_FILES))

SERVER=			$(addprefix $(SERV_PREFIX),$(SERV_FILES))

ENGINE=			$(addprefix $(ENGINE_PREFIX),$(ENGINE_FILES))

TOOLS=			$(addprefix $(TOOLS_PREFIX),$(TOOLS_FILES))

ENGINE_C=		$(addprefix $(ENGINE_PREFIX),$(ENGINE_C_FILES))

TOOLS_C=		$(addprefix $(TOOLS_PREFIX),$(TOOLS_C_FILES))

GAME+=			$(TOOLS)

GAME+=			$(ENGINE)

#SERVER+=		$(TOOLS)

NAME=			coldcube

NAMESERV=		server_game

HEAD=			-Iinclude

CXXFLAGS= $(HEAD) -W -Wall -Wextra

CFLAGS= $(HEAD) -W -Wall -Wextra

ifeq ($(DEBUG), yes)

CXXFLAGS+= -g -D DEBUG

CFLAGS+= -g -D DEBUG

endif

CC=			gcc

CXX=			clang

RM=			rm -f

LIB=			-lstdc++	\
			-lpthread	\
			-lSDL2		\
			-lGL		\
			-lm		\
			-lGLEW		\
			-lglut		\
			-lX11

OBJ=			$(GAME:.cpp=.o)

OBJ+=			$(ENGINE_C:.c=.o)

OBJSERV=		$(SERVER:.c=.o)

$(NAMESERV):	$(OBJSERV)
	@echo -n "[ "
	@echo -n -e "\e[1m\e[92mOK\e[0m"
	@echo -n " ] "
	@echo "Compiled server"
	@$(CC) $(OBJSERV) -o $(NAMESERV) $(LIB)

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
	@echo -n "[ "
	@echo -n -e "\e[1m\e[92mOK\e[0m"
	@echo -n " ] "
	@echo "Compiled game"
	@$(CXX) $(OBJ) -o $(NAME) $(LIB)

%.o:	%.c
	@echo -n "[ "
	@echo -n -e "\e[1m\e[92mOK\e[0m"
	@echo -n " ] "
	@echo "Compiling" $<
	@$(CC) $(CFLAGS) -c -o $@ $<

%.o:	%.cpp
	@echo -n "[ "
	@echo -n -e "\e[1m\e[92mOK\e[0m"
	@echo -n " ] "
	@echo "Compiling" $<
	@$(CXX) $(CXXFLAGS) -c -o $@ $<

all:	$(NAMESERV) $(NAME)

clean:
	@echo -n "[ "
	@echo -n -e "\e[1m\e[92mOK\e[0m"
	@echo -n " ] "
	@echo "Removing OBJ files ..."
	@$(RM) $(OBJ)
	@$(RM) $(OBJSERV)

fclean:	clean
	@echo -n "[ "
	@echo -n -e "\e[1m\e[92mOK\e[0m"
	@echo -n " ] "
	@echo "Deleting binaries ..."
	@$(RM) $(NAME)
	@$(RM) $(NAMESERV)

re:	fclean all

.PHONY:	all clean fclean re
