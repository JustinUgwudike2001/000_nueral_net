#include "array_object.h"

template<typename D>
Array<D>::Array(){
    strcpy(this->name, "array");
}
template<typename D>
Array<D>::Array(Shape s){
    this->shape = s;
    this->rank = s.dims();
    strcpy(this->name, "array");

    this->data = std::vector<D>(this->shape.size());
    this->dots = std::vector<float>(this->shape.size(), 0.);
}

template<typename D>
Array<D>::Array(std::initializer_list<int> dims){
    std::vector<int> shape(dims);
    Shape s(shape, dims.size());
    this->shape = s;
    this->rank = dims.size();
    strcpy(this->name, "array");

    this->data = std::vector<D>(this->shape.size());
    this->dots = std::vector<float>(this->shape.size(), 0.);
}

// template<typename D>
// Array<D>::Array(int _shape){
//     Shape s({_shape}, 1);
//     this->shape = s;
//     this->rank = 1;
//     strcpy(this->name, "array1");

//     this->data = std::vector<D>(this->shape.size());
//     this->dots = std::vector<float>(this->shape.size(), 0.);
// }
// template<typename D>
// Array<D>::Array(int _shape_0, int _shape_1){
//     Shape s({_shape_0, _shape_1}, 2);
//     this->shape = s;
//     this->rank = 2;
//     strcpy(this->name, "array2");

//     this->data = std::vector<D>(this->shape.size());
//     this->dots = std::vector<float>(this->shape.size(), 0.);
// }
// template<typename D>
// Array<D>::Array(int _shape_0, int _shape_1, int _shape_2){
//     Shape s({_shape_0, _shape_1, _shape_2}, 3);
//     this->shape = s;
//     this->rank = 3;
//     strcpy(this->name, "array3");

//     this->data = std::vector<D>(this->shape.size());
//     this->dots = std::vector<float>(this->shape.size(), 0.);
// }
// template<typename D>
// Array<D>::Array(int _shape_0, int _shape_1, int _shape_2, int _shape_3){
//     Shape s({_shape_0, _shape_1, _shape_2, _shape_3}, 4);
//     this->shape = s;
//     this->rank = 4;
//     strcpy(this->name, "array4");

//     this->data = std::vector<D>(this->shape.size());
//     this->dots = std::vector<float>(this->shape.size(), 0.);
// }

template<typename D>
inline Array<D> Array<D>::create_arr(){
    std::vector<int> shape = this->get_shape().shape();

    switch(this->rank){
        case 1:
            return Array<D>(this->shape.size());
        case 2:
            return Array<D>(shape[0],shape[1]);
        case 3:
            return Array<D>(shape[0], shape[1], shape[2]);
        case 4:
            return Array<D>(shape[0], shape[1], shape[2], shape[3]);
        default:
            return Array<D>(this->shape.size());
    }
}

int test_constructors(){

    Array<float> empty_arr;

    Array<int> array1({100});
    std::cout<<"array1 shape: "
        <<array1.get_shape().shape()[0]<<", "
        <<array1.get_shape().shape()[1]
        <<std::endl;      
        
    Array<float> array2({10, 10});
    std::cout<<"array2 shape: "
        <<array2.get_shape().shape()[0]<<", "
        <<array2.get_shape().shape()[1]
        <<std::endl;

    Array<int> array3({10, 5, 2});
    std::cout<<"array3 shape: "
        <<array3.get_shape().shape()[0]<<", "
        <<array3.get_shape().shape()[1]<<", "
        <<array3.get_shape().shape()[2]
        <<std::endl;

    Array<float> array4({2, 5, 5, 2});
    std::cout<<"array4 shape: "
        <<array4.get_shape().shape()[0]<<", "
        <<array4.get_shape().shape()[1]<<", "
        <<array4.get_shape().shape()[2]<<", "
        <<array4.get_shape().shape()[3]
        <<std::endl;

    return 0;

}