#include "TwoPlayerGame.h"

#include <iostream>

#include "../constants/Constants.h"
#include "../structs/Vec2.h"

TwoPlayerGame::TwoPlayerGame()
    : GameLoop()
    , _ball(
        Vec2( Constants::WindowWidth / 2.0f - Constants::BallHeight / 2.0f, Constants::WindowHeight / 2.0f - Constants::BallHeight / 2.0f ),
        Vec2( Constants::BallSpeed, 0.0f ),
        _renderer,
        Constants::BallHeight
    )
    , _p1Paddle(
        Vec2( Constants::PaddleGap, Constants::WindowHeight / 2.0f - Constants::PaddleHeight / 2.0f ),
        Vec2( 0.0f, 0.0f ),
        _renderer,
        Constants::PaddleHeight,
        Constants::PaddleWidth
    )
    , _p2Paddle(
        Vec2( Constants::WindowWidth - Constants::PaddleGap, Constants::WindowHeight / 2.0f - Constants::PaddleHeight / 2.0f ),
        Vec2 (0.0f, 0.0f ),
        _renderer,
        Constants::PaddleHeight,
        Constants::PaddleWidth
    )
    , _p1Score( Vec2( Constants::WindowWidth / 4, 20 ), _renderer, _scoreFont )
    , _p2Score( Vec2( 3 * Constants::WindowWidth / 4, 20 ), _renderer, _scoreFont )
{

}

void TwoPlayerGame::HandleEvents()
{
    while ( SDL_PollEvent( &_event ) )
    {
        std::cout << _event.key.keysym.sym << std::endl;
        if ( _event.type == SDL_QUIT ) _running = false;
        else if ( _event.type == SDL_KEYDOWN )
        {
            if ( _event.key.keysym.sym == SDLK_ESCAPE ) _running = false;
            else if ( _event.key.keysym.sym == SDLK_w ) { _playerButtonStates[Buttons::p1PaddleUp] = true; }
            else if ( _event.key.keysym.sym == SDLK_s ) { _playerButtonStates[Buttons::p1PaddleDown] = true; }
            else if ( _event.key.keysym.sym == SDLK_UP ) { _playerButtonStates[Buttons::p2PaddleUp] = true; }
            else if ( _event.key.keysym.sym == SDLK_DOWN ) { _playerButtonStates[Buttons::p2PaddleDown] = true; }
        }
        else if ( _event.type == SDL_KEYUP )
        {
            if ( _event.key.keysym.sym == SDLK_w ) { _playerButtonStates[Buttons::p1PaddleUp] = false; }
            else if ( _event.key.keysym.sym == SDLK_s ) { _playerButtonStates[Buttons::p1PaddleDown] = false; }
            else if ( _event.key.keysym.sym == SDLK_UP ) { _playerButtonStates[Buttons::p2PaddleUp] = false; }
            else if ( _event.key.keysym.sym == SDLK_DOWN ) { _playerButtonStates[Buttons::p2PaddleDown] = false; }
        }
    }
}

void TwoPlayerGame::UpdateAll()
{
    _collisionType = CollisionType::None;
    _p1Paddle.Update( _playerButtonStates[Buttons::p1PaddleUp], _playerButtonStates[Buttons::p1PaddleDown], _dt );
    _p2Paddle.Update( _playerButtonStates[Buttons::p2PaddleUp], _playerButtonStates[Buttons::p2PaddleDown], _dt );
    _collisionType = _ball.Update( _p1Paddle, _p2Paddle, _dt );
    if ( _collisionType == CollisionType::Right ) { _p1Score.Increment(); }
    if ( _collisionType == CollisionType::Left ) { _p2Score.Increment(); }
    if ( _p1Score.value == Constants::WinningScore || _p2Score.value == Constants::WinningScore ) { _running = false; }
}


void TwoPlayerGame::DrawAll()
{
    SDL_SetRenderDrawColor( _renderer, 0x0, 0x0, 0x00, 0xFF );
    SDL_RenderClear( _renderer );
    
    _net.Draw( Rgba{ 0xFF, 0XFF, 0XFF, 0XFF } );
    _p1Paddle.Draw( Rgba{ 0xFF, 0xFF, 0xFF, 0x00 } );
    _p2Paddle.Draw( Rgba{ 0xFF, 0xFF, 0xFF, 0x00 } );
    _ball.Draw( Rgba{ 0xFF, 0xFF, 0xFF, 0x00 } );
    _p1Score.Draw( Rgba{ 0xFF, 0XFF, 0XFF, 0XFF } );
    _p2Score.Draw( Rgba{ 0xFF, 0XFF, 0XFF, 0XFF } );

    SDL_RenderPresent( _renderer );
}
