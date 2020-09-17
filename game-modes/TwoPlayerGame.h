#pragma once

#include "GameLoop.h"

#include "../sprites/Ball.h"
#include "../sprites/Paddle.h"
#include "../sprites/PlayerScore.h"


class TwoPlayerGame final: public GameLoop
{
public:
    TwoPlayerGame();

protected:

virtual void HandleGameEvents();
virtual void UpdateAll();
virtual void DrawAll();

    Ball _ball;
    Paddle _p1Paddle;
    Paddle _p2Paddle;
    PlayerScore _p1Score;
    PlayerScore _p2Score;

    bool _playerButtonStates[4];
};