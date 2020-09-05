#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "assets/Ball.h"
#include "assets/Net.h"
#include "assets/Paddle.h"
#include "assets/PlayerScore.h"
#include "assets/Vec2.h"
#include "Constants.h"

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

void updateAll ( Ball &ball, Paddle &p1Paddle, Paddle &p2Paddle, PlayerScore &p1Score, PlayerScore &p2Score )
{
    ball.position += Vec2(0.3f, 0);
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

    TTF_Font *scoreFont { TTF_OpenFont( "DejaVuSansMono.ttf", 40 ) };

    Net& net { Net::GetInstance() };
    net.SetRenderer( renderer );

    Ball ball( Vec2( Constants::WindowWidth / 2.0f - Constants::BallHeight / 2.0f, Constants::WindowHeight / 2.0f - Constants::BallHeight / 2.0f ), renderer, Constants::BallHeight );
    
    Paddle p1Paddle( Vec2( Constants::PaddleGap, Constants::WindowHeight / 2.0f - Constants::PaddleHeight / 2.0f ), renderer,  Constants::PaddleHeight, Constants::PaddleWidth );
    Paddle p2Paddle( Vec2( Constants::WindowWidth - Constants::PaddleGap, Constants::WindowHeight / 2.0f - Constants::PaddleHeight / 2.0f ), renderer, Constants::PaddleHeight, Constants::PaddleWidth );
    
    PlayerScore p1Score( Vec2( Constants::WindowWidth / 4, 20 ), renderer, scoreFont );
    PlayerScore p2Score( Vec2( 3 * Constants::WindowWidth / 4, 20 ), renderer, scoreFont );
    
    bool running = true;
    while ( running )
    {
        SDL_Event event;
        while ( SDL_PollEvent( &event ) )
        {
            if ( event.type == SDL_QUIT ) running = false;
            if ( event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE ) running = false;
        }   

        updateAll( ball, p1Paddle, p2Paddle, p1Score, p2Score );
        drawAll( renderer, net, ball, p1Paddle, p2Paddle, p1Score, p2Score );
    }

    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    TTF_CloseFont( scoreFont );
    TTF_Quit();
    SDL_Quit();

    return 0;
}