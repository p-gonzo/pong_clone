#include "Ball.h"
#include "../constants/Constants.h"

#include <iostream>

Ball::Ball( Vec2 pos, Vec2 vel, SDL_Renderer* renderer, int diameter )
    :position( pos ), velocity ( vel ), renderer( renderer )
{
    rect.x = static_cast<int>( position.x );
    rect.y = static_cast<int>( position.y );
    rect.h = diameter;
    rect.w = diameter;
}

void Ball::Draw( const Rgba &color )
{
    SDL_SetRenderDrawColor( renderer, color.r, color.g, color.b, color.a );
    rect.x = static_cast<int>( position.x );
    rect.y = static_cast<int>( position.y );
    SDL_RenderFillRect( renderer, &rect );
}

CollisionType Ball::Update( const Paddle &p1Paddle, const Paddle &p2Paddle, const float dt )
{
    _collision = CollisionType::None;

    if (_inPlay)
    {
        position += velocity * dt;
        HandlePaddleCollision( p1Paddle, position.x, position.x + Constants::BallWidth, position.y, position.y + Constants::BallHeight );
        HandlePaddleCollision( p2Paddle, position.x, position.x + Constants::BallWidth, position.y, position.y + Constants::BallHeight );
        HandleWallCollision( position.y, position.y + Constants::BallHeight );
        HandleGoal();
    }
    else
    {
        std::chrono::duration<float> elapsed_seconds = std::chrono::system_clock::now() - _timeScored; 
        if (elapsed_seconds.count() > secondsBeforeInPay) { _inPlay = true; }
    }
    return _collision;
}

void Ball::HandleWallCollision( const float top, const float bottom )
{
    if ( position.y >= Constants::WindowHeight || position.y <= 0 )
    {
        float penetration = velocity.y < 0 ? -top : Constants::WindowHeight - bottom;
        position.y += penetration;
        
        velocity.y = -velocity.y;
        _collision = CollisionType::Wall;
    }
}

void Ball::HandleGoal()
{
    if ( position.x >= Constants::WindowWidth || position.x <= 0 )
    {
        _collision =  position.x <= 0 ? CollisionType::Left : CollisionType::Right;

        velocity.y = 0.0f;
        velocity.x = _collision == CollisionType::Left ? 1.0f : -1.0f;
        position.x = ( Constants::WindowWidth / 2.0f ) - ( Constants::BallWidth / 2.0f );
        position.y = ( Constants::WindowHeight / 2.0f ) - ( Constants::BallHeight / 2.0f );

        _timeScored = std::chrono::system_clock::now();
        _inPlay = false;
        
    }
}

void Ball::HandlePaddleCollision( const Paddle &paddle, const float left, const float right, const float top, const float bottom )
{

    float paddleLeft = paddle.position.x;
    float paddleRight = paddle.position.x + paddle.rect.w;
    float paddleTop = paddle.position.y;
    float paddleBottom = paddle.position.y + paddle.rect.h;

    if ( left < paddleRight && right > paddleLeft && top < paddleBottom && bottom > paddleTop )
    {
        float penetration = velocity.x < 0 ? paddleRight - left : paddleLeft - right;
        position.x += penetration;

        float ballYCenter = ( top + bottom ) / 2;
        float paddleYCenter = ( paddleTop + paddleBottom ) / 2;


        // Generate a random bounce for training
        bool isWall = paddleBottom - paddleTop == Constants::WindowHeight;
        float ballPaddleYDelta =  isWall ? ( rand() % ( Constants::PaddleHeight * 2 ) ) - Constants::PaddleHeight : ballYCenter - paddleYCenter;

        velocity.y = ( ballPaddleYDelta / ( 1 + ballPaddleYDelta ) ) * ( ballPaddleYDelta > 0 ? 1 : -1 );
        velocity.y *= Constants::BallXDeltaScalar;

        velocity.x = -velocity.x;
        _collision =  velocity.x > 0 ? CollisionType::P1Paddle : CollisionType::P2Paddle;
    }
}