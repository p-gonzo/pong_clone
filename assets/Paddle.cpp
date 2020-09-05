#include "Paddle.h"

Paddle::Paddle( Vec2 pos, SDL_Renderer *renderer, int height, int width )
    : position( pos ), renderer( renderer )
{
    rect.x = static_cast<int>( position.x );
    rect.y = static_cast<int>( position.y );
    rect.h = height;
    rect.w = width;
}

void Paddle::Draw()
{
    rect.y = static_cast<int>( position.y );
    SDL_RenderFillRect( renderer, &rect );
}