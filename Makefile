##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## Makefile
##

CORE_SRC    =   src/DLLoader.cpp	\
				src/ErrorHandling.cpp	\
				src/Arcade.cpp		\

GRAPHICS_SRC = 	src/Modules/Graphics.cpp	\
				src/Modules/Graphics/NCursesModule.cpp	\
				src/Modules/Graphics/SFMLModule.cpp	\
				src/Modules/Graphics/SDLModule.cpp

GAMES_SRC = 	src/Modules/Games/SnakeModule.cpp	\
				src/Modules/Games/NibblerModule.cpp	\

MAIN =  src/main.cpp    \

BINARY = arcade

INCLUDE = -Iinclude -Iinclude/Modules/Games -Iinclude/Modules/Graphics

CORE_OBJ = $(MAIN:.cpp=.o) $(CORE_SRC:.cpp=.o)

GRAPHICS_OBJ = $(GRAPHICS_SRC:%.cpp=%.o)

GAME_OBJ = $(GAMES_SRC:%.cpp=%.o)

CFLAGS  += -std=c++20 -Wextra

COMPILER	= 	g++

SFML = -L/usr/local/lib/ -lsfml-graphics -lsfml-window -lsfml-system

NCURSES = -lncurses

SDL2 = -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf

all:	core	games	graphicals

core:   $(CORE_OBJ)
	@$(COMPILER) -o $(BINARY) $(CORE_OBJ) -ldl $(INCLUDE)
	@make -s COMPLETE_TEXT

games:	CFLAGS += -fPIC
games:	$(GAME_OBJ)
	$(COMPILER) -shared -o lib/arcade_snake.so src/Modules/Games/SnakeModule.o $(INCLUDE) $(NCURSES)
	$(COMPILER) -shared -o lib/arcade_nibbler.so src/Modules/Games/NibblerModule.o $(INCLUDE) $(NCURSES)

graphicals: CFLAGS += -fPIC
graphicals: $(GRAPHICS_OBJ)
	$(COMPILER) -shared -o lib/arcade_ncurses.so src/Modules/Graphics/NCursesModule.o src/Modules/Graphics.o $(INCLUDE) $(NCURSES)
	$(COMPILER) -shared -o lib/arcade_sfml.so src/Modules/Graphics/SFMLModule.o src/Modules/Graphics.o $(INCLUDE) $(SFML)
	$(COMPILER) -shared -o lib/arcade_sdl2.so src/Modules/Graphics/SDLModule.o src/Modules/Graphics.o $(INCLUDE) $(SDL2)

COMPLETE_TEXT:
	@$(ECHO) $(BOLD) $(BLUE)"BUILD COMPELTED 🏗️"

CLEAN_TEXT:
	@$(ECHO) $(BOLD) $(BLUE)"CLEANING 🧽"

debug:      CFLAGS += -g
debug:      re

clean:
	@make -s CLEAN_TEXT
	@rm -f $(GAME_OBJ)
	@rm -f $(CORE_OBJ)
	@rm -f $(GRAPHICS_OBJ)
	@rm -f vgcore*
	@rm -f *.gch

fclean:     clean
	@rm -f $(BINARY)
	@rm -f lib/*

re:         fclean  all

.PHONY:     clean fclean re game

%.o :	%.cpp
	@$(COMPILER) -c -o $@ $^ $(CFLAGS) $(INCLUDE) && \
    $(ECHO) -n $(BOLD) $(GREEN)"  [OK] "$(WHITE) || \
    $(ECHO) -n $(BOLD) $(RED)"  [KO] "$(WHITE) && \
    $(ECHO) $(BOLD) $< | rev | cut -d/ -f 1 | rev && \
    $(ECHO) -n $(DEFAULT)

ECHO    =       /bin/echo -e
DEFAULT =       "\033[00m"

DEFAULT =       "\e[0m"
BOLD    =       "\e[1m"
DIM     =       "\e[2m"
UNDLN   =       "\e[4m"
SHINE   =       "\e[5;37m"
RODE    =       "\e[9;37m"

BLACK   =       "\e[30m"
RED     =       "\e[31m"
GREEN   =       "\e[32m"
YELLOW  =       "\e[33m"
BLUE    =       "\e[34m"
MAGEN   =       "\e[35m"
CYAN    =       "\e[36m"
WHITE   =       "\e[1;37m"

LIGHT_RED       =       "\e[91m"
LIGHT_GREEN     =       "\e[92m"
LIGHT_YELLOW    =       "\e[93m"
LIGHT_BLUE      =       "\e[94m"
LIGHT_MAGEN     =       "\e[95m"
LIGHT_CYAN      =       "\e[96m"
