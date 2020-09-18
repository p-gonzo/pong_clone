#pragma once

#include <vector>

#include "GameLoop.h"

#include "../constants/Constants.h"
#include "../sprites/Ball.h"
#include "../sprites/Paddle.h"
#include "../sprites/PlayerScore.h"
#include "../structs/Rgba.h"
#include "../neural-network/PaddleBrain.h"


class NeuroEvolutionTraining final: public GameLoop
{
public:
    NeuroEvolutionTraining();

    PaddleBrain GetPaddleBrain();

protected:

virtual void HandleGameEvents();
virtual void UpdateAll();
virtual void DrawAll();

    Paddle _randomWall;
    PlayerScore _generations;
    PlayerScore _hits;

    std::vector<Ball> _balls;
    std::vector<Paddle> _paddles;
    std::vector<Rgba> _colors;
    std::vector<PaddleBrain> _brains;

    std::random_device _randomSeed;

    const int _numberOfPaddles = Constants::TrainingPaddles;

private:
    float Transpose( float value, float leftMin, float leftMax, float rightMin, float rightMax ) const;
    void CloneAndMutatePaddleBrain();
    void PushPaddlesBallsAndColors();
    void RestartTraining();
};