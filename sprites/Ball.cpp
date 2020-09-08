#include "Ball.h"
#include "../constants/Constants.h"

Ball::Ball( Vec2 pos, Vec2 vel, SDL_Renderer* renderer, int diameter )
    :position( pos ), velocity ( vel ), renderer( renderer )
{
    rect.x = static_cast<int>( position.x );
    rect.y = static_cast<int>( position.y );
    rect.h = diameter;
    rect.w = diameter;
}

void Ball::Draw()
{
    rect.x = static_cast<int>( position.x );
    rect.y = static_cast<int>( position.y );
    SDL_RenderFillRect( renderer, &rect );
}

void Ball::Update( const Paddle &p1Paddle, const Paddle &p2Paddle, const float dt )
{
    position += velocity * dt;
    if ( CheckPaddleCollision( p1Paddle ) || CheckPaddleCollision( p2Paddle ) ) { velocity.x = -velocity.x; }
}

bool Ball::CheckPaddleCollision(const Paddle &paddle)
{
    float ballLeft = position.x;
    float ballRight = position.x + Constants::BallWidth;
    float ballTop = position.y;
    float ballBottom = position.y + Constants::BallHeight;

    float paddleLeft = paddle.position.x;
    float paddleRight = paddle.position.x + Constants::PaddleWidth;
    float paddleTop = paddle.position.y;
    float paddleBottom = paddle.position.y + Constants::PaddleHeight;

    if ( ballLeft >= paddleRight ) { return false; }
    if ( ballRight <= paddleLeft ) { return false; }
    if ( ballTop >= paddleBottom ) { return false; }
    if ( ballBottom <= paddleTop ) { return false; }

    return true;
}