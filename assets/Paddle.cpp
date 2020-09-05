#include "Paddle.h"

Paddle::Paddle( Vec2 pos, int height, int width )
    : position( pos )
{
    rect.x = static_cast<int>( position.x );
    rect.y = static_cast<int>( position.y );
    rect.h = height;
    rect.w = width;
}

void Paddle::Draw( SDL_Renderer *renderer )
{
    rect.y = static_cast<int>( position.y );
    SDL_RenderFillRect( renderer, &rect );
}