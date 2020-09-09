OBJS = sprites/Vec2.cpp sprites/Ball.cpp sprites/Paddle.cpp sprites/PlayerScore.cpp sprites/Net.cpp game.cpp
CC = g++
# -w suppresses all warnings
COMPILER_FLAGS = -w -std=c++17
LINKER_FLAGS = -lSDL2 -lSDL2_ttf -lSDL2_mixer
#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = Pong
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)