#pragma once

#include <SDL2/SDL.h>

#include "Vec2.h"

class Paddle
{
public:
    Paddle( Vec2 position, Vec2 velocity, SDL_Renderer *renderer, int height, int width );
    void Draw();
    void Update( const bool pressedUp, const bool pressedDown, const float dt );
    
    Vec2 position;
    Vec2 velocity;
    SDL_Rect rect {};
    SDL_Renderer *renderer;
};