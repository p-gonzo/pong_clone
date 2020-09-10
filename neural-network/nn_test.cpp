#include <iostream>

template <typename T>
void displayArray(const int y, T *ptr)
{
    for ( int j = 0; j < y; ++j )
    {
        std::cout << ptr[j] << " ";
    }
    std::cout << std::endl;
}

template <typename T>
void displayTensor(const int x, const int y, T *ptr)
{
    for ( int i = 0; i < x; ++i ) 
    {
        displayArray(y, ptr[i]);
    }
}

int main()
{
    float inputLayer[5] { 0.5, 0.5, 0.5, 0.5, 0.5 };
    
    int x[3][4] {
        { 0, 1, 2, 3 },
        { 4, 5, 6, 7 },
        { 8, 9, 10, 11 }
    };

    displayTensor(3, 4, x);
    std::cout << std::endl;
    displayArray(5, inputLayer);

}