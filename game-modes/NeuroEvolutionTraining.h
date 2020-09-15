#pragma once

#include <vector>

#include "GameLoop.h"

#include "../sprites/Ball.h"
#include "../sprites/Net.h"
#include "../sprites/Paddle.h"
#include "../sprites/PlayerScore.h"
#include "../structs/Rgba.h"
#include "../neural-network/PaddleBrain.h"


class NeuroEvolutionTraining final: public GameLoop
{
public:
    NeuroEvolutionTraining();

protected:

virtual void HandleEvents();
virtual void UpdateAll();
virtual void HandleSounds();
virtual void DrawAll();

    std::vector<Ball> _balls;
    Paddle _randomWall;
    std::vector<Paddle> _p2Paddles;
    PlayerScore _generations;
    PlayerScore _hits;
    std::vector<PaddleBrain> _brains;
    std::vector<Rgba> _colors;
    Net &_net { Net::GetInstance() };

    std::random_device randomSeed;
};