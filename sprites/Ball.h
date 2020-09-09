#pragma once

#include <SDL2/SDL.h>

#include <chrono>

#include "../constants/Enums.h"
#include "Paddle.h"
#include "Vec2.h"

class Ball
{
public:
    Ball( Vec2 position, Vec2 velocity, SDL_Renderer* renderer, int diameter );
    void Draw();
    CollisionType Update( const Paddle &p1Paddle, const Paddle &p2Paddle, const float dt );

    Vec2 position;
    Vec2 velocity;
    SDL_Renderer* renderer;
    SDL_Rect rect;

private:
    void HandlePaddleCollision( const Paddle &paddle, const float left, const float right, const float top, const float bottom );
    void HandleWallCollision( const float top, const float bottom );
    void HandleGoal();

    bool _inPlay { true };
    static constexpr auto secondsBeforeInPay { 1.0f };
    std::chrono::time_point<std::chrono::system_clock> _timeScored;
    CollisionType _collision { CollisionType::None };
};