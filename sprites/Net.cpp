#include "Net.h"

#include "../constants/Constants.h"

Net& Net::GetInstance()
{
    static Net onlyInstance;
    return onlyInstance;
}

void Net::SetRenderer( SDL_Renderer *r )
{
    renderer = r;
}

void Net::Draw( const Rgba &color )
{
    SDL_SetRenderDrawColor( renderer, color.r, color.g, color.b, color.a );
    for ( int y = 0; y < Constants::WindowHeight; ++y )
    {
        if ( y % 5 == 0 )
        {
            SDL_RenderDrawPoint( renderer, Constants::WindowWidth / 2, y);
        }
    }
}