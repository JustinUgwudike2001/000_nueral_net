#include <iostream> 

void displayArray(int array[], int size)
{
    std::cout << "[";

    for(int i = 0; i < size; i++){
        std::cout << array[i]; 

        if (i == size - 1)
            continue;

        std::cout << ", ";
    }

    std::cout << "]";

    return;
}

int main()
{

    std::cout << "Hello World!"<< "\n";
    std::cout << "GET OUT!!!" << "\n";

    int input_data[4] = {0, 1, 3, 4};

    displayArray(input_data, 4);

    std::cout << "\ninputs: " << input_data[0];



    return 0;
}