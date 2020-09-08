#pragma once

#include <SDL2/SDL.h>

#include "Vec2.h"

class Ball
{
public:
	Ball( Vec2 position, SDL_Renderer* renderer, int diameter );
	void Draw();

	Vec2 position;
	SDL_Renderer* renderer;
	SDL_Rect rect;
};