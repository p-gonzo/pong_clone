OBJS = game-modes/GameLoop.cpp game-modes/TwoPlayerGame.cpp game-modes/NeuroEvolutionTraining.cpp structs/Vec2.cpp sprites/Ball.cpp sprites/Paddle.cpp sprites/PlayerScore.cpp sprites/Net.cpp neural-network/PaddleBrain.cpp main.cpp
CC = g++
# -w suppresses all warnings
COMPILER_FLAGS = -w -std=c++17
LINKER_FLAGS = -lSDL2 -lSDL2_ttf -lSDL2_mixer
OBJ_NAME = build/Pong
all : $(OBJS)
	$(CC) $(COMPILER_FLAGS) -o $(OBJ_NAME) $(OBJS) $(LINKER_FLAGS)