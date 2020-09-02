#include "Net.h"

void Net::Draw( SDL_Renderer* renderer, int windowHeight, int windowWidth )
{
    for ( int y = 0; y < windowHeight; ++y )
    {
        if ( y % 5 == 0 )
        {
            SDL_RenderDrawPoint( renderer, windowWidth / 2, y);
        }
    }
}