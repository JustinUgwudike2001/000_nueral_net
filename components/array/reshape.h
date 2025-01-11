#include "access_operators.h"

template <typename D>
Array<D> Array<D>::reshape(std::vector<int> dims)
{

    Shape shape(dims, dims.size());

    if (this->shape.size() != shape.size())
    {
        std::cout << "Shape size not equal";
        exit(0);
    }

    Array<D> result = *this;
    result.shape = shape;
    result.rank =shape.dims();

    return result;
}

int test_reshape()
{

    Array<float> result;

    Array<float> array1({16});
    array1.random();
    array1.print();
    std::cout << std::endl;

    result = array1.reshape({4, 4});
    result.print();
    std::cout << std::endl;

    result = array1.reshape({2, 2, 4});
    result.print();
    std::cout << std::endl;

    result = array1.reshape({2, 2, 2, 2});
    result.print();
    std::cout << std::endl;

    Array<float> array2({2, 2, 3, 4});
    array2.lin();
    array2.print();
    std::cout << std::endl;

    result = array2.reshape({2, 2, 12});
    result.print();
    std::cout << std::endl;

    result = array2.reshape({2, 24});
    result.print();
    std::cout << std::endl;

    result = array2.reshape({48});
    result.print();
    result.print_grad();

    return 0;
}