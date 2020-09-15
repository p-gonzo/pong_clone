#include "game-modes/TwoPlayerGame.h"
#include "game-modes/NeuroEvolutionTraining.h"

int main( int argc, char** argv )
{
    GameLoop * game;
    
    if( argc > 1 && strcmp( argv[1], "train" ) == 0 )
    {
        game = new NeuroEvolutionTraining;;
    }
    else
    {
        game = new TwoPlayerGame;
    }

    game->Run();
    delete game;
    
    return 0;
}