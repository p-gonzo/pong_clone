#include <iostream>
#include <chrono>
#include <random>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "constants/Constants.h"
#include "constants/Enums.h"
#include "neural-network/PaddleBrain.h"
#include "sprites/Ball.h"
#include "sprites/Net.h"
#include "sprites/Paddle.h"
#include "sprites/PlayerScore.h"
#include "structs/Rgba.h"
#include "structs/Vec2.h"


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

void drawAll( SDL_Renderer* renderer, Net &net, std::vector<Ball> &balls, Paddle &p1Paddle, std::vector<Paddle> &p2Paddles, PlayerScore &p1Score, PlayerScore &p2Score, std::vector<Rgba> &colors )
{
    SDL_SetRenderDrawColor( renderer, 0x0, 0x0, 0x00, 0xFF );
    SDL_RenderClear( renderer );
    
    net.Draw( Rgba{ 0xFF, 0XFF, 0XFF, 0XFF } );
    p1Paddle.Draw( Rgba{ 0xFF, 0xFF, 0xFF, 0x00 } );
    
    for ( auto i = 0; i < p2Paddles.size(); ++ i)
    {
        p2Paddles[i].Draw( colors[i] );
        balls[i].Draw( colors[i] );
    }

    p1Score.Draw( Rgba{ 0xFF, 0XFF, 0XFF, 0XFF } );
    p2Score.Draw( Rgba{ 0xFF, 0XFF, 0XFF, 0XFF } );

    SDL_RenderPresent( renderer );
}

CollisionType updateAll ( bool &running, std::vector<Ball> &balls, Paddle &p1Paddle, std::vector<Paddle> &p2Paddles, PlayerScore &p1Score, PlayerScore &p2Score, bool buttons[4], float &dt )
{
    CollisionType collisionType { CollisionType::None };

    p1Paddle.Update( buttons[Buttons::p1PaddleUp], buttons[Buttons::p1PaddleDown], dt );
    for ( auto i = 0; i < p2Paddles.size(); ++i )
    {
        p2Paddles[i].Update( buttons[Buttons::p2PaddleUp], buttons[Buttons::p2PaddleDown], dt );
        collisionType = balls[i].Update( p1Paddle, p2Paddles[i], dt );
    }

    if ( collisionType == CollisionType::Right ) { p1Score.Increment(); }
    if ( collisionType == CollisionType::Left ) { p2Score.Increment(); }

    if ( p1Score.value == Constants::WinningScore || p2Score.value == Constants::WinningScore ) { running = false; }

    return collisionType;
}

float transpose( float value, float leftMin, float leftMax, float rightMin, float rightMax )
{
    float leftSpan = leftMax - leftMin;
    float rightSpan = rightMax - rightMin;
    float valueScaled = ( value - leftMin ) / leftSpan;
    return rightMin + ( valueScaled * rightSpan );
}

void generateNextBrainGeneration( std::vector<PaddleBrain> &brains )
{
    std::random_device randomSeed;
    auto targetBrain = brains[0];

    for ( auto i = 0; i < Constants::TrainingPaddles; ++i )
    {
        brains.push_back( PaddleBrain( randomSeed ) );
    }

}

void updateForTraining ( bool &running, std::vector<Ball> &balls, Paddle &p1Paddle, std::vector<Paddle> &p2Paddles, std::vector<PaddleBrain> &brains, std::vector<Rgba> &colors, float &dt, SDL_Renderer* renderer)
{
    std::vector<int> paddleIndexesToRemove;
    for ( auto i = 0; i < p2Paddles.size(); ++i )
    {
        auto own_delta = p2Paddles[i].velocity.y;
        auto own_center = transpose( ( p2Paddles[i].position.y + p2Paddles[i].position.y + Constants::PaddleHeight ) / 2.0f, 50, 670, -1, 1);
        auto x_delta =  transpose( p2Paddles[i].position.x - balls[i].position.x, 0, 1280, -1, 1 );
        auto y1_delta = transpose( p2Paddles[i].position.y - ( balls[i].position.y + Constants::BallHeight ), -1280, 1165, -1, 1 );
        auto y2_delta = transpose( ( p2Paddles[i].position.y + Constants::PaddleHeight ) - balls[i].position.y, -1280, 1165, -1, 1 ); 
        
        auto action = brains[i].Predict( std::vector<float> { own_center, x_delta, y1_delta, y2_delta } );

        p2Paddles[i].Update( action == Prediction::Up, action == Prediction::Down, dt );
        auto collistionType = balls[i].Update( p1Paddle, p2Paddles[i], dt );
        if ( collistionType == CollisionType::Right ) { paddleIndexesToRemove.push_back( i ); }
    }
    for ( auto i = 0; i < paddleIndexesToRemove.size(); ++i )
    {
        int idxToRemove = paddleIndexesToRemove[i] - i;
        p2Paddles.erase( p2Paddles.begin() + idxToRemove );
        balls.erase( balls.begin() + idxToRemove );
        brains.erase( brains.begin() + idxToRemove );
        colors.erase( colors.begin() + idxToRemove );
        if ( brains.size() == 1 )
        {
            generateNextBrainGeneration( brains );
            return;
        }
    }
    if ( p2Paddles.size() == 0 )
    {
        for ( auto i = 0; i < Constants::TrainingPaddles; ++i )
        {
                    p2Paddles.push_back(
            Paddle(
                Vec2( Constants::WindowWidth - Constants::PaddleGap, Constants::WindowHeight / 2.0f - Constants::PaddleHeight / 2.0f ),
                Vec2 (0.0f, 0.0f ),
                renderer,
                Constants::PaddleHeight,
                Constants::PaddleWidth
            )
        );
        balls.push_back(
            Ball(
                Vec2( Constants::WindowWidth / 2.0f - Constants::BallHeight / 2.0f, Constants::WindowHeight / 2.0f - Constants::BallHeight / 2.0f ),
                Vec2( Constants::BallSpeed, 0.0f ),
                renderer,
                Constants::BallHeight
            )
        );
        colors.push_back ( Rgba( rand() % 256, rand() % 256, rand() % 256, 0x00 ) );
        }
        std::cout << "Spawn next gen" << std::endl;
    }
}

