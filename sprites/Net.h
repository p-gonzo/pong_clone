#pragma once

#include <SDL2/SDL.h>

class Net
{
private:
    Net() {};
    Net( const Net& );
    const Net& operator=( const Net& );
    
    SDL_Renderer *renderer;

public:
    static Net& GetInstance();
    void SetRenderer( SDL_Renderer *r );
    void Draw();
};