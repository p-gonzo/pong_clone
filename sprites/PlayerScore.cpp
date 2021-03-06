#include <string>

#include "PlayerScore.h"

PlayerScore::PlayerScore( Vec2 pos, SDL_Renderer *rndr, TTF_Font *fnt )
    : renderer( rndr ), font ( fnt )
{
    SetTextures();
    rect.x = static_cast<int>( pos.x );
    rect.y = static_cast<int>( pos.y );
    
}

PlayerScore::~PlayerScore()
{
    CleanUpTextures();
}

void PlayerScore::Draw()
{
    SDL_RenderCopy( renderer, texture, nullptr, &rect );
}

void PlayerScore::Increment()
{
    SetScore( value + 1);
}

void PlayerScore::Clear()
{
    SetScore( 0 );
}

void PlayerScore::SetScore( int newScore )
{
    value = newScore;
    CleanUpTextures();
    SetTextures();
}

void PlayerScore::SetTextures()
{
    surface = TTF_RenderText_Solid( font, std::to_string(value).c_str(), { 0xFF, 0xFF, 0xFF, 0xFF });
    texture = SDL_CreateTextureFromSurface( renderer, surface );

    int width;
    int height;
    SDL_QueryTexture( texture, nullptr, nullptr, &width, &height );
    rect.w = width;
    rect.h = height;
}

void PlayerScore::CleanUpTextures()
{
    SDL_FreeSurface( surface );
    SDL_DestroyTexture( texture );
}
