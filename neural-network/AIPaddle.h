#pragma once

#include "../sprites/Paddle.h"
#include "../sprites/Ball.h"
#include "PaddleBrain.h"

class AIPaddle: public Paddle
{
public:
    AIPaddle(Vec2 position, Vec2 velocity, SDL_Renderer *renderer, int height, int width );
    
    void AutoUpdate( const Ball &ball, const float dt );

private:
    float Transpose(float value, float leftMin, float leftMax, float rightMin, float rightMax);
    
    Vec2 previousPosition;
    PaddleBrain brain { 1 };
};