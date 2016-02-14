DEBUG=			yes

GAME_PREFIX=		src/game/

GAME_FILES=		main.cpp	\
			free.cpp

SERV_PREFIX=		src/server/

SERV_FILES=		test.cpp

ENGINE_PREFIX=		src/engine/

ENGINE_FILES=

TOOLS_PREFIX=		src/tools/

TOOLS_FILES=

GAME=			$(addprefix $(GAME_PREFIX),$(GAME_FILES))

SERVER=			$(addprefix $(SERV_PREFIX),$(SERV_FILES))

ENGINE=			$(addprefix $(ENGINE_PREFIX),$(ENGINE_FILES))

TOOLS=			$(addprefix $(TOOLS_PREFIX),$(TOOLS_FILES))

#GAME+=			$(TOOLS)

#GAME+=			$(ENGINE)

SERVER+=		$(TOOLS)

NAME=			game

NAMESERV=		server_game

HEAD=			-Iinclude

ifeq ($(DEBUG), yes)
	CXXFLAGS= $(HEAD) -W -Wall -Wextra -g -D DEBUG
	CFLAGS= $(HEAD) -W -Wall -Wextra -g -D DEBUG
else
	CXXFLAGS= $(HEAD) -W -Wall -Wextra
	CFLAGS= $(HEAD) -W -Wall -Wextra
endif

CC=			gcc

CXX=			clang

RM=			rm -f

LIB=			-lstdc++	\
			-lpthread	\
			-lSDL		\
			-lSDL2		\
			-lGL		\
			-lGLEW

OBJ=			$(GAME:.cpp=.o)

OBJSERV=		$(SERVER:.cpp=.o)

$(NAMESERV):	$(NAME) $(OBJSERV)
	@echo -n "[ "
	@tput setaf 2; tput bold; echo -n "OK" ; tput sgr0
	@echo -n " ] "
	@echo "Compiled server"
	@$(CXX) $(OBJSERV) -o $(NAMESERV) $(LIB)

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
	@tput setaf 2; tput bold; echo -n "OK" ; tput sgr0
	@echo -n " ] "
	@echo "Compiled game"
	@$(CXX) $(OBJ) -o $(NAME) $(LIB)

%.o:	%.c
	@echo -n "[ "
	@tput setaf 2; tput bold; echo -n "OK" ; tput sgr0
	@echo -n " ] "
	@echo "Compiling" $<
	@$(CXX) $(CXXFLAGS) -c -o $@ $<

all:	$(NAME) $(NAMESERV)

clean:
	@echo -n "[ "
	@tput setaf 2; tput bold; echo -n "OK"; tput sgr0
	@echo -n " ] "
	@echo "Removing OBJ files ..."
	@$(RM) $(OBJ)
	@$(RM) $(OBJSERV)

fclean:	clean
	@echo -n "[ "
	@tput setaf 2; tput bold; echo -n "OK" ; tput sgr0
	@echo -n " ] "
	@echo "Deleting binaries ..."
	@$(RM) $(NAME)
	@$(RM) $(NAMESERV)

re:	fclean all

.PHONY:	all clean fclean re
