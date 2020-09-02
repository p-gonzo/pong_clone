#pragma once

#include <SDL2/SDL.h>

#include "Vec2.h"

class Ball
{
public:
	Ball( Vec2 position );
	void Draw( SDL_Renderer* renderer );

	Vec2 position;
	SDL_Rect rect;
    
    static constexpr auto diameter { 15 };
    static constexpr auto radius { diameter / 2.0f };
};