void handleCollisionSounds(CollisionType &collisionType, Mix_Chunk* wallHitSound, Mix_Chunk* paddleHitSound)
{
    if ( collisionType == CollisionType::Paddle ) { Mix_PlayChannel( -1, paddleHitSound, 0 ); }
    else if ( collisionType == CollisionType::Wall ) { Mix_PlayChannel( -1, wallHitSound, 0 ); }
}

int main( int argc, char** argv )
{
    bool train { false };
    int numP2Paddles { 1 };
    if( argc > 1 && strcmp( argv[1], "train" ) == 0 )
    {
        train = true;
        numP2Paddles = Constants::TrainingPaddles;
    }
    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
    {
        std::cout <<  "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    if ( TTF_Init() < 0 )
    {
        std::cout <<  "TTF could not initialize! TTF_Error: " << TTF_GetError() << std::endl;
        return -1;
    }

    if ( Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0 )
    {
        std::cout <<  "Mixer could not initialize! TTF_Error: " << TTF_GetError() << std::endl;
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

    Mix_Chunk* wallHitSound = Mix_LoadWAV( "assets/WallHit.wav" );
    if ( wallHitSound == NULL )
    {
        std::cout <<  "Mixer could not load wall hit! TTF_Error: " << TTF_GetError() << std::endl;
        return -1;
    }
    Mix_Chunk* paddleHitSound = Mix_LoadWAV( "assets/PaddleHit.wav" );
    if ( paddleHitSound == NULL )
    {
        std::cout <<  "Mixer could not load paddle hit! TTF_Error: " << TTF_GetError() << std::endl;
        return -1;
    }

    Net& net { Net::GetInstance() };
    net.SetRenderer( renderer );

    Paddle p1Paddle(
        Vec2( Constants::PaddleGap, train ? 0 : Constants::WindowHeight / 2.0f - Constants::PaddleHeight / 2.0f ),
        Vec2( 0.0f, 0.0f ),
        renderer,
        train ? Constants::WindowHeight : Constants::PaddleHeight,
        Constants::PaddleWidth
    );
    std::vector<Ball> balls;
    std::vector<Paddle> p2Paddles;
    std::vector<PaddleBrain> brains;
    std::vector<Rgba> colors { Rgba { 0xFF, 0xFF, 0xFF, 0x00 } };
    std::random_device randomSeed;
    for ( int i = 0; i < numP2Paddles; ++i )
    {
        p2Paddles.push_back(
            Paddle(
                Vec2( Constants::WindowWidth - Constants::PaddleGap, Constants::WindowHeight / 2.0f - Constants::PaddleHeight / 2.0f ),
                Vec2 (0.0f, 0.0f ),
                renderer,
                Constants::PaddleHeight,
                Constants::PaddleWidth
            )
        );
        balls.push_back(
            Ball(
                Vec2( Constants::WindowWidth / 2.0f - Constants::BallHeight / 2.0f, Constants::WindowHeight / 2.0f - Constants::BallHeight / 2.0f ),
                Vec2( Constants::BallSpeed, 0.0f ),
                renderer,
                Constants::BallHeight
            )
        );

        if ( train )
        {
            brains.push_back( PaddleBrain( randomSeed ) );
            colors.push_back ( Rgba( rand() % 256, rand() % 256, rand() % 256, 0x00 ) );
        }
    }
    
    PlayerScore p1Score( Vec2( Constants::WindowWidth / 4, 20 ), renderer, scoreFont );
    PlayerScore p2Score( Vec2( 3 * Constants::WindowWidth / 4, 20 ), renderer, scoreFont );
    
    bool buttons[4] = {};
    bool running = true;
    float dt = 0.0f;
    std::cout << brains.size() << std::endl;
    while ( running )
    {
        auto startTime = std::chrono::high_resolution_clock::now();

        SDL_Event event;
        handleEvents( event, running, buttons );

        CollisionType collisionType;
        if ( train )
        {
            updateForTraining( running, balls, p1Paddle, p2Paddles, brains, colors, dt, renderer );
        }
        else
        {
            collisionType = updateAll( running, balls, p1Paddle, p2Paddles, p1Score, p2Score, buttons, dt );
            handleCollisionSounds( collisionType, wallHitSound, paddleHitSound );
        }
        drawAll( renderer, net, balls, p1Paddle, p2Paddles, p1Score, p2Score, colors );

        auto stopTime = std::chrono::high_resolution_clock::now();
        dt = std::chrono::duration<float, std::chrono::milliseconds::period>(stopTime - startTime).count();
    }

    Mix_FreeChunk( wallHitSound );
    Mix_FreeChunk( paddleHitSound );
    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    TTF_CloseFont( scoreFont );
    Mix_Quit();
    TTF_Quit();
    SDL_Quit();

    return 0;
}