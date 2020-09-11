#include <time.h>

#include "PaddleBrain.h"

PaddleBrain::PaddleBrain()
{
    generator.seed( time( NULL ) );
}

Prediction PaddleBrain::Predict(Vector<float> inputLayer)
{
    Matrix<float> denseLayerWeights = GenerateRandomNormalDist( 5, 8 );
    Vector<float> denseLayerBiases( 8, 0.0f );
    Matrix<float> outputLayerWeights = GenerateRandomNormalDist( 8, 3 );
    Vector<float> outputLayerBiases( 3, 0.0f );

    Vector<float> denseLayer = Sum( DotProduct( inputLayer, denseLayerWeights ), denseLayerBiases );
    ReLUActivation(denseLayer);

    Vector<float> outputLayer = Sum( DotProduct( denseLayer, outputLayerWeights ), outputLayerBiases );
    Softmax( outputLayer );
    
    int highestIndex = 0;
    float highestVal = 0.0f;
    for ( auto i = 0; i < outputLayer.size(); ++i )
    {
        if ( outputLayer[i] > highestVal ) { highestVal = outputLayer[i]; highestIndex = i; }
    }
    return Prediction(highestIndex);
}

Vector<float> PaddleBrain::GenerateRandomNormalDist(const int size)
{
    Vector<float> vec;
    std::normal_distribution<float>distribution( 0.0f, 0.75f );

    for ( int i = 0; i < size; ++i )
    {
        vec.push_back( distribution( generator ) );
    }
    return vec;
}

Matrix<float> PaddleBrain::GenerateRandomNormalDist( const int x, const int y )
{
    Matrix<float> mat;
    for (int i = 0; i < x; ++i )
    {
        mat.push_back ( GenerateRandomNormalDist( y ) );
    }
    return mat;
}

Vector<float> PaddleBrain::DotProduct( const Vector<float> &vec, const Matrix<float> &mat )
{
    Vector<float> result( mat[0].size(), 0 );
    for ( int i = 0; i < mat.size(); ++i )
    {
        for ( int j = 0; j < mat[i].size(); ++j )
        {
            result[j] += mat[i][j] * vec[i];
        }
    }
    return result;
}

Vector<float> PaddleBrain::Sum( const Vector<float> &vec1, const Vector<float> &vec2 )
{
    Vector<float> result(vec1.size());
    for ( auto i = 0; i < vec1.size(); ++i )
    {
        result[i] = vec1[i] + vec2[i];
    }
    return result;
}

void PaddleBrain::ReLUActivation( Vector<float> &vec )
{
    for ( auto i = 0; i < vec.size(); ++i ) { if ( vec[i] < 0 ) { vec[i] = 0; } }
}

void PaddleBrain::Softmax( Vector<float> &vec )
{
    float eularSum;
    for ( auto i = 0; i < vec.size(); ++i )
    {
        eularSum += exp(vec[i]);
    }
    for ( auto i = 0; i < vec.size(); ++i )
    {
        vec[i] = exp(vec[i]) / eularSum;
    }
}