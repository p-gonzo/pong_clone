OBJS = sprites/Vec2.cpp sprites/Ball.cpp sprites/Paddle.cpp sprites/PlayerScore.cpp sprites/Net.cpp game.cpp
CC = g++
# -w suppresses all warnings
COMPILER_FLAGS = -w -std=c++17
LINKER_FLAGS = -lSDL2 -lSDL2_ttf -lSDL2_mixer
#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = build/Pong
all : $(OBJS)
	$(CC) $(COMPILER_FLAGS) -o $(OBJ_NAME) $(OBJS) $(LINKER_FLAGS)
nn : neural-network/nn_test.cpp
	$(CC) $(COMPILER_FLAGS) -o build/nn_test neural-network/nn_test.cpp