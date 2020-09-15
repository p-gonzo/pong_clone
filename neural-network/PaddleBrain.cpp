#include <time.h>
#include <iostream>
#include "PaddleBrain.h"

PaddleBrain::PaddleBrain( std::random_device &rd )
{
    _generator.seed(rd());
    
    _denseLayerWeights = GenerateRandomNormalDist( 3, 8 );
    _denseLayerBiases = Vector<float>( 8, 0.0f );
    _outputLayerWeights = GenerateRandomNormalDist( 8, 3 );
    _outputLayerBiases = Vector<float>( 3, 0.0f );
}

PaddleBrain::PaddleBrain( const PaddleBrain &parent, std::random_device &rd )
{
    _generator.seed(rd());

    _denseLayerWeights = GenerateMutatedMatrix( parent._denseLayerWeights );
    _denseLayerBiases = GenerateMutatedVector( parent._denseLayerBiases );
    _outputLayerWeights = GenerateMutatedMatrix (parent._outputLayerWeights );
    _outputLayerBiases = GenerateMutatedVector (parent._outputLayerBiases );
}

Prediction PaddleBrain::Predict(Vector<float> inputLayer)
{

    Vector<float> denseLayer = Sum( DotProduct( inputLayer, _denseLayerWeights ), _denseLayerBiases );
    ReLUActivation(denseLayer);

    Vector<float> outputLayer = Sum( DotProduct( denseLayer, _outputLayerWeights ), _outputLayerBiases );
    Softmax( outputLayer );

    if ( outputLayer[0] > 0.33 ) { return Prediction::Up; }
    else if ( outputLayer[2] > 0.33 ) { return Prediction::Down; }
    else return Prediction::Stay;
}

Vector<float> PaddleBrain::GenerateRandomNormalDist(const int size)
{
    Vector<float> vec;
    std::normal_distribution<float> distribution( 0.0f, 0.75f );

    for ( int i = 0; i < size; ++i )
    {
        vec.push_back( distribution( _generator ) );
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

Matrix<float> PaddleBrain::GenerateMutatedMatrix( const Matrix<float> &weights )
{   
    Matrix<float> newWeights;
    for ( auto i = 0; i < weights.size(); ++i )
    {
        newWeights.emplace_back( GenerateMutatedVector( weights[i] ) );
    }
    return newWeights;
}

Vector<float> PaddleBrain::GenerateMutatedVector( const Vector<float> &biases )
{
    Vector<float> newBiases;
    std::normal_distribution<float> distribution( 0.0f, 0.25f );
    int rollTen = rand() % 11;
    std::cout << rollTen << std::endl;
    for ( auto i = 0; i < biases.size(); ++i )
    {
        if ( rollTen > 8 )
        {
            newBiases.emplace_back( biases[i] + distribution( _generator ) );
        }
        else
        {
            newBiases.emplace_back( biases[i] );
        }
    }
    return newBiases;
}