OBJS = assets/Vec2.cpp assets/Ball.cpp assets/Paddle.cpp assets/PlayerScore.cpp assets/Net.cpp pong.cpp
CC = g++
# -w suppresses all warnings
COMPILER_FLAGS = -w -std=c++17
LINKER_FLAGS = -lSDL2 -lSDL2_ttf
#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = pong
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)