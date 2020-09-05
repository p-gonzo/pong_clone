#pragma once

#include <SDL2/SDL.h>

#include "Vec2.h"

class Ball
{
public:
	Ball( Vec2 position, int diameter );
	void Draw( SDL_Renderer* renderer );

	Vec2 position;
	SDL_Rect rect;
};