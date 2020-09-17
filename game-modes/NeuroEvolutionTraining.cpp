#include "NeuroEvolutionTraining.h"

#include "../structs/Vec2.h"

NeuroEvolutionTraining::NeuroEvolutionTraining()
    : GameLoop()
    , _randomWall(
        Vec2( Constants::PaddleGap, 0 ),
        Vec2( 0.0f, 0.0f ),
        _renderer,
        Constants::WindowHeight,
        Constants::PaddleWidth
    )
    , _generations( Vec2( Constants::WindowWidth / 4, 20 ), _renderer, _scoreFont, "Gen:" )
    , _hits( Vec2( 3 * Constants::WindowWidth / 4, 20 ), _renderer, _scoreFont, "Hit:" )

{
    _balls.reserve( _numberOfPaddles + 1 );
    _paddles.reserve( _numberOfPaddles + 1 );
    _brains.reserve( _numberOfPaddles + 1 );
    _colors.reserve( _numberOfPaddles + 1 );

    for ( int i = 0; i < _numberOfPaddles; ++i )
    {
        PushPaddlesBallsAndColors();
        _brains.emplace_back( PaddleBrain( _randomSeed ) );
    }
    _generations.Increment();
}

void NeuroEvolutionTraining::HandleGameEvents()
{
    // Logic handled in base class, GameLoop::HandleEvents
    return;
}

void NeuroEvolutionTraining::UpdateAll()
{
    std::vector<int> paddleIndexesToRemove;
    unsigned int allCollisions = 0;
    for ( auto i = 0; i < _paddles.size(); ++i )
    {
        auto x_delta =  Transpose( _paddles[i].position.x - _balls[i].position.x, 0, 1205, -1, 1 );
        auto y1_delta = Transpose( _paddles[i].position.y - ( _balls[i].position.y + Constants::BallHeight ), -720, 605, -1, 1 );
        auto y2_delta = Transpose( ( _paddles[i].position.y + Constants::PaddleHeight ) - _balls[i].position.y, -605, 720, -1, 1 ); 
        
        auto action = _brains[i].Predict( std::vector<float> { x_delta, y1_delta, y2_delta } );

        _paddles[i].Update( action == Prediction::Up, action == Prediction::Down, _dt );
        auto collistionType = _balls[i].Update( _randomWall, _paddles[i], _dt );
        
        allCollisions |= collistionType ;
        if ( collistionType == CollisionType::Right ) { paddleIndexesToRemove.emplace_back( i ); }
    }
    
    _collisionType = CollisionType::None;
    if ( CollisionType::P2Paddle & allCollisions ) { _hits.Increment(); _collisionType = CollisionType::P2Paddle; }
    else if ( CollisionType::P1Paddle & allCollisions ) { _collisionType = CollisionType::P1Paddle; }
    else if ( CollisionType::Wall & allCollisions ) { _collisionType = CollisionType::Wall; }
    
    for ( auto i = 0; i < paddleIndexesToRemove.size(); ++i )
    {
        int idxToRemove = paddleIndexesToRemove[i] - i;
        _paddles.erase( _paddles.begin() + idxToRemove );
        _balls.erase( _balls.begin() + idxToRemove );
        _brains.erase( _brains.begin() + idxToRemove );
        _colors.erase( _colors.begin() + idxToRemove );
        if ( _brains.size() == 1 )
        {
            CloneAndMutatePaddleBrain();
            return;
        }
    }
    if ( _paddles.size() == 0 )
    {
        _generations.Increment();
        _hits.Clear();
        for ( auto i = 0; i < _numberOfPaddles; ++i ) { PushPaddlesBallsAndColors(); }
    }
}

void NeuroEvolutionTraining::DrawAll()
{
    SDL_SetRenderDrawColor( _renderer, 0x0, 0x0, 0x00, 0xFF );
    SDL_RenderClear( _renderer );
    
    _net.Draw( Rgba{ 0xFF, 0XFF, 0XFF, 0XFF } );
    _randomWall.Draw( Rgba{ 0xFF, 0xFF, 0xFF, 0x00 } );
    
    for ( auto i = 0; i < _paddles.size(); ++ i)
    {
        _paddles[i].Draw( _colors[i] );
        _balls[i].Draw( _colors[i] );
    }

    _generations.Draw( Rgba{ 0xFF, 0XFF, 0XFF, 0XFF } );
    _hits.Draw( Rgba{ 0xFF, 0XFF, 0XFF, 0XFF } );

    SDL_RenderPresent( _renderer );
}

float NeuroEvolutionTraining::Transpose( float value, float leftMin, float leftMax, float rightMin, float rightMax ) const
{
    float leftSpan = leftMax - leftMin;
    float rightSpan = rightMax - rightMin;
    float valueScaled = ( value - leftMin ) / leftSpan;
    return rightMin + ( valueScaled * rightSpan );
}

void NeuroEvolutionTraining::CloneAndMutatePaddleBrain()
{
    for ( auto i = 0; i < Constants::TrainingPaddles; ++i )
    {
        _brains.emplace_back( PaddleBrain( _brains[0], _randomSeed, 0.1f, 0.25f ) );
    }
}

void NeuroEvolutionTraining::PushPaddlesBallsAndColors()
{
    _paddles.emplace_back(
        Paddle(
            Vec2( Constants::WindowWidth - Constants::PaddleGap, Constants::WindowHeight / 2.0f - Constants::PaddleHeight / 2.0f ),
            Vec2 (0.0f, 0.0f ),
            _renderer,
            Constants::PaddleHeight,
            Constants::PaddleWidth
        )
    );
    _balls.emplace_back(
        Ball(
            Vec2( Constants::WindowWidth / 2.0f - Constants::BallHeight / 2.0f, Constants::WindowHeight / 2.0f - Constants::BallHeight / 2.0f ),
            Vec2( Constants::BallSpeed, 0.0f ),
            _renderer,
            Constants::BallHeight
        )
    );
    _colors.emplace_back ( Rgba( rand() % 256, rand() % 256, rand() % 256, 0x00 ) );
}

PaddleBrain NeuroEvolutionTraining::GetPaddleBrain()
{
    return _brains[0];
}