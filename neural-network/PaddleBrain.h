#pragma once

#include <random>
#include <vector>

#include "Enums.h"

template<typename T> using Matrix = std::vector<std::vector<T>>;
template<typename T> using Vector = std::vector<T>;

class PaddleBrain
{
public:

    PaddleBrain( const int i );
    Prediction Predict(Vector<float> inputLayer);
    std::default_random_engine generator;

private:
    Vector<float> GenerateRandomNormalDist(const int size);
    Matrix<float> GenerateRandomNormalDist( const int x, const int y );
    Vector<float> DotProduct( const Vector<float> &vec, const Matrix<float> &mat );
    Vector<float> Sum( const Vector<float> &vec1, const Vector<float> &vec2 );
    void ReLUActivation( Vector<float> &vec );
    void Softmax( Vector<float> &vec );


};