#include "array_object.h"

template <typename D>
Array<D>::Array()
{
    strcpy(this->name, "array");
}
template <typename D>
Array<D>::Array(Shape s)
{
    this->shape = s;
    this->rank = s.dims();
    //this->tape = Tape();
    strcpy(this->name, "array");

    this->data = std::vector<D>(this->shape.size());
    this->nodes = std::vector<std::shared_ptr<Node<D>>>(this->shape.size());
    }

template <typename D>
Array<D>::Array(std::vector<int> dims)
{
    Shape s(dims, dims.size());
    this->shape = s;
    this->rank = dims.size();
    //this->tape = Tape();
    strcpy(this->name, "array");

    this->data = std::vector<D>(this->shape.size());
    this->nodes = std::vector<std::shared_ptr<Node<D>>>(this->shape.size());
}

int test_constructors()
{

    Array<float> empty_arr;

    Array<int> array1({100});
    std::cout << "array1 shape: "
              << array1.get_shape().shape()[0] << ", "
              << array1.get_shape().shape()[1]
              << std::endl;

    Array<float> array2({10, 10});
    std::cout << "array2 shape: "
              << array2.get_shape().shape()[0] << ", "
              << array2.get_shape().shape()[1]
              << std::endl;

    Array<int> array3({10, 5, 2});
    std::cout << "array3 shape: "
              << array3.get_shape().shape()[0] << ", "
              << array3.get_shape().shape()[1] << ", "
              << array3.get_shape().shape()[2]
              << std::endl;

    Array<float> array4({2, 5, 5, 2});
    std::cout << "array4 shape: "
              << array4.get_shape().shape()[0] << ", "
              << array4.get_shape().shape()[1] << ", "
              << array4.get_shape().shape()[2] << ", "
              << array4.get_shape().shape()[3]
              << std::endl;

    return 0;
}