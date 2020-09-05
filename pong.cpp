#include <SDL2/SDL.h>
#include <iostream>

#include "assets/Ball.h"
#include "assets/Net.h"
#include "assets/Paddle.h"
#include "assets/Vec2.h"
#include "Constants.h"

int main( int argc, char* args[] )
{
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        std::cout <<  "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow( "Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Constants::WindowWidth, Constants::WindowHeight, SDL_WINDOW_SHOWN );
    if( window == NULL )
    {
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    Ball ball( Vec2( Constants::WindowWidth / 2.0f - Constants::BallHeight / 2.0f, Constants::WindowHeight / 2.0f - Constants::BallHeight / 2.0f ), Constants::BallHeight );
    Paddle paddleOne( Vec2( Constants::PaddleGap, Constants::WindowHeight / 2.0f - Constants::PaddleHeight / 2.0f ), Constants::PaddleHeight, Constants::PaddleWidth );
    Paddle paddleTwo( Vec2( Constants::WindowWidth - Constants::PaddleGap, Constants::WindowHeight / 2.0f - Constants::PaddleHeight / 2.0f ), Constants::PaddleHeight, Constants::PaddleWidth );

    bool running = true;

    while ( running )
    {
        SDL_Event event;
        while ( SDL_PollEvent( &event ) )
        {
            if ( event.type == SDL_QUIT ) running = false;
            if ( event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE ) running = false;
        }

        SDL_SetRenderDrawColor( renderer, 0x0, 0x0, 0xFF, 0xFF );
        SDL_RenderClear( renderer );

        SDL_SetRenderDrawColor( renderer, 0xFF, 0XFF, 0XFF, 0XFF );
        Net::Draw( renderer, Constants::WindowHeight, Constants::WindowWidth );
        ball.position += Vec2(0.3, 0);
        ball.Draw( renderer );
        paddleOne.Draw ( renderer );
        paddleTwo.Draw ( renderer );

        SDL_RenderPresent( renderer ); // present the "backbuffer"
    }

    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    SDL_Quit();

    return 0;
}