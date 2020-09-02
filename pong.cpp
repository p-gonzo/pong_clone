#include <SDL2/SDL.h>
#include <iostream>

#include "assets/Ball.h";
#include "assets/Net.h";
#include "assets/Vec2.h";

const int WINDOW_WIDTH { 1280 };
const int WINDOW_HEIGHT { 720 };

int main( int argc, char* args[] )
{
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        std::cout <<  "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow( "Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN );
    if( window == NULL )
    {
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    Ball ball( Vec2( WINDOW_WIDTH / 2.0f - ball.radius, WINDOW_HEIGHT / 2.0f - ball.radius ) );

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
        Net::Draw( renderer, WINDOW_HEIGHT, WINDOW_WIDTH );
        // ball.position += Vec2(1, 0);
        ball.Draw( renderer );

        SDL_RenderPresent( renderer ); // present the "backbuffer"
    }

    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    SDL_Quit();

    return 0;
}