#include "Paddle.h"
#include "../Constants.h"

Paddle::Paddle( Vec2 pos, Vec2 vel, SDL_Renderer *renderer, int height, int width )
    : position( pos ), velocity( vel ), renderer( renderer )
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

void Paddle::Update(float dt)
{
    position += velocity * dt;
    if ( position.y < 0 ) { position.y = 0; }
    if ( position.y > ( Constants::WindowHeight - Constants::PaddleHeight ) )
    {
        position.y = Constants::WindowHeight - Constants::PaddleHeight;
    }
}