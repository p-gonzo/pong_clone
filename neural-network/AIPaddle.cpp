#include "AIPaddle.h"
#include "../constants/Constants.h"
#include "Enums.h"
#include "PaddleBrain.h"
#include <vector>
#include <iostream>

AIPaddle::AIPaddle(Vec2 position, Vec2 velocity, SDL_Renderer *renderer, int height, int width ):
    Paddle(position, velocity, renderer, height, width)
{
    previousPosition.x = position.x;
    previousPosition.y = position.y;
}
void AIPaddle::AutoUpdate( const Ball &ball, const float dt )
{
    auto own_delta = previousPosition.y - position.y;
    auto own_center = Transpose( ( position.y + position.y + Constants::PaddleHeight ) / 2.0f, 50, 670, -1, 1);
    auto x_delta =  Transpose( position.x - ball.position.x, 0, 1280, -1, 1 );

    // Todo - Rethink these values
    auto y1_delta = Transpose( position.y - ( ball.position.y + Constants::BallHeight ), -1280, 1165, -1, 1 );
    auto y2_delta = Transpose( ( position.y + Constants::PaddleHeight ) - ball.position.y, -1280, 1165, -1, 1 ); 

    // std::cout << own_delta << " " << own_center << " " << x_delta << " " << y1_delta << " " << y2_delta << std::endl;

    // Todo - Determine what will be sent up.
    auto action = brain.Predict(std::vector<float> { own_center, x_delta, y1_delta, y2_delta });

    if ( action == Prediction::Up ) { velocity.y = -Constants::PaddleSpeed; }
    else if ( action == Prediction::Down ) { velocity.y = Constants::PaddleSpeed; }
    else { velocity.y = 0.0f; }

    previousPosition.y = position.y;

    position += velocity * dt;
    if ( position.y < 0 ) { position.y = 0; }
    if ( position.y > ( Constants::WindowHeight - Constants::PaddleHeight ) )
    {
        position.y = Constants::WindowHeight - Constants::PaddleHeight;
    }
}

float AIPaddle::Transpose( float value, float leftMin, float leftMax, float rightMin, float rightMax )
{
    float leftSpan = leftMax - leftMin;
    float rightSpan = rightMax - rightMin;
    float valueScaled = ( value - leftMin ) / leftSpan;
    return rightMin + ( valueScaled * rightSpan );
}
