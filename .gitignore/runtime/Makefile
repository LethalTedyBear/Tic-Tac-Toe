OBJS = ..\src\main.cpp ..\src\Game.cpp

CC = g++

INCLUDE_PATHS = -IC:\Libraries\SDL2\include

LIBRARY_PATHS = -LC:\Libraries\SDL2\lib\x86

COMPILER_FLAGS = -w -W -s
#-subsystem,windows

LINKER_FLAGS = -lSDL2_image -lSDL2main -lSDL2 
OBJ_NAME = game

all : $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

