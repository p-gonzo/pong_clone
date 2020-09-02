#pragma once

#include <SDL2/SDL.h>

class Net
{
private:
    Net();
public:
    static void Draw( SDL_Renderer* renderer, int windowHeight, int windowWidth );
};