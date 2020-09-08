#include <iostream>
#include <chrono>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "constants/Constants.h"
#include "constants/Enums.h"
#include "sprites/Ball.h"
#include "sprites/Net.h"
#include "sprites/Paddle.h"
#include "sprites/PlayerScore.h"
#include "sprites/Vec2.h"

void handleEvents( SDL_Event &event, bool &running, bool buttons[4] )
{
    while ( SDL_PollEvent( &event ) )
    {
        if ( event.type == SDL_QUIT ) running = false;
        else if ( event.type == SDL_KEYDOWN )
        {
            if ( event.key.keysym.sym == SDLK_ESCAPE ) running = false;
            else if ( event.key.keysym.sym == SDLK_w ) { buttons[Buttons::p1PaddleUp] = true; }
            else if ( event.key.keysym.sym == SDLK_s ) { buttons[Buttons::p1PaddleDown] = true; }
            else if ( event.key.keysym.sym == SDLK_UP ) { buttons[Buttons::p2PaddleUp] = true; }
            else if ( event.key.keysym.sym == SDLK_DOWN ) { buttons[Buttons::p2PaddleDown] = true; }
        }
        else if ( event.type == SDL_KEYUP )
        {
            if ( event.key.keysym.sym == SDLK_w ) { buttons[Buttons::p1PaddleUp] = false; }
            else if ( event.key.keysym.sym == SDLK_s ) { buttons[Buttons::p1PaddleDown] = false; }
            else if ( event.key.keysym.sym == SDLK_UP ) { buttons[Buttons::p2PaddleUp] = false; }
            else if ( event.key.keysym.sym == SDLK_DOWN ) { buttons[Buttons::p2PaddleDown] = false; }
        }
    }
}

void drawAll( SDL_Renderer* renderer, Net &net, Ball &ball, Paddle &p1Paddle, Paddle &p2Paddle, PlayerScore &p1Score, PlayerScore &p2Score )
{
    SDL_SetRenderDrawColor( renderer, 0x0, 0x0, 0xFF, 0xFF );
    SDL_RenderClear( renderer );
    SDL_SetRenderDrawColor( renderer, 0xFF, 0XFF, 0XFF, 0XFF );
    
    net.Draw();
    ball.Draw();
    p1Paddle.Draw();
    p2Paddle.Draw();

    p1Score.Draw();
    p2Score.Draw();

    SDL_RenderPresent( renderer );
}

void updateAll ( Ball &ball, Paddle &p1Paddle, Paddle &p2Paddle, PlayerScore &p1Score, PlayerScore &p2Score, bool buttons[4], float &dt )
{
    p1Paddle.Update( buttons[Buttons::p1PaddleUp], buttons[Buttons::p1PaddleDown], dt );
    p2Paddle.Update( buttons[Buttons::p2PaddleUp], buttons[Buttons::p2PaddleDown], dt );

    ball.Update( p1Paddle, p2Paddle, dt );
}

int main( int argc, char* args[] )
{
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        std::cout <<  "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    if ( TTF_Init() < 0 )
    {
        std::cout <<  "TTF could not initialize! TTF_Error: " << TTF_GetError() << std::endl;
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow( "Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Constants::WindowWidth, Constants::WindowHeight, SDL_WINDOW_SHOWN );
    if( window == NULL )
    {
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_Renderer* renderer { SDL_CreateRenderer( window, -1, 0 ) }; 

    TTF_Font *scoreFont { TTF_OpenFont( "assets/DejaVuSansMono.ttf", 40 ) };

    Net& net { Net::GetInstance() };
    net.SetRenderer( renderer );

    Ball ball(
        Vec2( Constants::WindowWidth / 2.0f - Constants::BallHeight / 2.0f, Constants::WindowHeight / 2.0f - Constants::BallHeight / 2.0f ),
        Vec2( Constants::BallSpeed, 0.0f ),
        renderer,
        Constants::BallHeight
    );
    
    Paddle p1Paddle(
        Vec2( Constants::PaddleGap, Constants::WindowHeight / 2.0f - Constants::PaddleHeight / 2.0f ),
        Vec2( 0.0f, 0.0f ),
        renderer,
        Constants::PaddleHeight,
        Constants::PaddleWidth
    );
    Paddle p2Paddle(
        Vec2( Constants::WindowWidth - Constants::PaddleGap, Constants::WindowHeight / 2.0f - Constants::PaddleHeight / 2.0f ),
        Vec2 (0.0f, 0.0f ),
        renderer,
        Constants::PaddleHeight,
        Constants::PaddleWidth
    );
    
    PlayerScore p1Score( Vec2( Constants::WindowWidth / 4, 20 ), renderer, scoreFont );
    PlayerScore p2Score( Vec2( 3 * Constants::WindowWidth / 4, 20 ), renderer, scoreFont );
    
    bool buttons[4] = {};
    bool running = true;
    float dt = 0.0f;
    while ( running )
    {
        auto startTime = std::chrono::high_resolution_clock::now();

        SDL_Event event;
        handleEvents( event, running, buttons );

        updateAll( ball, p1Paddle, p2Paddle, p1Score, p2Score, buttons, dt );
        drawAll( renderer, net, ball, p1Paddle, p2Paddle, p1Score, p2Score );

        auto stopTime = std::chrono::high_resolution_clock::now();
        dt = std::chrono::duration<float, std::chrono::milliseconds::period>(stopTime - startTime).count();
    }

    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    TTF_CloseFont( scoreFont );
    TTF_Quit();
    SDL_Quit();

    return 0;
}