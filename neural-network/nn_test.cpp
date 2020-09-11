#include <iostream>
#include <string>
#include <random>
#include <stdio.h>
#include <time.h>
#include <vector>

using Matrix = std::vector<std::vector<double>>;
using Vector = std::vector<double>;

std::default_random_engine generator( time( NULL ) );

Vector generateRandomNormalDistVector(const int size)
{
    Vector vec;
    std::normal_distribution<float>distribution( 0.0, 0.75 );


    for ( int i = 0; i < size; ++i )
    {
        vec.push_back( distribution( generator ) );
    }
    return vec;
}

Matrix generateRandomNormalDistMatrix( const int x, const int y )
{
    Matrix mat;
    for (int i = 0; i < x; ++i )
    {
        mat.push_back ( generateRandomNormalDistVector( y ) );
    }
    return mat;
}

int main()
{
    Vector inputLayer(5, 0.5);
    Matrix denseLayerWeights = generateRandomNormalDistMatrix( 5, 8 );
    Vector denseLayerBiases( 8, 0.0 );
    Matrix outputLayerWeights = generateRandomNormalDistMatrix( 8, 3 );
    Vector outputLayerBiases( 3, 0.0 );

    return 0;
}