#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "../constants/Enums.h"
#include "../sprites/Net.h"

class GameLoop
{
public:
    GameLoop();
    void Run();

    virtual ~GameLoop();

protected:
    virtual void HandleEvents() = 0;
    virtual void UpdateAll() = 0;
    virtual void DrawAll() = 0;

    void HandleSounds();

    SDL_Window* _window;
    SDL_Renderer* _renderer;
    TTF_Font* _scoreFont;
    Mix_Chunk* _wallHitSound;
    Mix_Chunk* _paddleHitSound;

    SDL_Event _event;
    CollisionType _collisionType;

    Net &_net { Net::GetInstance() };

    bool _running { true };
    float _dt { 0.0f };
};