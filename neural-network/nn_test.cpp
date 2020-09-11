#include <iostream>
#include <vector>

#include "PaddleBrain.h"


int main()
{
    PaddleBrain brain;
    std::cout << brain.Predict( std::vector<float>{0.5f, 0.5f, 0.5f, 0.4f, 0.1f } ) << std::endl;
    return 0;
}