#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "../structs/Vec2.h"
#include "../structs/Rgba.h"

class PlayerScore
{
public:
    PlayerScore( Vec2 position, SDL_Renderer* renderer, TTF_Font* font );

    ~PlayerScore();
    void Draw( const Rgba &color );
    void Increment();
    void Clear();

    SDL_Renderer* renderer;
    TTF_Font* font;
    SDL_Surface* surface{};
    SDL_Texture* texture{};
    SDL_Rect rect{};
    int value { 0 };

private:
    void SetScore( int newScore );
    void SetTextures();
    void CleanUpTextures();

};