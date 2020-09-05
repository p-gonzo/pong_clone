#pragma once

#include <SDL2/SDL.h>

#include "Vec2.h"

class Paddle
{
public:
    Paddle( Vec2 position, int height, int width );
    void Draw( SDL_Renderer *renderer );
    
    Vec2 position;
    SDL_Rect rect {};
};