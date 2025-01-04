#include "array_functions.h"

template <typename D>
Array<D> Array<D>::reshape(std::vector<int> dims)
{

    Shape shape(dims, dims.size());

    if (this->shape.size() != shape.size())
    {
        std::cout << "Shape size not equal";
        exit(0);
    }

    this->shape = shape;
    this->rank = shape.dims();
    strcpy(this->name, "array");

    return *this;
}

int test_reshape()
{

    Array<float> array1({16});
    array1.random();
    array1.print();
    std::cout << std::endl;

    array1.reshape({4, 4});
    array1.print();
    std::cout << std::endl;

    array1.reshape({2, 2, 4});
    array1.print();
    std::cout << std::endl;

    array1.reshape({2, 2, 2, 2});
    array1.print();
    std::cout << std::endl;

    Array<float> array2({2, 2, 3, 4});
    array2.lin();
    array2.print();
    std::cout << std::endl;

    array2.reshape({2, 2, 12});
    array2.print();
    std::cout << std::endl;

    array2.reshape({2, 24});
    array2.print();
    std::cout << std::endl;

    array2.reshape({48});
    array2.print();

    return 0;
}