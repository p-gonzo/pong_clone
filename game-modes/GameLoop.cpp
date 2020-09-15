#include "GameLoop.h"

#include <chrono>
#include <exception>
#include <iostream>

#include "../constants/Constants.h"

GameLoop::GameLoop()
{
    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
    {
        std::cout <<  "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        throw std::exception();;
    }

    if ( TTF_Init() < 0 )
    {
        std::cout <<  "TTF could not initialize! TTF_Error: " << TTF_GetError() << std::endl;
        throw std::exception();;
    }

    if ( Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0 )
    {
        std::cout <<  "Mixer could not initialize! TTF_Error: " << TTF_GetError() << std::endl;
        throw std::exception();;
    }

    _window = SDL_CreateWindow( "Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Constants::WindowWidth, Constants::WindowHeight, SDL_WINDOW_SHOWN );
    if( _window == NULL )
    {
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        throw std::exception();;
    }

    _renderer = SDL_CreateRenderer( _window, -1, 0 );

    _scoreFont = TTF_OpenFont( "assets/DejaVuSansMono.ttf", 40 );

    _wallHitSound = Mix_LoadWAV( "assets/WallHit.wav" );
    if ( _wallHitSound == NULL )
    {
        std::cout <<  "Mixer could not load wall hit! TTF_Error: " << TTF_GetError() << std::endl;
        throw std::exception();;
    }
    _paddleHitSound = Mix_LoadWAV( "assets/PaddleHit.wav" );
    if ( _paddleHitSound == NULL )
    {
        std::cout <<  "Mixer could not load paddle hit! TTF_Error: " << TTF_GetError() << std::endl;
        throw std::exception();;
    }
    
    _net.SetRenderer( _renderer );
}

GameLoop::~GameLoop()
{
    Mix_FreeChunk( _wallHitSound );
    Mix_FreeChunk( _paddleHitSound );
    SDL_DestroyRenderer( _renderer );
    SDL_DestroyWindow( _window );
    TTF_CloseFont( _scoreFont );
    Mix_Quit();
    TTF_Quit();
    SDL_Quit();
}

void GameLoop::Run()
{
    while ( _running )
    {
        auto startTime = std::chrono::high_resolution_clock::now();
        HandleEvents();
        UpdateAll();
        HandleSounds();
        DrawAll();
        auto stopTime = std::chrono::high_resolution_clock::now();
        _dt = std::chrono::duration<float, std::chrono::milliseconds::period>(stopTime - startTime).count();
    }
}

void GameLoop::HandleSounds()
{
    if ( _collisionType == CollisionType::Paddle ) { Mix_PlayChannel( -1, _paddleHitSound, 0 ); }
    else if ( _collisionType == CollisionType::Wall ) { Mix_PlayChannel( -1, _wallHitSound, 0 ); }
}