#include "PlayerScore.h"

PlayerScore::PlayerScore( Vec2 pos, SDL_Renderer *rndr, TTF_Font *fnt )
    : renderer( rndr ), font ( fnt )
{
    surface = TTF_RenderText_Solid( font, "0", { 0xFF, 0xFF, 0xFF, 0xFF });
    texture = SDL_CreateTextureFromSurface( renderer, surface );

    int width;
    int height;
    SDL_QueryTexture( texture, nullptr, nullptr, &width, &height );

    rect.x = static_cast<int>( pos.x );
    rect.y = static_cast<int>( pos.y );
    rect.h = static_cast<int>( height );
    rect.w = static_cast<int>( width );
}

PlayerScore::~PlayerScore()
{
    SDL_FreeSurface( surface );
    SDL_DestroyTexture( texture );
}

void PlayerScore::Draw()
{
    SDL_RenderCopy( renderer, texture, nullptr, &rect );
}