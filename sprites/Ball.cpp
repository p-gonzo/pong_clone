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

    HandlePaddleCollision( p1Paddle, position.x, position.x + Constants::BallWidth, position.y, position.y + Constants::BallHeight );
    HandlePaddleCollision( p2Paddle, position.x, position.x + Constants::BallWidth, position.y, position.y + Constants::BallHeight );
    HandleWallCollision( position.y, position.y + Constants::BallHeight );
    HandleGoal();
}
void Ball::HandleWallCollision( const float top, const float bottom )
{
    if ( position.y >= Constants::WindowHeight || position.y <= 0 )
    {
        float penetration = velocity.y < 0 ? -top : Constants::WindowHeight - bottom;
        position.y += penetration;
        
        velocity.y = -velocity.y;
    }
}

void Ball::HandleGoal()
{
    if ( position.x >= Constants::WindowWidth || position.x <= 0 )
    {
        velocity.y = 0.0f;
        velocity.x = 1.0f;
        position.x = ( Constants::WindowWidth / 2.0f ) - ( Constants::BallWidth / 2.0f );
        position.y = ( Constants::WindowHeight / 2.0f ) - ( Constants::BallHeight / 2.0f );
    }
}

void Ball::HandlePaddleCollision( const Paddle &paddle, const float left, const float right, const float top, const float bottom )
{

    float paddleLeft = paddle.position.x;
    float paddleRight = paddle.position.x + Constants::PaddleWidth;
    float paddleTop = paddle.position.y;
    float paddleBottom = paddle.position.y + Constants::PaddleHeight;

    if ( left < paddleRight && right > paddleLeft && top < paddleBottom && bottom > paddleTop )
    {
        float penetration = velocity.x < 0 ? paddleRight - left : paddleLeft - right;
        position.x += penetration;

        float ballYCenter = ( top + bottom ) / 2;
        float paddleYCenter = ( paddleTop + paddleBottom ) / 2;
        float ballPaddleYDelta = ballYCenter - paddleYCenter;
        velocity.y = ( ballPaddleYDelta / ( 1 + ballPaddleYDelta ) ) * ( ballPaddleYDelta > 0 ? 1 : -1 );
        velocity.y *= Constants::BallXDeltaScalar;

        velocity.x = -velocity.x;
    }
}