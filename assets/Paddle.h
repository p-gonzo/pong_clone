#pragma once

#include <SDL2/SDL.h>

#include "Vec2.h"

class Paddle
{
public:
    Paddle( Vec2 position, SDL_Renderer *renderer, int height, int width );
    void Draw();
    
    Vec2 position;
    SDL_Rect rect {};
    SDL_Renderer *renderer;
};