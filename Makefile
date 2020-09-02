OBJS = assets/Vec2.cpp assets/Ball.cpp assets/Net.cpp pong.cpp
CC = g++
# -w suppresses all warnings
COMPILER_FLAGS = -w -g -std=c++17
LINKER_FLAGS = -lSDL2
#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = pong
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)